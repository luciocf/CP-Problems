// Codeforces 1344B - Monopole Magnets
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

const int maxn = 1e3+10;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int n, m;
int qtd[2][maxn];
char tab[maxn][maxn];
bool mark[maxn][maxn];

void dfs(int x, int y)
{
    mark[x][y] = 1;
    for (int i = 0; i < 4; i++)
    {
        int a = x+dx[i], b = y+dy[i];
        if (a < 1 or a > n or b < 1 or b > m or mark[a][b] or tab[a][b] == '.')
            continue;
        dfs(a, b);
    }
}

void solve()
{
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            mark[i][j] = 0;
            qtd[0][i] = qtd[1][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> tab[i][j];
    
    bool ok = 1;
    for (int i = 1; i <= n; i++)
    {
        int tot = 0;
        for (int j = 1; j <= m; j++)
        {
            if (tab[i][j] == '#')
            {
                ++tot;
                while (j+1 <= m and tab[i][j+1] == '#')
                    j++;
            }
        }

        if (tot > 1) ok = 0;
    }

    for (int j = 1; j <= m; j++)
    {
        int tot = 0;
        for (int i = 1; i <= n; i++)
        {
            if (tab[i][j] == '#')
            {
                ++tot;
                while (i+1 <= n and tab[i+1][j] == '#')
                    i++;
            }
        }

        if (tot > 1) ok = 0;
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (tab[i][j] == '#')
                qtd[0][i]++, qtd[1][j]++;

    for (int i = 1; i <= n; i++)
    {
        if (qtd[0][i] == 0)
        {
            bool has = 0;
            for (int j = 1; j <= m; j++)
                if (qtd[1][j] == 0)
                    has = 1;

            if (!has) ok = 0;
        }
    }

    for (int j = 1; j <= m; j++)
    {
        if (qtd[1][j] == 0)
        {
            bool has = 0;
            for (int i = 1; i <= n; i++)
                if (qtd[0][i] == 0)
                    has = 1;

            if (!has) ok = 0;
        }
    }

    if (!ok)
    {
        cout << "-1\n";
        return;
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (tab[i][j] == '#' and !mark[i][j])
                dfs(i, j), ++ans;

    cout << ans << nl;
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
 
