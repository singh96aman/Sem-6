#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main()
{
	FILE *fptr, *f2;
	fptr = fopen("input.txt","r");
	f2 = fopen("output.txt","w+");
	if(fptr==NULL)
		printf("\n Cannot open file");
	char keywords[6][50] = {"int","main","if","else","char","return"};
	char store[100][100];
	int storeindex=0;
	char buffer[50];
	char ca = getc(fptr);
	int index=0, i, k, flag=1, counter=1, counternum=1;
	while(ca!=EOF)
	{
		int flag=0;
		if(ca==' ' || ca=='(' || ca=='\n' || ca=='\t' || ca==';' || ca==')' || ca=='}' || ca=='>' || ca=='='|| ca=='<' || ca=='>'|| ca=='*'){
			buffer[index]='\0';
			printf("\n%s %c",buffer,ca);
			for(i=0; i<6; i++)
				if(strcmp(buffer,keywords[i])==0)
						{fprintf(f2,"<%s>",buffer); flag=1;}
			if(flag==0 && ca!='\n')
				{
					int flagtemp=0;
					if(buffer[0]>='0' && buffer[0]<='9')
						{fprintf(f2,"<num,%d>",counternum); counternum++;}
					else{
							int l=0;
							for(l=0; l<storeindex; l++)
								if(strcmp(store[l],buffer)==0)
									{fprintf(f2,"<id,%d>",l+2 ); flagtemp=1; break;}
							if(flagtemp==0)
								{fprintf(f2,"<id,%d>",counter); counter++; strcpy(store[storeindex],buffer); storeindex++;}
						}
				}
			//if(flag==0 && ca!='\n' && isdigit(buffer[0])==0)
			//	{fprintf(f2,"<num,%d>",counternum); counternum++;}
			if(ca==';')
				fprintf(f2,"<;>"); 
			else if(ca=='\n')
				fprintf(f2,"\n");
			else if(ca=='(')
				fprintf(f2,"<(>");
			else if(ca==')')
				fprintf(f2,"<)>");
			else if(ca=='{')
				fprintf(f2,"<{>");
			else if(ca=='}')
				fprintf(f2,"<}>");
			else if(ca=='=')
				fprintf(f2,"<=>");
			else if(ca=='<')
				fprintf(f2,"<<>");
			else if(ca=='>')
				fprintf(f2,"<>>");
			else if(ca=='*')
				fprintf(f2,"<*>");
			else 
				fprintf(f2,"%c",ca);
			index=0;		
			//index=0;
		}else{
			buffer[index++]=ca;
		}
		ca = getc(fptr);
	}
	fclose(fptr);
	return 0;
}