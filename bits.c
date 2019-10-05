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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  /*这道题实际上要求的是48<= x <=57,那么只要求得x-48和x-57的符号位即可
  而-48是~48+1，-57=~57+1;对所得的数进行移位操作就可判断
  要求的是x+(~48+1)第32位是0，x+(~57+1)第32位是1
  再考虑x+(~57+1)第32位是0显然满足条件。要求这样返回值是1，那就取&再去反
  就是*/
  return !((x+(~48+1)) >> 31)&((x+(~57+1)) >> 31);
}
/* 
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   Examples anyEvenBit(0xA) = 0, anyEvenBit(0xE) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyEvenBit(int x) {
  /*由于5的二进制表示是0101是偶数位是1，而题目要求偶数位是1时return 0，所以用到按位与&再取!!
  为了支持较大的数，我以0x55往上加 */
  int a = 0x55;
  int b = (a << 8) + a; //0x55 55
  int c = (b << 8) + a; //0x55 55 55
  int d = (c << 8) + a; //0x55 55 55 55
  return !!(x & d);
}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
  /*先将x左移31位从而让x的最低位移到最高位(32位)，然后再右移
  根据算数右移规则，从而得到所需结果 */
  return (x<<31)>>31;
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {
  /*假设二进制数x为1的最低位在第n位，将x-1时，则[n-1,0]变为全1，
  [n+1,31]位不变，这部分做异或操作就可变为0，即x^(x-1)，这时候[n,0]会全部变为1，
  所以做与操作。 */
  return (((x + ~0)^x)&x);
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    /*分类讨论，如果x >= 0, 那么 x/(2^n) = x >> n；
    如果 x < 0, 那么x/(2^n) = (x + (1 << n) - 1) >> n;
    现在构造一个数 bias 使得在 x >= 0时，bias = 0；
    在 x < 0 时，bias = (1 << n) - 1;
    signMask = x >> 31, 表示如果x负数则，signMask = 0xFFFFFFFF；
    否则signMask = 0x0。
    所以 bias = signMask & (1 << n) + ～0) 。其中～0 = -1。 */
  int signMask = x >> 31;
  return (x + (signMask & ((1 << n) + ~0))) >> n;
}


/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  /*将x的bit表示，分成两个一组，组内一位相加。
   例如：10010010111010101011101000001101，
   分成 10 01 00 10 11 10 10 10 10 11 10 10 00 00 11 01。
   组内相加得到x1 = 01 01 00 01 10 01 01 01 01 10 01 01 00 00 10 01.
   这样表示每组分别有多少个1。
   实现这个操作只要将(x & mask1) + ((x >> 1) & mask1), 其中mask1 = 01010101...0101.
   mask1 可以经过如上代码得到。
   再将x1的bit表示，分成四个一组，同样组内两位相加。
   10 01 00 10 11 10 10 10 10 11 10 10 00 00 11 01，
   分成1001 0010 1110 1010 1011 1010 0000 1101。
   组内相加得到x2 = 0010 0010 0101 100 0101 0100 0000 0101。同样地表示没组分别有多少个1。
   实现这个操作只要将(x & mask2) + ((x >> 2) & mask2), 其中mask2 = 00110011...0011.
   mask2 可以经过如上代码得到。
   以此类推... */
  int mask_1 = 0x55 << 8 | 0x55;
  int mask_2 = 0x33 << 8 | 0x33;
  int mask_4 = 0x0f << 8 | 0x0f;
  int mask_8 = 0xff << 16 | 0xff;
  int mask_16 = ~0 + (1 << 16);
  mask_1 |= mask_1 << 16;
  mask_2 |= mask_2 | mask_2 << 16;
  mask_4 |= mask_4 | mask_4 << 16;
  x = (x&mask_1) + ((x>>1)&mask_1);
  x = (x&mask_2) + ((x>>2)&mask_2);
  x = (x&mask_4) + ((x>>4)&mask_4);
  x = (x&mask_8) + ((x>>8)&mask_8);
  x = (x&mask_16) + ((x>>16)&mask_16);
  return x;
}

