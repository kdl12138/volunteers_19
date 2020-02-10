#include "main.h"
extern Node* head;
extern other_log* optLogHead;

void outputMenu() {
	printf("-------------------菜单----------------\n");
	printf("1:添加卡\n");
	printf("2:查询卡\n");
	printf("3:上机\n");
	printf("4:下机\n");
	printf("5:充值\n");
	printf("6:退费\n");
	printf("7:查询统计\n");
	printf("8:注销\n");
	printf("0:退出\n");
	printf("--------------------------------------\n");
	printf("请选择操作项：");
}

void addCard() {
	char name[18];
	char pwd[8];
	double money;
	Card* p;
	p = (Card*)malloc(sizeof(Card));
	if (p == NULL) {
		printf("内存分配失败");
			exit(-1);
	}
	int i;
	struct tm endtm;

	endtm.tm_year = 2025;
	endtm.tm_mon = 1;
	endtm.tm_mday = 1;

	printf("-----------------添加卡-----------------\n");
	printf("请输入卡号（16位）：");
	getchar();
	gets_s(name);
	while (strlen(name) != 16) {
		printf("请输入16位数字\n");
		gets_s(name);
	}
	if (queryCard(name) != NULL) {  
		printf("该卡号已被注册\n");
	}
	else {
		printf("请输入密码（6位）：");
		gets_s(pwd);
		while (strlen(pwd) != 6) {
			printf("请输入6位数字\n");
			gets_s(pwd);
		}
		printf("请输入开卡金额（￥）：");
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
			printf("开卡成功\n");
		}

	}


}

void printCard() {
	char name[18];
	Node* p;

	printf("----------------查询卡----------------\n");
	printf("请输入查询的卡号：");
	scanf_s("%s", name, 16);
	p = queryCards(name);
	if (p == NULL) {
		printf("未找到相关卡号\n");
	}
	else {
		printAll(p);
	}
}

void useComputer() {
	char name[18];
	char pwd[8];
	Card* p;

	printf("----------上机----------\n");
	printf("请输入卡号（16位）：");
	getchar();
	gets_s(name);
	while (strlen(name) != 16) {
		printf("请输入16位数字\n");
		gets_s(name);
	}
	printf("请输入密码（6位）：");
	gets_s(pwd);
	while (strlen(pwd) != 6) {
		printf("请输入6位数字\n");
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
					printf("上机成功！\n");
					addLogToList(p, 0, time(NULL));
				}
				else {
					printf("该卡处于上机状态或已注销或失效。\n");
				}
			}
			else {
				printf("余额不足\n");
			}
		}
		else {
			printf("密码错误\n");
		}
	}
	else {
		printf("无此用户\n");
	}
}

void exitComputer() {
	char name[18];
	char pwd[8];
	Card* p;
	long long int second;
	double money;
	double balance;

	printf("----------下机----------\n");
	printf("请输入卡号（16位）：");
	getchar();
	gets_s(name);
	while (strlen(name) != 16) {
		printf("请输入16位数字\n");
		gets_s(name);
	}
	printf("请输入密码（6位）：");
	gets_s(pwd);
	while (strlen(pwd) != 6) {
		printf("请输入6位数字\n");
		gets_s(pwd);
	}
	p = queryCard(name);  

	if (p != NULL) {

		if (strcmp(p->aPwd, pwd) == 0) {  

			if (p->nStatus == 1) {      

				second = time(NULL) - p->tLast; 
				money = (second / 3600 + !(!(second % 3600))) * price;
				p->fTotalUse += money;
				printf("花费了%.2f元\n", money);
				while (1) {
					balance = p->fBalance - money;        
					if (balance >= 0) {                
						p->fBalance = balance;       
						p->tLast = time(NULL);        
						p->nStatus = 0;              
						printf("下机成功\n");
						addLogToList(p, 1, time(NULL));
						break;
					}
					else {
						printf("余额不足，请充值%.2f元。\n", money - (p->fBalance));
						topUp();
					}
				}
			}
			else {
				printf("该用户不处于上机状态或已注销或失效\n");
			}

		}
		else {
			printf("密码错误\n");
		}
	}
	else {
		printf("无此用户\n");
	}
}

