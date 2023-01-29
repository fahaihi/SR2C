#!/bin/bash
module load compiler/gnu/gcc-compiler-8.4.0
g++ --version
gcc --version
#bash ./../install.sh
Name="File-NAME"
TestFileName="/public/home/jd_sunhui/genCompressor/SR2C/data/${Name}.fastq"
MinirmdPath="/public/home/jd_sunhui/genCompressor/SR2C/script/minirmd"
Sr2cPathPath="/public/home/jd_sunhui/genCompressor/SR2C/src/"
MainPath=$(pwd)
CPUCore=1

ReadLen=$(head -40 ${TestFileName} | wc -L)


# test minirmd + sr2c
for ((i = 0; i < 4; i++)); do
  echo
  echo
  echo
  echo "****************************************************************************"
  cd ${MinirmdPath}
  #make
  #chmod +x minirmd
  echo "/bin/time -v -p ./minirmd -i ${TestFileName} -o ${Name}_rm_${i}.fastq -d ${i} -t 1"
  /bin/time -v -p ./minirmd -i ${TestFileName} -o ${Name}_rm_${i}.fastq -d ${i} -t ${CPUCore}
  if [ $? -ne 0 ]; then
    echo "Minirmd wrong!"
    exit 0
  fi
  cd ${Sr2cPathPath}
  mkdir ${Name}_rm_${i}
  echo "/bin/time -v -p ./PCHL.out ${ReadLen} ${MinirmdPath}/${Name}_rm_${i}.fastq ${Name}_rm_${i} ${CPUCore} 0 0"
  /bin/time -v -p ./PCHL.out ${ReadLen} ${MinirmdPath}/${Name}_rm_${i}.fastq ${Name}_rm_${i} ${CPUCore} 0 0
  if [ $? -ne 0 ]; then
    echo "SR2C wrong!"
    exit 0
  fi
  wc -l "${Name}_rm_${i}/reads.txt"

done

# test sr2c
# echo "****************************************************************************"
# for i in 20; do
# cd ${Sr2cPathPath}
# mkdir ${Name}_Pure_Core${i}_SR2C
# echo " /bin/time -v -p ./PCHL.out ${ReadLen} ${TestFileName} ${Name}_Pure_Core${i}_SR2C ${i} 0 0"
# /bin/time -v -p ./PCHL.out ${ReadLen} ${TestFileName} ${Name}_Pure_SR2C ${i} 0 0

#if [ $? -ne 0 ]; then
#    echo "SR2C wrong!"
#    exit 0
#fi

#wc -l "${Name}_Pure_Core${i}_SR2C/reads.txt"
#done