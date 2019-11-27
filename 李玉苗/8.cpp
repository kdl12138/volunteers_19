#include <stdio.h>
const int maxn = 10005;

int main(){
	int era[maxn];
	int count = 0;
	
	for(int i = 0; i <= 10000; i++)
		era[i] = 1;
	for(int i = 2; i <= 10000; i++)
		for(int j = 2; j * i <= 10000; j++)
			era[i * j] = 0;	
	for(int i = 2; i <= 10000; i++){
		if(era[i]){
			printf("%d ", i); 
			count++;
			if(count%5 == 0)
				printf("\n");
		}
	}
	
	return 0;
}
