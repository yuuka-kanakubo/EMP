/*
 *
 *    Copyright (c) 2015-2021
 *      SMASH Team
 *
 *    GNU General Public License (GPLv3 or later)
 *
 */

#include "smash/energymomentumtensor.h"

#include <iomanip>
#include <iostream>

#include <Eigen/Dense>  // NOLINT(build/include_order)

#include "smash/logging.h"
#include "smash/numerics.h"

namespace smash {
static constexpr int LTmn = LogArea::Tmn::id;

FourVector EnergyMomentumTensor::landau_frame_4velocity() const {
  using Eigen::Matrix4d;
  using Eigen::Vector4d;
  /* We want to solve the generalized eigenvalue problem
     T^{\mu \nu} h_{nu} = \lambda g^{\mu \nu} h_{nu}, or in the other way
     T_{\mu}^{\nu} h_{nu} = \lambda h_{mu}. The eigenvector
     corresponding to the largest (and the only positive) eigenvalue is
     proportional to 4-velocity of the Landau frame.
     Denote T^{\mu}_{\nu} as A and g^{\mu \nu} as B.
     A is symmetric and positive semi-definite. B is symmetric.
     A x = \lambda B x. I have to solve generalized eigenvalue
     problem, because A can be not positively definite (e.g. if
     energy-momentum tensor is computed for particles with momenta lying
     in one plane). For positively definite A a more efficient solution
     is possible, but I (oliiny) do not consider it, until it becomes
     important for SMASH performance.
     */
  Matrix4d A;
  // A = T_{\mu}^{\nu} = g_{\mu \mu'} T^{\mu' \nu}
  // clang-format off
  A <<  Tmn_[0],  Tmn_[1],  Tmn_[2],  Tmn_[3],
       -Tmn_[1], -Tmn_[4], -Tmn_[5], -Tmn_[6],
       -Tmn_[2], -Tmn_[5], -Tmn_[7], -Tmn_[8],
       -Tmn_[3], -Tmn_[6], -Tmn_[8], -Tmn_[9];
  // clang-format on

  logg[LTmn].debug("Looking for Landau frame for T_{mu}^{nu} ", A);
  Eigen::EigenSolver<Matrix4d> es(A);

  Vector4d eig_im = es.eigenvalues().imag();
  Vector4d eig_re = es.eigenvalues().real();
  size_t i_maxeigenvalue = 0;
  for (size_t i = 0; i < 4; i++) {
std::cout << "ME:) " << eig_re(i) << std::endl;
    if (eig_re(i_maxeigenvalue) < eig_re(i)) {
      i_maxeigenvalue = i;
    }
  }

  // Sanity checks
  // Eigen values of A should be strictly real, the largest one corresponding
  // to energy density should be non-negative, the other ones
  // corresponding to pressure should be non-positive, because of the
  // metric tensor gmunu = (1, -1, -1, -1) convention.
  if (i_maxeigenvalue != 0) {
    logg[LTmn].warn(
        "The Tmn diagonalization code previously relied on assumption that"
        " 0th eigenvalue is the largest one. It seems to be always fulfilled "
        "in practice, but not guaranteed by Eigen. Here is Tmn * gmn, ",
        A, " for which it is not fulfilled. Please let Dima(oliiny) know.");
  }
  for (size_t i = 0; i < 4; i++) {
    if (std::abs(eig_im(i)) > really_small) {
      logg[LTmn].error("Tmn*gmn\n ", A, "\n has a complex eigenvalue ",
                       eig_re(i), " + i * ", eig_im(i));
    }
    if (i == i_maxeigenvalue && eig_re(i) < -really_small) {
      logg[LTmn].error("Tmn*gmn\n", A,
                       "\nenergy density eigenvalue is not positive ",
                       eig_re(i), " + i * ", eig_im(i));
      logg[LTmn].error("i_max = ", i_maxeigenvalue);
    }
    if (i != i_maxeigenvalue && eig_re(i) > really_small) {
      logg[LTmn].error("Tmn*gmn\n", A, "\npressure eigenvalue is not negative ",
                       eig_re(i), " + i * ", eig_im(i));
    }
  }

  Vector4d tmp = es.eigenvectors().col(i_maxeigenvalue).real();
std::cout << "ME:) es.eigenvectors() " << es.eigenvectors()  << std::endl;
std::cout << "ME:) i_maxeigenvalue " << i_maxeigenvalue << std::endl;
std::cout << "ME:) es.eigenvectors().col() " << es.eigenvectors().col(i_maxeigenvalue)  << std::endl;
std::cout << "ME:) tmp " << tmp << std::endl;
  // Choose sign so that zeroth component is positive because we want
  // 4-velocity to have 0-component positive
  if (tmp(0) < 0.0) {
    tmp = -tmp;
  }

  FourVector u(tmp(0), tmp(1), tmp(2), tmp(3));
std::cout << "ME:) u (after sign treatment) " << u << std::endl;
  const double u_sqr = u.sqr();
  if (u_sqr > really_small) {
    u /= std::sqrt(u_sqr);
  } else {
    logg[LTmn].error(
        "Landau frame is not defined.", " Eigen vector", u, " of ", A,
        " is not time-like and",
        " cannot be 4-velocity. This may happen if energy-momentum",
        " tensor was constructed for a massless particle.");
    u = FourVector(1., 0., 0., 0.);
  }
std::cout << "ME:) u (after normalization) " << u << std::endl;
  return u;
}

EnergyMomentumTensor EnergyMomentumTensor::boosted(const FourVector &u) const {
  using Eigen::Matrix4d;
  Matrix4d A, L, R;
  // Energy-momentum tensor
  // clang-format off
  A << Tmn_[0], Tmn_[1], Tmn_[2], Tmn_[3],
       Tmn_[1], Tmn_[4], Tmn_[5], Tmn_[6],
       Tmn_[2], Tmn_[5], Tmn_[7], Tmn_[8],
       Tmn_[3], Tmn_[6], Tmn_[8], Tmn_[9];
  // clang-format on
  // Compute Lorentz matrix of boost
  const ThreeVector tmp = u.threevec() / (1.0 + u[0]);
  // clang-format off
  L << u[0], u[1], u[2], u[3],
       u[1], u[1] * tmp.x1() + 1.0, u[2] * tmp.x1(), u[3] * tmp.x1(),
       u[2], u[1] * tmp.x2(), u[2] * tmp.x2() + 1.0, u[3] * tmp.x2(),
       u[3], u[1] * tmp.x3(), u[2] * tmp.x3(), u[3] * tmp.x3() + 1.0;
  // clang-format on
  // Boost
  R = L * A * L;
  // clang-format off
  return EnergyMomentumTensor({R(0, 0), R(0, 1), R(0, 2), R(0, 3),
                                        R(1, 1), R(1, 2), R(1, 3),
                                                 R(2, 2), R(2, 3),
                                                          R(3, 3)});
  // clang-format on
}

void EnergyMomentumTensor::add_particle(const FourVector &mom) {
  const ThreeVector tmp = mom.threevec() / mom[0];
  Tmn_[0] += mom[0];
  Tmn_[1] += mom[1];
  Tmn_[2] += mom[2];
  Tmn_[3] += mom[3];
  Tmn_[4] += mom[1] * tmp.x1();
  Tmn_[5] += mom[1] * tmp.x2();
  Tmn_[6] += mom[1] * tmp.x3();
  Tmn_[7] += mom[2] * tmp.x2();
  Tmn_[8] += mom[2] * tmp.x3();
  Tmn_[9] += mom[3] * tmp.x3();
}

void EnergyMomentumTensor::add_particle(const ParticleData &p, double factor) {
  if (factor != 0) {
    add_particle(p.momentum() * factor);
  }
}

std::ostream &operator<<(std::ostream &out, const EnergyMomentumTensor &Tmn) {
  out.width(12);
  for (size_t mu = 0; mu < 4; mu++) {
    for (size_t nu = 0; nu < 4; nu++) {
      out << std::setprecision(3) << std::setw(12) << std::fixed
          << Tmn[EnergyMomentumTensor::tmn_index(mu, nu)];
    }
    out << std::endl;
  }
  return out;
}

}  // namespace smash
