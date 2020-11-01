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

#### 3.9

![image-20201101135412460](assets/image-20201101135412460.png)

```ASM
shift_ledt44_rightn:
	movq %rdi,%rax ; rax<-x
	salq $4 , %rax ;x<<4
	movl %esi,%ecx ;取n低32位存入rcx低32位
	sarq %cl,%rax  ;64位数据移位量是cl的低6位                              
```

#### 3.10

![image-20201101141926175](assets/image-20201101141926175.png)

```asm
orq rsi,rdi -> rdi=rsi | rdi -> x=x | y
sarq 3,rdi ->  rdi=rdi>>3 -> x=x>>3
notq rdi -> rdi=~rdi -> x=~x
movq rdx,rax -> rax = z
subq rdi,rax -> rax=rax-x
```

转换为C语言

```c
long t1 = x|y;
long t2 = t1>>3;
long t3 = ~t2;
long t4 = z-t3;
```

#### 3.11

![image-20201101142825696](assets/image-20201101142825696.png)

A: 用于将寄存器`rdx`清零

B：`mov $0, %rax`

C: `xorq`版本代码需要3字节，而`movq`版本需要7字节，