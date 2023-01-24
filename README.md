![made-with-C++14](https://img.shields.io/badge/Made%20with-C++14-brightgreen)


<!-- LOGO -->
<br />
<h1>
<p align="center">
  <img src="https://github.com/fahaihi/SR2C/blob/master/SR2C_LOGO.png" alt="Logo" width="1305" height="326">
  <br>FastColabCopy
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
  <a href="#best-practice">Best Practice</a> •
  <a href="#credits">Credits</a> •
  <a href="examples.md">More Examples</a>
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
```sh
usage: fast-copy.py [-h HELP] source destination [-d DELETE] [-s SYNC] [-r REPLACE]

optional arguments:
  -h --help            show this help message and exit
  source                the drive you are copying from
  destination           the drive you are copying to
  -d --delete           delete the source files after copy
  -s --sync             delete files in destination if not found in source (do not use, if using with rsync)
  -r --replace          replace files if they exist
  -t --thread           set the amount of parallel threads used
  -l --size-limit       set max size of files copied (supports gb, mb, kb) eg 1.5gb
```
The `source` and `destination` fields are required. Everything else is optional.

## 测试数据集
```py
from google.colab import drive
drive.mount('/gdrive', force_remount=False)
import os
!wget -q https://raw.githubusercontent.com/L0garithmic/fastcolabcopy/main/fastcopy.py
import fastcopy
!python fastcopy.py /gdrive/Shareddrives/Source/. /gdrive/Shareddrives/Destination --thread 20 --size-limit 400mb
```
If you want to see copy execution time:
```mod
!pip install -q ipython-autotime
%load_ext autotime
```
Check out <a href="examples.md">examples.md</a> for some more examples.

## Best Practice
Colab has wildly varying transfer speeds, because of this, the best we can offer are suggestions:
- For large groups of medium/small files, 15-40 threads seems to work best.
- For 50+ files with significantly varying sizes, try 2 sequentially copies. `-t 15 -l 400` then `-t 2`
- For files that are 100MB+, it is best to use 2 threads. It is still faster then rsync.   
- Currently `--sync` breaks if rsync is ran after. If you are mirroring drives. Disable `--sync` and use the rsync's `--delete` function.

## Credits
- Credit to [ikonikon](https://github.com/ikonikon/fast-copy) for the base multi-threading code.   
- Thanks to [@Ostokhoon](https://www.freelancer.com/u/Ostokhoon) for ALL argument and folder hierarchy functionality.
