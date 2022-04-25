#include <stdio.h>
#include <malloc.h>
#include <process.h>
#include "time.h"

//最大容车量
#define MAX 3
//费用
#define PRICE_PER_HOUR 6
#define PRICE_PER_MIN 0.2

//时间
typedef struct
{
	int hour;
	int min;
} Time;

//车
typedef struct
{
	//车牌号
	char num[10];
	Time in_time;
	Time out_time;
} Car;

//车栈
#define STACK_INIT_SIZE 10
#define STACKINCREMENT 2

typedef struct
{
	Car car[STACK_INIT_SIZE];
	int top;
} CarSqStack;
//便道
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
		printf("\t\t*********************欢迎使用停车场系统******************\n");
		printf("\t\t*********************1.车辆到达**************************\n");
		printf("\t\t*********************2.车辆离开**************************\n");
		printf("\t\t*********************3.车辆信息**************************\n");
		printf("\t\t*********************4.退出系统**************************\n");
		printf("\t\t*********************欢迎使用停车场系统******************\n");
		printf("\n\n          请选择服务，请输入1/2/3/4:\n");
		while(1)
		{
			scanf("%d",&item);
			if(item>4)
				printf("输入无效数字，请重新输入！\n");
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
//初始化栈
void InitStack (CarSqStack *s)
{
	int i;
	s->top=0;
//	for(i=0; i<STACK_INIT_SIZE; i++)
//	{
//		s->car[i]=NULL;
//	}
}
//压栈
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

//出栈
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
//队列初始化
void InitQueue(Passway *q)
{
	q->front=(Car_p *)malloc(sizeof(Car_p));
	if(q->front!=NULL)
	{
		q->front->next=NULL;
		q->rear=q->front;
	}
}
//入队
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
//出队
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
	printf("请输入车牌号:");
	gets(p->num );
	if(s->top<MAX)
	{
		printf("车辆在停车场中的位置为  %d:\n",s->top+1);
		printf("请输入到达的时间(hh:mm): ");
		scanf("%d:%d",&(p->in_time.hour),&(p->in_time.min));
		Push(s,*p);
	}
	else
	{
		printf("\n\n----------------------停车场已满正在进入便道！-----------------\n");
		EnQueue(q,*p);
	}
}

void print(Car *p)
{
	int t1,t2;
	printf("请输入离开的时间(hh:mm): ");
	scanf("%d:%d",&(p->out_time.hour),&(p->out_time .min));
	printf("离开车辆的车牌号码:" );
	puts(p->num);
	printf("离开车辆的进入时间为%2d:%d\n",p->in_time.hour ,p->in_time .min  );
	printf("离开车辆的离开时间为%2d:%d\n",p->out_time.hour ,p->out_time .min  );
	t1=(p->out_time.hour)-(p->in_time.hour);
	t2=(p->out_time.min)-(p->in_time.min);
	printf("应缴纳费用%f元\n\n",t1*PRICE_PER_HOUR+t2*PRICE_PER_MIN);
}

void leave(CarSqStack *s,CarSqStack *temp,Passway *q)
{
	int room;
	Car *p;
//判断停车场内是否有车；
	if(s->top>0)
	{
		while(1)
		{
			printf("停车场里停车总数:%d\n",s->top);
			printf("请输入停车场中要离开的车的位置:\n");
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

		//通道是否有车
		if((q->front!=q->rear) &&s->top<MAX)
		{
			DeQueue(q,p);
			printf("现在请便道%s车进入车库%d位置\n",p->num,s->top+1);
			printf("请输入到达的时间(hh:mm): ");
			fflush(stdin);
			scanf("%d:%d",&(p->in_time.hour),&(p->in_time.min));
			Push(s,*p);
		}
		else
			printf("通道里没有车\n");
			
		while(temp->top>0)
		{
			Pop(temp,p);
			Push(s,*p);
		}
	}
	else
		printf("\n目前车库里没有车\n");

}

void info(CarSqStack *s,CarSqStack *temp,Passway *q)
{
	Car_p *p;
	Car *c = (Car *) malloc(sizeof(Car));
	int i;

	int item;
	printf("\n\n");
	printf("\t\t******************1.查看车库中车的信息********************\n");
	printf("\t\t******************2.查看便道中车的信息********************\n");
	printf("\t\t******************3.返回***********************************\n");
	printf("\t\t**************请选择所需的服务*******************\n");
	fflush(stdin);
	scanf("%d",&item);

	switch(item)
	{

		case 1:
			if(s->top>0)
			{
				printf("\n\n");
				printf("---------------------停车场信息-------------\n");
				printf("停车位置       到达时间         车牌号\n");

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
				printf("车库里没有车\n");
			break;
		case 2:


			p=(Car_p *)malloc(sizeof(Car_p));
			//p=q->head->next;
			p=q->front->next;
			if(q->front!=q->rear)
			{

				printf("\n\n------------------通道-------------------\n");
				printf("            等待车辆的车牌号码为:  \n");

				while(p!=NULL)
				{
					puts(p->data.num);
					p=p->next;
				}
				printf("\n-----------------------------------------------------");
			}
			else
				printf("\n\n---------------------便道里没有车-------------\n\n\n");
			break;
		case 3:
			break;
		default:
			printf("输入错误 请重新输入:\n");
			break;
	}
}
