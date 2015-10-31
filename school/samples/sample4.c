#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

int funk(char *file)
{FILE *fp;
 char c;
 int okfile;
 char cl,cr;
 double *a;
 int dot,spc,num;
 int i;
 int b;
 int prop;

 fp=fopen(file,"r");
 c='0';
 *a=0;
 dot=-1;
 spc=1;
 num=0;
 prop=0;

 if (fp==NULL) return(-1);/*cant read file*/

 else
 {okfile=1;
  while(c != EOF)
    {c=getc(fp);if((!isdigit(c))&&(!isspace(c))&&(c!=EOF)&&(c!='.')) okfile=0;}
  rewind(fp);

  cl='0';c='0';cr='0';
  while(cr != EOF)
    {cl=c;c=cr;cr=getc(fp);
     if(c=='.') if((cl=='.')||(cr=='.')) okfile=0;
		else if(cl==' ') okfile=0;
     }
 rewind(fp);

 if (okfile==0) return(-2);/*though readable but bad file*/

 else
 {while(c!=EOF)
  {c=getc(fp);
   if (isdigit(c)) {*a=(*a)*10+c-'0';if(dot>=0) dot++;num=num+(spc>0);spc=0;}
   if (c == '.') dot=0;
   if (isspace(c)) {spc++;if ((spc==1)&&(num>0)) {*a=(*a)*pow10(-dot);a++;*a=0;dot=-1;}}
   if ((c==EOF)&&(spc==0)) {*a=(*a)*pow10(-dot);a=a-(num-1);}
   if ((c==EOF)&&(spc>0)) {*a=(*a)*pow10(-dot);a=a-num;}
  }

  puts("the sequence is:");
  for(i=num;i>0;i--) {printf("%f ",*a);a++;}

  b=0;
  a=a-num;
  for(i=num;i>1;i--) {b=b+(*a >= *(a+1));a++;}
  if(b == 0) prop=1;/*seq is strictly increasing*/

  b=0;
  a=a-num+1;
  for(i=num;i>1;i--) {b=b+(*a <= *(a+1));a++;}
  if(b == 0) prop=2;/*seq is strictly decreasing*/

  b=0;
  a=a-num+1;
  for(i=num;i>1;i--) {b=b+(*a != *(a+1));a++;}
  if(b == 0) prop=3;/*seq is const*/

  return(prop);
 }

 }

}

int main()
{char *s;
 int a;

 clrscr();
 puts("file-to-read-from name is:");
 gets(s);puts("\n");

 a=funk(s);

 puts("\n\nresult code\n(-2)=bad data in file\n(-1)=cant open file\n0=nonmonotonous seq\n1=str incr\n2=str decr\n3=const\n");
 printf("result: %d",a);
 return(0);
}
