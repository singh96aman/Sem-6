%{
	void convert(char *num);
%}
%%
[0|1]+ convert(yytext);
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
	char buf[100];
	for(i=0; num[i]!='\0'; i++){
		buf[i]=((num[i]-48)==0)+48;
	}
	buf[i]='\0';
	printf("\n%s",buf);
}