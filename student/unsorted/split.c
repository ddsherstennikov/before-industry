#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* split: разбить строку s в массив подстрок, c - разделитель */
void split(char* s, char c, int *cargs, char **args)
{
 char* ts = " ";
 char tmps[100];
 int i = 0;
 int j;
 
 while(ts != NULL)
     {
	  ts = strchr(s,c);               /*занести в ts подстроку s, нач-ся с 1го вхождения c в s*/
	  int n = strlen(s) - strlen(ts); /*получить число символов в s-ts (нужной подстроке s)*/
	  strncpy(tmps, s, n);            /*занести в tmps (типа const char*) подстроку s равную s-ts*/
	  tmps[n] = '\0';                 /*поставить символ конца строки*/
	  //strcpy(ts, tmps);          /*занести в очередную строку массива строк args сегмент tmps*/
	  for(j=0;j<strlen(tmps);j++) args[i][j] = tmps[j];
	  i++;
	 } 
 i--; 
 cargs = &i;	 
}

void main()
{
 char **args;
 char *s;
 int n;
 
 args[0] = "hello world";
 //split("HI.MY.NAME.IS", '.', &n, args);
 /*!!!!!!!!*/s[0] = args[0][0];/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
 puts(s);
}