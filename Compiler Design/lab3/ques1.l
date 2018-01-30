%{
	int vowels=0;
	int consonants=0;
%}
%%
['a','e','i','o','u','A','E','I','O','U'] vowels++;
[A-Za-z] consonants++;
%%
int main()
{
	yylex();
	printf("\nThere were %d vowels\n",vowels);
	printf("\nThere were %d Consonants\n",consonants);
	return 0;
}

int yywrap(){
	return 1;
}