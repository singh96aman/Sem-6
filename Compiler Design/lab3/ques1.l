%{
	int vowels=0;
	int total=0;
%}
%%
['a','e','i','o','u','A','E','I','O','U'] vowels++;
[A-Za-z] total++;
%%
int main()
{
	yylex();
	printf("\nThere were %d vowels\n",vowels);
	printf("\nThere were %d Consonants\n",total);
	return 0;
}

int yywrap(){
	return 1;
}