#!/bin/bash
module load compiler/gnu/gcc-compiler-8.4.0
# a script file to test universal_compressors.
g++ --version
gcc --version
TestFileDir="/public/home/jd_sunhui/genCompressor/SR2C/src/"
SR2CPath="/public/home/jd_sunhui/genCompressor/SR2C/src/"
CPUThread=8

Func_7Z() {
  echo "test 7z algorithm************************************************************************"
  for dirName in File-NAME; do
    echo "************dirName:${dirName}****************"
    sourceFileName=${TestFileDir}${dirName}/recover.txt
    dealFileName=${TestFileDir}${dirName}/reads.txt
    echo "sourceFileName:${sourceFileName}"
    echo "dealFileName:${dealFileName}"
    cd ${TestFileDir}${dirName}
    mkdir "7z"
    tar -cf 7zinfo.tar count.txt id_1.txt id_pos.txt info.txt reads.txt
    /bin/time -v -p 7z a -bso0 -bse0 -bsp0 -mmt${CPUThread} -mx9 -y 7z/7zinfo.tar.7z 7zinfo.tar
    #/bin/time -v -p 7z a -bso0 -bse0 -bsp0 -mmt${CPUThread} -mx9 -y 7z/reads.7z reads.txt
    /bin/time -v -p 7z a -bso0 -bse0 -bsp0 -mmt${CPUThread} -mx9 -y 7z/recover.7z recover.txt
    #ls -l --block-size=KB 7z/reads.7z
    ls -l --block-size=KB 7z/7zinfo.tar.7z
    ls -l --block-size=KB 7z/recover.7z
    rm 7zinfo.tar
    cd 7z
    #/bin/time -v -p 7z x -bso0 -bse0 -bsp0 -mmt${CPUThread} -mx9 -y reads.7z
    /bin/time -v -p 7z x -bso0 -bse0 -bsp0 -mmt${CPUThread} -mx9 -y 7zinfo.tar.7z
    /bin/time -v -p 7z x -bso0 -bse0 -bsp0 -mmt${CPUThread} -mx9 -y recover.7z
    echo
    echo
  done
}
Func_7Z

Func_XZ() {
  echo "test XZ algorithm************************************************************************"
  for dirName in File-NAME; do
    echo "************dirName:${dirName}****************"
    sourceFileName=${TestFileDir}${dirName}/recover.txt
    dealFileName=${TestFileDir}${dirName}/reads.txt
    echo "sourceFileName:${sourceFileName}"
    echo "dealFileName:${dealFileName}"
    cd ${TestFileDir}${dirName}
    mkdir "xz"
    tar -cf xzinfo.tar count.txt id_1.txt id_pos.txt info.txt reads.txt
    /bin/time -v -p xz -T ${CPUThread} -9 -c xzinfo.tar > xz/xzinfo.tar.xz
    /bin/time -v -p xz -T ${CPUThread} -9 -c recover.txt > xz/recover.xz
    ls -l --block-size=KB xz/xzinfo.tar.xz
    ls -l --block-size=KB xz/recover.xz
    rm xzinfo.tar
    cd xz
    /bin/time -v -p xz -T ${CPUThread} -9 -d xzinfo.tar.xz
    /bin/time -v -p xz -T ${CPUThread} -9 -d recover.xz
    echo
    echo
  done
}
echo
Func_XZ

Func_BZIP2() {
  echo "test BZIP2 algorithm************************************************************************"
  for dirName in File-NAME; do
    echo "************dirName:${dirName}****************"
    sourceFileName=${TestFileDir}${dirName}/recover.txt
    dealFileName=${TestFileDir}${dirName}/reads.txt
    echo "sourceFileName:${sourceFileName}"
    echo "dealFileName:${dealFileName}"
    cd ${TestFileDir}${dirName}
    rm -rf bzip2
    mkdir "bzip2"
    tar -cf bzip2info.tar count.txt id_1.txt id_pos.txt info.txt reads.txt
    /bin/time -v -p pbzip2 -k -9 -p${CPUThread} -c bzip2info.tar > bzip2/bzip2info.tar.bz2
    /bin/time -v -p pbzip2 -k -9 -p${CPUThread} -c recover.txt > bzip2/recover.bz2
    ls -l --block-size=KB bzip2/bzip2info.tar.bz2
    ls -l --block-size=KB bzip2/recover.bz2
    rm bzip2info.tar
    cd bzip2
    /bin/time -v -p pbzip2 -k -9 -p${CPUThread} -d bzip2info.tar.bz2
    /bin/time -v -p pbzip2 -k -9 -p${CPUThread} -d recover.bz2
    echo
    echo
  done
}
echo
Func_BZIP2

Func_PIGZ() {
  echo "test PIGZ algorithm************************************************************************"
  for dirName in File-NAME; do
    echo "************dirName:${dirName}****************"
    sourceFileName=${TestFileDir}${dirName}/recover.txt
    dealFileName=${TestFileDir}${dirName}/reads.txt
    echo "sourceFileName:${sourceFileName}"
    echo "dealFileName:${dealFileName}"
    cd ${TestFileDir}${dirName}
    rm -rf pigz
    mkdir "pigz"
    tar -cf pigzinfo.tar count.txt id_1.txt id_pos.txt info.txt reads.txt
    /bin/time -v -p pigz -p ${CPUThread} --best -c pigzinfo.tar > pigz/pigzinfo.tar.gz
    /bin/time -v -p pigz -p ${CPUThread} --best -c recover.txt > pigz/recover.gz
    ls -l --block-size=KB pigz/pigzinfo.tar.gz
    ls -l --block-size=KB pigz/recover.gz
    rm pigzinfo.tar
    cd pigz
    /bin/time -v -p unpigz -p ${CPUThread} -d pigzinfo.tar.gz
    /bin/time -v -p unpigz -p ${CPUThread} -d recover.gz
    echo
    echo
  done
}
echo
Func_PIGZ