#include "menu.h"
#include "card_file.h"
#include "tool.h"
#include "list.h"
#include "card_service.h"
#include "login_log.h"
#include "login_log_file.h"
#include "other_log.h"
#include "other_log_file.h"
#include "search_file.h"
int main() {
	int flag;
	//初始化链表
	initOptLog();
	initLoginLog();
	initCardList();

	//queryCard("a");
	
	printf("欢迎使用计费管理系统\n");

	do {
		outputMenu();
		switch (opt) {
		case 1:addCard(); break;
		case 2:printCard(); break;
		case 3:useComputer(); break;
		case 4:exitComputer(); break;
		case 5:topUp(); break;
		case 6:withdraw(); break;
		case 7:searchAll(); break;
		case 8:exitCard(); break;
		case 0:updateSaveAll();updateLog();updateOptLog(); break;
		default:printf("请正确输入编码！\n");
		}
		printf("是否继续使用计费管理系统（1 or 0）：");
		scanf("%d", &flag);
	}while (flag);

	//更新文件中的数据
	updateSaveAll();
	updateOptLog();
	//updateLog();

return 0;
}	

