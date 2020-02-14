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
	char	aName[18];		//����
	char	aPwd[8];		//����
	int		nStatus;		//��״̬��0-δ�ϻ���1-�����ϻ���2-��ע����3-ʧЧ��
	time_t	tStart;			//����ʱ��
	time_t	tEnd;			//���Ľ�ֹʱ��
	float	fTotalUse;		//�ۼƽ��
	time_t	tLast;			//���ʹ��ʱ��
	int		nUseCount;		//ʹ�ô���
	float	fBalance;		//���
	int		nDel;			//ɾ����ʶ 0-δɾ����1-ɾ��
}Card;

typedef struct Node
{
	Card* data;
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


int opt;				// �ϻ�״̬ 
Node card;				// ������ 
login_log loginLog;		// ��¼����log���� 
//other_log optLog;		// ����log���� 
Node* head;
login_log* headl;
other_log* heado;


// ���濨��Ϣ
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
// ��ʼ������
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
// ��ѯ��
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
// ��������
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
// ģ����ѯ��
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

// ɾ���ڵ� 
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
// ��������
//Card* searchList(char* aName, Node* head);


// ��ӡ�������� 
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
	printf("----------�˵�----------\n"
		"1: ��ӿ�\n"
		"2: ��ѯ��\n"
		"3: �ϻ�\n"
		"4: �»�\n"
		"5����ֵ\n"
		"6: �˷�\n"
		"7: ��ѯͳ��\n"
		"8: ע��\n"
		"0: �˳�ϵͳ\n"
		"��ѡ��˵����ţ� ");
	scanf_s("%d", &opt);
}
//��ӿ�
void addCard()
{
	puts("----------��ӿ�----------");
	char Name[18];
	Card* p;
	p = (Card*)malloc(sizeof(Card));
	printf("�����뿨��<����Ϊ1~18>: ");
	scanf_s("%s", Name);
	if (queryCard(Name))
		puts("�����ѱ�ע��");
	else {
		strcpy_s(p->aName, sizeof(p->aName) / sizeof(p->aName[0]), Name);
		printf("����������<����Ϊ1~8>: ");
		scanf_s("%s", p->aPwd);
		printf("�����뿪�����<RMB>: ");
		scanf_s("%.2f", p->fBalance);
		p->nStatus = 0;
		p->tStart = time(NULL);
		p->fTotalUse = 0;
		p->tLast = time(NULL);
		p->nUseCount = 0;
		p->nDel = 0;
		addToList(p, head);
		if (int i = saveCard(p)) {
			puts("��ӿ�����Ϣ�ɹ���");
		}
	}
}
//��ѯ��
void printCard()
{
	puts("----------��ѯ��----------");
	char Name[19];
	printf("�������ѯ�Ŀ���<����Ϊ1~18>: ");
	scanf_s("%s", Name);
	Node* p = queryCards(Name);
	if (p) {
		printAll(p);
	}
	else {
		printf("�޴˿���\n");
	}
}
//�ϻ�
void useComputer()
{
	puts("----------�ϻ�----------");
	char Name[19], Pwd[9];
	printf("�����뿨��: ");
	scanf_s("%s", &Name);
	Card* p = queryCard(Name);
	if (p) {
		printf("����������: ");
		scanf_s("%s", Pwd);
		if (strcmp(p->aPwd, Pwd) == 0) {
			if (p->fBalance > 0) {
				if (p->nStatus == 0) {
					p->tLast = time(NULL);
					p->nStatus = 1;
					p->nUseCount++;
					puts("�ϻ��ɹ�");
					printf("����\t���\t�ϻ�ʱ��\n");
					printf("%s\t%s\t%s %s\n", p->aName, p->aPwd, __TIME__, __DATE__);
				}
				else {
					puts("Error:�ظ���½");
				}
			}
			else {
				puts("����");
			}
		}
		else {
			puts("�޴˿���");
		}
	}

}
//�»�
void exitComputer()
{
	puts("----------�»�----------");
	char Name[19], Pwd[9];
	printf("�����뿨��: ");
	scanf_s("%s", &Name);
	Card* p = queryCard(Name);
	if (p) {
		printf("����������: ");
		scanf_s("%s", Pwd);
		if (strcmp(p->aPwd, Pwd) == 0) {
			if (p->fBalance > 0) {
				if (p->nStatus == 1) {
					p->tLast = time(NULL);
					p->nStatus = 0;
					p->fBalance -= 0.01;
					puts("�»��ɹ�");
				}
				else {
					puts("Error:δ��¼");
				}
			}
			else {
				puts("����");
			}
		}
		else {
			puts("�������");
		}
	}
}
//��ֵ
void topUp()
{
	puts("----------��ֵ----------");
	printf("�������˺ţ�");
	char Name[19], Pwd[9];
	scanf_s("%s", Name);
	Card* p = queryCard(Name);
	if (p) {
		printf("����������: ");
		scanf_s("%s", Pwd);
		if (strcmp(p->aPwd, Pwd) == 0) {
			if (p->nStatus == 1) {
				p->tLast = time(NULL);
				printf("�������ֵ��");
				float n;
				scanf_s("%.2f", &n);
				if (n > 0) {
					p->fBalance += n;
					puts("��ֵ�ɹ�����ֵ��Ϣ����");
					printf("����\t��ֵ���\t���\n");
					printf("%s\t%.2f\t%.2f\n", Name, n, p->fBalance);
					if (p->fBalance > 0) {
						p->nStatus = 0;
						puts("�»��ɹ�");
					}
					else
						printf("���㣬���ٳ�ֵ%.2fԪ\n", -p->fBalance);
				}
				else
					puts("��ֵʧ�ܻ��ֵ���Ϊ0");
			}
			else
				puts("Error:δ��¼");
		}
		else
			puts("�������");
	}
}
//�˷�
void withdraw()
{
	puts("----------�˷�----------");
	char Name[19], Pwd[9];
	printf("�����뿨��: ");
	scanf_s("%s", &Name);
	Card* p = queryCard(Name);
	if (p) {
		printf("����������: ");
		scanf_s("%s", Pwd);
		if (strcmp(p->aPwd, Pwd) == 0) {
			if (p->fBalance > 0) {
				if (p->nStatus == 1) {
					p->tLast = time(NULL);
					printf("�˷ѽ�");
					float n;
					scanf_s("%.2f", &n);
					if (p->fBalance - n >= 0) {
						p->fBalance -= n;
						puts("�˷ѳɹ�");
					}
					else
						puts("�˷�ʧ��");
				}
				else {
					puts("Error:δ��¼");
				}
			}
			else {
				puts("����");
			}
		}
		else {
			puts("�������");
		}
	}
}
//��ѯͳ��
void searchAll()
{
	puts("----------�˷�ͳ��----------");
	puts("    ------  �˵�  ------");
	puts("1:��ѯ�û����Ѽ�¼");
	puts("2:��ѯ��Ӫҵ��");
	puts("3:��ѯ��Ӫҵ��");
	puts("��ѡ��˵�����: ");
	int menu;
	do
		scanf_s("%d", &menu);
	while (strchr("123", menu) == 0);
	switch (menu) {
	case '1':
	case '2':
	case '3':puts("�ù���ά���У���ͣʹ�ã����ˣ�����"); break;
	}
}
//ע��
void exitCard()
{
	puts("----------ע��----------");
	char Name[19], Pwd[8];
	printf("������ע������<����Ϊ1~18>��");
	scanf_s("%s", Name);
	Card* p = queryCard(Name);
	if (p) {
		printf("���������룺");
		scanf_s("%s", Pwd);
		if (strcmp(p->aPwd, Pwd) == 0) {
			if (p->fBalance >= 0) {
				if (p->nStatus == 1)
					puts("����ʹ��");
				else {
					p->nDel = 1;
					puts("ע���ɹ�");
					printf("����\t�˷ѽ��\n");
					printf("%s\t%.2f\n", Name, &p->fBalance);
					Node* current = queryCards(Name);
					deleNode(Name, current);
				}
			}
			else
				printf("���㣬���ֵ%.2f\n", &p->fBalance);
		}
		else
			puts("�������");
	}
	else
		puts("�޴˿���");
}
// ��ʼ��log 
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
// ���log 
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
// ��log 
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

// ����log�ļ� 
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
