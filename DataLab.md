# CSAPP LAB

## DataLabMini

#### 1.bitAnd

```
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 10
 *   Rating: 8
 */
int bitAnd(int x, int y) {
  return ~(~x|~y);
}
```



#### 2.tmux

+(~0) = -1

```
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 8
 */
int tmax(void) {
  return (1 << 31) + ~0;
}
```



#### 3.negate

-x = ~x + 1

```
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 8
 */
int negate(int x) {
  return ~x + 1;
}
```



#### 4.copyLSB

```
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 8
 */
int copyLSB(int x) {
  return ~(x & 1) + 1;
}
```



#### 5.getByte

255 = B11111111

```
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (least significant) to 3 (most significant)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 8
 */
int getByte(int x, int n) {
  return (x >> (n << 3)) & 255;
}
```



#### 6.conditional

~!0 + 1 = 0

```
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 8
 */
int conditional(int x, int y, int z) {
  return (~!x + 1) ^ ((~!x + 1) | y) ^ ((~!x + 1) & z);
}
```



#### 7.isPositive

```
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 8
 */
int isPositive(int x) {
  return !x ^ ((x >> 31) + 1);
}
```



#### 8.logicalShift

注意 n = 0时,1 << (32 + ~n + 1) = 1

因为逻辑左移是循环移位,实际移位次数为x mod 32,所以移位32次等于没有移位

但是 1 << (32 + ~0 + 1) = 0???

```
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 8
 */
int logicalShift(int x, int n) {
  return (x >> n) & ((1 << (32 + ~n) << 1) + ~0);
}
```



#### 9.replaceByte

```
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 8
 */
int replaceByte(int x, int n, int c) {
  return (x & ~(255 << (n << 3))) | (c << (n << 3));
}
```



#### 10.multFiveEighths

大于0时,舍掉小数

小于0时,舍掉小数-1

```
/*
 * multFiveEighths - multiplies by 5/8 rounding toward 0.
 *   Should exactly duplicate effect of C expression (x*5/8),
 *   including overflow behavior.
 *   Examples: multFiveEighths(77) = 48
 *             multFiveEighths(-22) = -13
 *             multFiveEighths(1073741824) = 13421728 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 3
 */
int multFiveEighths(int x) {
  return (x << 2) + x + ((x >> 31) & 7) >> 3;
}
```



#### 11.bang

除0以外的所有数, x | (~x + 1)的最高位为1

```
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int bang(int x) {
  return ((x | (~x + 1)) >> 31) + 1;
}
```

## DataLab

#### 1.bitXor

#### 2.tmin

```
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;

}
```



#### 3.isTmax

注意不能使用 << 和 >> 

```
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  return !~(x + 1 + x) & !!(~x);
}
```



#### 4.allOddBits

注意只能使用0-255(0xoo-0xff)的数字,不能直接使用0xAAAAAAAA

```
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int y = 0x55 + (0x55 << 8);
  y = y + (y << 16);
  return !~(x | y);
}
```



#### 5.negate

```
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
```



#### 6.isAsciiDigit

我们通过!((x + ~0x2f) >> 31)来判断x是否大于30

注意当x=0x80000000时,!((x + ~0x2f) >> 31) = 0,计算表明x>30,但实际x<0x30,实际应该是1但是计算成了0.

但是同样的事情在第二部分算式中又出现了一次,导致0^0=1^1,最终结果是正确的.

在只有1个算式的时候,不能这样计算是否小于等于,还需要讨论符号位是否相同,相同时可以这样算,不同时可以直接讨论符号位

```
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
  return !((x + ~0x2f) >> 31) ^ !((x + ~0x39) >> 31);
}
```



#### 7.conditional

```
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int a = ~!x + 1;
  return a ^ (a | y) ^ (a & z);
}
```



#### 8.isLessOrEqual

先考虑符号位,详见6

```
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int a = x >> 31;
  int b = y >> 31;
  return ((a ^ b) & 1 & a) | (!(a ^ b) & !((y + ~x + 1) >> 31));
}
```



#### 9.logicalNeg

```
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  return ((x | (~x + 1)) >> 31) + 1;
}
```



#### 10.howManyBits

#### 11.floatScale2

#### 12.floatFloat2Int

#### 13.floatPower2