#!/bin/bash
#module load compiler/gnu/gcc-compiler-8.4.0
#g++ --version
#gcc --version
#bash ./../install.sh
TestFileDir="/public/home/jd_sunhui/genCompressor/SR2C/data/"
SR2CPath="/public/home/jd_sunhui/genCompressor/SR2C/src/"

MainPath=$(pwd)
SaveFilePath="/public/home/jd_sunhui/genCompressor/SR2C/src/"
Pr=1





for FNIndex in File-NAME; do
  echo "***************************************************************************"
  FileName="${TestFileDir}${FNIndex}.fastq"
  SavePath="${SaveFilePath}${FNIndex}_PR1"
  ReadLen=$(head -40 ${FileName} | wc -L)
  echo "FileName: ${FileName}"
  echo "SavePath: ${SavePath}"
  echo "ReadLen: ${ReadLen}"
  mkdir ${SavePath}
  if [ $? -ne 0 ]; then
    echo "mkdir wrong!"
    exit 0
  fi
  cd ${SR2CPath}


  echo "test chl"
  /bin/time -v -p ./PCHL.out ${ReadLen} ${FileName} ${SavePath} ${Pr} 0 0
  if [ $? -ne 0 ]; then
    echo "PCHL.out wrong!"
    exit 0
  fi


  echo "test rchl"
  /bin/time -v -p ./RCHL.out ${SavePath} ${SavePath}/recover.txt ${Pr}
  if [ $? -ne 0 ]; then
    echo "RCHL.out wrong!"
    exit 0
  fi


  echo "verify"
  ./verify.out ${FileName} ${SavePath}/recover.txt
  if [ $? -ne 0 ]; then
    echo "verify.out wrong!"
    exit 0
  fi
  echo
  echo
  echo
done

