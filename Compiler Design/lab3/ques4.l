%{
	int p_count=0, s_count=0;
%}
%%
printf {p_count++; fprintf(yyout,"write");}
scanf {s_count++; fprintf(yyout,"read");}
%%
int main()
{
	yyin = fopen("input.txt","r");
	yyout = fopen("output.txt","w");
	yylex();
	printf("\n The no of printf are : %d",p_count);
	printf("\n The no of scanf are : %d",s_count);
	return 0;
}
int yywrap(){
	return 1;
}