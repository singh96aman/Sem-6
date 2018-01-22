%{
	int positive=0;
	int negative=0;
	int posfloat=0;
	int negfloat=0;
%}
%%
[+]?[0-9]* positive++;
[-]+[0-9]* negative++;
[+]?[0-9]*\.[0-9]* posfloat++;
[-]+[0-9]*\.[0-9]* negfloat++;
%%
int main()
{
	yylex();
	printf("\nPositives : %d\nNegative : %d\nPositive float : %d\nNegative float : %d\n",positive,negative,posfloat,negfloat);
	return 0;
}

int yywrap(){
	return 1;
}

