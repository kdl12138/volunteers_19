#include <stdio.h>
#include <stdlib.h>

typedef struct ListNote{
	int x;
	struct ListNote *next;
}Node, *pNode;

Node *InputNode(){
	Node *node,*p, *q;
    int num = 0;
    node = p = q = NULL;
    scanf("%d", &num);
    if (num != 0)
    {
       node = p = (Node *)malloc(sizeof(Node));
    }
    while (num != 0)
    {
        p->x = num;
        scanf("%d", &num);
        if (num != 0)
        {
            q = (Node *)malloc(sizeof(Node));
            p->next = q;
            p = q;
        }
        p->next = NULL;
    }
    return node;
} 


Node* TestNode(pNode pHead){
	pNode fast = pHead;
	pNode slow = pHead;
	while( fast != NULL && fast->next != NULL){  

		fast = fast->next->next;  
		slow = slow->next;  
		if(fast == slow)   
			break;  
	}  
	if(fast == NULL || fast->next == NULL)  
		return NULL;  
	slow = pHead; 
	while(slow != fast)  {  
		slow = slow->next;  
		fast = fast->next;  
	}  
	
	return slow;  
}


int NodeLength(pNode pHead){
	if(TestNode(pHead) == NULL) {
		return 0;  
	}
	pNode fast = pHead;  
	pNode slow = pHead;  
	int length = 0; 
	bool begin = false;  
	bool agian = false;  
	while( fast != NULL && fast->next != NULL)  
	{  
		fast = fast->next->next;  
		slow = slow->next;  
		if(fast == slow && agian == true)  
			break;  
		if(fast == slow && agian == false)  
		{             
			begin = true;  
			agian = true;  
		}  
	}  
	
	if(begin == true)  
	{
		++length;
	}
	return length;  
}


void OutputNode(Node *node){
	if (node == NULL)
    {
        printf("No data!\n");
        return ;
    }
    while (node != NULL)
    {
		printf("%d\n",node->x);
        node = node->next; 
    }
    printf("\n");
    return ;
} 

int main(){
	Node *head = InputNode();
	if(TestNode(head) == NULL)
		OutputNode(head);
	else
	    printf("%d %d",head->x,NodeLength(head));
		
	return 0;	 
}
