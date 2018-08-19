#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int val;
}*NODE;

NODE hash[10];

int search(int d){
	if(hash[d%10]==NULL){
		return d%10;
	}else{
		int i=0;
		for(i=d%10; i<10; i++)
			if(hash[i]==NULL)
				return i;
		for(i=0; i<d%10; i++)
			if(hash[i]==NULL)
				return i;
	}
	return 0;
}

void insert(int d){
	int num = search(d);
	hash[num] = (struct node *) malloc(sizeof(struct node *));
	hash[num]->val = d;
}

void print(){
	int i=0;
	for(i=0; i<10; i++)
		if(hash[i]!=NULL)
			printf("\n %d : %d",i,hash[i]->val);
}

int main(){
	char c='y';
	int n=5;
	int d;
	while(c=='y'){
		printf("\n Enter a Number : ");
		scanf("%d",&d);
		insert(d);
		print();
		printf("\n Enter y/n : ");
		scanf(" %c",&c);
	}
}