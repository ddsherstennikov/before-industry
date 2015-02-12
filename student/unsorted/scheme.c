#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a,b) ((a)>(b) ? (a) : (b))
#define min(a,b) ((a)<(b) ? (a) : (b))
#define not(a) 1-a

/* структура, моделирующая вентиль */
struct gate {
    int id;                //number
    struct gate * dep[2];  //pointer to 0, 1 or 2 other gates on which this depends
    struct gate * next;    //pointer to the next gate in the list (of gates of the same level) 
    int val;               //value = 0 or 1
    char type;             //type = '&','|','~','>'(output) or '<'(input)	
};

/* newitem: создать новый элемент по полям id, val, type*/
struct gate *newitem(int id, int val, char type)
{
    struct gate *newp;
	newp = (struct gate*) malloc(sizeof(struct gate));
    newp->id = id;
	newp->val = val;
	newp->type = type;
	newp->dep[0] = newp->dep[1] = newp->next = NULL;
	return newp;
}	

/* addfront: добавить элемент в начало списка */
struct gate *addfront(struct gate *listp, struct gate * newp)
{
 newp->next = listp;
 return newp;
}

/* lookup: найти в списке элемент с эл-т.id == id */
struct gate *lookup(struct gate *listp, int id)
{
 for( ; listp != NULL; listp = listp->next)
    if (id == listp->id) return listp;
 return NULL; /* нет совпадений */ 
}

/* split: разбить строку s в массив подстрок, c - разделитель */
/*
char** split(char* s, char c, int *cargs)
{
 char** args;
 char* ts = " ";
 char tmps[100];
 int i = 0;
 
 while(ts != NULL)
     {*/
	  //ts = strchr(s,c);               /*занести в ts подстроку s, нач-ся с 1го вхождения c в s*/   
      //int n = strlen(s) - strlen(ts); /*получить число символов в s-ts (нужной подстроке s)*/
	  //strncpy(tmps, s, n);            /*занести в tmps (типа const char*) подстроку s равную s-ts*/
	  //tmps[n] = '\0';                 /*поставить символ конца строки*/
	  //strcpy(args[i], tmps);          /*занести в очередную строку массива строк args сегмент tmps*/
	  /*puts("!");
	  i++;
	 } 
 i--; 
 cargs = &i;	 
 return args;
}
*/

