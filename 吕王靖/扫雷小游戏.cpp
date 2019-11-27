#include<stdio.h>
int main(){
	char a[52][52]; 
	int i,j;
	int n,m;
	scanf("%d %d\n",&n,&m);
	for(i = 1;i<=n;i++){
		for(j = 1;j<=m+1;j++)
	//	a[i][j] = getchar();
		scanf("%c",&a[i][j]);
	}
	for(i = 1;i<=n;i++){
		for(j = 1;j<=m;j++){
			if(a[i][j]!='*'){
				a[i][j] = '0';				
				if(a[i-1][j-1] == '*')
				a[i][j]++;
				if(a[i-1][j] == '*')
				a[i][j]++;
				if(a[i-1][j+1] == '*')
				a[i][j]++;
				if(a[i][j-1] == '*')
				a[i][j]++;
				if(a[i][j+1] == '*')
				a[i][j]++;
				if(a[i+1][j-1] == '*')
				a[i][j]++;
				if(a[i+1][j] == '*')
				a[i][j]++;
				if(a[i+1][j+1] == '*')
				a[i][j]++;
			}
			printf("%c",a[i][j]);
		}
		printf("\n");
	}
return 0;
}
