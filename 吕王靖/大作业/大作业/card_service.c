#include "card_service.h"
#include "list.h"
#include <string.h>

//��ʼ������
void initCardList() {
	FILE* fp;

	if ((fp = fopen("card_info.txt", "r")) == NULL) {   //���ļ�
		printf("File open error.\n");
		return;
	}
	if ((Node*)malloc(sizeof(Node)) == NULL) {
		printf("bug\n");
	}
	head = (Node*)malloc(sizeof(Node));
	Node* p = head;
	p->data = NULL;
	//int i;
	//char str[2] = "a", str1[4] = "123";
	//��ʼ������������
	/*for (i = 0;i < 5;i++) {
		p->data = (Card*)malloc(sizeof(Card));
		str[0] += i;
		strcpy(p->data->aName, str);
		strcpy(p->data->aPwd, str1);
		p->data->nStatus = 0;
		time(&(p->data->tStart));
		time(&(p->data->tEnd));
		p->data->fTotalUse = 816;
		time(&(p->data->tLast));
		p->data->nUseCount = 3;
		p->data->fBalance = 86;
		p->data->nDel = 0;
		p->next = (Node*)malloc(sizeof(Node)); //Ϊp��next�����ڴ�ռ�
		if (i == 4) {
			p->next = NULL;
		}
		p = p->next;   //��pָ��������һ���ڵ�
	}*/
	while (!feof(fp)) {
		p->data = (Card*)malloc(sizeof(Card));
		/*
		fscanf(fp, "%s", p->data->aName);             //����
		fscanf(fp, "%s", p->data->aPwd);              //����
		fscanf(fp, "%d", &p->data->nStatus);         //��״̬
		fscanf(fp, "%lld",&p->data->tStart);         //����ʱ��
		fscanf(fp, "%lld",&p->data->tEnd);           //����ʱ��
		fscanf(fp, "%f",&p->data->fTotalUse);        //�ۼƽ��
		fscanf(fp, "%lld",&p->data->tLast);          //���ʹ��ʱ��
		fscanf(fp, "%d",&p->data->nUseCount);        //ʹ�ô���
		fscanf(fp, "%f",&p->data->fBalance);        //���
		fscanf(fp, "%d",&p->data->nDel);            //ɾ����ʶ
		*/
		if (fscanf(fp, "%s %s %d %lld %lld %f %lld %d %f %d", p->data->aName, p->data->aPwd,
			&(p->data->nStatus), &(p->data->tStart), &(p->data->tEnd), &(p->data->fTotalUse), &(p->data->tLast),
			&(p->data->nUseCount), &(p->data->fBalance), &(p->data->nDel)) == -1) {
			p->data = NULL;
			break;
		}
		p->next = (Node*)malloc(sizeof(Node));      //Ϊp��next�����ڴ��ַ
		p = p->next;                                //��pָ��������һ���ڵ�
	}
	p->next = NULL;

	if (fclose(fp)) {                    //�ر��ļ� 
		printf("Can not close the file!\n");
	}
}  

//��ѯ��
Card* queryCard(char* aName) {
	Node* p = head;
	Node* t = NULL;
	//����������������Ҫ���ҵĿ�����ͬ�Ľṹ��Card��Ϣ��������
	while (p->data != NULL) {
		if (strcmp(p->data->aName, aName) == 0) {
	        //printCardInfo(p->data);           
			t = p;
			return t->data;
		}
		p = p->next;
	}
	//��δ�ҵ�������NULL
	if(t == NULL) {
		//printf("δ��ѯ����ؿ��ţ����������Ƿ���ȷ��\n");
		return NULL;
	}
	
}

//ģ����ѯ��
Node* queryCards(const char* pName) {

	Node* p = head;
	Node* current;        //����һ��currentָ�룬����Ϊ�׽ڵ㣬���������������ͷ�ѱ���ʼ��ΪNULL��
	current = (Node*)malloc(sizeof(Node));
	current->data = NULL;
	current->next = NULL;
	
	//ʹ��strstr�������Ұ�����Ҫ���ҵĽڵ�
	while (p != NULL && p->data != NULL) {
		if (strstr(p->data->aName, pName) != NULL) {
			addToList(p->data, current);  //����addToList������current������ӽ��
		}
		p = p->next;
	}
	
	return current->next;    //���صڶ�����㣬��Ϊ��һ������ʼ��ΪNULL
	
}
