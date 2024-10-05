# CR,LF,CRLF

CR(Carriage Return,回车),ASCII字符为\r,将光标移动到行首,不移到下一行

LF(Line Feed,换行),ASCII字符为\n

CRLF(Carriage Return & Line Feed,回车换行),ASCII字符为\r\n,将光标移动到行首,并移动到下一行



Windows默认使用\r\n作为换行符

Linux(unix)默认使用\n作为换行符

Mac默认使用\r作为换行符



Unix和Mac系统下的文件在Windows里打开的话,所有文字都变成一行.

Windows里的文件在Unix和Mac里打开的话,在每行结尾可能会多出一个^M符号