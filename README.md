# Software Engineering Project 4: 等价判断

### Equivalence Judgement

实现了OJ程序的等价判断工具。

通过随机生成输入并运行程序得到输出，确认程序对间的等价关系并予以确认。

------

### 程序环境：

- 操作系统:

Ubuntu 18.04.3

- 语言Language：

C++

- IDE

Visual Studio Code（Linux开发） & Visual Studio 2022（Windows验证与远程目录上载）

------

### 输入输出：

#### **输入格式**：

输入一个文件夹input。

- 输入文件夹中包含多个子文件夹dir，每个子文件夹dir中包含若干C/C++编写的OJ源程序，以及一个保存OJ标准输入格式的文件`stdin_format.txt`。

```
input
└─dir
    ├─oj1.cpp
    ├─oj2.cpp
    ├─oj3.cpp
    └─stdin_format.txt
```

- OJ程序的标准输入格式由stdin_format.txt表示：

  每行由多个type组成，其中type只包括了int、char和string:

  -  `int(a,b)`: a<=value(int)<=b
  -  `char`: 随机大小写字母
  -  `string(a,b)`: 由char组成，a<=length(string)<=b

  各个type之间用空格分割，例如：

  ```
  int(1,2) string(2,3)
  ```

  该格式可以构造的一个随机输入：

   `1 abc`

#### **输出格式**：

equal.csv保存等价的OJ程序的相对路径对，inequal.csv保存不等价的OJ程序的相对路径对。

  ```
output
├─equal.csv
└─inequal.csv
  ```

#### **CSV Format**：

  equal.csv和inequal.csv的文件格式都如下表所示。

| file1             | file2             |
| ----------------- | ----------------- |
| input/dir/oj1.cpp | input/dir/oj2.cpp |
| ...               | ...               |

------

### 使用说明：

#### 运行程序：

下载本项目；在/Code文件夹中打开命令行，输入make以生成执行文件test，使用./test执行本程序。

程序工作需要一个输入文件夹input（具体格式见**输入输出**）。同时在运行时需要输入存储input文件夹的父目录。

程序的输出会生成在输入的目录中（具体格式见**输入输出**）。

#### 清理程序：

在/Code文件夹中输入make veryclean以清除所有生成的程序。