void main(int argc, char* argv[])
{
 /* char** args;
	int cargs;
	int i;    */
	
	/*char *s;
	char c = '?';*/
	
    struct gate * SCHEME[6];
    struct gate * gtlist;
    int i=0; 
	int n;
 
   //INPUT//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /* 
   while ((c = getchar()) != '\n') 
	    {
		 if (c != ' ') 
		     {
			  s[i] = c;
			  i++;
			  //putchar(c);
			 } 
		 else for(j=0;j<=i;j++) putchar('-');
		}
   */ 
 	/*args = split("hi.my.name.is.denis", '.', &cargs);
    for(i=0;i<cargs;i++) puts(args[i]);*/
	
	int x[] = {3,0,0,0};
    int n_lvl = 6;
	
    /*level 0*/
	gtlist = NULL;
	gtlist = addfront(gtlist, newitem(16,-1,'>'));
    gtlist = addfront(gtlist, newitem(17,-1,'>'));
	SCHEME[0] = addfront(gtlist, newitem(18,-1,'>'));
	/*level 1*/	
	gtlist = NULL;
	gtlist = addfront(gtlist, newitem(10,-1,'&')); gtlist->dep[0] = lookup(SCHEME[0], 17); gtlist->dep[1] = lookup(SCHEME[0], 18);
    gtlist = addfront(gtlist, newitem(4,-1,'~')); gtlist->dep[0] = lookup(SCHEME[0], 18);
	gtlist = addfront(gtlist, newitem(3,-1,'~')); gtlist->dep[0] = lookup(SCHEME[0], 17);
	gtlist = addfront(gtlist, newitem(2,-1,'~')); gtlist->dep[0] = lookup(SCHEME[0], 16);
	SCHEME[1] = addfront(gtlist, newitem(1,-1,'&')); SCHEME[1]->dep[0] = lookup(SCHEME[0], 16); SCHEME[1]->dep[1] = lookup(SCHEME[0], 17);
	/*level 2*/
	gtlist = NULL;
	gtlist = addfront(gtlist, newitem(5,-1,'&')); gtlist->dep[0] = lookup(SCHEME[1], 1); gtlist->dep[1] = lookup(SCHEME[1], 4);
    gtlist = addfront(gtlist, newitem(6,-1,'&')); gtlist->dep[0] = lookup(SCHEME[1], 2); gtlist->dep[1] = lookup(SCHEME[1], 3);
	gtlist = addfront(gtlist, newitem(7,-1,'&')); gtlist->dep[0] = lookup(SCHEME[1], 3); gtlist->dep[1] = lookup(SCHEME[1], 4);
	SCHEME[2] = addfront(gtlist, newitem(9,-1,'&')); gtlist->dep[0] = lookup(SCHEME[1], 3); gtlist->dep[1] = lookup(SCHEME[0], 18);
	/*level 3*/
	gtlist = NULL;
	gtlist = addfront(gtlist, newitem(8,-1,'&')); gtlist->dep[0] = lookup(SCHEME[2], 6); gtlist->dep[1] = lookup(SCHEME[0], 18);
    gtlist = addfront(gtlist, newitem(11,-1,'|')); gtlist->dep[0] = lookup(SCHEME[1], 10); gtlist->dep[1] = lookup(SCHEME[2], 7);
	SCHEME[3] = addfront(gtlist, newitem(20,-1,'<')); gtlist->dep[0] = lookup(SCHEME[2], 9); 
	/*level 4*/
	gtlist = NULL;
	gtlist = addfront(gtlist, newitem(12,-1,'&')); gtlist->dep[0] = lookup(SCHEME[1], 1); gtlist->dep[1] = lookup(SCHEME[3], 11);
	SCHEME[4] = addfront(gtlist, newitem(13,-1,'&')); gtlist->dep[0] = lookup(SCHEME[3], 11); gtlist->dep[1] = lookup(SCHEME[1], 2);
	/*level 5*/
	gtlist = NULL;
	gtlist = addfront(gtlist, newitem(14,-1,'|')); gtlist->dep[0] = lookup(SCHEME[2], 5); gtlist->dep[1] = lookup(SCHEME[4], 13);
	SCHEME[5] = addfront(gtlist, newitem(15,-1,'|')); gtlist->dep[0] = lookup(SCHEME[3], 8); gtlist->dep[1] = lookup(SCHEME[4], 12);
	/*level 6*/
	gtlist = NULL;
	gtlist = addfront(gtlist, newitem(19,-1,'<')); gtlist->dep[0] = lookup(SCHEME[5], 14);
	SCHEME[6] = addfront(gtlist, newitem(21,-1,'<')); gtlist->dep[0] = lookup(SCHEME[5], 15);
	
	//CALCULATION///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	gtlist = SCHEME[0];
    while(gtlist != NULL)
        {
		 n = gtlist->id - 15;
		 gtlist->val = x[n];
		 gtlist = gtlist->next;
		}		

	for(i=1;i<=n_lvl;i++)   //changin` levels
        {
		 gtlist = SCHEME[i];
		 puts("!");
		 while (gtlist != NULL)
		     {
			  puts("*");
			  switch (gtlist->type)
		          {
		           case '&': gtlist->val = max(gtlist->dep[0]->val,gtlist->dep[1]->val); break;
                   case '|': gtlist->val = min(gtlist->dep[0]->val,gtlist->dep[1]->val); break;
			       case '~': gtlist->val = not(gtlist->dep[0]->val); break;	
			       case '<': gtlist->val = gtlist->dep[0]->val; break;
			       default : gtlist->val = -1; break;
			      }
		      gtlist = gtlist->next;
			 } 
	    }
	
    //OUTPUT/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	gtlist = SCHEME[n_lvl];
	while(gtlist != NULL)
	    {
		 printf("%d\n", gtlist->val);	
		 gtlist = gtlist->next;
		}
		
}





























