#include "main.h"
extern Node* head;

void initCardList() {
	FILE* fp;
	fp = (FILE*)malloc(sizeof(FILE));
	if (fp == NULL) {
		printf("内存分配失败\n");
		exit(-1);
	}

	if ((fp = fopen("card_info.txt", "r")) == NULL) {   //打开文件
		printf("文件打开失败\n");
		return;
	}

	head = (Node*)malloc(sizeof(Node));
	if (head == NULL) {
		printf("内存分配失败\n");
		exit(-1);
	}

	Node* p = head;
	p->data = NULL;

	while (!feof(fp)) {
		p->data = (Card*)malloc(sizeof(Card));
		if (p->data == NULL) {
			printf("内存分配失败\n");
			exit(-1);
		}
		
		if (fscanf(fp, "%s %s %d %lld %lld %lf %lld %d %lf %d", p->data->aName, p->data->aPwd,
			&(p->data->nStatus), &(p->data->tStart), &(p->data->tEnd), &(p->data->fTotalUse), &(p->data->tLast),
			&(p->data->nUseCount), &(p->data->fBalance), &(p->data->nDel)) == -1) {
			p->data = NULL;
			break;
		}
		p->next = (Node*)malloc(sizeof(Node));      
		p = p->next;                                
	}
	p->next = NULL;

	if (fclose(fp)) {                    
		printf("Can not close the file!\n");
	}
}

void addToList(Card* p, Node* head) {
	Node* t = head;
	Node* add;

	add = (Node*)malloc(sizeof(Node));
	if (add == NULL) {
		printf("内存分配失败\n");
		exit(-1);
	}

	add->data = p;
	add->next = NULL;

	while (t != NULL &&t->next != NULL && t->next->data != NULL) {
		t = t->next;
	}
	t->next = add;
}

Card* queryCard(char* aName) {
	Node* p = head;
	Node* t = NULL;
	if (p == NULL || p->data == NULL) {
		return NULL;
	}
	while (p->data != NULL) {
		if (strcmp(p->data->aName, aName) == 0) {       
			t = p;
			return t->data;
		}
		p = p->next;
	}
	if (t == NULL) {
		return NULL;
	}
}

Node* queryCards(const char aName[]) {
	Node* p = head;
	Node* t;    

	t = (Node*)malloc(sizeof(Node));
	if (t == NULL) {
		printf("内存分配失败\n");
		exit(-1);
	}

	t->data = NULL;
	t->next = NULL;
	while (p != NULL && p->data != NULL) {
		if (strstr(p->data->aName, aName) != NULL) {
			addToList(p->data, t); 
		}
		p = p->next;
	}

	return t->next;
}

void  printAll(const Node* p) {
	const Node* t = p;
	printf("卡号\t\t\t状态\t余额\t\t累计使用\t使用次数\t上次使用时间\n");

	while (t != NULL) {
		struct tm* m = gmtime(&(t->data->tLast));

		printf("%s\t", t->data->aName);
		printf("%d\t", t->data->nStatus);
		printf("%lf\t", t->data->fBalance);
		printf("%lf\t", t->data->fTotalUse);
		printf("%d\t\t", t->data->nUseCount);
		printf("%d-%d-%d %d:%d\n", 1900 + m->tm_year, 1 + m->tm_mon, m->tm_mday, m->tm_hour, m->tm_min);

		t = t->next;
	}
}