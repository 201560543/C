#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define MAX 50		//maximum number of amino acids in a sequence//
#define AA 20		//Total number of amino acids//
#define SEQ 2		//Maximum number of sequences//
#define S 2       //Maximum number of randomized scores//
char string[MAX];

int getarraynumber (char chararray[21], char charachter);
int matcharray (int array[MAX], int charachter, int length);
void randomize (char stringptr[MAX], int length);
void main()
{
	FILE *fptr, *blosum, *scorefile;
	srand(time(NULL));
	char ignore,aa[AA],seq[SEQ][MAX]={"\0"},dmatrix[MAX][MAX]={"\0"};
	char filename[20]={"\0"};
	int bmatrix[AA][AA],smatrix[MAX+1][MAX+1];
	int i=0,j,ig,count=-1,len1,len2,scores[S],gap,a=0,b=0,s1,s2,s3,sc1,sc2,sc3,R,score;
getch();
	//////////READING BLOSUM_62 MATRIX///////////////////////
	//Read aminoacids//
	blosum=fopen("Blosum_62.txt","r");
	ignore=getc(blosum);
	while(ignore!='\t')
		ignore=getc(blosum);
	while(ignore!='\n')
	{
		if(ignore!='\t' && ignore!='\n')
			aa[i++]=ignore;
		ignore=getc(blosum);
	}
	//Read scores for aminoacids//
	for(i=0;i<AA;i++)
		for(j=0;j<AA+1;j++)
		{
			ignore=getc(blosum);
			if(ignore=='\n')
				break;
			else
			{
				fscanf(blosum,"%d",&ig);
				bmatrix[i][j]=ig;
			}
		}
	fclose(blosum);
	////////READING SEQUENCES//////////////////
	printf("Enter file name: ");
	fgets(filename,20,stdin);
	for(i=0;i<20;i++)
		if(filename[i]=='\n')
			filename[i]='\0';
	printf("\n[%s]\n",filename);
	if(!fopen(filename,"r"))
	{
		printf("Error: File cannot be opened!");
		return;
	}
	else
		fptr=fopen(filename,"r");
	ignore=getc(fptr);
	while(ignore!=EOF)
	{
		if(ignore=='>')
		{
			count++;
			i=0;
			while(ignore!='\n')
				ignore=getc(fptr);
		}
		ignore=getc(fptr);
		if(ignore!='\n' && ignore!=' ' && ignore!='>' && ignore!=EOF)
		{
			seq[count][i]=ignore;
			i++;
		}
	}
	len1=strlen(seq[0]);
	len2=strlen(seq[1]);
	printf("\nSEQ1 [%d]:\n%s\n\nSEQ2 [%d]:\n%s\n",len1,seq[0],len2,seq[1]);
	
	//////////USER INPUT///////
	printf("\nInput gap penalty (constant) : ");
	scanf("%d",&gap);
    scorefile=fopen("Scores.txt","w");
    fprintf(scorefile,"%d\n",S);
	for(R=0;R<S;R++) ////////RANDOMIZE FOR LOOP/////////////
    {
    len1=strlen(seq[0]);
	len2=strlen(seq[1]);
	printf("\nSEQ1 [%d]:\n%s\n\nSEQ2 [%d]:\n%s\n",len1,seq[0],len2,seq[1]);
	///////INITIALIZATION///////
	for(i=0;i<=len1;i++)
        for(j=0;j<=len2;j++)
			smatrix[i][j]=0;
	for(i=0;i<=len1;i++)
		for(j=0;j<=len2;j++)
		{
			smatrix[0][j]=j*gap;
			dmatrix[0][j]='l';
			smatrix[i][0]=i*gap;
			dmatrix[i][0]='u';
		}
	dmatrix[0][0]='n';

	////////FILL//////////////////////////
	for(i=1;i<=len1;i++)
		for(j=1;j<=len2;j++)
		{
			s1=smatrix[i-1][j];
			s2=smatrix[i-1][j-1];
			s3=smatrix[i][j-1];
			sc1=s1+gap;
			a=getarraynumber(aa,seq[0][i-1]);
			b=getarraynumber(aa,seq[1][j-1]);
			sc2=s2+bmatrix[a][b];
			sc3=s3+gap;
			if(sc2>=sc3&&sc2>=sc1)
			{
				dmatrix[i][j]='d';
				smatrix[i][j]=sc2;
            }
  		    else if(sc1>=sc2&&sc1>=sc3)
  		    {
		 		dmatrix[i][j]='u';
				smatrix[i][j]=sc1;
            }
			else
			{
 		        dmatrix[i][j]='l';
				smatrix[i][j]=sc3;
            }
		}
	/*for(i=0;i<=len1;i++)
	{
		for(j=0;j<=len2;j++)
			printf("\t%d",smatrix[i][j]);
        printf("\n");
    }*/
	
    printf("score=%d",smatrix[len1][len2]);
    
    
    /////////////////TRACEBACK//////////////////////////
    ///////////TRACEBACK PROCESS///////////////////////
    i=len1;
    j=len2;
    score=0;
    printf("SEQ1\tSEQ2\tSCORE\n");
    while(dmatrix[i][j]!='n')
    {
         if(dmatrix[i][j]=='d')
         {
              printf("%c\t%c\t%d\n",seq[0][i-1],seq[1][j-1],smatrix[i][j]-smatrix[i-1][j-1]);
              score=score+(smatrix[i][j]-smatrix[i-1][j-1]);
              i--;
              j--;
         }
         else if(dmatrix[i][j]=='u')
         {
              printf("%c\t_\t%d\n",seq[0][i-1],gap); 
              i--;
              score=score+gap;
	 }
         else if(dmatrix[i][j]=='l')
         {
	          printf("_\t%c\t%d\n",seq[1][j-1],gap);
              j--;
              score=score+gap;
         }
	 else
	 {
		printf("\nERROR: directionmatrix\n");
	 }
    }
    ///////////////////////RANDOMIZE////////////////////////
    scores[R]=smatrix[len1][len2];
    fprintf(scorefile,"%d\n",scores[R]);
    randomize(seq[0],len1);
    strcpy(seq[0],string);
    randomize(seq[1],len2);
    strcpy(seq[1],string);
    }
    for(R=0;R<S;R++)
    printf("\n%d",scores[R]);
    
	getch();
}

int getarraynumber (char chararray[AA], char charachter)
{
	int i;
	for(i=0;i<AA;i++)
        if(charachter==chararray[i])
			return i;
}

void randomize (char stringptr[MAX], int length)
{
	int i,x;
	int array[MAX];
	for(i=0;i<MAX;i++)
	string[i]='\0';
	for(i=0;i<length;i++)
	{
		x=rand();
		x=x%length;
		while(matcharray(array,x,length)!=0)
		{
			x=rand();
		    x=x%length;
        }
        array[i]=x;
		string[i]=stringptr[x];
	}
}

int matcharray (int array[MAX], int charachter, int length)
{
	int i;
	for(i=0;i<length;i++)
        if(charachter==array[i])
			return 1;
	return 0;
}
