#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* split: ������� ������ s � ������ ��������, c - ����������� */
void split(char* s, char c, int *cargs, char **args)
{
 char* ts = " ";
 char tmps[100];
 int i = 0;
 int j;
 
 while(ts != NULL)
     {
	  ts = strchr(s,c);               /*������� � ts ��������� s, ���-�� � 1�� ��������� c � s*/
	  int n = strlen(s) - strlen(ts); /*�������� ����� �������� � s-ts (������ ��������� s)*/
	  strncpy(tmps, s, n);            /*������� � tmps (���� const char*) ��������� s ������ s-ts*/
	  tmps[n] = '\0';                 /*��������� ������ ����� ������*/
	  //strcpy(ts, tmps);          /*������� � ��������� ������ ������� ����� args ������� tmps*/
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