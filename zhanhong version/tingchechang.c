#include <stdio.h>
#include <malloc.h>
#include <process.h>
#include "time.h"

//����ݳ���
#define MAX 3
//����
#define PRICE_PER_HOUR 6
#define PRICE_PER_MIN 0.2

//ʱ��
typedef struct
{
	int hour;
	int min;
} Time;

//��
typedef struct
{
	//���ƺ�
	char num[10];
	Time in_time;
	Time out_time;
} Car;

//��ջ
#define STACK_INIT_SIZE 10
#define STACKINCREMENT 2

typedef struct
{
	Car car[STACK_INIT_SIZE];
	int top;
} CarSqStack;
//���
typedef struct Car_p
{
	Car data;
	struct Car_p *next;
} Car_p;
typedef struct
{
	Car_p *front;
	Car_p *rear;
} Passway;

void InitStack (CarSqStack *);
void Push(CarSqStack *,Car);
void Pop(CarSqStack *,Car *);
void InitQueue(Passway *);
void EnQueue(Passway *,Car);
void DeQueue(Passway *,Car *);
void arrival(CarSqStack *,Passway*);
void leave(CarSqStack *,CarSqStack *,Passway*);
void info(CarSqStack*,CarSqStack*,Passway*);
void print(Car *);

int main ()
{
	int item;
	CarSqStack barn,temp;
	Passway passway;
	InitStack(&barn);
	InitStack(&temp);
	InitQueue(&passway);

	while(1)
	{

		fflush(stdin);
		printf("\n\n");
		printf("\t\t*********************��ӭʹ��ͣ����ϵͳ******************\n");
		printf("\t\t*********************1.��������**************************\n");
		printf("\t\t*********************2.�����뿪**************************\n");
		printf("\t\t*********************3.������Ϣ**************************\n");
		printf("\t\t*********************4.�˳�ϵͳ**************************\n");
		printf("\t\t*********************��ӭʹ��ͣ����ϵͳ******************\n");
		printf("\n\n          ��ѡ�����������1/2/3/4:\n");
		while(1)
		{
			scanf("%d",&item);
			if(item>4)
				printf("������Ч���֣����������룡\n");
			else
				break;
		}
		switch(item)
		{
			case 1:
				arrival(&barn,&passway);
				break;
			case 2:
				leave(&barn,&temp,&passway);
				break;
			case 3:
				info(&barn,&temp,&passway);
				break;
			case 4:
				exit(0);
			default:
				break;
		}
	}

	return 0;
}
//��ʼ��ջ
void InitStack (CarSqStack *s)
{
	int i;
	s->top=0;
//	for(i=0; i<STACK_INIT_SIZE; i++)
//	{
//		s->car[i]=NULL;
//	}
}
//ѹջ
void Push(CarSqStack *s,Car e)
{

	if(s->top>=STACK_INIT_SIZE)
	{
		printf("ERROR!");
		return;
	}
	s->car[s->top] = e;
	s->top++;
}

//��ջ
void Pop(CarSqStack *s,Car *e)
{

	if(s->top>=STACK_INIT_SIZE)
	{
		printf("ERROR\n");
		return;
	}
	s->top--;
	*e = s->car[s->top];
}
//���г�ʼ��
void InitQueue(Passway *q)
{
	q->front=(Car_p *)malloc(sizeof(Car_p));
	if(q->front!=NULL)
	{
		q->front->next=NULL;
		q->rear=q->front;
	}
}
//���
void EnQueue(Passway *Q,Car e)
{
	Car_p *car_p=(Car_p *)malloc(sizeof(Car_p));
	car_p->data=e;
	car_p->next=NULL;
	if(Q->front==Q->rear)
	{
		Q->front->next=car_p;
		Q->rear=car_p;
	}
	else
	{
		Q->rear->next=car_p;
		Q->rear=car_p;
	}
}
//����
void DeQueue(Passway *Q,Car *e)
{
	if(Q->front==Q->rear)
	{
		printf("ERROR!");
		return;
	}

	*e=Q->front->next->data;
	Q->front->next=Q->front->next->next;
	if(Q->front->next==NULL)
	{
		Q->rear=Q->front;
	}
}

