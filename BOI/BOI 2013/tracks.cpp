// BOI 2013 - Tracks
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 4e3+10;

typedef pair<int, int> pii;

int n, m;
int ans;

char tab[maxn][maxn];

bool mark[maxn][maxn];

int linha[] = {-1, 1, 0, 0};
int coluna[] = {0, 0, -1, 1};

void bfs(void)
{
    deque<pair<pii, int>> dq;

    ans = 1, mark[0][0] = 1;
    dq.push_front({{0, 0}, 1});

    while (!dq.empty())
    {
        int x = dq.front().first.first;
        int y = dq.front().first.second;
        int t = dq.front().second;
        dq.pop_front();

        ans = max(ans, t);

        for (int i = 0; i < 4; i++)
        {
            int a = x+linha[i], b = y+coluna[i];

            if (a < 0 || a >= n || b < 0 || b >= m || mark[a][b] || tab[a][b] == '.') continue;

            if (tab[a][b] != tab[x][y]) dq.push_back({{a, b}, t+1});
            else dq.push_front({{a, b}, t});

            mark[a][b] = 1;
        }
    }
}

int main(void)
{
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf(" %c", &tab[i][j]);

    bfs();

    printf("%d\n", ans);
}
