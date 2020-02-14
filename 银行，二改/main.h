#pragma once
#ifndef MAIN_H
#define MAIN_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAXCARDNUMBER 100000
#define _CRT_SECURE_NO_WARNINGS
#define bool int
#define true 1
#define false 0

typedef struct Card
{
	char	aName[18];		//卡号
	char	aPwd[8];		//密码
	int		nStatus;		//卡状态（0-未上机；1-正在上机；2-已注销；3-失效）
	time_t	tStart;			//开卡时间
	time_t	tEnd;			//卡的截止时间
	float	fTotalUse;		//累计金额
	time_t	tLast;			//最后使用时间
	int		nUseCount;		//使用次数
	float	fBalance;		//余额
	int		nDel;			//删除标识 0-未删除，1-删除
}Card;

typedef struct Node
{
	Card* data;
	struct Node* next;
}Node;

typedef struct login_log
{
	Card* card;
	int opt; // opt-1:下机 0:上机
	time_t time;
	struct login_log* next;
}login_log;

typedef struct other_log
{
	Card* card;
	int opt; 			// opt-0:注销卡 1:充值 2:退费
	int money;			// 当opt==1 or 2时：操作所涉及的金额 ；opt==0:money=0
	int pre_money;		// 当opt==1 or 2时：操作前的金额 ；opt==0:pre_money=0
	int after_money;	// 当opt==1 or 2时：操作后的金额 ；opt==0:after_money=0
	time_t time;
	struct other_log* next;
}other_log;


int opt;				// 上机状态 
Node card;				// 卡链表 
login_log loginLog;		// 登录操作log链表 
//other_log optLog;		// 消费log链表 
Node* head;
login_log* headl;
other_log* heado;


// 保存卡信息
int saveCard(Card* p)
{
	char str[19];
	strcpy_s(str, sizeof(str) / sizeof(str[0]), p->aName);
	FILE* fp;
	fopen_s(&fp, "data.txt", "a+");
	if (fp == NULL) {
		puts("Wrong.");
		return 0;
	}
	fprintf(fp, "%s\t%s\t%d\t%d\t%d\t%.2f\t%d\t%d\t%d\t%.2f\t%d\n",
		p->aName, p->aPwd, p->nStatus, p->tStart, p->tEnd, p->fTotalUse, p->tLast, p->nUseCount, p->fBalance, p->nDel);
	if (fclose(fp)) {
		printf("Can't close \"data.txt\".\n");
		return 0;
	}
	return 1;
}
// 初始化链表
void initCardList()
{
	FILE* fp;
	if ((fopen_s(&fp, "data.txt", "r")) == NULL) {
		printf("Can't open this file.\n");
	}
	if ((Node*)malloc(sizeof(Node)) == NULL) {
		printf("Can't malloc the Node *");
	}
	head = (Node*)malloc(sizeof(Node));
	Node* p = head;
	while (feof(fp)) {
		p->data = (Card*)malloc(sizeof(Card));
		fscanf_s(fp, "%s", p->data->aName);
		fscanf_s(fp, "%s", p->data->aPwd);
		fscanf_s(fp, "%d", &p->data->nStatus);
		fscanf_s(fp, "%d", &p->data->tStart);
		fscanf_s(fp, "%d", &p->data->tEnd);
		fscanf_s(fp, "%.2f", &p->data->fTotalUse);
		fscanf_s(fp, "%d", &p->data->tLast);
		fscanf_s(fp, "%d", &p->data->nUseCount);
		fscanf_s(fp, "%.2f", &p->data->fBalance);
		fscanf_s(fp, "%d", &p->data->nDel);
		p->next = (Node*)malloc(sizeof(Node));
		p = p->next;
	}
	p->next = NULL;
	if (fclose(fp))
		printf("Can't close this file.\n");
}
// 查询卡
Card* queryCard(char* aName)
{
	Node* p = head;
	Node* c = NULL;
	while (p->data != NULL) {
		if (strcmp(p->data->aName, aName) == 0) {
			c = p;
			return c->data;
		}
		p = p->next;
	}
	if (c == NULL) {
		printf("This card doesn't exist.\n");
		return NULL;
	}
}
// 加入链表
void addToList(Card* a, Node* head)
{
	Node* p = head;
	Node* insert;
	insert = (Node*)malloc(sizeof(Node));
	while (p->next->data) {
		p = p->next;
	}
	p->next = insert;
	insert->data = a;
	insert->next = NULL;
}
// 模糊查询卡
Node* queryCards(const char* aName)
{
	Node* p = head, * c;
	c = (Node*)malloc(sizeof(Node));
	while (p->data) {
		if (strstr(p->data->aName, aName)) {
			addToList(p->data, c);
		}
		p = p->next;
	}
	return c;
}

// 删除节点 
int deleNode(char* aName, Node* head)
{
	Node* p = head;
	while (p) {
		if (strcmp(p->next->data->aName, aName) == 0) {
			p->next = p->next->next;
			return 1;
		}
	}
	printf("Can't find that Node.\n");
	return 0;
}
// 查找链表
//Card* searchList(char* aName, Node* head);


