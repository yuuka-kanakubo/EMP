/*
 *
 *    Copyright (c) 2014-2018
 *      SMASH Team
 *
 *    GNU General Public License (GPLv3 or later)
 *
 */

#include "threevector.h"

#include "iomanipulators.h"


std::ostream &operator<<(std::ostream &out, const ThreeVector &v) {
  out.put('(');
  out.fill(' ');
  for (auto x : v) {
    out << field<8> << x;
  }
  return out << ')';
}

