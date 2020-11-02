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

![image-20201101135412460](http://qixycp91n.hn-bkt.clouddn.com/picGo/image-20201101135412460.png)

```ASM
shift_ledt44_rightn:
	movq %rdi,%rax ; rax<-x
	salq $4 , %rax ;x<<4
	movl %esi,%ecx ;取n低32位存入rcx低32位
	sarq %cl,%rax  ;64位数据移位量是cl的低6位                              
```

#### 3.10

![image-20201101141926175](http://qixycp91n.hn-bkt.clouddn.com/picGo/image-20201101141926175.png)

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

![image-20201101142825696](http://qixycp91n.hn-bkt.clouddn.com/picGo/image-20201101142825696.png)

A: 用于将寄存器`rdx`清零

B：`mov $0, %rax`

C: `xorq`版本代码需要3字节，而`movq`版本需要7字节，

#### 3.12

![image-20201102214113753](http://qixycp91n.hn-bkt.clouddn.com/picGo/image-20201102214113753.png)

64位汇编除法中64位被除数应该存在`%rax`中,无符号除法应该将`%rdx`设置为全0

```asm
; x in rdi,y in rsi , qp in rdx, rp in rcx
uremdiv:
	movq %rdx,%r8 ; copy qp value to r8
	movq %rdi,%rax ; copy x value to rax 作为被除数
	movl $0,%edx ; %rdx?? 
	divq %rsi ; divided by y
	movq %rax,(%r8) ; 商在rax中,复制到内存*qp中
    movq %rdx, (%rcx); 余数在rdx中,复制余数
	ret
```

#### 3.13

![image-20201102215859787](http://qixycp91n.hn-bkt.clouddn.com/picGo/image-20201102215859787.png)

**汇编代码不会记录程序值的类型**

##### A：

比较指令`cmp`具有后缀`l`，（对set指令后缀意义不同于此）

| 后缀 | 表示字节数 |
| ---- | ---------- |
| b    | 1          |
| w    | 2          |
| l    | 4          |
| q    | 8          |

表示则是两个4字节32位数据的比较，比较是`setl`表示小于时设置 ，将数据视为补码

推断`data_t`是`int`

##### B:

`cmpw`,w reflects they are 2bytes, 16bit

`setge` means  setting when condition is  `>=`, also two's complement 

`data_t `  is  `short`

##### C:

`cmpb` b reflects they are byte ,8 bit

`setbe` means setting when `<=`  and  `unsigned`

`data_t`  is  `unsigned char`

##### D:

`cmpq` q ,so they are 8bytes 64bits

`setne`  not equal  can be `signed` 、`unsigned`、and `point parameter` 

`data_t`可以是`long int`、 `unsigned long int`、`某种形式的指针 (xxx)*`

#### 3.15

![image-20201102221614669](http://qixycp91n.hn-bkt.clouddn.com/picGo/image-20201102221614669.png)

##### A:

此处跳转指令的目标偏移量用单字节补码表示0x02，下一条指令地址4003fc+偏移量0x02=目标0x4003FE

##### B:

0x400431+0xf4=0x400431-0xC (12)=0x400425

##### C：

pop 地址 p 

p+0x02=0x400547，p=0x400545

ja指令占据两个字节, ja指令地址是 0x400543

##### D:

目标的偏移量由4字节表示，小端法，实际偏移量是0xffffff73=-(0x8C+1)=-141

4005ed-0x8D=400560

`jmpq 400560`

#### 3.16

![image-20201102223851082](http://qixycp91n.hn-bkt.clouddn.com/picGo/image-20201102223851082.png)

##### A:

```c
void cond(long a,long *p){
	if(p==0)//可以判断就直接跳过，短路效应
        goto done;
    if(*p>=a)
        goto done;
    *p=a;
    done:
    	return;
}
```

##### B:

题干中的C代码只有一个`if`是因为表达式有`&&`，在汇编代码中第一个条件分支用于测试`&&`左边的条件,第二个分支用于测试第二个条件

#### 3.17

![image-20201102224507663](http://qixycp91n.hn-bkt.clouddn.com/picGo/image-20201102224507663.png)

##### A：

```c
long lt_cnt=0;
long ge_cnt=0;
long absdiff_se(long x,long y){
	long result;
    if(x<y)
        goto true;
    ge_cnt++;
    result=x-y;
    return result;
    true:
    	lt_cnt++;
    	result=y-x;
    	return result;
}
```

##### B:

一般情况两种方案都可以，但是原来的方法对于常见的仅一个`if`没有`else`的情况更好，这种翻译更麻烦

#### 3.18

<img src="http://qixycp91n.hn-bkt.clouddn.com/picGo/image-20201102225144293.png" alt="image-20201102225144293" style="zoom:50%;" />

```c
long test(long x,long y,long z){
	long val =x+y+z;//0,1,2行，存入%rax
    if(x<-3){//x>=-3跳转
		if(y<z){
            val=x*y;
		}else{
         	val=y*z;   
		}
    }//每个Label都有ret,加上else
 	else{
        if(x>2)
          	val=x*z;
	}   
    return val;
}
```

