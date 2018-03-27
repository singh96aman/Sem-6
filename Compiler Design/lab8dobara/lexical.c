#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char datatype[20][20] = {"int","char","float","double","long"};
int noofdatatype=5;
int sizeofdatatype[] = {4,1,4,8,8};
char keywords[40][20] = {"int","char","float","double","long","if","else","void","return","include","do","while","for","stdio","string","ctype","stdlib","NULL","FILE","switch","case","printf","main"};
int noofkeywords = 23;
char specialop[20][20] = {"==",">=","<=","!=","&&","||","++","--","+=","-=","*=","/=","%=","<<",">>"};
int noofspecialop=15;
char data[100][100]; //Contains only lexemes
int dataindex=0;

char symbols[20][20];
int symindex=0;
char func[20][20];
int funcindex=0;
int num[20];
int numindex=0;

typedef struct symbol{
	char name[50];
	char type[50];
	int size;
	int Scope;
	int noofarg;
	char arg[50];
	char ret[50];
}SYMBOL;

SYMBOL table[100];
int symboltableindex=0;

char *buf2;

int checkforSpecialop(char buf[100])
{
	int i=0;
	//printf("%s\n",buf);
	for(i=0; i<noofspecialop; i++)
		if(strcmp(buf,specialop[i])==0)
			break;
	if(i==noofspecialop)
		return -1;
	else
		return i;
}

int insertsymbol(char buf[100]){
	int i=0;
	for(i=0; i<symindex; i++)
		if(strcmp(buf,symbols[i])==0)
			break;
	if(i==symindex)
		strcpy(symbols[symindex++],buf);
	return i;
}

int checkkeywords(char buf[100]){
	int i=0;
	for(i=0; i<noofkeywords; i++)
		if(strcmp(buf,keywords[i])==0)
			break;
	if(i==noofkeywords)
		return -1;
	else
		return i;
}

int insertNumber(char buf[100]){
	int i, n = atoi(buf);
	//printf("%d\n",n);
	for(i=0; i<numindex; i++)
		if(n==num[i])
			break;
	if(i==numindex)
		num[numindex++] = n;
	return i;

}

int checkdataype(char buf[100]){
	int i=0;
	for(i=0; i<noofdatatype; i++)
		if(strcmp(buf,datatype[i])==0)
			break;
	if(i==noofdatatype)
		return -1;
	else
		return i;
}
char buf[100];
char* getNextToken(FILE *fp1)
{
	char c;
	// Start of Program

	c = getc(fp1);
	int i=0; //counter
	while(c!=EOF){
		// Skip text
		if(c==' ' || c=='\t'){
			while(c==' ' || c=='\t')
				c=getc(fp1);
			i=0;
		}
		// Print New Line
		else if(c=='\n'){
			//fprintf(fp2,"\n"); 
			c=getc(fp1);
			i=0;
		}
		// Ignore Literals
		else if(c=='"'){
			c=getc(fp1);
			while(c!='"')
				c=getc(fp1);
			c=getc(fp1);
			i=0;
		}
		// Check for special operator
		else if(c=='=' || c=='+' || c=='>' || c=='<' || c=='-' || c=='&' || c=='|' || c=='*' || c=='/' || c=='!' || c=='%' || c=='['){
			i=0;
			buf[i++]=c;
			c=fgetc(fp1);
			buf[i++]=c;
			buf[i]='\0';
			int index=checkforSpecialop(buf);
			if(index!=-1){
				//fprintf(fp2,"<%s>",buf); 
				return buf;
				c=getc(fp1);
				strcpy(data[dataindex++],buf);
				i=0;
				}
			else{
				//fprintf(fp2, "<%c>",buf[0]);
				buf[1]='\0';
				fseek(fp1,-1,SEEK_CUR);
				return buf;
				//printf("\n%s",buf);
				strcpy(data[dataindex++],buf);
				i=0;
			}
		}
		// Check for Identifiers
		else if(isalpha(c) || c=='_'){
			buf[i++]=c;
			c=fgetc(fp1);
			while(isalnum(c) || c=='_' ){
				buf[i++]=c;
				c=getc(fp1);
			}
			buf[i]='\0';
			//printf("\n%s",buf);
			//Check for keywords
			int index=checkkeywords(buf);
			if(index==-1){
				index=insertsymbol(buf);
				strcpy(data[dataindex++],buf);
				fseek(fp1,-1,SEEK_CUR);
				//printf("\nId : %s",buf);
				return "id";
				//fprintf(fp2, "<id,%d>",index+1);
			}else{
				//fprintf(fp2, "<%s>",buf);
				fseek(fp1,-1,SEEK_CUR);
				return buf;
				strcpy(data[dataindex++],buf);
			}
			i=0;
		}
		//Check for numbers
		else if(isdigit(c)){
			buf[i++]=c;
			c=fgetc(fp1);
			while(isdigit(c)){
				buf[i++]=c;
				c=getc(fp1);
			}
			buf[i]='\0';
			fseek(fp1,-1,SEEK_CUR);
			//InsertNumber
			int index=insertNumber(buf);
			strcpy(data[dataindex++],buf);
			return buf;
			//fprintf(fp2, "<num,%d>",index+1);
			i=0;
		}
		else{
			buf[i++]=c;
			buf[1]='\0';
			strcpy(data[dataindex++],buf);
			return buf;
			//fprintf(fp2,"<%c>",c);
			c=fgetc(fp1);
			i=0;
		}
	}
	return "end";
}