#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char keywords[40][40]={"int","char","float","double","long","main","return","else","if","printf"};
int noofkeywords=10;
char data[40][40]={"int","char","float","double","long"};
int noofdata=5;

int checkData(char buf[100]){
	int i=0;
	for(i=0; i<noofdata; i++)
		if(strcmp(data[i],buf)==0)
			return 1;
	return 0;
}

void checkFunction(FILE *f1, char buf[100]){
	long n = ftell(f1);
	char temp[100];
	int i=0;
	//printf("%s",buf);
	while(buf[i]!=' ' && buf[i]!='\0')
		{temp[i]=buf[i]; i++;}
	temp[i]='\0';
	if(checkData(temp))
		printf(" Return Type : %s", temp);
}

int main(){
	char file1[50], file2[50];
	FILE * f1, *f2;
	printf("\n Enter file 1 : ");
	scanf("%s",file1);
	printf("\n Enter file 2 : ");
	scanf("%s",file2);
	f1 = fopen(file1, "r");
	f2 = fopen(file2, "w+");
	if(!f1 || !f2){
		printf("\n Wrong file !");
		exit(0);
	}
	char c = fgetc(f1);
	char buf[100];
	int i=0;

	while(c!=EOF){
		if(c==' '){
			fputc(c,f2);
			c=fgetc(f1);
			while(c==' ')
				c=fgetc(f1);
		}
		else if(c=='\t'){
			fputc(c,f2);
			c=fgetc(f1);
			while(c=='\t')
				c=fgetc(f1);
		}
		else if(c=='#'){
			c=getc(f1);
			while(c!='\n')
				c=fgetc(f1);
			putc('\n',f2);
			c=fgetc(f1);
		}
		else if(c=='('){
			printf("\n %s ",buf);
			while(c!='\n' && c!='\t'){
				c=fgetc(f1);
				fseek(f1, -2, SEEK_CUR);
			}
			fseek(f1, 2, SEEK_CUR);
			c=fgetc(f1);
			while(c!='('){
				buf[i++]=c;
				c=fgetc(f1);
			}
			fputc(c,f2);
			c=fgetc(f1);
			buf[i]='\0';
			checkFunction(f1, buf);
			i=0;
		}
		else{
			buf[i++]=c;
			c=fgetc(f1);
			while(c!=' ' && c!='(' && c!=EOF && c!='\t' && c!='\n'){
				buf[i++]=c;
				c=fgetc(f1);
			}
			buf[i]='\0';
			int j=0;
			for(j=0; j<noofkeywords; j++)
				if(strcmp(keywords[j],buf)==0){
					int k=0;
					for(k=0; buf[k]!='\0'; k++)
						buf[k]-=32;
					break;
				}
			fprintf(f2,"%s",buf);
			i=0;
		}
	}
	fclose(f1);
	fclose(f2);
}