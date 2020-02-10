#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef MAIN_H
#define MAIN_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#define MAXCARDNUMBER 100000
#define _CRT_SECURE_NO_WARNINGS
#define bool int
#define true 1
#define false 0
#define  price 10

typedef struct Card
{
	char	aName[18];		//卡号
	char	aPwd[8];		//密码
	char    Name[18];		//持卡人
	int		nStatus;		//卡状态（0-未上机；1-正在上机；2-已注销；3-失效）
	time_t	tStart;			//开卡时间
	time_t	tEnd;			//卡的截止时间
	double	fTotalUse;		//累计金额
	time_t	tLast;			//最后使用时间
	int		nUseCount;		//使用次数
	double	fBalance;		//余额
	int		nDel;			//删除标识 0-未删除，1-删除
}Card;

typedef struct Node
{
	Card*	data;
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

//菜单			
void outputMenu();
void addCard();
void printCard();
void useComputer();
void exitComputer();
void topUp();
void withdraw();
void searchAll();
void exitCard();


//文件
int saveCard(char aName[],char aPwd[],double fBalance,struct tm endtm);
void updateSave(Card* data);
void updateSaveAll();

//链表
void initCardList();
void addToList(Card* p, Node* head);
Card* queryCard(char aName[]);
Node* queryCards(const char aName[]);
void printAll(const Node* p);

//log
void initOptLog();
void initLoginLog();
void addLogToList(Card* card, int opt, time_t time);
void addOptLogToList(Card* card, int opt, time_t time, double money, double pre_money, double after_money, other_log* optLogHead);
other_log* searchOptLog(char aName[]);

//log文件
void saveLog(login_log* p);
void updateLog();
void updateOptLog();
void saveOptLog(other_log* p);

//查询
void search_user_total();
void search_user_cost_log();
void search_total_input();
void search_total_input_month();


#endif