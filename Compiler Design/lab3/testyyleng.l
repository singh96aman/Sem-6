%{
	int count=0;
%}
%%
[a-d] {count+=yyleng; printf("\n%s",yytext);}
%%
int main(){
	yylex();
	printf("\n%d\n",count);
	//yyleng returns the length of the matched string
	return 0;
}
int yywrap(){
	return 1;
}
