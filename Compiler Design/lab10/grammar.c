#include <stdio.h>
#include "lexical.c"
#include <string.h>
#include <ctype.h>

void Program(FILE *fp1);
void declaration(FILE *fp1);
int data_type(FILE *fp1);
void identifier_list(FILE *fp1);
void assign_stat(FILE *fp1);
void assign_stat2(FILE *fp1);
void expn(FILE *fp1);
void eprime(FILE *fp1);
void simple_exp(FILE *fp1);
void seprime(FILE *fp1);
void term(FILE *fp1);
void tprime(FILE *fp1);
void factor(FILE *fp1);
int relop(FILE *fp1);
int addop(FILE *fp1);
int mulop(FILE *fp1);
void statement_list(FILE *fp1);
int statement(FILE *fp1);
void decision_stat(FILE *fp1);
void looping_stat(FILE *fp1);

char *buf2;

void Program(FILE *fp1){
	buf2 = getNextToken(fp1);
	if(strcmp(buf2,"main")==0){
		buf2 = getNextToken(fp1);
		if(strcmp(buf2,"(")==0){
			buf2 = getNextToken(fp1);
			if(strcmp(buf2,")")==0){
				buf2 = getNextToken(fp1);
				if(strcmp(buf2,"{")==0){
					declaration(fp1);
					statement_list(fp1);
					//printf("\nbujy %s",buf2);
					if(strcmp(buf2,"}")==0){
						printf("\nString accepted!\n");
						exit(0);
					}
				}
			}
		}
	}
}

void declaration(FILE *fp1){
		buf2 = getNextToken(fp1);
		if((data_type(fp1))==1){
			identifier_list(fp1);
		}
}

int data_type(FILE *fp1){
	if(strcmp(buf2,"int")==0 || strcmp(buf2,"char")==0)
		return 1;
	return 0;
}

void identifier_list(FILE *fp1){
	buf2 = getNextToken(fp1);
	if(strcmp(buf2,"id")==0){
		buf2 = getNextToken(fp1);
		if(strcmp(buf2,",")==0)
			identifier_list(fp1);
		else if(strcmp(buf2,";")==0)
			{declaration(fp1);}
		else if(strcmp(buf2,"[")==0){
			buf2 = getNextToken(fp1);
			buf2 = getNextToken(fp1);
			if(strcmp(buf2,"]")==0){
				buf2 = getNextToken(fp1);
				if(strcmp(buf2,",")==0)
					identifier_list(fp1);
				else
				{declaration(fp1);}
			}
		}
	}
}

void statement_list(FILE *fp1){
	//printf("\nHello %s",buf2);
	if(statement(fp1)){
		statement_list(fp1);
		//printf("\nHello %s",buf2);
	}
	//printf("\nstat result %s",buf2);
}

int statement(FILE *fp1){
	assign_stat(fp1);
	decision_stat(fp1);
	looping_stat(fp1);
	//printf("\ntest2 %s",buf2);
	if(strcmp(buf2,";")==0){
		buf2 = getNextToken(fp1);
		if(strcmp(buf2,"id")==0 || strcmp(buf2,"for")==0 || strcmp(buf2,"if")==0)
			return 1;
	}
	if(strcmp(buf2,"id")==0 || strcmp(buf2,"if")==0 || strcmp(buf2,"for")==0 || strcmp(buf2,"while")==0)	
		return 1;
	return 0;
}

void assign_stat(FILE *fp1){
	//printf("\ntest2 %s",buf2);
	if(strcmp(buf2,"id")==0){
		buf2 = getNextToken(fp1);
		if(strcmp(buf2,"=")==0){
			buf2 = getNextToken(fp1);
			expn(fp1);
			//printf("\n assign %s",buf2);
		}else
			exit(0);
	}
}

void decision_stat(FILE *fp1){
	//printf("\ndec_stat");
	if(strcmp(buf2,"if")==0){
		buf2 = getNextToken(fp1);
		if(strcmp(buf2,"(")==0){
			buf2 = getNextToken(fp1);
			expn(fp1);
			if(strcmp(buf2,")")==0){
				buf2 = getNextToken(fp1);
				if(strcmp(buf2,"{")==0){
					buf2 = getNextToken(fp1);
					//printf("\ndec %s",buf2);
					statement_list(fp1);
					//printf("\ndec2 %s",buf2);
					if(strcmp(buf2,"}")==0)
						buf2 = getNextToken(fp1);
					else
						exit(0);
				}
			}
		}
	}
}

