## GCC的编译命令

```shell
gcc  -{...}  -o -{outputfilename} - {....}
```

`-o`参数是用来指定输出文件名称的，默认是`a.out`，有多个参数时没有顺序要求.

### 4个阶段

`.c`文件转换为可执行文件在`gcc`下分为**预处理、编译、汇编、链接**4个阶段。

注意`.c`文件可以根据参数直接进行到当前参数的阶段。

#### 预处理 -E

根据文件所有`#`开头的命令，修改原程序，比如include头文件，把头文件内容加到当前文件对应位置，通常输出文件的扩展名是`.i`

**预处理参数 -E (大写)**

```shell
gcc -E  file.c -o file.i
gcc -E .\helloworld.c -o hellloworld.i #windows10
```

要指定输出文件名，否则可能直接在shell中把文件打印出来而不生成`.i`文件

#### 编译阶段 -S/s

编译器将文本文件翻译成一个当前平台的汇编语言程序，文件扩展名一般是`.s`

**编译参数 -S/s**

并不要求当前的输入文件是预处理的`.i`，也可以从`.c`直接进行

```shell
gcc -S file.? -o file.s
gcc -S .\helloworld.c -o hellloworld.s
gcc -S .\helloworld.i -o helloworld.s
```

#### 汇编阶段 -C/c

汇编器将`.s`的汇编语言文件程序翻译成机器语言的指令文件，并打包成一个**可重定位目标程序**，生成的文件扩展名是`.o`，这是一个二进制文件，`.o`文件可以供其他`.o`程序连接

**汇编参数 -C/c**

```shell
gcc -c file.? -o file.o
gcc -c .\helloworld.i -o helloworld.o
gcc -c .\helloworld.c -o helloworld.o
#...
```

#### 链接阶段

在编译过程中，除非使用了`-E、-S、-C`选项（或者编译出错阻止了完整的编译过程）否则最后的步骤都是链接。

直接使用`gcc`即可，事实上如果不加以上参数，`gcc`会直接把`.c`执行到这一阶段生成可执行文件，但是注意如果需要和额外的`.o`文件链接需要在命令中写明.

```shell
gcc -o helloworld helloworld.c
PS F:\MyNotes\GCC_make> .\helloworld.exe
> hello world!
gcc -o helloworld helloworld.o
```

貌似不能用`.s`的汇编语言文件作为输入



#### 多文件编译

编译只需要将`.c`文件作为输入

**分开编译**

注意`.o`文件仍然是不可执行的，需要和依赖的其他`.o`进行链接，如果已经生成了其他的依赖的第三方`.o`，可以用

```shell
g++ .\main.o .\compute.o .\setProperty.o -o test
```

生成可执行的`test`文件，这样只有修改了的文件才会重新冲重新汇编成`.o`

也可以把所有`.c/.cpp`一起编译

```shell
g++ -o test .\compute.cpp .\main.cpp .\setProperty.cpp
```

但是可能会出错。



#### 链接到外部库

` -L` 指定库的路径 `-l` 指定需连接的库名 `-I`指定第一个头文件目录

```shell
gcc -o hello hello.c -I /home/hello/include -L /home/hello/lib -lworld
```

上面这句表示在编译`hello.c`时：



大写`I`: `-I /home/hello/include`表示将`/home/hello/include`目录作为第一个寻找头文件的目录，寻找的顺序是：`/home/hello/include-->/usr/include-->/usr/local/include`



就拿数学库来说，他的库名是m，他的库文件名是libm.so，很容易看出，把库文件名的头`lib`和尾`.so`去掉就是库名了。

**.so和.a**

动态库(.so)

静态库(.a) 

静态库在程序编译时会被连接到目标代码中，程序运行时将不再需要该静态库。编译之后程序文件大，但加载快，隔离性也好。 动态库在程序编译时并不会被连接到目标代码中，而是在程序运行是才被载入，因此在程序运行时还需要动态库存在。多个应用程序可以使用同一个动态库，启动多个应用程序的时候，只需要将动态库加载到内存一次即可。



好了现在我们知道怎么得到库名了，比如我们自已要用到一个第三方提供的库名字叫libtest.so，那么我们只要把libtest.so拷贝到`/usr/lib`里，编译时加上`-l test`参数，我们就能用上libtest.so库了（当然要用libtest.so库里的函数，我们还需要与libtest.so配套的头文件）。

**不在主目录里**

放在`/lib`和`/usr/lib`和`/usr/local/lib`里的库直接用-`l`参数就能链接了，但如果库文件没放在这三个目录里，而是放在其他目录里，这时我们只用`-l`参数的话，链接还是会出错，出错信息大概是：`“/usr/bin/ld: cannot find -lxxx”`，也就是链接程序**ld**在那3个目录里找不到`libxxx.so`

这时另外一个参数`-L`就派上用场了，比如常用的`X11`的库，它放在`/usr/X11R6/lib`目录下，我们编译时就要用`-L /usr/X11R6/lib` `-l X11`参数，-L参数跟着的是库文件所在的目录名。

再比如我们把`libtest.so`放在`/aaa/bbb/ccc`目录下，那链接参数就是`-L /aaa/bbb/ccc -l test`



#### 安装apue.h   （静态库.a）

1. 下载: `[src.3e.tar.gz](http://www.apuebook.com/src.3e.tar.gz)`
2. 解压:` tar xvf src.3e.tar.gz`
3. 安装相应库:` sudo apt-get install libbsd-dev`
4. 进入到apue.3e目录，执行: make
5. `cp ./include/apue.h  /usr/include/`
6. `cp ./lib/libapue.a  /usr/local/lib/`
7. 编译时链接到相应库: `gcc -o 1-3 1-3.c -l apue`，这里把`.h .a`都放到了`/use/local`下，不需要`-L`

命令`cp`即copy，

```
cp [options] source dest
```

#### -m32/64

每台计算机都有一个字长，知名指针数据的标称大小。字长决定的最重要的系统参数是**虚拟地址空间的最大大小**，对于一个字长位$\omega$位的机器而言，虚拟地址的范围是$0~2^{\omega}-1$，最多访问$2^{\omega}$字节

`gcc -m32 {filename}.c`将生成32位程序

`gcc -m64 {filename}.c`生成64位程序

`MingW-GCC`中，`int`为保证兼容还是32位，若64位编译器要使用`int 64`，使用`__int64 __int32`表示

#### 优化命令

假定一个C程序有两个文件p1.c，p2.c，

编译命令`gcc -Og -o p p1.c p2.c`

`-Og`告诉编译器会生成符合原始C代码整体结构的机器代码的优化等级，使用较高级别的优化代码会严重变形。

以`-O1 / -O2`作为优化等级被认为是较好的选择。