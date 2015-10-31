#include <stdio.h>
#include <stdlib.h>

double* funk(double *a,int l);

double* funk(double *a,int l)
{double tmp;
 int i,s;

 if(l%2==0) 
 {for(i=1;i<=l/2;i++) {s=l-1-2*(i-1);tmp=*(a+s);*(a+s)=*a;*a=tmp;a++;}
  a=a-l/2;}
 
 else
 {for(i=1;i<=(l-1)/2;i++) {s=l-1-2*(i-1);tmp=*(a+s);*(a+s)=*a;*a=tmp;a++;}
  a=a-(l-1)/2;} 
  
 return(a);
}

int main(void)
{FILE *f;
 double *a;
 int l,i;	
 
 f=fopen("seq.c","r");	
  
 fscanf(f,"%d",&l);
 printf("length is: %d",l);
 a=(double*)malloc(l*sizeof(double)); 
 
 if((l<0)||(l==0)) puts("input error"); 
 else
 {	 
 for(i=1;i<=l;i++) {fscanf(f,"%lg",a);a++;}
  
 a=a-l;
 puts("\n\nthe massive was:");
 for(i=1;i<=l;i++) {printf("%lg\n",*a);a++;}  
 a=a-l;
 
 a=funk(a,l);
 
 puts("\n\nthe new massive:");
 for(i=1;i<=l;i++) {printf("%lg\n",*a);a++;}  
 
 fclose(f);}
 return(0);
}
