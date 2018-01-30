%{
int pos=0;
int neg=0;
int posf=0;
int negf=0;
%}
%%
[+]?[0-9]* pos++;
[-]+[0-9]* neg++;
[+]?[0-9]*.[0-9]* posf++;
[-]+[0-9]*.[0-9]* negf++;
%%
int main()
{
	yylex();
	printf("\n Pos Float : %d\n Neg Float : %d\n Pos : %d\n Neg : %d",posf,negf,pos,neg);
	return 0;
}
int yywrap(){
	return 1;
}