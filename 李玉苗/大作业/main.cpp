#include "main.h"
int nowCardNum;
Node card;			// ������ 
Node* head;
login_log loginLog;		// ��¼����log���� 
login_log* loginHead;
other_log optLog;		// ����log���� 
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
			printf("������0-8\n");
			break;
		}
		printf("--------------------------------------\n");
		do {
			printf("������0��1\n");
			printf("�Ƿ����ʹ�ã�(1.���� 0.�˳�)\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
			scanf_s("%d", &flag);
			if (flag == 0)
				break;
		} while (flag != 1 && flag != 0);

	} while (flag != 0);

	return 0;
}