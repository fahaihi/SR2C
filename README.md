![made-with-C++](https://img.shields.io/badge/Made%20with-C++11-brightgreen)
![made-with-OpenMP](https://img.shields.io/badge/Made%20with-OpenMP-blue)


<!-- LOGO -->
<br />
<h1>
<p align="center">
  <img src="https://github.com/fahaihi/SR2C/blob/master/SR2C_LOGO.png" alt="Logo" width="653" height="163">
  <br>Structal Redundant Short Reads Collapser
</h1>
  <p align="center">
    A DNA sequencing data structure redundant short reads deduplicator via cyclic hash linkege
    <br />
    </p>
</p>
<p align="center">
  <a href="#项目说明">项目说明</a> •
  <a href="#使用方法">使用方法</a> •
  <a href="#测试数据集">测试数据集</a> •
  <a href="#致谢及相关仓库链接">致谢及相关仓库链接</a> •
  <a href="#补充信息">补充信息</a> •
</p>  

<p align="center">
  
![screenshot](img/clip.gif)
</p>                                                                                                                             
                                                                                                                                                      
## 项目说明
SR2C（Structal Redundant Short Reads Collapser）是一款基于循环哈希链表（Cycle-Hash-Linkage）数据结构的短序列去重器。SR2C旨在去除高通量基因组测序数据中的结构冗余序列，包括直接重复(Direct Repeats, DRs)、镜像重复(Mirror Repeats, MRs)、反转重复(Inverted Repeats, IRs)、配对重复(Paired Repeats, PRs)和互补回文重复(Complementary Palindromes Repeats, CPRs)。

## 使用方法

从GitHub克隆SR2C项目并编译:
```shell script
git clone https://github.com/fahaihi/SR2C.git
cd SR2C
chmod +x install.sh
./install.sh
```

SR2C命令行工具使用方法如下:
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

以下是一个使用示例：

**A：使用2个线程对data/test.fastq文件进行结构冗余去重，文件保存在test目录下**
```shell script
data=`pwd`/data/test.fastq
./SR2C -d test -f ${data} -t 2
```
运行结果如下：
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
**B：使用4个线程恢复test目录下的结构冗余序列**
```shell script
./SR2C -r test -t 4
```
运行结果如下：
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
**C：校验是否是无损恢复原始测序序列**
```shell script
./SR2C -v test -f ${data}
```
运行结果如下：
```sh
FileA:/public/home/jd_sunhui/genCompressor/SR2C/data/test.fastq
FileB:/public/home/jd_sunhui/genCompressor/SR2C/test/recover.txt
无法恢复序列：0
```
Notes: 时间内存测试脚本如下：
```shell script
/bin/time -v -p [your command]
```
## 测试数据集

实验采用NCBI开源数据库(https://www.ncbi.nlm.nih.gov) 中8组真实开源测序数据集
`SRR8386204_2`
`SRR11994956`	
`SRR17794741_1`	
`SRR17794741_2`	
`SRR8386204_1`	
`SRR13556216_1`	
`SRR16553126_1`	和
`SRR11995278`	
用于实验评估（序列总数：105,016,192条、数据规模：25,607,473KB）。详细数据集描述如下：

![Table1](https://github.com/fahaihi/SR2C/blob/master/datasets.png "datasets")

实验数据集下载使用`sra-tools` 工具，其脚本配置参见：https://github.com/ncbi/sra-tools. 数据集下载脚本如下：

数据集1： C.arietinum(鹰嘴豆) URL: https://www.ebi.ac.uk/ena/browser/view/SRR13556216
```shell script
cd SR2C/data
prefetch SRR13556216
fastq-dump SRR13556216
rm -rf SRR13556216 SRR13556216_2.fastq
```

数据集2： Human(人类宏基因组) URL: https://www.ebi.ac.uk/ena/browser/view/SRR16553126
```shell script
prefetch SRR16553126
fastq-dump SRR16553126 
rm -rf SRR16553126 SRR16553126_2.fastq

```

数据集3&4：M.fascicularis(食蟹猕猴) URL: https://www.ebi.ac.uk/ena/browser/view/SRR8386204
```shell script
prefetch SRR8386204
fastq-dump SRR8386204
rm -rf SRR8386204
```

数据集5&6：Mouse.tumor(小鼠肿瘤) URL: https://www.ebi.ac.uk/ena/browser/view/SRR17794741
```shell script
prefetch SRR17794741
fastq-dump --split-files SRR17794741
rm -rf  SRR17794741 
```

数据集7：S.fontinalis-1(美洲红点鲑) URL: https://www.ebi.ac.uk/ena/browser/view/SRR11995278
```shell script
prefetch SRR11995278
fastq-dump SRR11995278
rm -rf SRR11995278
```

数据集8：S.fontinalis-2(美洲红点鲑) URL: https://www.ebi.ac.uk/ena/browser/view/SRR11994956
```shell script
prefetch SRR11994956
fastq-dump SRR11994956
rm -rf SRR11994956
```
## 致谢及相关仓库链接
- Thanks to [@HPC-GXU](https://hpc.gxu.edu.cn) for the computing device support.   
- Thanks to [@NCBI](https://www.freelancer.com/u/Ostokhoon) for all available datasets.
- Thanks to [@HARC-Project](https://github.com/shubhamchandak94/HARC) for HARC source code.
- Thanks to [@SPRING-Project](https://github.com/shubhamchandak94/Spring) for SPRING source code.
- Thanks to [@MSTCOM-Project](https://github.com/yuansliu/mstcom) for MSTCOM source code.
- Thanks to [@FASTQCLS-Project](https://github.com/Krlucete/FastqCLS) for FastqCLS source code.
- Thanks to [@PIGZ-Project](https://github.com/madler/pigz) for Pigz source code.
- Thanks to [@PBZIP2-Project](https://github.com/cosnicolaou/pbzip2) for PBzip2 source code.
- Thanks to [@XZ-Project](https://tukaani.org/xz) for XZ source code.
- Thanks to [@7ZProject](https://www.7-zip.org/sdk.html) for 7Z source code.
- Thanks to [@Minirmd](https://github.com/yuansliu/minirmd) for 7Z source code.

## 补充信息
**版本信息-Version：**    V1.2023.01.24.

**作者-Authors:**     NBJL-BioGrop.

**联系我们-ContactUS:**  https://nbjl.nankai.edu.cn OR sunh@nbjl.naikai.edu.cn

**补充材料-Supplementary:**  https://github.com/fahaihi/SR2C/blob/master/Supplementary.pdf
