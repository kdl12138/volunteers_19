#include "main.h"
int nowCardNum;
Node card;			// 卡链表 
Node* head;
login_log loginLog;		// 登录操作log链表 
login_log* loginHead;
other_log optLog;		// 消费log链表 
other_log* optLogHead;


int main() {
	int opt;
	int flag;

	initOptLog();
	initLoginLog();
	initCardList();
	initCardList();

	do {
		outputMenu();
		scanf_s("%d", &opt);
		switch (opt) {
		case 1:
			addCard();
			break;
		case 2:
			printCard();
			break;
		case 3:
			useComputer();
			break;
		case 4:
			exitComputer();
			break;
		case 5:
			topUp();
			break;
		case 6:
			withdraw();
			break;
		case 7:
			searchAll();
			break;
		case 8:
			exitCard();
			break;
		case 0:
			updateSaveAll();
			updateLog();
			updateOptLog();
			break;
		default:
			printf("请输入0-8\n");
			break;
		}
		printf("--------------------------------------\n");
		do {
			printf("请输入0或1\n");
			printf("是否继续使用：(1.继续 0.退出)\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
			scanf_s("%d", &flag);
			if (flag == 0)
				break;
		} while (flag != 1 && flag != 0);

	} while (flag != 0);

	return 0;
}