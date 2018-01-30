%{
	void convert(char *num);
%}
%%
[0-9]+ convert(yytext);
%%
int main(){
	yylex();
	return 0;
}
int yywrap(){
	return 1;
}
void convert(char *num){
	int i=0;
	int temp=0, temp2;
	for(i=0; i<strlen(num); i++)
		temp=temp*10+(num[i]-48);
	while(temp!=0){
		int temp2=temp%16;
		switch(temp2){
			case 10 : printf("A");
						break;
			case 11 : printf("B");
						break;
			case 12 : printf("C");
						break;
			case 13 : printf("D");
						break;
			case 14 : printf("E");
						break;
			case 15 : printf("F");
						break;
			default : printf("%d",temp2);
						break;
		}
		temp = temp/16;
	}
}