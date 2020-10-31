#### 3.6

![image-20201031215853009](http://qixycp91n.hn-bkt.clouddn.com/picGo/image-20201031215853009.png)

**答：**

`leaq 6(%rax),%rdx`（图示有误）表示将` %ax +6` 赋值给`%rdx`，结果6+x

`leaq (%rax,%rcx),%rdx`，结果x+y

`leaq (%rax,%rcx,4) %rdx`，x+4y

`leaq 7(%rax,%rax,8) %rdx`,9x+7

`leaq 0xA(,%rcx,4) %rdx`,10+4y

`leaq 9(%rax,%rcx,2),%rdx ` , 9+x+2y

#### 3.7

![image-20201031221320800](http://qixycp91n.hn-bkt.clouddn.com/picGo/image-20201031221320800.png)

```
rax=x+4x=5x;
rax=rax+2rsi=5x+2y;
rax=rax+8rdx=5x+2y+8z
```

因此，缺失的C表达式是

```c
long t = 5*x+2*y+8*z;
```

#### 3.8

![image-20201031222310473](http://qixycp91n.hn-bkt.clouddn.com/picGo/image-20201031222310473.png)

`addq %rcx,(%rax)`表示将内存`(%rax)`处的值减去`%rcx`，目的 0x100，值0xFF+0x1=0x100

`subq rdx,8(rax)`,target is 0x100+8=0x108, value is 0xAB-0x3=0xA8

`imulq $16,(rax,rdx,8)`,target is `rax+8*rdx=0x100+8*0x3=0x118`,value is 16* 0x11=0x10*0x11=0x110

`incq 16(rax)`,target is `rax+16=0x110`,value is 0x13+1=0x14

`decq rcx` target is `%rcx`,value is 0x1-1=0x0

`subq rdx,rax`,target is `%rax`,value is 0x100-0x3=0xFD

