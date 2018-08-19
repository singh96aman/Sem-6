#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char datatype[10][40]={"int","char","double","long","float"};
int noofdatatype=5;
int size[10]={4,1,8,8,4};
char keywords[40][40]={"if","else","return","include","for","while","struct","enum","NULL","FILE","switch","case","include","void","string","break","sizeof","do"};
int noofkeywords=18;
char op[20]={'=','+','-','%','/','&','|','<','>','!'};
int noofop=10;
char spop[20][20]={"==","+=","-=","*=","/=","%=","++","--","!=","&&","||","<=",">="};
int noofspop=13;
char delim[20]={' ','+','-','*','/',',',';','>','<','=','[',']','(',')','{','}'};
int noofdelim=16;
char data[200][50];
int dataindex=0;

// Skip text, Print New Line, Ignore Literals, Check for special operator
//Check for Identifiers, Check for keywords, Check for numbers, Insert keywords, Insert Numbers

typedef struct hash{
	char name[100];
	char type[100];
	int size;
	char scope;
	char arguments[100];
	char rey[100];
}*HASH;

enum State {Working = 1, Failed = 0}; 

HASH symbol[126];


int checkOp(char c){
	int i;
	for(i=0; i<noofop; i++)
		if(op[i]==c)
			return i;
	return -1;
}

int checkSpOp(char buf[10]){
	int i;
	for(i=0; i<noofspop; i++)
		if(strcmp(buf,spop[i])==0)
			return i;
	return -1;
}

int checkDelim(char c){
	int i;
	for(i=0; i<noofdelim; i++)
		if(c==delim[i])
			return i;
	return -1;
}

int checkKeywords(char buf[100]){
	int i;
	for(i=0; i<noofkeywords; i++)
		if(strcmp(buf,keywords[i])==0)
			return i;
	return -1;
}

int checkDatatype(char buf[100]){
	int i;
	for(i=0; i<noofdatatype; i++)
		if(strcmp(buf,datatype[i])==0)
			return i;
	return -1;
}

int searchVal(char buf[100]){
	int i, hashval=buf[0]-'a';
	if(symbol[hashval]!=NULL){
		if(strcmp(symbol[hashval]->name, buf)==0)
			return hashval;
	}
	for(i=hashval; i<126; i++)
		if(symbol[i]!=NULL){
			if(strcmp(symbol[i]->name, buf)==0)
				return i;
		}
	for(i=0; i<hashval; i++)
		if(symbol[i]!=NULL){
			if(strcmp(symbol[i]->name, buf)==0)
			return i;
		}
	return -1;
}

int searchEmpty(char buf[100]){
	int hashval=buf[0]-'a';
	if(symbol[hashval]==NULL){
		return hashval;
	}else{
		int i=0;
		for(i=hashval; i<126; i++)
			if(symbol[i]==NULL)
				return i;
		for(i=0; i<hashval; i++)
			if(symbol[i]==NULL)
				return i;
	}
	return 0;
}

int insert(char buf[100]){
	int i, j, hashval=searchEmpty(buf);
	symbol[hashval] = (struct hash *) malloc(sizeof(struct hash *));
	strcpy(symbol[hashval]->name,buf);
	for(i=0; i<dataindex; i++)
		if(strcmp(data[i],buf)==0){
			j=i-1;
			while(j>=0){
				if(checkDatatype(data[j])!=-1){
					strcpy(symbol[hashval]->type,data[j]);
					int l = checkDatatype(data[j]);
					symbol[hashval]->size = size[l];
					break;
				}
				j--;
			}
			j=i-1;
			symbol[hashval]->scope='G';
			while(j>=0){
				if(strcmp(data[j],"{")==0){
					symbol[hashval]->scope='L';
					break;
				}
				if(strcmp(data[j],"}")==0){
					symbol[hashval]->scope='G';
					break;
				}
				j--;
			}
			break;
		}
	return hashval;
}

void print(){
	int i=0;
	for(i=0; i<126; i++)
		if(symbol[i]!=NULL){
			printf("\n %d %s %s %d %c\n",i,symbol[i]->name,symbol[i]->type,symbol[i]->size,symbol[i]->scope);
		}
}

int main()
{
	FILE *f1, *f2;
	f1 = fopen("input.txt","r");
	f2 = fopen("output.txt","w+");
	char c =getc(f1);
	int i=0;
	char buf[100];
	while(c!=EOF){
		if(c==' ' || c=='\t'){
			while(c==' ' || c=='\t')
				c=fgetc(f1);
			i=0;
		}else if(c=='\n'){
			fputc(c,f2);
			c=fgetc(f1);
			while(c=='\n')
				c=fgetc(f1);
			i=0;
		}else if(c=='"'){
			c=fgetc(f1);
			while(c!='"')
				c=fgetc(f1);
			c=fgetc(f1);
			i=0;
		}else if(checkOp(c)!=-1){
			buf[i++]=c;
			c=fgetc(f1);
			buf[i++]=c; buf[i]='\0';
			if(checkSpOp(buf)!=-1){
				fprintf(f2,"<%s>",buf);
				i=0;
				c=fgetc(f1);
			}else{
				buf[1]='\0';
				fprintf(f2,"<%s>",buf);
				i=0;
			}
			strcpy(data[dataindex++],buf);
		}else if(isalpha(c) || c=='_'){
			buf[i++]=c;
			c=fgetc(f1);
			while(isalnum(c) || c=='_'){
				buf[i++]=c;
				c=fgetc(f1);
			}
			buf[i]='\0';
			strcpy(data[dataindex++],buf);
			if(checkDatatype(buf)==-1 && checkKeywords(buf)==-1){
				int ch = searchVal(buf);
				if(ch!=-1)
					fprintf(f2,"<id,%d>",ch);
				else{
					ch=insert(buf);
					fprintf(f2,"<id,%d>",ch);
				}
			}else
				fprintf(f2,"<%s>",buf);
			i=0;
		}else if(isdigit(c)){
			buf[i++]=c;
			c=fgetc(f1);
			while(isdigit(c)){
				buf[i++]=c;
				c=fgetc(f1);
			}
			buf[i]='\0';
			fprintf(f2,"<%s>",buf);
			strcpy(data[dataindex++],buf);
			i=0;
		}
		else{
			//printf("\n%c",c);
			buf[i++]=c;
			buf[i]='\0';
			fprintf(f2,"<%s>",buf);
			strcpy(data[dataindex++],buf);
			c=fgetc(f1);
			i=0;
		}

	}
	fclose(f1);

	//print();
}