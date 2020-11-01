/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
// 1
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) { 
    //异或,位不同为1
    //计算不是同时为0情况和不是同时为1的情况进行位与
    // ~(x&y)两数全1的位为0,其余位为1
    // ~(~x&~y)两数全0为0,其余位为1
    //相与,为1的位即是两数不同的位
    return ~(~x&~y)&~(x&y);
    //return 2; 
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
//int 是32位
int tmin(void) { 
    return 0x1<<31;
    //return 2; 
}
// 2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    //int的补码最大值是0b0111....1
    int i = x+1;//Tmin,0b1000...
    x=x+i;//0b1,1111...
    x=~x;//0b0,0000...
    i=!i;//i=0b0111...1
    x=x+i;//x=0b111..1+0b0111..1=0b0000...0
    return !x;
    //return 2; 
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
//判断所有奇数位是否都为1
int allOddBits(int x) { 
    /**
     * 采用掩码方式解决。首先要构造掩码，
     * 使用移位运算符构造出奇数位全1的数 mask ，
     * 然后获取输入 x 值的奇数位，
     * 其他位清零（mask&x），
     * 然后与 mask 进行异或操作，若相同则最终结果为0，然后返回其值的逻辑非。
    */
    int mask=0xAAAAAAAA;
    //如果是奇数位全1,掩码与的结果就是mask,与mask异或结果为0
    return !((mask&x)^mask);
    //return 2; 
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
//补码实际上是一个阿贝尔群，对于 x，-x 是其补码，所以 -x 可以通过对 x 取反加1得到。
int negate(int x) {   
    return ~x+1;
    //return 2; 
}
// 3
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0'
 * to '9') Example: isAsciiDigit(0x35) = 1. isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) { 
    /**
     * 使用两个数，一个数是加上比0x39大的数后符号由正变负，
     * 另一个数是加上比0x30小的值时是负数。
     * 这两个数是代码中初始化的 upperBound 和 lowerBound，
     * 然后加法之后获取其符号位判断即可。
    */
    int sign = 0x1<<31;
    //max=0b01111...1
    int upperBound = ~(sign|0x39);// upper=max-0x39
    int lowerBound = ~0x30;//lower=-(1+0x30)= -0x31

    upperBound = sign&(upperBound+x)>>31;//C为算数右移,全bit置为符号位再与
    lowerBound = sign&(lowerBound+1+x)>>31;
    //如果是ASCII'0'-'9',两个结果均是正数,右移后与sign与的结果为0x0,否则两个结果有一个是负数，与结果有一个非0
    //或运算为0则是字符，返回1
    return !(upperBound|lowerBound);
    //return 2; 
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) { 
    //x不为0,将x置为1;x为0,将x置为0
    x = !!x;
    //上述处理后,x为1,结果x=0xFF...F
    //x为0,结果x=0
    x = ~x+1;
    return (x&y)|(~x&z);
    //return 2; 
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
//符号不同正数为大，二是符号相同看差值符号
int isLessOrEqual(int x, int y) { 
    int negX=~x+1;//-x
    int addX=negX+y;//y-x
    int checkSign = addX>>31&1; //y-x的符号
    int leftBit = 1<<31;//最大位为1的32位有符号数
    int xLeft = x&leftBit;//x的符号
    int yLeft = y&leftBit;//y的符号
    int bitXor = xLeft ^ yLeft;//x和y符号相同标志位，相同为0不同为1
    bitXor = (bitXor>>31)&1;//符号相同标志位格式化为0或1
    // 返回1有两种情况：
    // 符号相同标志位为0（相同）位 且 y-x 的符号为0（y-x>=0，正数）
    // 符号相同标志位为1（不同）位 且 x的符号位为1（x<0）
    return ((!bitXor)&(!checkSign))|(bitXor&(xLeft>>31));
    //return 2; 
}
// 4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
//使用位级运算求逻辑非 !
//非0为1，非非0为0
int logicalNeg(int x) { 
    return ((x|(~x+1))>>31)+1;
    //return 2; 
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
//求值：“一个数用补码表示最少需要几位？”
/**
 * 如果是一个正数，则需要找到它最高的一位（假设是n）是1的，再加上符号位，结果为n+1；
 * 如果是一个负数，则需要知道其最高的一位是0的（例如4位的1101和三位的101补码表示的是一个值：-3，最少需要3位来表示）。结果为n+1
*/
int howManyBits(int x) { 
    int b16,b8,b4,b2,b1,b0;
    int sign=x>>31;//以x符号位填满一个int
    x = (sign&~x)|(~sign&x);//如果x为正则不变，否则按位取反（这样好找最高位为1的，原来是最高位为0的，这样也将符号位去掉了）
    // 不断缩小范围
    b16 = !!(x>>16)<<4;//高十六位是否有1 先取x高16位,再!!判断有无1,再右移4位 (*16
    x = x>>b16;//如果有（至少需要16位），则将原数右移16位,因为如果有则b16=1<<4=16,x成为0x0000(原高16位);否则b16=0
    b8 = !!(x>>8)<<3;//剩余位高8位是否有1
    x = x>>b8;//如果有（至少需要16+8=24位），则右移8位
    b4 = !!(x>>4)<<2;//同理,
    x = x>>b4;
    b2 = !!(x>>2)<<1;
    x = x>>b2;
    b1 = !!(x>>1);
    x = x>>b1;
    b0 = x;
    return b16+b8+b4+b2+b1+b0+1;//+1表示加上符号位
    //return 0; 
}
// float
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
//求2乘一个浮点数(单精度)
unsigned floatScale2(unsigned uf) { 
    // exp 获取 uf的 E阶码 8位并右移至低8位
    int exp = (uf&0x7f800000)>>23;
    // sign 结果是  0b[uf的符号位]00..0
    int sign = uf&(1<<31);
    
    //如果是非规格化数,阶码域全0,此时数值是0.[M部分]
    //规格化和非规格化过渡是平滑的,非规格化数直接左移1位并复原符号位即是乘以2
    // ?[0x00][1100....] *2 = (2^{-1}+2^{-2})*2 
    // ?[0x01][1000....] = 1+2^{-1} (规格化了,有前导1了)
    if(exp==0) 
        return uf<<1|sign;
    //是特殊值 无穷或者NaN,直接返回
    if(exp==255) 
        return uf;
    // 如果指数+1之后为指数为255,说明乘以2后到达特殊值情况,则返回原符号无穷大
    exp++;
    if(exp==255) 
        return 0x7f800000|sign;
    // 否则返回指数+1(前面已经有exp++了)之后的原符号数
                        // 保留uf的符号位和尾数位,指数位清零,用对应的exp给指数位赋值
    return (exp<<23)|(uf&0x807fffff);
    //return 2; 
}
/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
// 将浮点数转换为整数
int floatFloat2Int(unsigned uf) { 
    // 获取符号位并把s_全部位置为符号位
    int s_    = uf>>31;
    // 获取指数位并转换(-Bias)为真实表示值
    int exp_  = ((uf&0x7f800000)>>23)-127;
    // 获取尾数的23(第0-22)位,并把第23位置为1 (前导1)
    int frac_ = (uf&0x007fffff)|0x00800000;
    
    // 如果uf除去符号位外全0
    if(!(uf&0x7fffffff)) 
        return 0;
    // 真实指数大于31（frac部分是大于等于1的，1<<31位会覆盖符号位），返回规定的溢出值0x80000000u
    if(exp_ > 31) 
        return 0x80000000;
    // 真实指数小于0,则绝对值必是一个0-1的小数,取整0
    if(exp_ < 0) 
        return 0;
    // 指数大于23,小数部分不再是小数,为整数部分,把小数转换为应该的整数 ([1]frac*2 ^{exp})
    if(exp_ > 23) 
        frac_ <<= (exp_-23);
    else 
        frac_ >>= (23-exp_);

    // 如果和原符号相同则直接返回
    if(!((frac_>>31)^s_)) 
        return frac_;
    // 转整的frac的第31位是1,符号与原来不同,现在是负,原来是正,溢出
    else if(frac_>>31) 
        return 0x80000000;
    // 符号和原来的不同,31位是0,现在是正,原来是负,应该返回的是负数,返回数值的相反数补码
    else 
        return ~frac_+1;
    //return 2; 
}
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
// 求2.0^{x}
unsigned floatPower2(int x) { 
    int bias = 127;
    /*
    if(x<-150) 
        return 0;
    */
    if(x>127) // res>= 2^128,单精度没法表示
        return 0xff<<23;//返回正无穷大 0b0111 1111 1 0000 0...0
    if(x<-127) // res<= 2^{-128},没法表示
        return 0;//全0
    // x+bias即乘幂后的指数 <<23 移动到对应的位置
    return (x+bias)<<23;
    //return 2; 
}
