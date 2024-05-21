#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
#define MAX_TIME 54001
#define MAX_FOOD 100
#define MAX_COMBO 100
#define MAX_ORDERS 54001
#define MAX_TIME_LENGTH 9 // 定义时间字符串的最大长度
//current为当前订单
typedef struct
{
	char name[20];
	int time_to_make;
	int max_storage;
	int current_storage;
}Food;

typedef struct
{
	char name[20];
	char foods[MAX_FOOD][20];
	int num_foods;
}Combo;

typedef struct
{
	char food_name[20];
	char start_time[MAX_TIME_LENGTH];
	char finish_time[MAX_TIME_LENGTH];
	int completed;//0表示订单下单失败，1表示订单立即完成，2表示订单需等待
}Order;
Food foods[MAX_FOOD];
Combo combos[MAX_COMBO];
Order orders[MAX_ORDERS];
int food_count,combo_count;
int w1,w2;
int num_orders;

void input_menu()//读取菜单信息
{
	int i,j;
	FILE*filename=fopen("dict.dic.txt","r");
	fscanf(filename,"%d %d",&food_count,&combo_count);
	for(i=0;i<food_count;i++)
	fscanf(filename,"%s",foods[i].name);
	for(i=0;i<food_count;i++)
	fscanf(filename,"%d",&foods[i].time_to_make);
	for(i=0;i<food_count;i++)
	{
		fscanf(filename,"%d",&foods[i].max_storage);
		foods[i].current_storage=0;
	}
	fscanf(filename,"%d %d",&w1,&w2);
	for(i=0;i<combo_count;i++)
	{
		fscanf(filename,"%s",combos[i].name);
		combos[i].num_foods=0;
		char line[100];
		while(fgets(line,sizeof(line),filename)!=NULL)
		{
			char*token=strtok(line," ");
			j=0;
			while(token!=NULL)
			{
				strcpy(combos[i].foods[j],token);
				token=strtok(NULL," ");
				j++;
				combos[i].num_foods++;
			}
			break;
		}
	}
	fclose(filename);
}

void input_order(int num_orders)//读取订单信息
{
	scanf("%d",&num_orders);
	for(int i=0;i<num_orders;i++)
	{
		scanf("%s %s",orders[i].start_time,orders[i].food_name);	
	}
}

int calculate_delta_time(Order orders[],int num_orders)//计算订单时间差
{
	int time_difference;
	int hour1,min1,sec1;
	int hour2,min2,sec2;
	sscanf(orders[num_orders].start_time,"%d:%d:%d",&hour1,&min1,&sec1);
	sscanf(orders[num_orders-1].start_time,"%d:%d:%d",&hour2,&min2,&sec2);
	time_difference=hour1*3600+min1*60+sec1-(hour2*3600+min2*60+sec2);
	return time_difference;	
}

void update_food_storage(Food foods[],Order orders[])//更新食物储备
{
	int delta_time=calculate_delta_time(orders,num_orders);
	for(int i=0;i<num_orders;i++)
	{
		foods[i].current_storage=(foods[i].current_storage)+delta_time/foods[i].time_to_make;
		if(foods[i].current_storage>foods[i].max_storage)
		foods[i].current_storage=foods[i].max_storage;
	}
}

int judge_type(Order orders[],Combo combos[],int current,int combo_count)//判断是单点还是套餐，单点返回1，套餐返回0
{
	int result=1;
	for(int i=0;i<combo_count&&result!=0;i++)
	result=strcmp(orders[current].food_name,combos[i].name);
	return result;
}

void update_time(Order orders[],int current,int waiting_time)//更新订单完成时间
{
	int hour,min,sec;
	sscanf(orders[current].start_time,"%d:%d:%d",&hour,&min,&sec);
	int totalSeconds = hour * 3600 + min * 60 + sec;
	totalSeconds += waiting_time;
	hour = (totalSeconds / 3600) % 24;
	min = (totalSeconds / 60) % 60;
	sec = totalSeconds % 60;
	sprintf(orders[current].finish_time, "%02d:%02d:%02d", hour, min, sec);
}

void printresult(Order order[],int num_orders)//打印最终结果
{
	int i;
	for(i=0;i<num_orders;i++)
	{
		if(orders[i].completed==0)
		printf("Fail\n");
		else
		printf("%s\n",order[i].finish_time);
	}
}

