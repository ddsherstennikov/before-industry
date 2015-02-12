#include <stdio.h>
#include <string.h>

 char cell = 'i';

int change(int m[3][3]) 
{
 int i, j, n=0;
 int fall=0, rise=0;
 
 for(i=0;i<=2;i++)  
 for(j=0;j<=2;j++)
 n += (m[i][j] == cell); 
 if(m[1][1] == cell) n--;
            
 fall = ( (m[1][1] == cell) && ((n < 2)||(n > 3)) ); 
 rise = ( (m[1][1] == '.') && (n == 3) );

 if ( (fall) || (rise) ) return 1;
                    else return 0; 

}


int main(int argc, char* argv[])
{
 int err;                                                        //0 = no error, 1 =  error
 int i, j, ii, jj, I, J;                                        //ii,jj,I,J - params to get nh
 int h, w, t;                       
 int c;                                                            //char variable 4input
 int b;                                                              //boolean 4tests







 //get params

 c = argv[1][1]; if(c != 't') err=1;
 c = argv[2][1]; if(c != 'h') err=1;
 c = argv[3][1]; if(c != 'w') err=1;


 t = argv[1][2]-'0';                                             //t = 1 if tor, 0 if rectangle
 h = argv[2][2]-'0';
 w = argv[3][2]-'0';

 if((t!=0)&&(t!=1)) err=1;
 if((h<3)||(h>25)) err=1;
 if((w<3)||(w>25)) err=1;

 if(err == 1) printf("\nparameters declined.");
 else {

 int L[h][w];
 int R[h][w];
 int nh[3][3] = { '.', '.', '.',
                  '.', '.', '.',
                  '.', '.', '.'  };





 //get data

 i=0; j=0; err=0;
 while ((c = fgetc(stdin)) != EOF) 
 {
  if (((c == '\n') + (j == w)) == 1) 
   {err=1; break;}            //line shorter or longer then w => error
  if(j == w) {j=0; i++;}                             //ok line => go to a new one
  if(i == h) {err=1; break;}  //input is more then h lines long => error

  L[i][j] = c;

  if(c != '\n') j++; 
 }

 if(err) printf("\ninput does not fit your parameters.");
 else {

 


 //step

 i=0; j=0;
 for(i=0;i<=h-1;i++)
 for(j=0;j<=w-1;j++)
 {
  


  //get nh (3x3 neighbourhood of L[i][j])
  
  if(t) {
  for(ii=i-1;ii<=i+1;ii++)  
  for(jj=j-1;jj<=j+1;jj++)  
   {
    I=ii; 
    J=jj;
   
    if (I<0) I=h-1; else if (I>h-1) I=0;
    if (J<0) J=w-1; else if (J>w-1) J=0;
    
    nh[ii-(i-1)][jj-(j-1)] = L[I][J];
   }     }

  if(!t) {
  for(ii=i-1;ii<=i+1;ii++)  
  for(jj=j-1;jj<=j+1;jj++)  
   {
    I=ii; J=jj;
 
    if ((I<0)||(I>h-1)||(J<0)||(J>w-1)) 
    nh[ii-(i-1)][jj-(j-1)] = '.';
    else
    nh[ii-(i-1)][jj-(j-1)] = L[I][J];
   }     }





  //update R[i][j]
  b = change(nh);
  if(!b) R[i][j]=L[i][j];
  else {if (L[i][j]=='.') R[i][j]=cell; if (L[i][j]==cell) R[i][j]='.';}




 }

 



 for(i=0;i<=h-1;i++) {for(j=0;j<=w-1;j++) fputc(R[i][j], stdout); fputc('\n', stdout);}


 
 } }                                           //"if (error) else" `s end 
 return 0;
}

