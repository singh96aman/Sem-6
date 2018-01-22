%{
	int noscanf=0;
	int noprintf=0;	
%}
%%
scanf noscanf++;
printf noprintf++;
%%
int main()
{
	yylex();
	printf("\n No of Scanf : %d & No of Printf : %d",noscanf,noprintf);
	return 0;
}
int yywrap(){
	return 1;
}