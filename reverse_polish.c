#include <stdio.h>
#include <stdlib.h>

#define INIT 50
#define EXTEND 20
#define OPSETSIZE 7

char OPSET[OPSETSIZE]={'+','-','*','/','(',')','#'};

unsigned char Prior[OPSETSIZE][OPSETSIZE]=
{
	'<','<','<','<','<','>','>',
	'<','<','<','<','<','>','>',
	'>','>','<','<','<','>','>',
	'>','>','<','<','<','>','>',
	'<','<','<','<','<','=','?',
	'>','>','>','>','?','>','>',
	'<','<','<','<','<','?','='
};

typedef char ElemType;

typedef struct
{
	ElemType data;
	int tag;
}Info;

typedef struct
{
	Info *base;
	Info *top;
	int size;
}Stack;

void InitStack(Stack *s)
{
	s->base=(Info*)malloc(INIT*sizeof(Info));
	s->top=s->base;
	s->size=INIT;
}

void push(Stack *s,Info e)
{
	if(s->top-s->base>s->size)
	{
		s->base=(Info*)realloc(s->base,(s->size+EXTEND)*sizeof(Info));
		s->size+=EXTEND;
	}
	*(s->top++)=e;
}

void pop(Stack *s)
{
	if(s->top==s->base)
	{
		printf("Stack is empty\n");
		return;
	}
	s->top--;
}

Info getop(Stack *s)
{
	Info e;
	e=*(s->top-1);
	return e;
}

int isCchar(ElemType c)
{
	switch(c)
	{
		case '+':return 1;	
		case '-':return 1;	
		case '*':return 1;	
		case '/':return 1;	
		case '(':return 1;
		case ')':return 1;
		case '#':return 1;
		default :return 0;	
	}
}

int locate(ElemType c)
{
	switch(c)
	{
		case '+':return 0;	
		case '-':return 1;	
		case '*':return 2;	
		case '/':return 3;	
		case '(':return 4;
		case ')':return 5;
		case '#':return 6;
		default :return -1;
	}
}

ElemType order(Info a,Info b)
{
	if(a.tag==b.tag)
		return Prior[locate(a.data)][locate(b.data)];
	else if(a.tag>b.tag)
		return '>';
	else
		return '<';
}

int isempty(Stack *s)
{
	if(s->top==s->base)
		return 1;
	else
		return 0;
}

int Isalpha(ElemType c)
{
	if(c>='A' && c<='Z')
		return 1;
	else if(c>='a' && c<='z')
		return 1;
	else
		return 0;
}

int main()
{
	Stack *optr,*opnd;
	ElemType c;
	Info input,*p;
	int temp=1;

	optr=(Stack*)malloc(sizeof(Stack));
	opnd=(Stack*)malloc(sizeof(Stack));
	InitStack(optr),InitStack(opnd);
	input.data='#';
	input.tag=1;
	push(optr,input);

	while(c=getchar())
	{	
		input.data=c;
		input.tag=temp;
		if(c=='\n')
			break;
		if(isCchar(c))
		{
			if(c=='(')
				temp=2;
			else if(c==')')
				temp=1;
			else
			{
				if(order(input,getop(optr))!='>')
				{	
					restart:;
					push(opnd,getop(optr));
					pop(optr);
					if(order(input,getop(optr))!='>')
						goto restart;
					else
						push(optr,input);
				}
				else
					push(optr,input);
			}
		}
		else if(Isalpha(c))
		{
			push(opnd,input);
		}
	}

	while(!isempty(optr))
	{
		push(opnd,getop(optr));
		pop(optr);
	}
	for(p=opnd->base;p!=opnd->top;p++)
		{	
			if(p->data!='#')
				printf("%c",p->data);
		}
	printf("\n");
	return 0;
}