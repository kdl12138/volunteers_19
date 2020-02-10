#include "other_log_file.h"

/*//读消费log文件
void readOptLog()
{
	FILE* fp;

	if (fopen("otner_log_info.txt", "w") == NULL) {
		printf("File open error.\n");
	}

	other_log* p = head;

	while (!feof(fp)) {
		p->card = (Card * )malloc(sizeof(Card));

		if(fscanf())
	}
}
//格式化消费log文件
void praseOptLog()
{
}*/

//保存消费log文件
void saveOptLog(other_log* log)
{
	FILE* fp;

	if ((fp = fopen("other_log_info.txt", "a")) == NULL) {   //打开文件
		printf("File open error.\n");
	}

	fprintf(fp, "%s\t", log->card->aName);
	fprintf(fp, "%s\t", log->card->aPwd);
	fprintf(fp, "%d\t", log->card->nStatus);
	fprintf(fp, "%lld\t", log->card->tStart);
	fprintf(fp, "%lld\t", log->card->tEnd);
	fprintf(fp, "%f\t", log->card->fTotalUse);
	fprintf(fp, "%lld\t", log->card->tLast);
	fprintf(fp, "%d\t", log->card->nUseCount);
	fprintf(fp, "%f\t", log->card->fBalance);
	fprintf(fp, "%d\t", log->card->nDel);
	fprintf(fp, "%d\t", log->opt);
	fprintf(fp, "%d\t", log->money);
	fprintf(fp, "%d\t", log->pre_money);
	fprintf(fp, "%d\t", log->after_money);
	fprintf(fp, "%lld\n", log->time);

	if (fclose(fp)) {          //关闭文件
		printf("File close error.\n");
	}
}

//更新消费log文件
void updateOptLog()
{
	FILE* fp;
	other_log* p = heado;

	if ((fp = fopen("other_log_info.txt", "w+")) == NULL) {
		printf("File open error.\n");
	}

	if (fclose(fp)) {                    //关闭文件 
		printf("Can not close the file!\n");
	}

	while (p != NULL) {
		if (p->card != NULL) {        //
			saveOptLog(p);
		}
		p = p->next;
	}

}
