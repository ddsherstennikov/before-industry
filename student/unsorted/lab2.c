// this program code was made assuming "aaa...bbb...ccc" pattern
#include <stdio.h>
#include <string.h>
int w = 80;

//проверка по шаблону
int ok_pattern (char s[w])
{
 char pt[w];
 int i, j, n, l, b, Bl;                                                 //bl-проверка на шаблон частей строки, n -их к-во

 i=0; j=0; n=0; l = strlen(s); b=1;

 while(l>1)
{
  while ((s[i]!=46)&&(i<l-1)) i++;   
  strncpy(pt, s, i); pt[i]=0;                                        //printf("%s", pt);
  while ((s[i]==46)&&(i<l-1)) i++; 
  
  //считает нулевой символ в посл. куске - поэтому Bl обращается в 0
  Bl = ((strspn(pt, "abcdefghijklmnopqrstuvyxyz"))==(strlen(pt)));    //ABCDEFGHIJKLMNOPQRSTUVWXYZ
  n++; b= b*Bl;
//  printf(" Bl=%d \n", Bl);

  s = s+i; i = 0; l = strlen(s); 
}

  return ((n==3)&&(b));
}




int main()
{
 int fin=33; //'!' sign 
 char s[w];

 printf ("\npattern is [aaa...aaa...aaa]. \ninput ('!' to terminate): \n\n"); 

 fgets(s, w, stdin);
 ok_pattern(s);

 while (s[0] != fin)
{
 if  (ok_pattern(s)) {puts("yep!"); printf("%s\n", s);}
 else puts("nei.\n"); 
 
 fgets(s, w, stdin);
}

return 0;
}
