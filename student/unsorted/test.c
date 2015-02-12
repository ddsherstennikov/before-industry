#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
 char **args;
 char *s;
 char *str;
 
 *args = "hello world";
 args++;
 *args = "goodbye world";
 args--;

 puts(*args);
 puts(*(args + 1));

 s = *args;
 str = (char *) malloc( (strlen(s)+1) * sizeof(char) );
 strcpy(str, s);
 puts(s);
}