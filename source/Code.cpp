#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_TIME			54002
#define MAX_FOOD			101
#define MAX_COMBO			101
#define MAX_ORDERS			54002
#define MAX_TIME_LENGTH		9 // 定义时间字符串的最大长度
#define MAX_NAME_LEN		51
#define MAX_FOOD_NUM		5
#define ORDER_FAIL			0
#define ORDER_DONE			1
#define ORDER_WAIT			2
#define ORDER_T_COMBO		0
#define ORDER_T_FOOD		1
#define SYSTEM_ON			1
#define SYSTEM_DOWN			0


typedef struct
{
	char name[MAX_NAME_LEN];
	int food_index;	
	int time_to_make;
	int max_storage;
	int current_storage;
	int pass_time;
}Food;

typedef struct
{
	char name[MAX_NAME_LEN];
	char foods[MAX_FOOD_NUM][MAX_NAME_LEN];
	int num_foods;
}Combo;

typedef struct
{
	char food_name[MAX_NAME_LEN];
	char start_time[MAX_TIME_LENGTH];
	char finish_time[MAX_TIME_LENGTH];
	int completed;//0表示订单下单失败，1表示订单立即完成，2表示订单需等待
}Order;

Food foods[MAX_FOOD];
Combo combos[MAX_COMBO];
Order orders[MAX_ORDERS];
int food_count, combo_count;
int w1, w2;
int num_orders;
int system_state = SYSTEM_ON;

void input_menu()//读取菜单信息
{
	int i, j;
	FILE* filename = fopen("dict.dic", "r");
	fscanf(filename, "%d %d", &food_count, &combo_count);
	for (i = 0; i < food_count; i++)
		fscanf(filename, "%s", foods[i].name);

	for (i = 0; i < food_count; i++)
		fscanf(filename, "%d", &foods[i].time_to_make);

	for (i = 0; i < food_count; i++)
	{
		fscanf(filename, "%d", &foods[i].max_storage);
		foods[i].current_storage = 0;
		foods[i].pass_time = 0;
	}

	fscanf(filename, "%d %d", &w1, &w2);
	for (i = 0; i < combo_count; i++)
	{
		fscanf(filename, "%s", combos[i].name);
		combos[i].num_foods = 0;
		char line[MAX_FOOD_NUM * MAX_NAME_LEN];
		while (fgets(line, sizeof(line), filename) != NULL)
		{
			char* token = strtok(line, " ");
			j = 0;
			while (token != NULL)
			{
				strcpy(combos[i].foods[j], token);
				token = strtok(NULL, " ");
				j++;
				combos[i].num_foods++;
			}
			combos[i].foods[j - 1][strlen(combos[i].foods[j - 1]) - 1] = 0;
			break;
		}
	}
	fclose(filename);
}

void input_order()//读取订单信息
{
	scanf("%d", &num_orders);
	for (int i = 0; i < num_orders; i++)
	{
		scanf("%s %s", orders[i].start_time, orders[i].food_name);
	}
}

int calculate_delta_time(int currentIndex)//计算订单时间差
{
	int time_difference;
	int hour1, min1, sec1;
	int hour2, min2, sec2;
	if (currentIndex == 0) {
		hour2 = 7;
		min2 = 0;
		sec2 = 0;
		sscanf(orders[currentIndex].start_time, "%d:%d:%d", &hour1, &min1, &sec1);
	}
	else {
		sscanf(orders[currentIndex].start_time, "%d:%d:%d", &hour1, &min1, &sec1);
		sscanf(orders[currentIndex - 1].start_time, "%d:%d:%d", &hour2, &min2, &sec2);
	}
	
	time_difference = hour1 * 3600 + min1 * 60 + sec1 - (hour2 * 3600 + min2 * 60 + sec2);
	return time_difference;
}

void update_food_storage(int currentIndex)//更新食物储备
{
	int delta_time = calculate_delta_time(currentIndex);
	for (int i = 0; i < food_count; i++)
	{
		foods[i].current_storage = (foods[i].current_storage) + (delta_time + foods[i].pass_time) / foods[i].time_to_make;
		foods[i].pass_time = (delta_time + foods[i].pass_time) % foods[i].time_to_make;

		if (foods[i].current_storage >= foods[i].max_storage) {
			foods[i].current_storage = foods[i].max_storage;
			foods[i].pass_time = 0;
		}
	}
}

int judge_type(int current)//判断是单点还是套餐，单点返回1，套餐返回0
{
	int result = ORDER_T_FOOD;
	for (int i = 0; i < combo_count && result != ORDER_T_COMBO; i++)
		result = strcmp(orders[current].food_name, combos[i].name);
	return result == ORDER_T_COMBO ? ORDER_T_COMBO : ORDER_T_FOOD;
}

void update_time(int current, int waiting_time)//更新订单完成时间
{
	int hour, min, sec;
	sscanf(orders[current].start_time, "%d:%d:%d", &hour, &min, &sec);
	int totalSeconds = hour * 3600 + min * 60 + sec;
	totalSeconds += waiting_time;
	hour = (totalSeconds / 3600) % 24;
	min = (totalSeconds / 60) % 60;
	sec = totalSeconds % 60;
	sprintf(orders[current].finish_time, "%02d:%02d:%02d", hour, min, sec);
}

