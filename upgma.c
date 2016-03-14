#include <stdio.h>
#include <conio.h>
#define MAX 10
//#define TREE 10
#define SEQ 10
#define AA 20
int getarraynumber (char chararray[AA], char charachter);

void main()
{
	FILE *fptr, *blosum;
	int i,j,k,m,n,gap,len1,len2,s1,s2,s3,sc1,sc2,sc3,a,b,score,local;
	int smatrix[MAX][MAX],scores=0,o,p,dist[SEQ][SEQ];
	float fl1,fl2,fl3,outgroup,smatrix2[SEQ][SEQ];
	char filename[20]={"\0"};
	char aa[AA],ignore,seq[SEQ][MAX]={"\0"},dmatrix[MAX][MAX]={"\0"};
	int bmatrix[AA][AA],ig,count=-1,len[SEQ];
	for(i=0;i<SEQ;i++)
	for(j=0;j<SEQ;j++)
	{
        dist[i][j]=0;
        smatrix2[i][j]=0;
    }
	//////////READING BLOSUM_62 MATRIX///////////////////////
	//Read aminoacids//
	blosum=fopen("Blosum_62.txt","r");
	ignore=getc(blosum);
	i=0;
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
	getch();
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
		getch();
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
	printf("\n\nTotal Sequences=%d",count+1);
	for(i=0;i<=count;i++)
	{
		printf("\n\nSeq%d [Length=%d]:\n[%s]\n",i+1,strlen(seq[i]),seq[i]);
		len[i]=strlen(seq[i]);
    }
    len1=len[0];
	getch();
    //////////USER INPUT///////
	printf("\nInput gap penalty (constant) : ");
	scanf("%d",&gap);
	
////////////////////////////////////////////////////////////////////	
for(o=0;o<count;o++)
for(p=o+1;p<=count;p++)
{
	len1=len[o];
	len2=len[p];
	///////INITIALIZATION///////
	for(i=0;i<MAX;i++)
        for(j=0;j<MAX;j++)
			smatrix[i][j]=0;

	//////FILL STEP/////////////////////////////
	for(i=1;i<=len1;i++)
		for(j=1;j<=len2;j++)
		{
			s1=smatrix[i-1][j];
			s2=smatrix[i-1][j-1];
			s3=smatrix[i][j-1];
			sc1=s1+gap;
			sc3=s3+gap;
				a=getarraynumber(aa,seq[o][i-1]);
				b=getarraynumber(aa,seq[p][j-1]);
			sc2=s2+bmatrix[a][b];
			if(sc2>=sc3&&sc2>=sc1)
			{
				if(sc2<0)
				sc2=0;
				else
                dmatrix[i][j]='d';
				smatrix[i][j]=sc2;
			}
			else if(sc1>=sc2&&sc1>=sc3)
			{
		 		if(sc1<0)
				sc1=0;
				else
                dmatrix[i][j]='u';
				smatrix[i][j]=sc1;
			}
			else
			{
				if(sc3<0)
				sc3=0;
				else
                 dmatrix[i][j]='l';
				smatrix[i][j]=sc3;
			}
		}
	for(i=0;i<=len1;i++)
	{
		for(j=0;j<=len2;j++)
			printf("\t%d",smatrix[i][j]);
        	printf("\n");
	}
    local=0;
    for(i=0;i<=len1;i++)
    for(j=0;j<=len2;j++)
    {
	if(smatrix[i][j]>local)
	{
		local=smatrix[i][j];
		a=i;
		b=j;
	}
    }

    i=a;
    j=b;
    printf("score=%d and Traceback score=",smatrix[i][j]);
    
    /////////////////TRACEBACK//////////////////////////
    ///////////TRACEBACK PROCESS///////////////////////
	score=0;
	while(dmatrix[i][j]!='\0')
    {
         if(dmatrix[i][j]=='d')
         {
              score=score+(smatrix[i][j]-smatrix[i-1][j-1]);
              i--;
              j--;
         }
         else if(dmatrix[i][j]=='u')
         {
              i--;
              score=score+gap;
	 }
         else if(dmatrix[i][j]=='l')
         {
              j--;
              score=score+gap;
         }
	     else
	     {
              printf("\nERROR: directionmatrix\n");
	     }
    }
    printf("%d\n",score);
	dist[o][p]=score;
    dist[p][o]=score;	
}
printf("\nCount=%d",count);
printf("\nDistances\n");
for(i=0;i<=count;i++)
{
	for(j=0;j<=count;j++)
	printf("\t%d",dist[i][j]);
	printf("\n");
}
score=0;
for(i=count-1;i>=0;i--)
	score=dist[count][i]+score;
fl1=score;
fl2=count;
outgroup=fl1/fl2;
score=0;
fl1=0;
fl2=0;
for(i=0;i<count-1;i++)
{
    for(j=i+1;j<count;j++)
    {
        for(n=0;n<count;n++)
        if(n!=i && n!=j)
        score=score+dist[i][n];
        fl1=score;
        score=0;
        for(n=0;n<count;n++)
        if(n!=j && n!=i)
        score=score+dist[j][n];
        fl2=score;
        score=0;
        fl3=dist[i][j];
        fl3=fl3-(fl1+fl2);
        fl3=fl3/2;
        fl3=fl3+outgroup;
        smatrix2[i][j]=fl3;
        smatrix2[j][i]=fl3;
    }
}
printf("\n\nScoring Matrix 2\n");
for(i=0;i<count;i++)
{
    for(j=0;j<count;j++)
    printf("\t%f",smatrix2[i][j]);
    printf("\n");
}

getch();
}

int getarraynumber (char chararray[AA], char charachter)
{
	int i;
	for(i=0;i<AA;i++)
        if(charachter==chararray[i])
			return i;
}
