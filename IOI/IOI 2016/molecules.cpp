// IOI 2016 - Detecting Molecules
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5+10;

typedef long long ll;

struct P {
    int ind;
    ll v;
} num[MAXN];

bool comp(P a, P b)
{
    return a.v < b.v;
}

ll soma[MAXN];

int w[MAXN], res[MAXN];

int busca(int pos, int k, int n)
{
    int ini = pos, fim = n;
    while (ini <= fim)
    {
        int mid = (ini+fim)>>1;

        if (mid == n && soma[mid]-soma[pos-1] <= k) return mid;
        else if (mid == n)
        {
            fim = mid-1;
            continue;
        }

        if (soma[mid]-soma[pos-1] <= k && soma[mid+1]-soma[pos-1] <= k) ini = mid+1;
        else if (soma[mid]-soma[pos-1] <= k && soma[mid+1]-soma[pos-1] > k) return mid;
        else if (soma[mid]-soma[pos-1] > k) fim = mid-1;
    }
    return -1;
}

int find_subset(int l, int r, int w[], int n, int result[])
{
    for (int i = 1; i <= n; i++)
        num[i].ind = i-1, num[i].v = w[i-1];
    sort(num+1, num+n+1, comp);

    for (int i = 1; i <= n; i++)
        soma[i] = soma[i-1]+num[i].v;

    int ini = -1, fim = -1;
    for (int i = 1; i <= n; i++)
    {
        int pos = busca(i, r, n);
        if (pos == -1) continue;

        if (soma[pos]-soma[i-1] >= l)
        {
            ini = i, fim = pos;
            break;
        }
    }

    if (ini == -1)
    {
        cout << "0\n";
        return 0;
    }

    int ind = -1;
    for (int i = ini; i <= fim; i++)
        result[++ind] = num[i].ind;

    cout << ind+1 << "\n" << result[0];
    for (int i = 1; i <= ind; i++)
        cout << " " << result[i];
    cout << "\n";
    return ind+1;
}


int main(void)
{
    int n, l, r;
    cin >> n >> l >> r;

    for (int i = 0; i < n; i++) cin >> w[i];

    find_subset(l, r, w, n, res);
}
