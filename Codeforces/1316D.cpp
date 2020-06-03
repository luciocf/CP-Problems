// Codeforces 1316D - Nash Matrix
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>
 
#define ff first
#define ss second
 
using namespace std;
 
typedef pair<int, int> pii;
 
const int maxn = 1e3+10;
 
int linha[] = {-1, 1, 0, 0};
int coluna[] = {0, 0, -1, 1};
 
int n;
pii pos[maxn][maxn];
 
char ans[maxn][maxn];
 
bool mark[maxn][maxn];
 
void dfs(int x, int y)
{
	mark[x][y] = 1;
 
	for (int i = 0; i < 4; i++)
	{
		int a = x+linha[i], b = y+coluna[i];
 
		if (a < 1 || a > n || b < 1 || b > n || mark[a][b] || pos[a][b].ff != pos[x][y].ff || pos[a][b].ss != pos[x][y].ss) continue;
 
		if (linha[i] == 1) ans[a][b] = 'U';
		else if (linha[i] == -1) ans[a][b] = 'D';
		else if (coluna[i] == 1) ans[a][b] = 'L';
		else ans[a][b] = 'R';
 
		dfs(a, b);
	}
}
 
int main(void)
{
	scanf("%d", &n);
 
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d %d", &pos[i][j].ff, &pos[i][j].ss);
 
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			int a = pos[i][j].ff, b = pos[i][j].ss;
 
			if (a != -1 && !mark[i][j])
			{
				if (mark[a][b] || pos[a][b].ff != a || pos[a][b].ss != b)
				{
					printf("INVALID\n");
					return 0;
				}
 
				ans[a][b] = 'X';
				dfs(a, b);
			}
		}
	}
 
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (pos[i][j].ff != -1) continue;
 
			bool ok = 0;
 
			for (int l = 0; l < 4; l++)
			{
				int a = i+linha[l], b = j+coluna[l];
 
				if (a < 1 || a > n || b < 1 || b > n || mark[a][b]) continue;
 
				ok = 1;
 
				if (linha[l] == 1) ans[i][j] = 'D';
				else if (linha[l] == -1) ans[i][j] = 'U';
				else if (coluna[l] == 1) ans[i][j] = 'R';
				else ans[i][j] = 'L';
 
				break;
			}
 
			if (!ok)
			{
				printf("INVALID\n");
				return 0;
			}
		}
	}
 
	printf("VALID\n");
 
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			printf("%c", ans[i][j]);
		printf("\n");
	}
}