// 打印所有数据 
void printAll(Node* head)
{
	puts("The information retrieved is as follows:");
	puts("Card\tStatus\tBalance\tTotalUse\tCountUse\tLastTime");
	Node* p = head;
	while (p) {
		struct tm* t = NULL;
		gmtime_s(t, &(p->data->tLast));
		printf("%s\t%d\t%.2f\t%.2f\t%d\t%d:%d\t%d.%d.%d\n", p->data->aName, p->data->nStatus,
			p->data->fBalance, p->data->fTotalUse, p->data->nUseCount,
			t->tm_hour, t->tm_min, 1 + t->tm_mon, t->tm_mday, 1900 + t->tm_year);
		p = p->next;
	}
}
void outputMenu()
{
	printf("----------菜单----------\n"
		"1: 添加卡\n"
		"2: 查询卡\n"
		"3: 上机\n"
		"4: 下机\n"
		"5：充值\n"
		"6: 退费\n"
		"7: 查询统计\n"
		"8: 注销\n"
		"0: 退出系统\n"
		"请选择菜单项编号： ");
	scanf_s("%d", &opt);
}
//添加卡
void addCard()
{
	puts("----------添加卡----------");
	char Name[18];
	Card* p;
	p = (Card*)malloc(sizeof(Card));
	printf("请输入卡号<长度为1~18>: ");
	scanf_s("%s", Name);
	if (queryCard(Name))
		puts("卡号已被注册");
	else {
		strcpy_s(p->aName, sizeof(p->aName) / sizeof(p->aName[0]), Name);
		printf("请输入密码<长度为1~8>: ");
		scanf_s("%s", p->aPwd);
		printf("请输入开卡金额<RMB>: ");
		scanf_s("%.2f", p->fBalance);
		p->nStatus = 0;
		p->tStart = time(NULL);
		p->fTotalUse = 0;
		p->tLast = time(NULL);
		p->nUseCount = 0;
		p->nDel = 0;
		addToList(p, head);
		if (int i = saveCard(p)) {
			puts("添加开卡信息成功！");
		}
	}
}
//查询卡
void printCard()
{
	puts("----------查询卡----------");
	char Name[19];
	printf("请输入查询的卡号<长度为1~18>: ");
	scanf_s("%s", Name);
	Node* p = queryCards(Name);
	if (p) {
		printAll(p);
	}
	else {
		printf("无此卡号\n");
	}
}
//上机
void useComputer()
{
	puts("----------上机----------");
	char Name[19], Pwd[9];
	printf("请输入卡号: ");
	scanf_s("%s", &Name);
	Card* p = queryCard(Name);
	if (p) {
		printf("请输入密码: ");
		scanf_s("%s", Pwd);
		if (strcmp(p->aPwd, Pwd) == 0) {
			if (p->fBalance > 0) {
				if (p->nStatus == 0) {
					p->tLast = time(NULL);
					p->nStatus = 1;
					p->nUseCount++;
					puts("上机成功");
					printf("卡号\t余额\t上机时间\n");
					printf("%s\t%s\t%s %s\n", p->aName, p->aPwd, __TIME__, __DATE__);
				}
				else {
					puts("Error:重复登陆");
				}
			}
			else {
				puts("余额不足");
			}
		}
		else {
			puts("无此卡号");
		}
	}

}
//下机
void exitComputer()
{
	puts("----------下机----------");
	char Name[19], Pwd[9];
	printf("请输入卡号: ");
	scanf_s("%s", &Name);
	Card* p = queryCard(Name);
	if (p) {
		printf("请输入密码: ");
		scanf_s("%s", Pwd);
		if (strcmp(p->aPwd, Pwd) == 0) {
			if (p->fBalance > 0) {
				if (p->nStatus == 1) {
					p->tLast = time(NULL);
					p->nStatus = 0;
					p->fBalance -= 0.01;
					puts("下机成功");
				}
				else {
					puts("Error:未登录");
				}
			}
			else {
				puts("余额不足");
			}
		}
		else {
			puts("密码错误");
		}
	}
}
//充值
void topUp()
{
	puts("----------充值----------");
	printf("请输入账号：");
	char Name[19], Pwd[9];
	scanf_s("%s", Name);
	Card* p = queryCard(Name);
	if (p) {
		printf("请输入密码: ");
		scanf_s("%s", Pwd);
		if (strcmp(p->aPwd, Pwd) == 0) {
			if (p->nStatus == 1) {
				p->tLast = time(NULL);
				printf("请输入充值金额：");
				float n;
				scanf_s("%.2f", &n);
				if (n > 0) {
					p->fBalance += n;
					puts("充值成功，充值信息如下");
					printf("卡号\t充值金额\t余额\n");
					printf("%s\t%.2f\t%.2f\n", Name, n, p->fBalance);
					if (p->fBalance > 0) {
						p->nStatus = 0;
						puts("下机成功");
					}
					else
						printf("余额不足，请再充值%.2f元\n", -p->fBalance);
				}
				else
					puts("充值失败或充值金额为0");
			}
			else
				puts("Error:未登录");
		}
		else
			puts("密码错误");
	}
}
//退费
void withdraw()
{
	puts("----------退费----------");
	char Name[19], Pwd[9];
	printf("请输入卡号: ");
	scanf_s("%s", &Name);
	Card* p = queryCard(Name);
	if (p) {
		printf("请输入密码: ");
		scanf_s("%s", Pwd);
		if (strcmp(p->aPwd, Pwd) == 0) {
			if (p->fBalance > 0) {
				if (p->nStatus == 1) {
					p->tLast = time(NULL);
					printf("退费金额：");
					float n;
					scanf_s("%.2f", &n);
					if (p->fBalance - n >= 0) {
						p->fBalance -= n;
						puts("退费成功");
					}
					else
						puts("退费失败");
				}
				else {
					puts("Error:未登录");
				}
			}
			else {
				puts("余额不足");
			}
		}
		else {
			puts("密码错误");
		}
	}
}
//查询统计
void searchAll()
{
	puts("----------退费统计----------");
	puts("    ------  菜单  ------");
	puts("1:查询用户消费记录");
	puts("2:查询总营业额");
	puts("3:查询月营业额");
	puts("请选择菜单项编号: ");
	int menu;
	do
		scanf_s("%d", &menu);
	while (strchr("123", menu) == 0);
	switch (menu) {
	case '1':
	case '2':
	case '3':puts("该功能维护中，暂停使用（＞人＜；）"); break;
	}
}
//注销
void exitCard()
{
	puts("----------注销----------");
	char Name[19], Pwd[8];
	printf("请输入注销卡号<长度为1~18>：");
	scanf_s("%s", Name);
	Card* p = queryCard(Name);
	if (p) {
		printf("请输入密码：");
		scanf_s("%s", Pwd);
		if (strcmp(p->aPwd, Pwd) == 0) {
			if (p->fBalance >= 0) {
				if (p->nStatus == 1)
					puts("正在使用");
				else {
					p->nDel = 1;
					puts("注销成功");
					printf("卡号\t退费金额\n");
					printf("%s\t%.2f\n", Name, &p->fBalance);
					Node* current = queryCards(Name);
					deleNode(Name, current);
				}
			}
			else
				printf("余额不足，请充值%.2f\n", &p->fBalance);
		}
		else
			puts("密码错误");
	}
	else
		puts("无此卡号");
}
// 初始化log 
void initLoginLog()
{
	FILE* fp;
	if ((fopen_s(&fp, "LoginLog.txt", "r")) == NULL) {
		puts("Can't open that file.\n");
	}
	headl = (login_log*)malloc(sizeof(login_log));
	login_log* p = headl;
	headl->card == NULL;
	while (!feof(fp)) {
		p->card = (Card*)malloc(sizeof(login_log));
		fscanf_s(fp, "%s %s %d %d %d %.2f %d %d %.2f %d %d %d", p->card->aName, p->card->aPwd, &(p->card->nStatus), &(p->card->tStart), &(p->card->tEnd),
			&(p->card->fTotalUse), &(p->card->tLast), &(p->card->nUseCount), &(p->card->fBalance), &(p->card->nDel), &(p->opt), &(p->time));
		p->next = (login_log*)malloc(sizeof(login_log));
		p = p->next;
	}
	p->next = NULL;
	if (fclose(fp))
		puts("Can't close that file.");
}
void saveLog(login_log* log)
{
	FILE* fp;
	if ((fopen_s(&fp, "LoginLog.txt", "a+")) == NULL) {
		puts("Can't open LoginLog.txt.");
	}
	fprintf(fp, "%s\t%s\t%d\t%d\t%d\t%.2f\t%d\t%d\t%.2f\t%d\t%d\t%d\t%d\n", log->card->aName, log->card->aPwd, log->card->nStatus, log->card->tStart,
		log->card->tEnd, log->card->fTotalUse, log->card->tLast, log->card->nUseCount, log->card->fBalance, log->card->nDel, log->opt, log->time);
	if (fclose(fp)) {
		puts("Can't close file.");
	}
}
// 添加log 
void addLogToList(Card* card, int opt, time_t time)
{
	login_log* p = headl;
	login_log* insert;
	insert = (login_log*)malloc(sizeof(login_log));
	while (p->next->card) {
		p = p->next;
	}
	p->next = insert;
	insert->card = card;
	insert->opt = opt;
	insert->time = time;
	insert->next = NULL;
	saveLog(insert);
}
// 查log 
login_log* searchLog(char* aName)
{
	login_log* p = headl;
	login_log* c = NULL;
	while (p->card) {
		if (!strcmp(p->card->aName, aName)) {
			c = p;
			return c;
		}
		p = p->next;
	}
	if (c) {
		printf("Can't find the log.\n");
		return NULL;
	}
}

// 更新log文件 
void updateLog()
{
	FILE* fp;
	login_log* p;
	p = headl;
	if ((fopen_s(&fp, "LoginLog.txt", "w+")) == NULL) {
		puts("Can't open LoginLog.txt.");
	}
	while (p) {
		if (p->card)
			saveLog(p);
		p = p->next;
	}
	if (fclose(fp)) {
		puts("Can't close LoginLog.txt.");
	}
}
#endif
