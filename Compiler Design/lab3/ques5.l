%{
	int countjoin=0;
%}
%%
[ ]and[ ] countjoin++;
[ ]or[ ] countjoin++;
[ ]so[ ] countjoin++;
[ ]but[ ] countjoin++;
[ ]because[ ] countjoin++;
%%
int main(){
	yylex();
	if(countjoin>=1)
		printf("\n The sentence is compund with joining words : %d\n",countjoin);
	else
		printf("\n The sentence is not compund");
		return 0;
}
int yywrap(){
	return 1;
}