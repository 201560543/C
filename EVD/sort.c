#include <stdio.h>
#include <conio.h>

void main()
{
          FILE *fptr,*fptr2;
          int i,S,scores[10],ig,swap,j;
          char c;
          fptr=fopen("Scores.txt","r");
          fscanf(fptr,"%d",&S);
          printf("%d",S);
          for(i=0;i<S;i++)
          {
               fscanf(fptr,"%d",&ig);
               printf("%d\t",ig);
               scores[i]=ig;
          }
          fclose(fptr);
          ig=scores[0];
          for(j=0;j<S;j++)
               for(i=1;i<S;i++)
               {
                         if(scores[i]>scores[i-1])
                         {
                              swap=scores[i];
                              scores[i]=scores[i-1];
                              scores[i-1]=swap;
                              printf("test");
                         }
               }
          fptr2=fopen("Scores.txt","w");
          for(i=0;i<S;i++)
               fprintf(fptr2,"%d\n",scores[i]);    
          getch();
}     