void arrival(CarSqStack *s,Passway *q)
{
	Car *p;

	fflush(stdin);
	printf("�����복�ƺ�:");
	gets(p->num );
	if(s->top<MAX)
	{
		printf("������ͣ�����е�λ��Ϊ  %d:\n",s->top+1);
		printf("�����뵽���ʱ��(hh:mm): ");
		scanf("%d:%d",&(p->in_time.hour),&(p->in_time.min));
		Push(s,*p);
	}
	else
	{
		printf("\n\n----------------------ͣ�����������ڽ�������-----------------\n");
		EnQueue(q,*p);
	}
}

void print(Car *p)
{
	int t1,t2;
	printf("�������뿪��ʱ��(hh:mm): ");
	scanf("%d:%d",&(p->out_time.hour),&(p->out_time .min));
	printf("�뿪�����ĳ��ƺ���:" );
	puts(p->num);
	printf("�뿪�����Ľ���ʱ��Ϊ%2d:%d\n",p->in_time.hour ,p->in_time .min  );
	printf("�뿪�������뿪ʱ��Ϊ%2d:%d\n",p->out_time.hour ,p->out_time .min  );
	t1=(p->out_time.hour)-(p->in_time.hour);
	t2=(p->out_time.min)-(p->in_time.min);
	printf("Ӧ���ɷ���%fԪ\n\n",t1*PRICE_PER_HOUR+t2*PRICE_PER_MIN);
}

void leave(CarSqStack *s,CarSqStack *temp,Passway *q)
{
	int room;
	Car *p;
//�ж�ͣ�������Ƿ��г���
	if(s->top>0)
	{
		while(1)
		{
			printf("ͣ������ͣ������:%d\n",s->top);
			printf("������ͣ������Ҫ�뿪�ĳ���λ��:\n");
			fflush(stdin);
			scanf("%d",&room);

			if(room>=1&&room<=s->top)
				break;
		}
		while(s->top>room)
		{
			Pop(s,p);
			Push(temp,*p);
		}
		Pop(s,p);
		
		print(p);

		//ͨ���Ƿ��г�
		if((q->front!=q->rear) &&s->top<MAX)
		{
			DeQueue(q,p);
			printf("��������%s�����복��%dλ��\n",p->num,s->top+1);
			printf("�����뵽���ʱ��(hh:mm): ");
			fflush(stdin);
			scanf("%d:%d",&(p->in_time.hour),&(p->in_time.min));
			Push(s,*p);
		}
		else
			printf("ͨ����û�г�\n");
			
		while(temp->top>0)
		{
			Pop(temp,p);
			Push(s,*p);
		}
	}
	else
		printf("\nĿǰ������û�г�\n");

}

void info(CarSqStack *s,CarSqStack *temp,Passway *q)
{
	Car_p *p;
	Car *c = (Car *) malloc(sizeof(Car));
	int i;

	int item;
	printf("\n\n");
	printf("\t\t******************1.�鿴�����г�����Ϣ********************\n");
	printf("\t\t******************2.�鿴����г�����Ϣ********************\n");
	printf("\t\t******************3.����***********************************\n");
	printf("\t\t**************��ѡ������ķ���*******************\n");
	fflush(stdin);
	scanf("%d",&item);

	switch(item)
	{

		case 1:
			if(s->top>0)
			{
				printf("\n\n");
				printf("---------------------ͣ������Ϣ-------------\n");
				printf("ͣ��λ��       ����ʱ��         ���ƺ�\n");

				while((s->top)>0)
				{

					Pop(s,c);
					Push(temp,*c);
				}

				for(i=0; temp->top>0; i++)
				{
					printf("%6d",i+1);
					Pop(temp,c);
					Push(s,*c);
					printf("%12d:%2d",c->in_time.hour,c->in_time.min);
					printf("          ");
					puts(c->num);
				}
				printf("----------------------------------------------------\n\n");
			}
			else
				printf("������û�г�\n");
			break;
		case 2:


			p=(Car_p *)malloc(sizeof(Car_p));
			//p=q->head->next;
			p=q->front->next;
			if(q->front!=q->rear)
			{

				printf("\n\n------------------ͨ��-------------------\n");
				printf("            �ȴ������ĳ��ƺ���Ϊ:  \n");

				while(p!=NULL)
				{
					puts(p->data.num);
					p=p->next;
				}
				printf("\n-----------------------------------------------------");
			}
			else
				printf("\n\n---------------------�����û�г�-------------\n\n\n");
			break;
		case 3:
			break;
		default:
			printf("������� ����������:\n");
			break;
	}
}
