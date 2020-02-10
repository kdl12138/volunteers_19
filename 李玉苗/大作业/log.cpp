#include "main.h"
extern login_log* loginHead;
extern other_log* optLogHead;

void initOptLog(){
	FILE* fp;
	if ((fp = fopen("other_log_info.txt", "r")) == NULL) {   
		printf("文件打开失败\n");
	}


	optLogHead = (other_log*)malloc(sizeof(other_log));
	if (optLogHead == NULL) {
		printf("内存分配失败\n");
		exit(-1);
	}
	other_log* p = optLogHead;
	optLogHead->card = NULL;

	while (!feof(fp)) {
		p->card = (Card*)malloc(sizeof(Card));
		if (fscanf(fp, "%s %s %d %lld %lld %lf %lld %d %lf %d %d %d %d %d %lld", p->card->aName, p->card->aPwd,
			&(p->card->nStatus), &(p->card->tStart), &(p->card->tEnd), &(p->card->fTotalUse), &(p->card->tLast),
			&(p->card->nUseCount), &(p->card->fBalance), &(p->card->nDel), &(p->opt), &(p->money), &(p->pre_money),
			&(p->after_money), &(p->time)) == -1) {
			p->card = NULL;
			p->opt = NULL;
			p->money = NULL;
			p->pre_money = NULL;
			p->after_money = NULL;
			p->time = NULL;
			break;
		}
		p->next = (other_log*)malloc(sizeof(other_log));  
		if (p->next == NULL) {
			printf("内存分配失败\n");
			exit(-1);
		}
		p = p->next;                                      
	}
	p->next = NULL;

	if (fclose(fp)) {                               
		printf("文件关闭失败\n");
	}
}

void initLoginLog(){

	loginHead = (login_log*)malloc(sizeof(login_log));
	if (loginHead == NULL) {
		printf("内存分配失败\n");
		exit(-1);
	}

	login_log* p = loginHead;
	loginHead->card = NULL;

	FILE* fp;
	fp = (FILE*)malloc(sizeof(FILE));
	if (fp == NULL) {
		printf("内存分配失败\n");
		exit(-1);
	}

	if ((fp = fopen("login_log_info.txt", "r")) == NULL) {   
		printf("文件打开失败\n");
	}

	while (!feof(fp)) {
		p->card = (Card*)malloc(sizeof(Card));
		if (p->card == NULL) {
			printf("内存分配失败\n");
			exit(-1);
		}

		if (p->card == NULL) {
			printf("内存分配失败\n");
			exit(-1);
		}

		if (fscanf(fp, "%s %s %d %lld %lld %lf %lld %d %lf %d %d %lld", p->card->aName, p->card->aPwd,
			&(p->card->nStatus), &(p->card->tStart), &(p->card->tEnd), &(p->card->fTotalUse), &(p->card->tLast),
			&(p->card->nUseCount), &(p->card->fBalance), &(p->card->nDel), &(p->opt), &(p->time)) == -1) {
			p->card = NULL;
			p->opt = NULL;
			p->time = NULL;
			break;
		}
		p->next = (login_log*)malloc(sizeof(login_log));   
		p = p->next;                                      
	}
	p->next = NULL;

	if (fclose(fp)) {                                 
		printf("文件关闭失败\n");
	}
}

void addLogToList(Card* card, int opt, time_t time) {
	login_log* p = loginHead;
	login_log* t;
	t = (login_log*)malloc(sizeof(login_log));
	if (t == NULL) {
		printf("内存分配失败\n");
		exit(-1);
	}

	while (p->next != NULL && p->next->card != NULL) {
		p = p->next;
	}

	p->next = t;
	t->card = card;
	t->opt = opt;
	t->time = time;
	t->next = NULL;
	saveLog(t);
}

void addOptLogToList(Card* card, int opt, time_t time, double money, double pre_money, double after_money, other_log* optLogHead) {
	other_log* t;
	other_log* p = optLogHead;
	t = (other_log*)malloc(sizeof(other_log));
	if (t == NULL) {
		printf("内存分配失败");
			exit(-1);
	}

	while (p->next != NULL && p->next->card != NULL) {
		p = p->next;
	}

	p->next = t;
	t->card = card;
	t->opt = opt;
	t->money = money;
	t->pre_money = pre_money;
	t->after_money = after_money;
	t->time = time;
	t->next = NULL;
}

other_log* searchOptLog(char aName[]) {
	other_log* p = optLogHead;
	other_log* t;
	t = (other_log*)malloc(sizeof(other_log));
	if (t == NULL) {
		printf("文件打开失败\n");
		exit(-1);
	}
	t->card = NULL;
	t->next = NULL;

	while (p != NULL && p->card != NULL) {
		if (strcmp(p->card->aName, aName) == 0) {
			addOptLogToList(p->card, p->opt, p->time, p->money, p->pre_money, p->after_money, t);
		}
		p = p->next;
	}

	return t->next;
}

