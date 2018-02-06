#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{

	FILE *fp1, *fp2;

	fp1 = fopen("Input.txt", "r");
	fp2 = fopen("Output.txt", "w");

	if(fp1==NULL || fp2==NULL)
		{
			printf("File not found.\n");
			exit(0);
		}

	char c;
	char buf[10];
	int ctr;
	char used [20][20];
	int usedcur=0;
	char key [20][20]={"if", "else", "int", "num", "return", "int"};

	c = fgetc(fp1);

	while(c!=EOF)
	{
		int i=0;
		buf[0]='\0';

		if(c==' ') c=getc(fp1);

		else if(c=='\n'){fprintf(fp2, "\n");c=getc(fp1);}
		
		else if(c=='=')
		{
			buf[i++]=c;
			c=fgetc(fp1);
			if(c=='=')
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
		else if(c=='<'||c=='>')
		{
			buf[i++]=c;
			c=fgetc(fp1);
			if(c=='=')
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
		else if(c=='!')
		{
			buf[i++]=c;
			c=fgetc(fp1);
			if(c=='=')
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
		else if((c>='A' &&c <='Z')||(c>='a' &&c <='z'))
		{
			buf[i++]=c;
			c=fgetc(fp1);
			while((c>='A' && c<='Z')||(c>='a' && c<='z')||(c>='0' && c<='9'))
				{buf[i++]=c;c=fgetc(fp1);}
			buf[i]='\0';
			int keyflag=0;
			for(int k=0;k<6;k++)
			{	if(strcmp(buf, key[k])==0)
					{keyflag=1;break;}
			}

			if(keyflag==1)
					fprintf(fp2, "<%s>", buf);
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
		else
		{	fprintf(fp2, "<%c>", c);
			c=fgetc(fp1);
		}
	}
	fclose(fp1);
	fclose(fp2);
return 0;
}
				
					

				
				
		
			

	
