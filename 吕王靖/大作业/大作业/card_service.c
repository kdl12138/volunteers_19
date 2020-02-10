#include "card_service.h"
#include "list.h"
#include <string.h>

//初始化链表
void initCardList() {
	FILE* fp;

	if ((fp = fopen("card_info.txt", "r")) == NULL) {   //打开文件
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
	//初始化并连成链表
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
		p->next = (Node*)malloc(sizeof(Node)); //为p的next申请内存空间
		if (i == 4) {
			p->next = NULL;
		}
		p = p->next;   //把p指向他的下一个节点
	}*/
	while (!feof(fp)) {
		p->data = (Card*)malloc(sizeof(Card));
		/*
		fscanf(fp, "%s", p->data->aName);             //卡号
		fscanf(fp, "%s", p->data->aPwd);              //密码
		fscanf(fp, "%d", &p->data->nStatus);         //卡状态
		fscanf(fp, "%lld",&p->data->tStart);         //开卡时间
		fscanf(fp, "%lld",&p->data->tEnd);           //截至时间
		fscanf(fp, "%f",&p->data->fTotalUse);        //累计金额
		fscanf(fp, "%lld",&p->data->tLast);          //最后使用时间
		fscanf(fp, "%d",&p->data->nUseCount);        //使用次数
		fscanf(fp, "%f",&p->data->fBalance);        //余额
		fscanf(fp, "%d",&p->data->nDel);            //删除标识
		*/
		if (fscanf(fp, "%s %s %d %lld %lld %f %lld %d %f %d", p->data->aName, p->data->aPwd,
			&(p->data->nStatus), &(p->data->tStart), &(p->data->tEnd), &(p->data->fTotalUse), &(p->data->tLast),
			&(p->data->nUseCount), &(p->data->fBalance), &(p->data->nDel)) == -1) {
			p->data = NULL;
			break;
		}
		p->next = (Node*)malloc(sizeof(Node));      //为p的next申请内存地址
		p = p->next;                                //把p指向他的下一个节点
	}
	p->next = NULL;

	if (fclose(fp)) {                    //关闭文件 
		printf("Can not close the file!\n");
	}
}  

//查询卡
Card* queryCard(char* aName) {
	Node* p = head;
	Node* t = NULL;
	//遍历链表，查找与需要查找的卡号相同的结构体Card信息，并返回
	while (p->data != NULL) {
		if (strcmp(p->data->aName, aName) == 0) {
	        //printCardInfo(p->data);           
			t = p;
			return t->data;
		}
		p = p->next;
	}
	//若未找到，返回NULL
	if(t == NULL) {
		//printf("未查询到相关卡号，请检查输入是否正确。\n");
		return NULL;
	}
	
}

//模糊查询卡
Node* queryCards(const char* pName) {

	Node* p = head;
	Node* current;        //声明一个current指针，以他为首节点，建立链表（改链表的头已被初始化为NULL）
	current = (Node*)malloc(sizeof(Node));
	current->data = NULL;
	current->next = NULL;
	
	//使用strstr函数查找包含需要查找的节点
	while (p != NULL && p->data != NULL) {
		if (strstr(p->data->aName, pName) != NULL) {
			addToList(p->data, current);  //调用addToList函数给current函数添加结点
		}
		p = p->next;
	}
	
	return current->next;    //返回第二个结点，因为第一个结点初始化为NULL
	
}
