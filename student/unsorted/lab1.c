//test input and output through standard i/o streams
#include <stdio.h>
#include <math.h>

int l = 26;

int main()
{
  int fin, i, j, c, sum;
  int m[l];  
  float proz, f1, f2;

 for (i=0;i<=l-1;i++) m[i]=0;

 while ((c = fgetc(stdin)) != EOF) 
{
  if((c>='A')&&(c<='Z')) m[c-'A']++;
  if((c>='a')&&(c<='z')) m[c-'a']++;
}

 sum = 0; 
 for(i=0;i<=l-1;i++) sum += m[i];
 
 for (i=0;i<=l-1;i++) 
{
 f1=(float)(m[i]); 
 f2=(float)(sum);
 proz = (f1/f2)*100.;
 printf ("%c  %02.1f    ", (65+i), proz);
 putc('%', stdout);
 printf("   "); 
 for (j=1;j<=m[i];j++) putc('*', stdout);
 puts ("");
}

 return 0;
}

