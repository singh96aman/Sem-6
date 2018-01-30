%%
[a-z] printf("%c",yytext[0]-32);
%%
int main(){
	yylex();
	return 0;
}
int yywrap(){
	return 1;
}