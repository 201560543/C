#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#define MAX 500
char string[MAX];


void removewhitespace (char *stringptr, int length);
void main()
{
	FILE *fptr;
	char seq1[MAX]={"\0"},seq2[MAX]={"\0"};
	char ignore;
	int i=0,j=0,len,row,column,ma,misma,gap,s1,s2,s3,sc1,sc2,sc3,score;
	int scoringmatrix[MAX][MAX];
	char directionmatrix[MAX][MAX];
	fptr=fopen("FASTA.txt","r");
	fscanf(fptr,"%c",&ignore);
	while(ignore!='\n')
		fscanf(fptr,"%c",&ignore);


	//////Read Sequence 1  ////////////////
	while(ignore!='>')
	{
		fscanf(fptr,"%c",&ignore);
		seq1[i]=ignore;
		i++;
	}
	seq1[i-1]=NULL;
	len=strlen(seq1);
	removewhitespace(seq1,len);
	strcpy(seq1,string);
	for(i=0;i<MAX;i++)
	string[i]=NULL;
	len=strlen(seq1);
	printf("Sequence 1:\n%s",seq1);
	printf("\nlength=%d",len);
	row=len;


	////////////Read Sequence 2///////////
	while(ignore!='\n')
		ignore=getc(fptr);
	i=0;


	while(ignore!=EOF)
	{
		ignore=getc(fptr);
		seq2[i]=ignore;
		i++;
	}
	seq2[i-1]=NULL;
	len=strlen(seq2);
	removewhitespace(seq2,len);
	strcpy(seq2,string);
	len=strlen(seq2);
	printf("\n\nSequence 2:\n%s",seq2);
	printf("\nlength=%d",len);
	column=len;


	///////READ SCORING SCHEME (Input by user)///////////
	printf("\n\nEnter match score");
	scanf("%d",&ma);
	printf("Enter mis match score");
	scanf("%d",&misma);
	printf("Enter gap penalty");
	scanf("%d",&gap);




	////////INITIALIZATION////////////////////////
	printf("\nPress any key to initialize\n");
	getch();
	for(i=1;i<=row;i++)
	{
		j=j+gap;
		scoringmatrix[i][0]=j;
	}
	j=0;
	for(i=1;i<=column;i++)
	{
		j=j+gap;
		scoringmatrix[0][i]=j;
	}
	for(i=0;i<=row;i++)
	{
		for(j=0;j<=column;j++)
			printf("%d\t",scoringmatrix[i][j]);
		printf("\n");
    }


    ////////////FILL PROCESS///////////////////////
    printf("\n\nPress any key to fill\n");
    getch();
    for(i=1;i<=row;i++)
		for(j=1;j<=column;j++)
		{
			s1=scoringmatrix[i-1][j];
			s2=scoringmatrix[i-1][j-1];
			s3=scoringmatrix[i][j-1];
			sc1=s1+gap;
			if(seq1[i-1]==seq2[j-1])
				sc2=s2+ma;
			else
				sc2=s2+misma;
			sc3=s3+gap;
			
			if(sc2>=sc3&&sc2>=sc1)
			{
				directionmatrix[i][j]='d';
                scoringmatrix[i][j]=sc2;
            }
            else if(sc1>=sc2&&sc1>=sc3)
            {
                 directionmatrix[i][j]='u';
			    scoringmatrix[i][j]=sc1;
            }
			else
			{
                directionmatrix[i][j]='l';
				scoringmatrix[i][j]=sc3;
            }
		}
    for(i=0;i<=row;i++)
	{
		for(j=0;j<=column;j++)
			printf("%d\t",scoringmatrix[i][j]);
		printf("\n");
		score=scoringmatrix[row][column];
    }
    printf("Similarity Score = %d\n\n\n",score);
    score=0;
    ///////////TRACEBACK PROCESS///////////////////////
    i=row;
    j=column;
    printf("SEQ1\tSEQ2\tSCORE\n");
    while(j!=0&&i!=0)
    {
         if(directionmatrix[i][j]=='d')
         {
              printf("%c\t%c\t%d\n",seq1[i-1],seq2[j-1],scoringmatrix[i][j]);
              i--;
              j--;
              score=score+scoringmatrix[i][j];
         }
         else if(directionmatrix[i][j]=='u')
         {
              printf("%c\t_\t%d\n",seq1[i-1],gap); 
              i--;
              score=score+gap;
         }
         else if(directionmatrix[i][j]=='l')
         {
              printf("_\t%c\t%d\n",seq2[j-1],gap); 
              j--;
              score=score+gap;
         }
    }
    while(i!=0)
    {
        score=score+gap;
	printf("%c\t_\t%d\n",seq1[i-1],gap);
        i--;
    }
    while(j!=0)
    {
        score=score+gap;
	printf("_\t%c\t%d\n",seq2[j-1],gap);
        j--;
    }
    printf("\n\nFINAL SMILARITY SCORE: %d\n",score);
         
              
	getch();
}


void removewhitespace (char *stringptr, int length)
{
	int a,b=0;
	for(a=0;a<=length;a++)
	{
		if(!isspace(stringptr[a]))
		{
			string[b]=stringptr[a];
			b++;
		}
	}
	return;
}