![made-with-C++](https://img.shields.io/badge/Made%20with-C++11-brightgreen)
![made-with-OpenMP](https://img.shields.io/badge/Made%20with-OpenMP-blue)


<!-- LOGO -->
<br />
<h1>
<p align="center">
  <img src="https://github.com/fahaihi/SR2C/blob/master/SR2C_LOGO.png" alt="Logo" width="653" height="163">
  <br>Structurally Redundant Short Reads Collapser
</h1>
  <p align="center">
    A DNA sequencing data structure redundant short reads deduplicator via cyclic hash linkege
    <br />
    </p>
</p>
<p align="center">
  <a href="#about-the-sr2c">About The SR2C</a> •
  <a href="#useage">Useage</a> •
  <a href="#dataset-acquisition">Dataset Acquisition</a> •
  <a href="#aknowledgements">Acknowledgements</a> •
  <a href="#additional-information">Additional Information</a> •
</p>  

<p align="center">
  
![screenshot](img/clip.gif)
</p>                                                                                                                             
                                                                                                                                                      
## About The SR2C
SR2C（Structurally Redundant Short Reads Collapser） is a short sequencing reads deduplicator based on the Cycle-Hash-Linkage data structure. SR2C aims to remove structurally redundant sequences in high-throughput genome sequencing data, including Direct Repeats (DRs), Mirror Repeats (MRs), Inverted Repeats (IRs), Paired Repeats (PRs), and Complementary Palindromes Repeats (CPRs).
In the current version, we use SR2C for data compression optimization.

## Useage

Clone the SR2C project from GitHub and compile it:
```shell script
git clone https://github.com/fahaihi/SR2C.git
cd SR2C
chmod +x install.sh
./install.sh
```

The usage of SR2C command-line tool is as follows:
```shell script
Usage:
Deduplication:
  ./SR2C -d [Save-Dir] -f [FastQ-File-Name]  -t [Threads-Num]
Recover:
  ./SR2C -r [Save-Dir] -t [Threads-Num]
Verify:
  ./SR2C -v [Save-Dir] -f [FastQ-File-Name]
Help (print this message)
  ./SR2C -h
```

An example:

**A：To perform structural redundancy removal on the data/test.fastq file using 2 threads and save the result in the test directory, use the following command:**
```shell script
data=`pwd`/data/test.fastq
./SR2C -d test -f ${data} -t 2
```
Results：
```sh
FileName:/public/home/jd_sunhui/genCompressor/SR2C/data/test.fastq
SaveDIR: /public/home/jd_sunhui/genCompressor/SR2C/test
ReadLen: 80
Threads: 2
STEP1:Begin Cycle-HASH-Linkage~
   RLength:80
   FileName:/public/home/jd_sunhui/genCompressor/SR2C/data/test.fastq
   SaveFileName:/public/home/jd_sunhui/genCompressor/SR2C/test
   Thread:2
   QualityScoreFlag:0
   HeaderFlag:0
STEP2:Begin Load Data~
   Data.size(): 1500
   Load_Data(*) running over~
STEP3:Begin Build CHL~
   LOG:1500/1500 --> 100%
   Build_CHL(*) running over~
STEP4:Begin Files SAVING~
  File_Name_reads:/public/home/jd_sunhui/genCompressor/SR2C/test/reads.txt
   File_Name_count:/public/home/jd_sunhui/genCompressor/SR2C/test/count.txt
   File_Name_id_1:/public/home/jd_sunhui/genCompressor/SR2C/test/id_1.txt
   File_Name_id_and_pos:/public/home/jd_sunhui/genCompressor/SR2C/test/id_pos.txt
   File_Name_info:/public/home/jd_sunhui/genCompressor/SR2C/test/info.txt
   FatherNum : 971
   Func_File_Saving(*) over~
STEP5:End Cycle-HASH-Linkage~
```
**B：To recover structural redundancy sequences from the test directory using 4 threads, use the following command:**
```shell script
./SR2C -r test -t 4
```
Results：
```sh
SaveDIR: /public/home/jd_sunhui/genCompressor/SR2C/test
Threads: 4
STEP1:Get Parameter over~
   ReadsNum:1500
   FatherNum:971
   RLength:80
   InputDir:/public/home/jd_sunhui/genCompressor/SR2C/test
STEP2:Load File over~
STEP3:Paralle Recover Row Data.
   CPU Cores:4
   LOG:971/971 --> 100%
STEP5:Save File Over.
   OutputSavedPath:/public/home/jd_sunhui/genCompressor/SR2C/test/recover.txt
```
<font color="red">Notes</font>：If `terminate called after throwing an instance of 'std::invalid_argument'` error message happened, please run `./install.sh` and try to redo the deduplication step (A).


**C：Verify if it is lossless to recover the original sequencing reads**
```shell script
./SR2C -v test -f ${data}
```
Result：
```sh
FileA:/public/home/jd_sunhui/genCompressor/SR2C/data/test.fastq
FileB:/public/home/jd_sunhui/genCompressor/SR2C/test/recover.txt
Unable to recover sequences：0
```
Notes: Here is a time and memory testing script:：
```shell script
/bin/time -v -p [your command]
```
## Dataset Acquisition

The experiment used 8 real open-source sequencing datasets from the NCBI open-source database (https://www.ncbi.nlm.nih.gov):
`SRR8386204_2`
`SRR11994956`	
`SRR17794741_1`	
`SRR17794741_2`	
`SRR8386204_1`	
`SRR13556216_1`	
`SRR16553126_1`	和
`SRR11995278`	
These datasets were used for experimental evaluation, consisting of a total of 105,016,192 reads and a data size of 25,607,473KB. Detailed descriptions of the datasets are as follows:

![Table1](https://github.com/fahaihi/SR2C/blob/master/datasets.png "datasets")

The experimental datasets were downloaded using the sra-tools package, and the script configuration can be found at https://github.com/ncbi/sra-tools. The dataset download script is as follows:

dataset-1： C.arietinum(鹰嘴豆) URL: https://www.ebi.ac.uk/ena/browser/view/SRR13556216
```shell script
cd SR2C/data
prefetch SRR13556216
fastq-dump SRR13556216
rm -rf SRR13556216 SRR13556216_2.fastq
```

dataset-2： Human(人类宏基因组) URL: https://www.ebi.ac.uk/ena/browser/view/SRR16553126
```shell script
prefetch SRR16553126
fastq-dump SRR16553126 
rm -rf SRR16553126 SRR16553126_2.fastq

```

dataset-3&4：M.fascicularis(食蟹猕猴) URL: https://www.ebi.ac.uk/ena/browser/view/SRR8386204
```shell script
prefetch SRR8386204
fastq-dump SRR8386204
rm -rf SRR8386204
```

dataset-5&6：Mouse.tumor(小鼠肿瘤) URL: https://www.ebi.ac.uk/ena/browser/view/SRR17794741
```shell script
prefetch SRR17794741
fastq-dump --split-files SRR17794741
rm -rf  SRR17794741 
```

dataset-7：S.fontinalis-1(美洲红点鲑) URL: https://www.ebi.ac.uk/ena/browser/view/SRR11995278
```shell script
prefetch SRR11995278
fastq-dump SRR11995278
rm -rf SRR11995278
```

dataset-8：S.fontinalis-2(美洲红点鲑) URL: https://www.ebi.ac.uk/ena/browser/view/SRR11994956
```shell script
prefetch SRR11994956
fastq-dump SRR11994956
rm -rf SRR11994956
```
## Acknowledgements
- Thanks to [@HPC-GXU](https://hpc.gxu.edu.cn) for the computing device support.   
- Thanks to [@NCBI](https://www.freelancer.com/u/Ostokhoon) for all available datasets.
- Thanks to [@PIGZ-Project](https://github.com/madler/pigz) for Pigz source code.
- Thanks to [@PBZIP2-Project](https://github.com/cosnicolaou/pbzip2) for PBzip2 source code.
- Thanks to [@XZ-Project](https://tukaani.org/xz) for XZ source code.
- Thanks to [@7ZProject](https://www.7-zip.org/sdk.html) for 7Z source code.
- Thanks to [@Minirmd](https://github.com/yuansliu/minirmd) for 7Z source code.

## Additional Information
**Version：**    V1.2023.01.24.

**Authors:**     NBJL-BioGrop.

**ContactUS:**  https://nbjl.nankai.edu.cn OR sunh@nbjl.naikai.edu.cn

**Supplementary:**  https://github.com/fahaihi/SR2C/blob/master/Supplementary.pdf
