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
    基于循环哈希链表的DNA测序数据结构冗余短序列去重器
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
```sh
git clone https://github.com/fahaihi/SR2C.git
cd SR2C
chmod +x install.sh
./install.sh
```

Import from Google Drive:
```py
!cp /gdrive/MyDrive/fastcopy.py .
import fastcopy
```


## 测试数据集

实验采用NCBI开源数据库(https://www.ncbi.nlm.nih.gov) 中14组开源开数据集
`SRR13556216_2`	
`ERR7091256`	
`SRR8386204_2`	
`SRR921889`	
`SRR11994956`	
`SRR17794741_1`	
`SRR17794741_2`	
`SRR8386204_1`	
`SRR13556216_1`	
`SRR16553126_1`	
`SRR16552220_1`	
`SRR11995278`	
`SRR15112778_1`	
`SRR15112778_2`	
用于实验评估（序列总数：239,985,080条、数据规模：64,874,833KB）。详细数据集描述如下：

![Table1](https://github.com/fahaihi/SR2C/blob/master/datasets.png "datasets")

实验数据集下载使用sra-tools 工具，其脚本配置参见：https://github.com/ncbi/sra-tools. 以下给出部分测试数据集的下载脚本：

```sh
# SRR921889 人类病毒宏基因组
# URL: https://www.ebi.ac.uk/ena/browser/view/SRR921889
cd SR2C/data
prefetch SRR921889
fastq-dump SRR921889
rm -rf  SRR921889
```

```sh
# ERR7091256 智人
# URL: https://www.ebi.ac.uk/ena/browser/view/ERR7091256
prefetch ERR7091256
fastq-dump ERR7091256 
rm -rf  ERR7091256
```

```sh
# SRR11994956 美洲红点鲑
# URL: https://www.ebi.ac.uk/ena/browser/view/SRR11994956
prefetch SRR11994956
fastq-dump SRR11994956
rm -rf  SRR11994956
```

```sh
# SRR17794741_1	小鼠肿瘤
# URL: https://www.ebi.ac.uk/ena/browser/view/SRR17794741
prefetch SRR17794741
fastq-dump --split-files SRR17794741
rm -rf  SRR17794741 SRR17794741_2.fastq
```

```sh
# SRR13556216_2	鹰嘴豆
# URL: https://www.ebi.ac.uk/ena/browser/view/SRR13556216
prefetch SRR13556216
fastq-dump --split-files SRR13556216
rm -rf  SRR13556216 SRR13556216_1.fastq
```

```sh
# SRR8386204_2	食蟹猕猴
#URL: https://www.ebi.ac.uk/ena/browser/view/SRR8386204
prefetch SRR8386204
fastq-dump --split-files SRR8386204
rm -rf  SRR8386204 SRR8386204_1.fastq
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

## 补充信息
**Version：**    V1.2023.01.24.

**Authors:**     NBJL-BioGrop.

**Contact us:**  https://nbjl.nankai.edu.cn OR sunh@nbjl.naikai.edu.cn
