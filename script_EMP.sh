#!/bin/sh

DIR="/n/work02/yukanaku/mcaa-master/data/16Jan2024_test/60_70"
EV="ev"
EXT="EKRTminijet.txt"
outputdir="TestAfterPropagation"
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


./EMP \
 -n $n -outdir ${outputdir} -dir ${DIR} -f ${EV} -ext ${EXT}  \
 --fs \
##> ${log_dname}${log_fname}.log  2>&1  &
