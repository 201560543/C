#include<stdio.h>
#include<string.h>
#include<conio.h>

void main(){
	FILE *fp;
	char c;
	int sc[100][100];
	char di[100][100]={"\0"};
	int i=0;
	int j=0;
	int score;
	int len;
	int len1;
	int len2;
	int count=-1;
	int ma=2;
	int mi=1;
	int gap=-1;
	char seq[2][1000];
	fp=fopen("sequence.fasta","r");
	c=getc(fp);
	while(c!=EOF){
		if(c=='>'){
			count++;
			i=0;
			while(c!='\n'){
				c=getc(fp);
			}
		}
			c=getc(fp);
			if(c!='\n' && c!=' ' && c!='>' && c!=EOF){
				seq[count][i]=c;
				i++;
			}
		}
		len1=strlen(seq[0]);
		len2=strlen(seq[1]);
		for(i=0;i<=(len1);i++){
			for(j=0;j<=(len2-2);j++){
				sc[i][j]=0;
			}
		}
		for(i=0;i<=(len1);i++){
			for(j=0;j<=(len2-2);j++){
				sc[0][j]=j*gap;
				di[0][j]='l';
			}
			sc[i][0]=i*gap;
			di[i][0]='t';
		}
		di[0][0]='n';
		for(i=0;i<=(len1);i++){
			for(j=0;j<=(len2-2);j++){
				printf("%d",sc[i][j]);
			}
			printf("\n");
		}
		for(i=1;i<=len1;i++){
			for(j=1;j<=(len2-2);j++){
				if(seq[0][i-1]==seq[1][j-1]){
					sc[i][j]=ma;
				}
				else{
					sc[i][j]=mi;
				}
			}
		}
		for(i=0;i<=(len1);i++){
			for(j=0;j<=(len2-2);j++){
				printf("%d",sc[i][j]);
			}
printf("\n");
		score=sc[i][j];
    }
    printf("Similarity Score = %d\n\n\n",score);
    score=0;
		}



    while (j!=0&&i!=0)
    {
	 if(di[i][j]=='d')
	 {
	      printf("%c\t%c\t%d\n",seq1[i-1],seq2[j-1],sc[i][j]);
	      i--;
	      j--;
	      score=score+sc[i][j];
	 }
	 else if(di[i][j]=='t')
	 {
	      printf("%c\t_\t%d\n",seq1[i-1],gap);
	      i--;
	      score=score+gap;
	 }
	 else if(di[i][j]=='l')
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




