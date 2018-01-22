%{  
#include <stdlib.h>
#include <stdio.h>

int charCount=0;
int wordCount=0;
int lineCount=0;
%}
%%
\n      {charCount++; lineCount++;}   
[^ \t\n]+   {wordCount++; charCount+=yyleng;}
.       {charCount++;}

%%
int main(argc, argv)
int argc;
char** argv;
{           
if (argc > 1)
{
    FILE *file;
    file = fopen(argv[1], "r");
    if (!file)
    {
        fprintf(stderr, "Could not open %s\n", argv[1]);
        exit(1);
    }
    yyin = file;
}

yylex();
printf("%d   %d   %d\n", charCount, wordCount, lineCount);
}