int reduce_food(int current,Food foods[])//减少食物量
{
	int state=1;
	if(foods[current].current_storage<1)
	state=2;
	else
	foods[current].current_storage--;
	return state;
}

int compare_time(Order orders[],int current,int i)//比较当前订单与之前订单时间
{
	int time_difference;
	int hour1,min1,sec1;
	int hour2,min2,sec2;
	sscanf(orders[i].start_time,"%d:%d:%d",&hour1,&min1,&sec1);
	sscanf(orders[current].start_time,"%d:%d:%d",&hour2,&min2,&sec2);
	time_difference=hour1*3600+min1*60+sec1-(hour2*3600+min2*60+sec2);
	if(time_difference<0)
	return 1;
	else
	return 0;
}

void update_order(int current,int num_orders,Order orders[])//更新订单状态
{
	for(int i=0;i<num_orders;i++)
	{
		if(orders[i].completed==1)
		continue;
		else if(orders[i].completed==2)
		{
			if(compare_time(orders,current,i))
			{
				orders[i].completed=1;
				break;
			}
		}
	}
}

void calculate_waiting_time(Order orders[],int combo_count,int food_count,int current,Food foods[],Combo combos[])
{
	int waiting_time=0;
	int i=0,j=0,k=0;
	if(orders[current].completed==1)
	strcpy(orders[current].finish_time,orders[current].start_time);
	else if(orders[current].completed==2)
	{
		if(judge_type(orders,combos,current,combo_count)==1)
		{
			for(i=0;i<food_count;i++)
			{
				if(strcmp(foods[i].name,orders[current].food_name)==0)
				break;
			}
			waiting_time=(1-foods[i].current_storage)*foods[i].time_to_make;
			update_time(orders,current,waiting_time);
		}
		else if(judge_type(orders,combos,current,combo_count)==0)
		{
			for(i=0;i<combo_count;i++)
			{
				if(strcmp(combos[i].name,orders[current].food_name)==0)
				break;
			}
			for(j=1;j<5&&strcmp(combos[i].foods[j],"")!=0;j++)
			{
				for(k=0;k<food_count;k++)
				{
					if(strcmp(combos[i].foods[j],foods[k].name)==0)
					break;
				}
				if(waiting_time<((1-foods[k].current_storage)*foods[k].time_to_make))
				waiting_time=((1-foods[k].current_storage)*foods[k].time_to_make);
			}
			update_time(orders,current,waiting_time);
		}
	}
}
void judge_systeam(Order orders[],int current,int w2,int num_orders,int *on_off)
{
	
}
int judge_order(Order orders[],Food foods[],Combo combos[], int current,int w1,int num_orders,int food_count,int combo_count)//判断是否下单成功
{
	int hour;
	int i,j,k,state=1,uncompleted=0;
	sscanf(orders[current].start_time,"%d",&hour);
	if(hour<7||hour>21)
	{
		orders[current].completed=0;
		return 0;	
	}
	for(i=0;i<current;i++)
	{
		if(orders[i].completed==2)
		uncompleted++;
	}
	if(uncompleted>w1)
	{
		orders[current].completed=0;
		return 0;
	}
	else
	{
		if(judge_type(orders,combos,current,combo_count)==1)
		{
			for(i=0;i<num_orders;i++)
			{
				if(strcmp(orders[current].food_name,foods[i].name)==0)
				break;
			}
			orders[current].completed=reduce_food(current,foods);
		}
		else if(judge_type(orders,combos,current,combo_count)==0)
		{
			for(i=0;i<combo_count;i++)
			{
				if(strcmp(orders[current].food_name,combos[i].name))
				break;
			}
			for(j=1;j<5;j++)
			{
				if(strcmp(combos[i].foods[j],"")==0)
				break;
				for(k=0;k<food_count;k++)
				{
					if(strcmp(combos[i].foods[j],foods[k].name)==0)
					break;
				}
				if(reduce_food(k,foods)==2)
				{
					state=2;
					break;
				}
			}
			orders[current].completed=state;
		}
	}
	return orders[current].completed;
}

int main()
{
	input_menu();
	input_order(num_orders);
	for(int i=0;i<num_orders;i++)
	{
		update_food_storage(foods,orders);
		update_order(i,num_orders,orders);
		if((judge_order(orders,foods,combos,i,w1,num_orders,food_count,combo_count))!=0)
		{
			calculate_waiting_time(orders,combo_count,food_count,i,foods,combos);
		}
	}
	printresult(orders,num_orders);
	return 0;
}
