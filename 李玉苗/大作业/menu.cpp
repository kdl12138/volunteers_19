#include "main.h"
extern Node* head;
extern other_log* optLogHead;

void outputMenu() {
	printf("-------------------�˵�----------------\n");
	printf("1:��ӿ�\n");
	printf("2:��ѯ��\n");
	printf("3:�ϻ�\n");
	printf("4:�»�\n");
	printf("5:��ֵ\n");
	printf("6:�˷�\n");
	printf("7:��ѯͳ��\n");
	printf("8:ע��\n");
	printf("0:�˳�\n");
	printf("--------------------------------------\n");
	printf("��ѡ������");
}

void addCard() {
	char name[18];
	char pwd[8];
	double money;
	Card* p;
	p = (Card*)malloc(sizeof(Card));
	if (p == NULL) {
		printf("�ڴ����ʧ��");
			exit(-1);
	}
	int i;
	struct tm endtm;

	endtm.tm_year = 2025;
	endtm.tm_mon = 1;
	endtm.tm_mday = 1;

	printf("-----------------��ӿ�-----------------\n");
	printf("�����뿨�ţ�16λ����");
	getchar();
	gets_s(name);
	while (strlen(name) != 16) {
		printf("������16λ����\n");
		gets_s(name);
	}
	if (queryCard(name) != NULL) {  
		printf("�ÿ����ѱ�ע��\n");
	}
	else {
		printf("���������루6λ����");
		gets_s(pwd);
		while (strlen(pwd) != 6) {
			printf("������6λ����\n");
			gets_s(pwd);
		}
		printf("�����뿪����������");
		scanf_s("%lf", &money);
		strcpy(p->aName, name);
		strcpy(p->aPwd, pwd);
		p->fBalance = money;
		p->nStatus = 0;
		p->tStart = time(NULL);
		p->fTotalUse = 0;
		p->tLast = time(NULL);
		p->nUseCount = 0;
		p->nDel = 0;
    	addToList(p, head);    
		if ((i = saveCard(name, pwd, money, endtm)) == 1) {
			printf("�����ɹ�\n");
		}

	}


}

void printCard() {
	char name[18];
	Node* p;

	printf("----------------��ѯ��----------------\n");
	printf("�������ѯ�Ŀ��ţ�");
	scanf_s("%s", name, 16);
	p = queryCards(name);
	if (p == NULL) {
		printf("δ�ҵ���ؿ���\n");
	}
	else {
		printAll(p);
	}
}

void useComputer() {
	char name[18];
	char pwd[8];
	Card* p;

	printf("----------�ϻ�----------\n");
	printf("�����뿨�ţ�16λ����");
	getchar();
	gets_s(name);
	while (strlen(name) != 16) {
		printf("������16λ����\n");
		gets_s(name);
	}
	printf("���������루6λ����");
	gets_s(pwd);
	while (strlen(pwd) != 6) {
		printf("������6λ����\n");
		gets_s(pwd);
	}
	p = queryCard(name);   
	if (p != NULL) {
		if (strcmp(p->aPwd, pwd) == 0) {   
			if (p->fBalance > 0) {       
				if (p->nStatus == 0) {   
					p->tLast = time(NULL); 
					p->nStatus = 1;        
					p->nUseCount++;       
					printf("�ϻ��ɹ���\n");
					addLogToList(p, 0, time(NULL));
				}
				else {
					printf("�ÿ������ϻ�״̬����ע����ʧЧ��\n");
				}
			}
			else {
				printf("����\n");
			}
		}
		else {
			printf("�������\n");
		}
	}
	else {
		printf("�޴��û�\n");
	}
}

void exitComputer() {
	char name[18];
	char pwd[8];
	Card* p;
	long long int second;
	double money;
	double balance;

	printf("----------�»�----------\n");
	printf("�����뿨�ţ�16λ����");
	getchar();
	gets_s(name);
	while (strlen(name) != 16) {
		printf("������16λ����\n");
		gets_s(name);
	}
	printf("���������루6λ����");
	gets_s(pwd);
	while (strlen(pwd) != 6) {
		printf("������6λ����\n");
		gets_s(pwd);
	}
	p = queryCard(name);  

	if (p != NULL) {

		if (strcmp(p->aPwd, pwd) == 0) {  

			if (p->nStatus == 1) {      

				second = time(NULL) - p->tLast; 
				money = (second / 3600 + !(!(second % 3600))) * price;
				p->fTotalUse += money;
				printf("������%.2fԪ\n", money);
				while (1) {
					balance = p->fBalance - money;        
					if (balance >= 0) {                
						p->fBalance = balance;       
						p->tLast = time(NULL);        
						p->nStatus = 0;              
						printf("�»��ɹ�\n");
						addLogToList(p, 1, time(NULL));
						break;
					}
					else {
						printf("���㣬���ֵ%.2fԪ��\n", money - (p->fBalance));
						topUp();
					}
				}
			}
			else {
				printf("���û��������ϻ�״̬����ע����ʧЧ\n");
			}

		}
		else {
			printf("�������\n");
		}
	}
	else {
		printf("�޴��û�\n");
	}
}

