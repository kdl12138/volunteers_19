#include "main.h"
extern other_log* optLogHead;

void search_user_total() {
	char name[18];
	char pwd[8];
	Card* p;
	other_log* t;
	struct tm* time;

	printf("请输入卡号（16位）：");
	getchar();
	gets_s(name);
	while (strlen(name) != 16) {
		printf("请输入16位数字\n");
		gets_s(name);
	}
	printf("请输入密码（6位）：");
	gets_s(pwd);
	while (strlen(pwd) != 6) {
		printf("请输入6位数字\n");
		gets_s(pwd);
	}

	p = queryCard(name);

	if (p != NULL) {

		if (strcmp(p->aPwd, pwd) == 0) {
			t = searchOptLog(name);
			printf("消费时间\t\t\t消费金额\t\t\t消费类型\n");
			while (t != NULL) {
				time = gmtime(&(t->time));
				printf("%d-%d-%d %d:%d\t%d\t%d\n", 1900 + time->tm_year, 1 + time->tm_mon, time->tm_mday,
					time->tm_hour, time->tm_min, t->money, t->opt);
				t = t->next;
			}
		}
		else {
			printf("密码错误\n");
		}
	}
	else {
		printf("无此用户\n");
	}
}

void search_user_cost_log() {
	char name[18];
	char pwd[8];
	int start_year, start_month, start_day;
	int end_year, end_month, end_day;
	Card* p;
	other_log* t;
	struct tm* time;

	printf("请输入卡号（16位）：");
	getchar();
	gets_s(name);
	while (strlen(name) != 16) {
		printf("请输入16位数字\n");
		gets_s(name);
	}
	printf("请输入密码（6位）：");
	gets_s(pwd);
	while (strlen(pwd) != 6) {
		printf("请输入6位数字\n");
		gets_s(pwd);
	}

	p = queryCard(name);

	if (p != NULL) {

		if (strcmp(p->aPwd, pwd) == 0) {

			printf("请输入起始时间（格式为xxxx:xx:xx）:");
			scanf_s("%d:%d:%d", &start_year, &start_month, &start_day);
			printf("请输入结束时间（格式为xxxx:xx:xx）:");
			scanf_s("%d:%d:%d", &end_year, &end_month, &end_day);
			t = searchOptLog(name);
			printf("消费时间\t消费金额\t消费类型\n");
			while (t != NULL) {
				time = gmtime(&(t->time));
				if ((start_year <= (1900 + time->tm_year)) && (start_month <= (1 + time->tm_mon)) && (start_day <= time->tm_mday)
					&& (end_year >= (1900 + time->tm_year)) && (end_month >= (time->tm_mon + 1)) && (end_day >= time->tm_mday)) {
					printf("%d-%d-%d %d:%d\t%d\t%d\n", 1900 + time->tm_year, 1 + time->tm_mon, time->tm_mday,
						time->tm_hour, time->tm_min, t->money, t->opt);
				}
				t = t->next;
			}
		}
		else {
			printf("密码错误。\n");
		}

	}
	else {
		printf("无此用户。\n");
	}
}

void search_total_input(){
	int start_year, start_month, start_day;
	int end_year, end_month, end_day;
	other_log* t;
	struct tm* time;
	int money = 0;

	t = optLogHead;

	printf("请输入起始时间（格式为xxxx:xx:xx）:");
	scanf_s("%d:%d:%d", &start_year, &start_month, &start_day);
	printf("请输入结束时间（格式为xxxx:xx:xx）:");
	scanf_s("%d:%d:%d", &end_year, &end_month, &end_day);
	while (t != NULL) {
		time = gmtime(&(t->time));
		if ((start_year <= (1900 + time->tm_year)) && (start_month <= (1 + time->tm_mon)) && (start_day <= time->tm_mday)
			&& (end_year >= (1900 + time->tm_year)) && (end_month >= (time->tm_mon + 1)) && (end_day >= time->tm_mday)) {
			money = money + (t->money);
		}
		t = t->next;
	}
	printf("总营业额为：%d元\n", money);
}

void search_total_input_month() {
	int month;
	int money = 0;
	other_log* p;
	struct tm* time;

	p = optLogHead;

	printf("请输入月份：");
	scanf_s("%d", &month);
	while (p != NULL) {
		time = gmtime(&(p->time));
		if (month == (time->tm_mon + 1)) {
			money = money + (p->money);
		}
		p = p->next;
	}
	printf("%d月的营业额为%d元\n", month, money);
}
