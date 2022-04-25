#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_SIZE 10
#define STACKINCREASEMENT 5

typedef struct BiTNode
{
	char data;
	struct BiTNode* lchild, * rchild;
} BiTNode, * BiTree;
BiTree bt;
BiTNode *p;

typedef struct
{
	BiTree bn[STACK_INIT_SIZE];
	int top;
	int stacksize;
} SqStack;
SqStack L,Path;
void InitStack (SqStack *);
void Push(SqStack *,BiTree);
void Pop(SqStack *,BiTree *);
int Equal(BiTree,BiTree);
void CreateBiTree(BiTree*);
void PostPush(BiTree,char);

int main()
{
	InitStack(&L);
	InitStack(&Path);
	printf("�밴���������˳������������Ľ��(��#��ʾ�ս��):\n");
	CreateBiTree(&bt);

	printf("\n����������ҵĽ��(A-J):");
	char a;
	fflush(stdin);
	scanf("%c",&a);
	while(a<'A'||a>'J')
	{
		printf("\n������������������:");
		scanf("%c",&a);
	}
	PostPush(bt,a);

	return 0;
}
//�������������������н���ֵ��������������ʾ�Ķ�����
void CreateBiTree(BiTree* T)
{
	char ch;
	scanf("%c",&ch);
	if(ch=='#') *T=NULL;
	else
	{
		*T=(BiTree)malloc(sizeof(BiTNode));
		(*T)->data=ch;
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}
}
void visit(BiTNode e)
{
	printf("%c ",e);
}
//��ʼ��ջ
void InitStack (SqStack *s)
{
	int i;
	s->top=0;

}
//ѹջ
void Push(SqStack *s,BiTree e)
{

	if(s->top>=STACK_INIT_SIZE)
	{
		printf("ERROR!");
		return;
	}
	s->bn[s->top] = e;
	s->top++;
}

//��ջ
void Pop(SqStack *s,BiTree *e)
{

	if(s->top>=STACK_INIT_SIZE)
	{
		printf("ERROR\n");
		return;
	}
	s->top--;
	*e = s->bn[s->top];
}
//�ж�������Ƿ����
int Equal(BiTree e1,BiTree e2)
{
	if(e1==NULL||e2==NULL)
		return 0;
	if(e1->data == e2->data && e1->lchild == e2->lchild && e1->rchild == e2->rchild)
		return 1;
	else
		return 0;
}

void PostPush(BiTree root,char ch)
{
	int i;
	BiTree p,q;
	p=root;
	q=NULL;
	while(p!=NULL||L.top!=0)
	{
		if(p)
		{
			Push(&L,p);
			p=p->lchild;
		}
		else
		{
			Pop(&L,&p);
			Push(&L,p);
			if(p->rchild==NULL||p->rchild==q)
			{
				if(p->data==ch)
				{
					while(L.top>0)
					{
						Pop(&L,&p);
						Push(&Path,p);
					}
					while(Path.top>1)
					{
						Pop(&Path,&p);
						printf("%c->",p->data);
					}
					printf("%c",ch);
					return;
				}
				else
				{
					q=p;
					Pop(&L,&p);
					p=NULL;
				}
			}
			else p=p->rchild;
		}
	}

}
