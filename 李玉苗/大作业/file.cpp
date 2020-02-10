#include "main.h"
extern Node* head;
int saveCard(char aName[], char aPwd[], double fBalance, struct tm endtm) {
	FILE* fp;
	fp = (FILE*)malloc(sizeof(FILE));
	if (fp == NULL) {
		printf("�ڴ����ʧ��\n");
		exit(-1);
	}

	if ((fp = fopen("card_info.txt", "a+")) == NULL) { 
		printf("�ļ���ʧ��\n");
		return 0;
	}

	fprintf(fp, "%s\t", aName);               
	fprintf(fp, "%s\t", aPwd);              
	fprintf(fp, "%d\t", 0);                  
	fprintf(fp, "%lld\t", time(NULL));       
	fprintf(fp, "%lld\t", mktime(&endtm));   
	fprintf(fp, "%lf\t", 0.0);             
	fprintf(fp, "%lld\t", time(NULL));      
	fprintf(fp, "%d\t", 0);               
	fprintf(fp, "%lf\t", fBalance);       
	fprintf(fp, "%d\n", 0);              

	if (fclose(fp)) {                     
		printf("�ļ��ر�ʧ��\n");
		return 0;
	}
	return 1;
}

void updateSave(Card* data) {
	FILE* fp;

	fp = (FILE*)malloc(sizeof(FILE));
	if (fp == NULL) {
		printf("�ڴ����ʧ��\n");
		exit(-1);
	}

	if ((fp = fopen("card_info.txt", "a+")) == NULL) {  
		printf("�ļ���ʧ��\n");

	}

	fprintf(fp, "%s\t", data->aName);              
	fprintf(fp, "%s\t", data->aPwd);              
	fprintf(fp, "%d\t", data->nStatus);          
	fprintf(fp, "%lld\t", data->tStart);           
	fprintf(fp, "%lld\t", data->tEnd);            
	fprintf(fp, "%lf\t", data->fTotalUse);         
	fprintf(fp, "%lld\t", data->tLast);            
	fprintf(fp, "%d\t", data->nUseCount);         
	fprintf(fp, "%lf\t", data->fBalance);        
	fprintf(fp, "%d\n", data->nDel);             

	if (fclose(fp)) {                   
		printf("�ļ��ر�ʧ��\n");
	}

}

void updateSaveAll() {
	FILE* fp;
	Node* p = head;

	fp = (FILE*)malloc(sizeof(FILE));
	if (fp == NULL) {
		printf("�ڴ����ʧ��\n");
		exit(-1);
	}

	if ((fp = fopen("card_info.txt", "w+")) == NULL) {
		printf("�ļ���ʧ��\n");
	}

	if (fclose(fp)) {                    
		printf("�ļ��ر�ʧ��\n");
	}

	while (p != NULL) {
		if (p->data != NULL) {       
			updateSave(p->data);
		}
		p = p->next;
	}

}