void topUp() {
	char name[18];
	char pwd[8];
	double money;
	Card* p;
	p = (Card*)malloc(sizeof(Card));
	if (p == NULL) {
		printf("�ڴ����ʧ��\n");
		exit(-1);
	}

	printf("----------��ֵ----------\n");
	printf("�����뿨�ţ�16λ����");
	getchar();
	gets_s(name);
	while (strlen(name) != 16) {
		printf("������16λ����\n");
		gets_s(name);
	}
	printf("���������루6λ����");
	gets_s(pwd);
	while (strlen(pwd) != 6) {
		printf("������6λ����\n");
		gets_s(pwd);
	}

	if (p != NULL) {     
		if (strcmp(p->aPwd, pwd) == 0) {   
			printf("�������ֵ��");    
			scanf_s("%lf", &money);
			p->fBalance += money;         
			printf("��ֵ�ɹ�����ֵ��Ϣ���£�\n");
			printf("����\t\t\t��ֵ���\t\t\t���\n");       
			printf("%s\t\t\t%.2lf\t\t\t%.2lf\n", p->aName, money, p->fBalance);
			addOptLogToList(p, 1, time(NULL), money, p->fBalance - money, p->fBalance, optLogHead);
		}
		else {
			printf("�������\n");
		}

	}
	else {
		printf("�޴��û���\n");
	}
}

void withdraw() {
	char name[18];
	char pwd[8];
	Card* p;

	printf("----------�˷�----------\n");
	printf("�����뿨�ţ�16λ����");
	getchar();
	gets_s(name);
	while (strlen(name) != 16) {
		printf("������16λ����\n");
		gets_s(name);
	}
	printf("���������루6λ����");
	gets_s(pwd);
	while (strlen(pwd) != 6) {
		printf("������6λ����\n");
		gets_s(pwd);
	}

	p = queryCard(name);     
	if (p != NULL) {       
		if (strcmp(p->aPwd, pwd) == 0) {  
			if (p->nStatus == 0) {   
				if (p->fBalance > 0) {   
					printf("�˷ѽ�%.2lf\n", p->fBalance);
					printf("�˷ѳɹ���\n");
					addOptLogToList(p, 2, time(NULL), p->fBalance, p->fBalance, 0, optLogHead);
					p->fBalance = 0;     	
				}
				else {
					printf("���㣬�˷�ʧ��\n");
				}
			}
			else {
				printf("�ÿ������ϻ�״̬����ע������ʧЧ,�˷�ʧ��\n");
			}
		}
		else {
			printf("��������˷�ʧ��\n");
		}
	}
	else {
		printf("�޴��û����˷�ʧ��\n");
	}
}

void searchAll() {
	int option;
	printf("---------------��ѯͳ��---------------\n");
	printf("1.��ѯ�û������Ѽ�¼\n");
	printf("2:��ѯ�û����Ѽ�¼\n");
	printf("3.��ѯ��Ӫҵ��\n");
	printf("4.��ѯ��Ӫҵ��\n");
	printf("---------------------------------------\n");
	printf("����������");
	scanf_s("%d", &option);
	switch (option) {
	case 1:
		search_user_total(); 
		break;
	case 2:
		search_user_cost_log();
		break;
	case 3:
		search_total_input(); 
		break;
	case 4:
		search_total_input_month();
		break;
	default:printf("��������1-4\n");
	}
}

void exitCard() {
	char name[18];
	char pwd[8];
	Card* p;

	printf("----------ע��----------\n");
	printf("�����뿨�ţ�16λ����");
	getchar();
	gets_s(name);
	while (strlen(name) != 16) {
		printf("������16λ����\n");
		gets_s(name);
	}
	p = queryCard(name);     
	if (p != NULL) {        
		printf("���������루6λ����");
		gets_s(pwd);
		while (strlen(pwd) != 6) {
			printf("������6λ����\n");
			gets_s(pwd);
		}

		if (strcmp(p->aPwd, pwd) == 0) {   
			if (p->nStatus == 0) {      
				printf("ע���ɹ���\n");
				printf("����\t�˷ѽ��\n");
				printf("%s\t%.2lf\n", p->aName, p->fBalance);
				p->fBalance = 0;    
				p->nStatus = 2;     
				addOptLogToList(p, 0, time(NULL), 0, 0, 0, optLogHead);
			}
			else {
				printf("�ÿ��������ϻ�״̬������ע����ʧЧ\n");
			}

		}
		else {
			printf("�������ע��ʧ��\n");
		}
	}
	else {
		printf("�޴��û�\n");
	}
}
