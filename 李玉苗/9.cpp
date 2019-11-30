/*不循环还是好康些（尬笑.jpg 
#include <stdio.h>
const int maxn = 50;
int main(){
	int m, n; 
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
		for(int j = 2; j < n + 2; j++){
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
				printf("%d ", mine[i][j] - 1);
			}
			else
				printf("* ");	
		}
		printf("\n");
	}
			
	return 0;
}*/


#include <stdio.h>
const int maxn = 50;
int main(){
	char mine[maxn][maxn];
	int m, n, count;
	
	scanf("%d %d", &m, &n);
	for(int i = 0; i < m + 2; i++)
		for(int j = 0; j < n + 2; j++)
			mine[i][j] = '?';
			
	for(int i = 1; i < m + 1; i++)
		for(int j = 1; j < n + 2; j++)
			mine[i][j] = getchar();
			
	for(int i = 1; i < m + 1; i++){
		for(int j = 1; j < n + 2; j++){
			if(mine[i][j] == '*')
				printf("* ");
			if(mine[i][j] == '?'){
				count = 0;
				for(int p = i - 1; p < i + 2; p++)
					for(int q = j - 1; q < j + 2; q++)
						if(mine[p][q] == '*')
							count++;
				printf("%d ", count);
			}
		}
		printf("\n");
	}
	
	return 0;
} 


















