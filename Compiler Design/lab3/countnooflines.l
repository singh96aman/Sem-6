%{
int linecount=0; //declaration of variable
%}
%%
\n linecount++; //regular expression to match a newline along with its action
%%
int main()
{
	yylex();
	printf("There were %d lines \n",linecount);
	return 0;
}
int yywrap()
{
	return 1;
}