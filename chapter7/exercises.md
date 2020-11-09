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



