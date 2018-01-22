%{
	int words=0;
	int blanks=0;
	int lines=0;
%}
%%
\n lines++;
[^ \t\n]+ words++;
. blanks++;
%%
int main()
{
	yylex();
	printf("\n lines : %d\n Blanks : %d\n Words : %d\n",lines,blanks,words);
	return 0;
}

int yywrap(){
	return 1;
}