void topUp() {
	char name[18];
	char pwd[8];
	double money;
	Card* p;
	p = (Card*)malloc(sizeof(Card));
	if (p == NULL) {
		printf("内存分配失败\n");
		exit(-1);
	}

	printf("----------充值----------\n");
	printf("请输入卡号（16位）：");
	getchar();
	gets_s(name);
	while (strlen(name) != 16) {
		printf("请输入16位数字\n");
		gets_s(name);
	}
	printf("请输入密码（6位）：");
	gets_s(pwd);
	while (strlen(pwd) != 6) {
		printf("请输入6位数字\n");
		gets_s(pwd);
	}

	if (p != NULL) {     
		if (strcmp(p->aPwd, pwd) == 0) {   
			printf("请输入充值金额：");    
			scanf_s("%lf", &money);
			p->fBalance += money;         
			printf("充值成功，充值信息如下：\n");
			printf("卡号\t\t\t充值金额\t\t\t余额\n");       
			printf("%s\t\t\t%.2lf\t\t\t%.2lf\n", p->aName, money, p->fBalance);
			addOptLogToList(p, 1, time(NULL), money, p->fBalance - money, p->fBalance, optLogHead);
		}
		else {
			printf("密码错误。\n");
		}

	}
	else {
		printf("无此用户。\n");
	}
}

void withdraw() {
	char name[18];
	char pwd[8];
	Card* p;

	printf("----------退费----------\n");
	printf("请输入卡号（16位）：");
	getchar();
	gets_s(name);
	while (strlen(name) != 16) {
		printf("请输入16位数字\n");
		gets_s(name);
	}
	printf("请输入密码（6位）：");
	gets_s(pwd);
	while (strlen(pwd) != 6) {
		printf("请输入6位数字\n");
		gets_s(pwd);
	}

	p = queryCard(name);     
	if (p != NULL) {       
		if (strcmp(p->aPwd, pwd) == 0) {  
			if (p->nStatus == 0) {   
				if (p->fBalance > 0) {   
					printf("退费金额：%.2lf\n", p->fBalance);
					printf("退费成功！\n");
					addOptLogToList(p, 2, time(NULL), p->fBalance, p->fBalance, 0, optLogHead);
					p->fBalance = 0;     	
				}
				else {
					printf("余额不足，退费失败\n");
				}
			}
			else {
				printf("该卡处于上机状态或已注销或已失效,退费失败\n");
			}
		}
		else {
			printf("密码错误，退费失败\n");
		}
	}
	else {
		printf("无此用户，退费失败\n");
	}
}

void searchAll() {
	int option;
	printf("---------------查询统计---------------\n");
	printf("1.查询用户总消费记录\n");
	printf("2:查询用户消费记录\n");
	printf("3.查询总营业额\n");
	printf("4.查询月营业额\n");
	printf("---------------------------------------\n");
	printf("请输入操作项：");
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
	default:printf("请输入正1-4\n");
	}
}

void exitCard() {
	char name[18];
	char pwd[8];
	Card* p;

	printf("----------注销----------\n");
	printf("请输入卡号（16位）：");
	getchar();
	gets_s(name);
	while (strlen(name) != 16) {
		printf("请输入16位数字\n");
		gets_s(name);
	}
	p = queryCard(name);     
	if (p != NULL) {        
		printf("请输入密码（6位）：");
		gets_s(pwd);
		while (strlen(pwd) != 6) {
			printf("请输入6位数字\n");
			gets_s(pwd);
		}

		if (strcmp(p->aPwd, pwd) == 0) {   
			if (p->nStatus == 0) {      
				printf("注销成功！\n");
				printf("卡号\t退费金额\n");
				printf("%s\t%.2lf\n", p->aName, p->fBalance);
				p->fBalance = 0;    
				p->nStatus = 2;     
				addOptLogToList(p, 0, time(NULL), 0, 0, 0, optLogHead);
			}
			else {
				printf("该卡正处于上机状态，或已注销或失效\n");
			}

		}
		else {
			printf("密码错误，注销失败\n");
		}
	}
	else {
		printf("无此用户\n");
	}
}
