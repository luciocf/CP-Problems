// Codeforces 1349C - Orac and Game of Life
// Lucio Figueiredo

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <deque>
#include <cstring>
#include <set>
#include <map>
#include <cmath>

using namespace std;

#define ff first
#define ss second
#define mkp make_pair
#define pb push_back
#define sz(x) (int)(x).size()
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert

const char nl = '\n';

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 1010;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int n, m;
char tab[maxn][maxn];
int comp[maxn][maxn], dist[maxn][maxn];

int qtd[maxn*maxn];

void dfs(int x, int y, int cc)
{
    comp[x][y] = cc;
    qtd[cc]++;
    for (int i = 0; i < 4; i++)
    {
        int a = x + dx[i];
        int b = y + dy[i];

        if (a < 1 or a > n or b < 1 or b > m or comp[a][b] or tab[a][b] != tab[x][y]) continue;
        dfs(a, b, cc);
    }
}

void bfs(void)
{
    memset(dist, -1, sizeof dist);

    queue<pii> fila;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (qtd[comp[i][j]] > 1)
                fila.push({i, j}), dist[i][j] = 0;

   while (!fila.empty())
   {
       int x = fila.front().ff, y = fila.front().ss;
       fila.pop();

       for (int i = 0; i < 4; i++)
       {
            int a = x + dx[i];
            int b = y + dy[i];

            if (a < 1 or a > n or b < 1 or b > m or dist[a][b] != -1) continue;
            dist[a][b] = dist[x][y]+1;
            fila.push({a, b});
       }
   }
}

void solve()
{
    int q;
    cin >> n >> m >> q;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> tab[i][j];

    int cc = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (!comp[i][j])
                dfs(i, j, ++cc);

    bfs();

    while (q--)
    {
        int x, y;
        ll t;
        cin >> x >> y >> t;

        if (dist[x][y] == -1 or 1ll*dist[x][y] >= t) cout << tab[x][y] << nl;
        else
        {
            t -= dist[x][y];
            if (t%2 == 0) cout << tab[x][y] << nl;
            else if (tab[x][y] == '1') cout << "0\n";
            else cout << "1\n";
        }
    }
}

int main(void)
{
	cin.tie(0)->sync_with_stdio(0); 
    cin.exceptions(cin.failbit);
    // xor ^ 
    
	int tc = 1;
//	cin >> tc;
	while (tc--)
	{
		solve();
	}
}

