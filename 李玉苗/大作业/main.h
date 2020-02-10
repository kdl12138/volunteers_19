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
	char	aName[18];		//����
	char	aPwd[8];		//����
	char    Name[18];		//�ֿ���
	int		nStatus;		//��״̬��0-δ�ϻ���1-�����ϻ���2-��ע����3-ʧЧ��
	time_t	tStart;			//����ʱ��
	time_t	tEnd;			//���Ľ�ֹʱ��
	double	fTotalUse;		//�ۼƽ��
	time_t	tLast;			//���ʹ��ʱ��
	int		nUseCount;		//ʹ�ô���
	double	fBalance;		//���
	int		nDel;			//ɾ����ʶ 0-δɾ����1-ɾ��
}Card;

typedef struct Node
{
	Card*	data;
	struct Node* next;
}Node;

typedef struct login_log
{
	Card* card;
	int opt; // opt-1:�»� 0:�ϻ�
	time_t time;
	struct login_log* next;
}login_log;

typedef struct other_log
{
	Card* card;
	int opt; 			// opt-0:ע���� 1:��ֵ 2:�˷�
	int money;			// ��opt==1 or 2ʱ���������漰�Ľ�� ��opt==0:money=0
	int pre_money;		// ��opt==1 or 2ʱ������ǰ�Ľ�� ��opt==0:pre_money=0
	int after_money;	// ��opt==1 or 2ʱ��������Ľ�� ��opt==0:after_money=0
	time_t time;
	struct other_log* next;
}other_log;

//�˵�			
void outputMenu();
void addCard();
void printCard();
void useComputer();
void exitComputer();
void topUp();
void withdraw();
void searchAll();
void exitCard();


//�ļ�
int saveCard(char aName[],char aPwd[],double fBalance,struct tm endtm);
void updateSave(Card* data);
void updateSaveAll();

//����
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

//log�ļ�
void saveLog(login_log* p);
void updateLog();
void updateOptLog();
void saveOptLog(other_log* p);

//��ѯ
void search_user_total();
void search_user_cost_log();
void search_total_input();
void search_total_input_month();


#endif