#ifndef COMMENTPROCESS_INCLUDED
#define COMMENTPROCESS_INCLUDED
#include <cstdio>

void comment_process(FILE* in_fp)
{
	int temp_c = 0; //临时存储字符的变量
	while (((temp_c = fgetc(in_fp)) == '/' || temp_c == '\n') && (!feof(in_fp))) //试探性读取一个字符
	{
		ungetc(temp_c, in_fp);
		while ((temp_c = fgetc(in_fp)) != '\n' && !feof(in_fp)); //如果是注释，把这行全略过，直至读到非注释的一行
	}	
	if(!feof(in_fp))
		ungetc(temp_c, in_fp); //如果没有读到文件尾部的话，就把当前字符放回去
}

#endif // !COMMENTPROCESS_INCLUDED

