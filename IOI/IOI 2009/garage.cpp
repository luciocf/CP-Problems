
// IOI 2009 - Garage
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110;
const int MAXM = 2010;

int num[MAXM], peso[MAXM], custo[MAXN];
bool ocupado[MAXN];

int main(void)
{
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> custo[i];
    for (int i = 1; i <= m; i++)
        cin >> peso[i];

    queue<int> fila;
    int ans = 0;
    for (int i = 1; i <= 2*m; i++)
    {
        int x;
        cin >> x;

        if (x > 0)
        {
            bool flag = 0;
            for (int i = 1; i <= n; i++)
            {
                if (!ocupado[i])
                {
                    ocupado[i] = 1;
                    flag = 1;
                    ans += peso[x]*custo[i];
                    num[x] = i;
                    break;
                }
            }
            if (!flag) fila.push(x);
        }
        else
        {
            x = -x;
            ocupado[num[x]] = 0;

            if (fila.size() > 0)
            {
                num[fila.front()] = num[x];
                ans += custo[num[x]]*peso[fila.front()];
                fila.pop();
                ocupado[num[x]] = 1;
            }
        }
    }
    cout << ans << "\n";
}
