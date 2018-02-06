%{
	int noofreserve=0, noofkeywords=0, noofrelop=0, noofternary=0, noofidentifier=0, noofop=0, noofsp=0;
	int slcomm=0, mulcom=0;
%}
%%
("--"|"++") {printf("\n Lexeme = %s, TokenType=Ternary",yytext); noofternary++;}
("=="|"&&") {printf("\n Lexeme = %s, TokenType=RelationalOperator",yytext); noofrelop++;}
(if|else|printf|scanf) {printf("\n Lexeme = %s,TokenType=ReservedWord\n",yytext); noofreserve++;}
[\<\=] {printf("\n Lexeme = %s, TokenType=RelationalOperator",yytext); noofrelop++;}
("+=")[ ] {printf("\n Lexeme = %s, TokenType=SpecialSymbol",yytext); noofsp++;}
[\+,\-,\/,\%] {printf("\n Lexeme = %s, TokenType=Operator\n",yytext); noofop++;}
[\#,\,\^,\&,\:,\?] {printf("\n Lexeme = %s, TokenType=SpecialSymbol\n",yytext); noofsp++;}
("int"|"char") {printf("\n Lexeme = %s, TokenType=Keyword\n",yytext); noofkeywords++;}
[a-zA-Z_][a-zA-Z|0-9|_]* {printf("\n Lexeme = %s, TokenType=Identifier\n",yytext); noofidentifier++;}
("//")[ ]. {printf("\n Lexeme = %s, It's a single line comment",yytext); slcomm++;}
("/*")[ ] {printf("\n Lexeme = %s, It's a multi line comment",yytext); mulcom++;}
%%
int main()
{
	yylex();
	printf("\n noofreserve=%d,\nnoofkeywords=%d,\nnoofrelop=%d,\nnoofternary=%d,\nnoofidentifier=%d,\nnoofop=%d,\nnoofsp=%d;",noofreserve,noofkeywords,noofrelop,noofternary,noofidentifier,noofop, noofsp);
	printf("\n Single line comment : %d\n Multi Line comment : %d\n",slcomm,mulcom);
	return 0;
}
int yywrap(){
	return 1;
}