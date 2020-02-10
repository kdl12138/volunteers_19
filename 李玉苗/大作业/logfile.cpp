#include "main.h"
extern login_log* loginHead;
extern other_log* optLogHead;

void saveLog(login_log* t) {
	FILE* fp;
	fp = (FILE*)malloc(sizeof(FILE));
	if (fp == NULL) {
		printf("内存分配失败");
		exit(-1);
	}

	if ((fp = fopen("login_log_info.txt", "a")) == NULL) {
		printf("文件打开失败\n");
	}

	fprintf(fp, "%s\t", t->card->aName);
	fprintf(fp, "%s\t", t->card->aPwd);
	fprintf(fp, "%d\t", t->card->nStatus);
	fprintf(fp, "%lld\t", t->card->tStart);
	fprintf(fp, "%lld\t", t->card->tEnd);
	fprintf(fp, "%lf\t", t->card->fTotalUse);
	fprintf(fp, "%lld\t", t->card->tLast);
	fprintf(fp, "%d\t", t->card->nUseCount);
	fprintf(fp, "%lf\t", t->card->fBalance);
	fprintf(fp, "%d\t", t->card->nDel);
	fprintf(fp, "%d\t", t->opt);
	fprintf(fp, "%lld\n", t->time);

	if (fclose(fp)) {
		printf("文件关闭失败\n");
	}
	free(fp);
}

void updateLog(){

	FILE* fp;
	login_log* p;
	p = loginHead;

	fp = (FILE*)malloc(sizeof(FILE));
	if (fp == NULL) {
		printf("内存分配失败");
		exit(-1);
	}
	if ((fp = fopen("login_log_info.txt", "w+")) == NULL) {
		printf("文件打开失败\n");
	}

	if (fclose(fp)) {                    
		printf("文件关闭失败\n");
	}

	while (p != NULL) {
		if (p->card != NULL) {        
			saveLog(p);
		}
		p = p->next;
	}
}

void updateOptLog() {
	FILE* fp;
	other_log* p = optLogHead;

	fp = (FILE*)malloc(sizeof(FILE));
	if (fp == NULL) {
		printf("内存分配失败");
		exit(-1);
	}

	if ((fp = fopen("other_log_info.txt", "w+")) == NULL) {
		printf("文件打开失败\n");
	}

	if (fclose(fp)) {                   
		printf("文件关闭失败\n");
	}

	while (p != NULL) {
		if (p->card != NULL) {        
			saveOptLog(p);
		}
		p = p->next;
	}
}

void saveOptLog(other_log* p) {
	FILE* fp;
	fp = (FILE*)malloc(sizeof(FILE));
	if (fp == NULL) {
		printf("内存分配失败");
		exit(-1);
	}


	if ((fp = fopen("other_log_info.txt", "a")) == NULL) { 
		printf("File open error.\n");
	}

	fprintf(fp, "%s\t", p->card->aName);
	fprintf(fp, "%s\t", p->card->aPwd);
	fprintf(fp, "%d\t", p->card->nStatus);
	fprintf(fp, "%lld\t", p->card->tStart);
	fprintf(fp, "%lld\t", p->card->tEnd);
	fprintf(fp, "%lf\t", p->card->fTotalUse);
	fprintf(fp, "%lld\t", p->card->tLast);
	fprintf(fp, "%d\t", p->card->nUseCount);
	fprintf(fp, "%lf\t", p->card->fBalance);
	fprintf(fp, "%d\t", p->card->nDel);
	fprintf(fp, "%d\t", p->opt);
	fprintf(fp, "%d\t", p->money);
	fprintf(fp, "%d\t", p->pre_money);
	fprintf(fp, "%d\t", p->after_money);
	fprintf(fp, "%lld\n", p->time);

	if (fclose(fp)) {         
		printf("File close error.\n");
	}
}