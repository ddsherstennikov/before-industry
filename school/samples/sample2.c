#include <stdio.h>
#include <stdlib.h>

int main(void)
{double **A;
 FILE *f;
 int i,j,n;
 
 f=fopen("seq.c","r");
 fscanf(f,"%d",&n);
 A=(double**)malloc(n*sizeof(double*));
 for(i=0;i<n;i++) A[i]=(double*)malloc(n*sizeof(double));

 for (i=0;i<n;i++)
 for (j=0;j<n;j++)
 {fscanf(f,"%lg",&A[i][j]);}

 for (i=0;i<n;i++)
 {
 for (j=0;j<n;j++) printf("%lg  ",A[i][j]);
 puts("\n");
 }

 return(0); 
}
