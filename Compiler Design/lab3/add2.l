%%
[a-z] fprintf(yyout,"%c",yytext[0]-32);
['\/']['\/']['a-z|A-Z|' '|0-9']* printf("\n Comment encountered!");
%%
int main(){
	yyin = fopen("add2input.txt","r");
	yyout = fopen("add2output.txt","w+");
	yylex();
	return 0;
}
int yywrap(){
	return 1;
}