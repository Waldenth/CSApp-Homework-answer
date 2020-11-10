### 链接 练习题



#### 7.1

<img src="http://qixycp91n.hn-bkt.clouddn.com/picGo/image-20201109224104840.png" alt="image-20201109224104840" style="zoom: 33%;" />

| 符号    | `.symtab`条目 | 符号类型 | 在哪个模块定义 | 节       |
| ------- | ------------- | -------- | -------------- | -------- |
| `buf`   | yes           | 外部     | `m.o`          | `.data`  |
| `bufp0` | yes           | 全局     | `swap.o`       | `.data`  |
| `bufp1` | yes           | 全局     | `swap.o`       | `COMMON` |
| `swap`  | yes           | 全局     | `swap.o`       | `.text`  |
| `temp`  | no            | -        | -              | -        |

####  7.2

<img src="http://qixycp91n.hn-bkt.clouddn.com/picGo/image-20201109230802551.png" alt="image-20201109230802551" style="zoom: 33%;" />

<img src="http://qixycp91n.hn-bkt.clouddn.com/picGo/image-20201109230817243.png" alt="image-20201109230817243" style="zoom:33%;" />

##### A：

```
REF(main.1) -> DEF () 
在模块1中符号main是一个函数，强；模块2中则是一个未初始化定义的数据，弱
因此 REF(main.1)->DEF(main.1)

同理，由于两个模块的main都是全局符号，全局符号解析只能选择所有输入模块的一个定义，选择强的
REF(main.2)->DEF(main.1)
```

##### B:

```
错误，两个模块都定义了一个强符号main，违反规则1
```

##### C:

```
两个都是全局符号，模块2定义的强，模块1定义的弱
REF(x.1)-> DEF(x.2)
REF(x.2)->DEF(x.2)
```

#### 7.3

<img src="http://qixycp91n.hn-bkt.clouddn.com/picGo/image-20201110153911933.png" alt="image-20201110153911933" style="zoom:50%;" />

##### A：

```bash
p.o -> libx.a
linux> gcc p.o libx.a
```

##### B:

```bash
linux> gcc p.o libx.a liby.a
```

##### C:

```bash
linux> gcc p.o libx.a liby.a libx.a 
```

**注意：**

之所以最后一个依赖`p.o`不用写在命令行里是因为`p.o`在前面已经加入集合`E`了，而`.a`文件要写在命令行是因为`.a`可以看作一个`.o`文件的集合，不知道`liby.a`依赖的是`libx.a`的哪个成员目标文件，究竟加没加载到集合`E`中

#### 7.4

<img src="http://qixycp91n.hn-bkt.clouddn.com/picGo/image-20201110184549082.png" alt="image-20201110184549082" style="zoom:33%;" />

##### A:

第五行指令机器码是`e8 05 00 00 00`，`e8`是`callq`的一字节操作码，后面的`05 00 00 00`则是`sum`重定位引用，由小端法这个引用是`0x05`，其最低字节地址是其地址，即`0x400de+1=0x400df`

##### B

根据`call`指令的操作，此时$PC$指向的应该是下一条指令即$PC=0x4004e3$，`sum`的重定位引用值是`05`，符号运行时地址是`0x4004e3+0x5=0x4004e8`

#### 7.5

<img src="http://qixycp91n.hn-bkt.clouddn.com/picGo/image-20201110185320249.png" alt="image-20201110185320249" style="zoom: 33%;" />

<img src="http://qixycp91n.hn-bkt.clouddn.com/picGo/image-20201110185333345.png" alt="image-20201110185333345" style="zoom:33%;" />

看`r.type`有`PC`标识，因此是重定位一个32位PC相对地址的引用。根据算法：

引用的运行时地址：`refaddr=ADDR(s)+r.offset=0x4004d0+0xa=0x4004da`

生成的可执行文件更新该引用：`*refptr=(unsigned)(0x4004e8-4-0x4004da)=0x0a`

得到的可执行目标文件中，对`swap`的PC相对引用值是`0x0a`

`e8 0a 00 00 00  call 4004e8<swap>`  

