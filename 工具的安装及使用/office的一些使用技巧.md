## EXCEL

1.在计算某些行/列平均值时,会使用AVERAGE函数来计算.但是数据可能会不断增加,如果不想每次增加完手动调整公式的范围,可以使用如下方法

```
=AVERAGE(D12:INDEX(12:12, MATCH(9^9, 12:12)))
```

表示我想计算从D12到12行中最后一个单元格的平均值

- MATCH(9^9, 12:12)返回12行中最后一个非空单元格的列号

  语法:MATCH(lookup_value, lookup_array, [match_type])

  lookup_value(必填):查找条件,在12行查找小于等于9^9的最大值,由于通常12行所有值都小于该数,所以会找到最后一个非空单元格

  lookup_array(必填):查找区域,12:12表示第12行的所有单元格(A:A表示A列所有单元格)

  match_type(选填):查找方式,默认为1,表示找到小于等于loopup_value的最大值(要找到最大值需要数组升序排列)

- INDEX(12:12, MATCH(9^9, 12:12)返回12行中最后一个非空单元格的引用

  语法:INDEX(array, row_num, column_num)

  array:查找的单元格范围

  row_num:返回值的行号

  column_num:返回值的列号