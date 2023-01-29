#!/bin/bash
g++ src/PCHL.cpp -std=c++11 -fpermissive -fopenmp -O3 -o src/PCHL.out
g++ src/RCHL.cpp -std=c++11 -fpermissive -fopenmp -O3 -o src/RCHL.out
g++ src/verify.cpp -O3 -std=c++11 -o src/verify.out
chmod +x SR2C

#readLen=100
#testName="/public/home/jd_sunhui/genCompressor/PSR2C/data/SRR921889.fastq"
#saveDir="SRR921889"
#threadNum=10
#QualityScoreFlag=0
#HeaderFlag=0

#cd src
#mkdir ${saveDir}
#/bin/time -v -p ./CHL.out ${readLen} ${testName} ${saveDir} ${threadNum} ${QualityScoreFlag} ${HeaderFlag}

#recoverPath="/public/home/jd_sunhui/genCompressor/PSR2C/src/SRR921889"
#SavePath="/public/home/jd_sunhui/genCompressor/PSR2C/data/SRR921889/Recover.txt"
#/bin/time -v -p ./RCHL.out ${recoverPath} ${SavePath} ${threadNum}

#./verify.out ${testName} ${SavePath}