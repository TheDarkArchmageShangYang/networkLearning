## DataLab

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
  return ~((~x) | (~y));
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
  return (1 << 31) + (~0);
}
```



#### 3.negate

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
  return (x & 1 << 32) + ~(x & 1) + 1;
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

#### 7.isPositive

#### 8.logicalShift

#### 9.replaceByte

#### 10.multFiveEighths

#### 11.bang