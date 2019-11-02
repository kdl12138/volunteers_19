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
	while(fast != NULL && fast->next != NULL){     //通过快慢指针相遇判断是否有环 
		fast = fast->next->next;
		slow = slow->next;
		if(fast == slow){
			pos = 0;
			while(slow != pospointer){            //找环的起点 
				slow = slow->next;
				pospointer = pospointer->next;
				pos++;
			}
			printf("环的起始位置为:",pos);
			return pospointer;
			break;
		}
	}
	printf("没有环");
	return NULL;
}
 //快慢指针都从环的起点出发，慢指针每移动一次环的长度加一，当快慢指针再次相遇时，返回的长度值便是环的长度
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
//遍历链表 
void list(struct ListNode *head){
	while(head != NULL){
		printf("%d",head->x);
		head = head->next;
	}
}

int main(){
	return 0;
}
