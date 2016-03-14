#include <stdio.h>
#include <string.h>
#define AA 20		
void main()
{
	FILE *fptr, *blosum;
	char ignore,aa[AA];
	int bmatrix[AA][AA];
	int i=0,j,ig,len1,len2;
	//////////READING BLOSUM_62 MATRIX///////////////////////
	//Read aminoacids//
	blosum=fopen("blosum62.txt","r");
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
	for(i=0;i<AA;i++)
	{
		for(j=0;j<AA;j++)
		printf("%d ",bmatrix[i][j]);
		printf("\n");
	}
}
	
