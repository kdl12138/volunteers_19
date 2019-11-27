#include<stdio.h>
int main(){
	int i,j;
	int a[10005];
	int n = 0;
	for(i = 1;i<10001;i++){
		a[i] = 1;
	}
	i = 2;
	while(i<10001){
		j = 2;
		while(i*j<10001){
			a[i*j] = 0;
			j++;
		}
		i++;
		while(i<10001 && a[i] == 0)
		i++;
	}
	for(i = 2;i<10001;i++){
		if(a[i]!=0){
			printf("%5d",i);
			n++;
			if(n%10 == 0)
			printf("\n");
		}
	}
	return 0;
}

