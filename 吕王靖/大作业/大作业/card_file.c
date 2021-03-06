#include "card_file.h"
#include <stdlib.h>

//保存卡信息
int saveCard(char* aName, char* aPwd, float fBalance, struct tm endtm) {
	FILE* fp;

	if ((fp = fopen("card_info.txt", "a+")) == NULL) {  //打开文件
		printf("File open error!\n");
		return 0;
	}

	fprintf(fp, "%s\t", aName);               //卡号
	fprintf(fp, "%s\t", aPwd);               //密码
	fprintf(fp, "%d\t", 0);                  //卡状态
	fprintf(fp, "%lld\t", time(NULL));       //开卡时间
	fprintf(fp, "%lld\t", mktime(&endtm));   //截至时间
	fprintf(fp, "%f\t", 0.0);              //累计金额
	fprintf(fp, "%lld\t", time(NULL));      //最后使用时间
	fprintf(fp, "%d\t", 0);                //使用次数
	fprintf(fp, "%f\t", fBalance);        //余额
	fprintf(fp, "%d\n", 0);               //删除标识

	if (fclose(fp)) {                    //关闭文件 
		printf("Can not close the file!\n");
		return 0;
	}
	return 1;
}

/*读取卡信息
int readCard() {
	FILE* fp;

	if (fp = fopen("card_info.txt", "r") == NULL) {    //打开文件
		printf("File open error.\n");
		return 0;
	}

	
}

//格式化卡信息
int parseCard() {

}*/

//添加卡信息
void updateSave(Card* data) {
	FILE* fp;
	if ((fp = fopen("card_info.txt", "a+")) == NULL) {  //打开文件
		printf("File open error!\n");

	}

	fprintf(fp, "%s\t", data->aName);               //卡号
	fprintf(fp, "%s\t", data->aPwd);               //密码
	fprintf(fp, "%d\t", data->nStatus);            //卡状态
	fprintf(fp, "%lld\t",data->tStart);           //开卡时间
	fprintf(fp, "%lld\t",data->tEnd);             //截至时间
	fprintf(fp, "%f\t",data->fTotalUse);          //累计金额
	fprintf(fp, "%lld\t",data->tLast);            //最后使用时间
	fprintf(fp, "%d\t",data->nUseCount);         //使用次数
	fprintf(fp, "%f\t",data->fBalance);          //余额
	fprintf(fp, "%d\n",data->nDel);               //删除标识

	if (fclose(fp)) {                    //关闭文件 
		printf("Can not close the file!\n");
	}

}

//重写卡信息文件
void updateSaveAll() {
	FILE* fp;
	Node* p;
	p = head;
	
	if ((fp = fopen("card_info.txt", "w+")) == NULL) {
		printf("File open error.\n");
	}

	if (fclose(fp)) {                    //关闭文件 
		printf("Can not close the file!\n");
	}

	while ( p != NULL) {
		if (p->data != NULL) {       //
			updateSave(p->data);
		}
		p = p->next;
	}

}

