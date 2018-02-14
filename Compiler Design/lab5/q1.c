#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct symbol{
	char name[50];
	char types[50];
	int size;
	char Scope;
	int noofarg;
	char arg[50];
	char ret[50];
}SYMBOL;

int symindex=0;

int main()
{

	FILE *fp1, *fp2;
	SYMBOL sym[50];
	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");

	if(fp1==NULL || fp2==NULL)
		{
			printf("File not found.\n");
			exit(0);
		}

	char c;
	char buf[10];
	int ctr;
	char used [20][20];
	char lines[20][20];
	int li=0, lj=0;
	int numused[20];
	int usednumcur=0;
	int usedcur=0;
	char key [20][20]={"if", "else", "int", "num", "return", "int","printf"};

	c = fgetc(fp1);

	while(c!=EOF)
	{

		int i=0;
		buf[0]='\0';

		if(c == ' ') c=getc(fp1);

		else if(c == '\n'){fprintf(fp2, "\n");c=getc(fp1);}

		else if(c == '"')
		{
			c=getc(fp1);
			while(c != '"')
				c=getc(fp1);
			c=getc(fp1);
		}
		else if(c == '=')
		{
			buf[i++]=c;
			c=fgetc(fp1);
			if(c == '=')
			{
				buf[i++]=c;
				buf[i]='\0';
				fprintf(fp2, "<%s>", buf);
			}
			else
			{
				buf[i]='\0';
				fprintf(fp2, "<%s>", buf);
			}
		}
		else if(c == '<' || c == '>')
		{
			buf[i++]=c;
			c=fgetc(fp1);
			if(c == '=')
			{
				buf[i++]=c;
				buf[i]='\0';
				fprintf(fp2, "<%s>", buf);
			}
		}
		else if(c == '-')
		{
			buf[i++]=c;
			c=fgetc(fp1);
		}
		else if(c == '!')
		{
			buf[i++]=c;
			c=fgetc(fp1);
			if(c == '=')
			{
				buf[i++]=c;
				buf[i]='\0';
				fprintf(fp2, "<%s>", buf);
			}
			else
			{
				buf[i]='\0';
				fprintf(fp2, "<%s>", buf);
			}
		}
		else if((c>='A' && c<='Z') || (c>='a' && c<='z') || (c>='0' && c<='9'))
		{
			buf[i++]=c;
			c=fgetc(fp1);
			while((c>='A' && c<='Z') || (c>='a' && c<='z') || (c>='0' && c<='9'))
				{buf[i++]=c;c=fgetc(fp1);}
			buf[i]='\0';
			int keyflag=0;
			for(int k=0;k<7;k++)
			{	if(strcmp(buf, key[k])==0)
					{keyflag=1;break;}
			}

			if(keyflag==1)
				fprintf(fp2, "<%s>", buf);
			else
			{
				if(buf[0] >= '0' && buf[0] <= '9')
				{ 
					while(c>='0' && c<='9')
						{buf[i++]=c; c=fgetc(fp1);}
					int usedflag=0;int pos=0;
					for(int k=0;k<usednumcur;k++)
					{	if(numused[k]==atoi(buf))
						{usedflag=1;pos=k;break;}
					}
					if(usedflag==1)
						fprintf(fp2, "<num,%d>", pos+1);
					else
					{
						numused[usednumcur++]=atoi(buf);
						fprintf(fp2, "<num,%d>", usednumcur);
					}

				}
				else
				{
					int usedflag=0;int pos=0;
					for(int k=0;k<usedcur;k++)
					{	if(strcmp(buf, used[k])==0)
						{usedflag=1;pos=k;break;}
					}
					if(usedflag==1)
						fprintf(fp2, "<id,%d>", pos+1);
					else
					{
					strcpy(used[usedcur++], buf);
					fprintf(fp2, "<id,%d>", usedcur);
					}	
				}
			}
		}
		else
		{	fprintf(fp2, "<%c>", c);
			c=fgetc(fp1);
		}
	}
	fp1 = fopen("input.txt", "r");
	c=fgetc(fp1);

	char func[50][50];
	int funcindex=0;
	char args[50][50];
	int argsind=0;
	while(c!=EOF)
		{
			if(c == ' ' || c == '\n' || c == ';' || c == '(' || c == ')')
			{
				lines[li][lj]='\0';
				if(c == '(' || c == ' ')
					{
								strcpy(func[funcindex++],lines[li]);
					}
				if(c == ')')
				{
					 			strcpy(args[argsind++],lines[li]); 
				}
				li++;
				lj=0;
			}
			else
					lines[li][lj++]=c;
			c=fgetc(fp1);
		}


	//for(int k=0; k<usednumcur; k++)
	//	printf("\n%d",numused[k]);
	for(int k=0; k<usedcur; k++)
		printf("\n%s",used[k]);
	//printf("\n");
	//for(int k=0; k<li; k++)
	//	printf("\n%s",lines[k]);
	//printf("\n");
	//	for(int k=0; k<funcindex; k++)
	//	printf("\n--%s",func[k]);

	for(int k=0; k<usedcur; k++)
	{
		for(int j=0; j<li; j++)
			if(strcmp(used[k],lines[j])==0)
				{
					strcpy(sym[symindex].name,used[k]);
					int flag=0;
					for(int l=0; l<funcindex; l++)
						if(strcmp(func[l],used[k])==0)
							{flag=1; break;}
					if(flag==1)
						strcpy(sym[symindex].types,"FUNC");
					else
						strcpy(sym[symindex].types,lines[j-1]); 
					if(strcmp(sym[symindex].types,"int")==0)
						sym[symindex].size=4;
					else
						sym[symindex].size=0;
					symindex++;
					break;
					}
	}
	/*
	for(int k=0; k<symindex; k++)
		printf("\n  %s   %s    %d",sym[k].name,sym[k].types,sym[k].size);
	printf("\n");
	printf("\n");
	for(int k=0; k<argsind; k++)
		printf("\n----%s",args[k]);
	*/
	fclose(fp1);
	fclose(fp2);
return 0;   
}
				
					

				
				
		
			

	