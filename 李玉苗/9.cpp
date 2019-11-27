#include <stdio.h>
const int maxn = 50;
int main(){
	int m, n, count = 0; 
	int mine[maxn][maxn];
	
	scanf("%d %d", &m, &n);
	for(int i = 0; i < m + 2; i++)
		for(int j = 0; j < n + 3; j++)
			mine[i][j] = 1;
	for(int i = 1; i < m + 1; i++){
		for(int j = 1; j < n + 2; j++){
			if(getchar() == '*')	
				mine[i][j] = 0;
		}
	}
	for(int i = 1; i < m + 1; i++){
		for(int j = 1; j < n + 2; j++){
			if(mine[i][j] != 0){
				if(mine[i - 1][j - 1] == 0)
					mine[i][j]++;
				if(mine[i - 1][j] == 0)
					mine[i][j]++;
				if(mine[i - 1][j + 1] == 0)
					mine[i][j]++;
				if(mine[i][j - 1] == 0)
					mine[i][j]++;
				if(mine[i][j + 1] == 0)
					mine[i][j]++;
				if(mine[i + 1][j - 1] == 0)
					mine[i][j]++;
				if(mine[i + 1][j] == 0)
					mine[i][j]++;
				if(mine[i + 1][j + 1] == 0)
					mine[i][j]++;
			}	
		}
	}
	for(int i = 1; i < m + 1; i++)
		for(int j = 2; j < n + 2; j++){
			if(mine[i][j] != 0)
				printf("%d ", mine[i][j] - 1);
			else
				printf("* ");
			count++;
			if(count % n == 0)
				printf("\n");		
		}
			
	return 0;
}
