#include<stdio.h>
#include<malloc.h>

struct ListNode{
	int x;
	struct ListNode *next;
};

struct ListNode *detectCycle(struct ListNode *head){
	int pos = -1;
	struct ListNode *fast = head;
	struct ListNode *slow = head;
	struct ListNode *pospointer = head; 
	while(fast != NULL && fast->next != NULL){     //ͨ������ָ�������ж��Ƿ��л� 
		fast = fast->next->next;
		slow = slow->next;
		if(fast == slow){
			pos = 0;
			while(slow != pospointer){            //�һ������ 
				slow = slow->next;
				pospointer = pospointer->next;
				pos++;
			}
			printf("������ʼλ��Ϊ:",pos);
			return pospointer;
			break;
		}
	}
	printf("û�л�");
	return NULL;
}
 //����ָ�붼�ӻ�������������ָ��ÿ�ƶ�һ�λ��ĳ��ȼ�һ��������ָ���ٴ�����ʱ�����صĳ���ֵ���ǻ��ĳ���
int NodeLength(struct ListNode *ringNode){    
    int Length = 0;
    struct ListNode *fast = ringNode;
    struct ListNode *slow = ringNode;
    do{
        fast = fast->next->next;
        slow = slow->next;
        Length++;
    }while(fast != slow);
    return Length;
}
//�������� 
void list(struct ListNode *head){
	while(head != NULL){
		printf("%d",head->x);
		head = head->next;
	}
}

int main(){
	return 0;
}
