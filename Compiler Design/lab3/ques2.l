%{
int words=0;
int characters=0;
int blanks=0;
int lines=0;
%}
%%
\n {lines++; words++;}
[' '] {blanks++; words++;}
. characters++;
%%
int main()
{
	yylex();
	printf("\nLines : %d\n Blanks : %d\n Characters : %d\n Words : %d",lines,blanks,characters,words);
	return 0;
}
int yywrap(){
	return 1;
}