#include<stdio.h>
void main(){
	FILE *fp,*fopen();
	char c;
	int i=0;
	int j=0;
	char seq[1000];
	fp=fopen("test.fasta","r");
	c=getc(fp);
	while(c!=EOF){
		if(c=='>'){
			while(c!='\n'){
				c=getc(fp);
			}
		}
		if(c!='\n' && c!=' '){
			seq[i]=c;
			i++;
		}
		c=getc(fp);
	/*putc(c,stdout);*/
	}
	for(j=0;j<i;j++){
		putc(seq[j],stdout);
	}
}
