%%
(if|else|printf|scanf) fprintf(yyout,"\n Lexeme = %s,TokenType=ReservedWord\n",yytext);
[\+,\-,\/,\*,\%] fprintf(yyout,"\n Lexeme = %s, TokenType=Operator\n",yytext);
[\#,\,\^] fprintf(yyout,"\n Lexeme = %s, TokenType=SpecialSymbol\n",yytext);
("int"|"char") fprintf(yyout,"\n Lexeme = %s, TokenType=Keyword\n",yytext);
[a-zA-Z_][a-zA-Z|0-9|_]* fprintf(yyout,"\n Lexeme = %s, TokenType=Identifier\n",yytext);
%%
int main()
{
	char file[50];
	scanf("%s",file);
	yyin = fopen(file,"r");
	yyout = fopen("saioutput.txt","w");
	yylex();
	return 0;
}
int yywrap(){
	return 1;
}