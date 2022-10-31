#!/bin/sh

DIR="../pythia8244/dynamical_fragmentation/data/20221026_initial_PBPB2.76TeV_MB_pT0Ref0.9_test"
#DIR="/home/yuuka/some_jets/npdf_proton_0"
EV="ev"
EXT="initial.txt"
#EXT="jets_SAT_MC.txt"
outputdir="test"
n=1


#Do not modify this.
#---------------------
log_dname="log/"
data_dir="data/"

today=$(date "+%Y%m%d")
log_fname=${today}${outputdir}
if [ ! -d $log_dname ]
then
    echo "Directory "$log_dname" DOES NOT exists." 
    echo "mkdir "$log_dname
    mkdir $log_dname
fi
if [ ! -d $data_dir ]
then
    echo "Directory "$data_dir" DOES NOT exists." 
    mkdir $data_dir
fi
#-------------------------


#Options.
#--------------
# --CentralityCut 9 \
# --CentralityCut_ext hadronFinal_corecorona_weakStop.txt \
# --HI \
# --only_corona \
# --INEL_lg_0 \
# --twosub  \
# --threesub  \
# --4particle \
# --tagged \
# --2PCfull \
# --2PCnearside \
# --2PCout \
# --setNcoeff 3 \
# --only_corona_associates \
# --vs_Multi 2 \

./EMP \
 -n $n -outdir ${outputdir} -dir ${DIR} -f ${EV} -ext ${EXT} 
 #> ${log_dname}${log_fname}.log  2>&1  &