void looping_stat(FILE *fp1){
	if(strcmp(buf2,"while")==0){
		buf2 = getNextToken(fp1);
		if(strcmp(buf2,"(")==0){
			buf2 = getNextToken(fp1);
			expn(fp1);
			if(strcmp(buf2,")")==0){
				buf2 = getNextToken(fp1);
				if(strcmp(buf2,"{")==0){
					buf2 = getNextToken(fp1);
					//printf("\ndec %s",buf2);
					statement_list(fp1);
					//printf("\ndec2 %s",buf2);
					if(strcmp(buf2,"}")==0)
						buf2 = getNextToken(fp1);
					else
						exit(0);
				}
			}
		}
	}
	else if(strcmp(buf2,"for")==0){
		buf2 = getNextToken(fp1);
		if(strcmp(buf2,"(")==0){
			buf2 = getNextToken(fp1);
			assign_stat(fp1);
			if(strcmp(buf2,";")==0){
				buf2 = getNextToken(fp1);
				expn(fp1);
				if(strcmp(buf2,";")==0){
					buf2 = getNextToken(fp1);
					assign_stat(fp1);
					if(strcmp(buf2,")")==0){
						buf2 = getNextToken(fp1);
						if(strcmp(buf2,"{")==0){
							buf2 = getNextToken(fp1);
							//printf("\ndec %s",buf2);
							statement_list(fp1);
							//printf("\ndec2 %s",buf2);
							if(strcmp(buf2,"}")==0)
								buf2 = getNextToken(fp1);
							else
								exit(0);
						}
					}
				}
			}
		}
	}
}

void expn(FILE *fp1){
	//printf("\n Hello");
	simple_exp(fp1);
	//printf("\neprime %s",buf2);
	eprime(fp1);
	//printf("\nexpn %s",buf2);
}

void eprime(FILE *fp1){
	if(relop(fp1))
		simple_exp(fp1);
}

void simple_exp(FILE *fp1){
	term(fp1);
	seprime(fp1);
	//printf("\nsimple_exp %s",buf2);
}

void seprime(FILE *fp1){
	if(addop(fp1)){
		term(fp1);
		//printf("\n%s",buf2);
		seprime(fp1);
	}
	//printf("\nseprime %s",buf2);
}

void term(FILE *fp1){
	//printf("\nkjgfd");
	factor(fp1);
	//printf("\n%s",buf2);
	tprime(fp1);
	//printf("\nterm %s",buf2);
}

void tprime(FILE *fp1){
	//printf("\ntprime");
	if(mulop(fp1)){
		//printf("\naman1");
		factor(fp1);
		tprime(fp1);
	}
	//printf("\ntprime %s",buf2);
}

void factor(FILE *fp1){
	if(strcmp(buf2,"id")==0 || strcmp(buf2,"5")==0) //check num not added
		buf2=getNextToken(fp1);
	//printf("\nfactor %s",buf2);
}

int relop(FILE *fp1){
	if(!(strcmp(buf2,"==")==0 || strcmp(buf2,"!=")==0 || strcmp(buf2,"<=")==0 ||  strcmp(buf2,">=")==0 || strcmp(buf2,">")==0 || strcmp(buf2,"<")==0))
		return 0;
	buf2=getNextToken(fp1);
	return 1;
}

int addop(FILE *fp1){
	//printf("\nadd %s",buf2);
	if(!(strcmp(buf2,"+")==0 || strcmp(buf2,"-")==0))
		return 0;
	buf2=getNextToken(fp1);
	return 1;
}

int mulop(FILE *fp1){
	//printf("\nmulop %s",buf2);
	if(!(strcmp(buf2,"*")==0 || strcmp(buf2,"/")==0 || strcmp(buf2,"%")==0))
		return 0;
	buf2=getNextToken(fp1);
	return 1;
}

int main(){
	FILE *fp1 = fopen("input.txt","r");
	buf2="start";
	fflush(stdout);
	Program(fp1);
	buf2 = getNextToken(fp1);
	printf("\n%s",buf2);
	return 0;
}