void printresult()//打印最终结果
{
	int i;
	for (i = 0; i < num_orders; i++)
	{
		if (orders[i].completed == ORDER_FAIL)
			printf("Fail\n");
		else
			printf("%s\n", orders[i].finish_time);
	}
}

int reduce_food(int current_food)//减少食物量
{
	int state = ORDER_DONE;
	if (foods[current_food].current_storage < 1)
		state = ORDER_WAIT;
	foods[current_food].current_storage--;
	return state;
}

int compare_time(int current, int i)//比较当前订单与之前订单时间
{
	int time_difference;
	int hour1, min1, sec1;
	int hour2, min2, sec2;
	sscanf(orders[i].finish_time, "%d:%d:%d", &hour1, &min1, &sec1);
	sscanf(orders[current].start_time, "%d:%d:%d", &hour2, &min2, &sec2);
	return time_difference = hour1 * 3600 + min1 * 60 + sec1 - (hour2 * 3600 + min2 * 60 + sec2);
}

void update_order(int current)//更新订单状态
{
	int uncompleted = 0;
	int result;
	int flag = 0;

	for (int i = 0; i < current; i++)
	{
		if (orders[i].completed == ORDER_DONE)
			continue;
		else if (orders[i].completed == ORDER_WAIT)
		{
			uncompleted++;
			result = compare_time(current, i);
			if (result > 0)
				continue;
			uncompleted--;
			orders[i].completed = ORDER_DONE;
			if (result == 0)
			{
				flag++;
			}
		}
	}
	
	if (flag == 0) {
		if (system_state == SYSTEM_DOWN && uncompleted < w2) {
			system_state = SYSTEM_ON;
		}
	}
	else {
		if (system_state == SYSTEM_DOWN && uncompleted < w2 - flag) {
			system_state = SYSTEM_ON;
		}
	}
}

void calculate_waiting_time(int current)
{
	int waiting_time = 0;
	int i = 0, j = 0, k = 0;
	if (orders[current].completed == ORDER_DONE)
		strcpy(orders[current].finish_time, orders[current].start_time);
	else if (orders[current].completed == ORDER_WAIT)
	{
		if (judge_type(current) == ORDER_T_FOOD)
		{
			for (i = 0; i < food_count; i++)
			{
				if (strcmp(foods[i].name, orders[current].food_name) == 0)
					break;
			}
			if (i != food_count) {
				waiting_time = (0 - foods[i].current_storage) * foods[i].time_to_make - foods[i].pass_time;
				update_time(current, waiting_time);
			}
		}
		else if (judge_type(current) == ORDER_T_COMBO)
		{
			for (i = 0; i < combo_count; i++)
			{
				if (strcmp(combos[i].name, orders[current].food_name) == 0)
					break;
			}
			for (j = 0; i != combo_count && j < MAX_FOOD_NUM && strcmp(combos[i].foods[j], "") != 0; j++)
			{
				for (k = 0; k < food_count; k++)
				{
					if (strcmp(combos[i].foods[j], foods[k].name) == 0)
						break;
				}
				if (k != food_count && waiting_time < ((0 - foods[k].current_storage) * foods[k].time_to_make - foods[k].pass_time))
					waiting_time = ((0 - foods[k].current_storage) * foods[k].time_to_make - foods[k].pass_time);
			}
			update_time(current, waiting_time);
		}
	}
}

int judge_order(int current)//判断是否下单成功
{
	int i, j, k, state = 1, uncompleted = 0;


	for (i = 0; i < current; i++)
	{
		if (orders[i].completed == ORDER_WAIT)
			uncompleted++;
	}
	if (system_state == SYSTEM_DOWN || uncompleted > w1)
	{
		orders[current].completed = ORDER_FAIL;
		return ORDER_FAIL;
	}

	if (judge_type(current) == ORDER_T_FOOD)
	{
		for (i = 0; i < food_count; i++)
		{
			if (strcmp(orders[current].food_name, foods[i].name) == 0)
				break;
		}
		orders[current].completed = reduce_food(i);
	}
	else if (judge_type(current) == ORDER_T_COMBO)
	{
		for (i = 0; i < combo_count; i++)
		{
			if (strcmp(orders[current].food_name, combos[i].name) == 0)
				break;
		}
		for (j = 0; j < MAX_FOOD_NUM; j++)
		{
			if (strcmp(combos[i].foods[j], "") == 0)
				break;
			for (k = 0; k < food_count; k++)
			{
				if (strcmp(combos[i].foods[j], foods[k].name) == 0)
					break;
			}
			if (k != food_count && reduce_food(k) == ORDER_WAIT)
			{
				state = ORDER_WAIT;
			}
		}
		orders[current].completed = state;
	}
	if (uncompleted >= w1 && orders[current].completed == ORDER_WAIT) {
		system_state = SYSTEM_DOWN;
	}
	
	return orders[current].completed;
}

int main()
{
	input_menu();
	input_order();
	for (int i = 0; i < num_orders; i++)
	{
		update_food_storage(i);
		update_order(i);
		if ((judge_order(i)) != ORDER_FAIL)
		{
			calculate_waiting_time(i);
		}
	}
	printresult();
	return 0;
}
