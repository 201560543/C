#include<stdio.h>
void reverse (const char*const sptr);
int main (void)
{
char sentence[80];
printf("enter a line \n");
fgets(sentence,80,stdin);
printf("\n the line is\n");
reverse(sentence);
return 0;
}
void reverse (const char*const sptr)
{
if (sptr [0]=='\0')
{
return;}
else
{
reverse (&sptr[1]);
putchar(sptr[0]);
}
}
