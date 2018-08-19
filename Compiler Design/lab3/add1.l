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
	char buf[100];
	i=0;
	while(temp!=0){
		int temp2=temp%16;
		switch(temp2){
			case 10 : buf[i++]='A';
						break;
			case 11 : buf[i++]='B';
						break;
			case 12 : buf[i++]='C';
						break;
			case 13 : buf[i++]='D';
						break;
			case 14 : buf[i++]='E';
						break;
			case 15 : buf[i++]='F';
						break;
			default : buf[i++]=(char)(temp2+48);
						break;
		}
		temp = temp/16;
	}
	buf[i]='\0';
	int j=0;
	for(j=0; j<i/2; j++){
		char l = buf[j];
		buf[j] = buf[i-j-1];
		buf[i-j-1] = l;
	}
	printf("%s",buf);
}