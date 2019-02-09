// IOI 2011 - Rice Hub
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5+10;

typedef long long ll;

ll num[MAXN], soma[MAXN], b;
int n;

bool ok(int k)
{
    if (k == 1) return true;

    ll c = soma[k]-soma[1]-(k-1)*num[1];
    int ind = 1;
    for (int i = 2; i <= k; i++)
    {
        ll aux = (i-1)*num[i]-soma[i-1]+soma[k]-soma[i]-(k-i)*num[i];
        if (aux <= c) c = aux, ind = i;
    }

    if (c <= b) return true;

    for (int i = k+1; i <= n; i++)
    {
        c -= (num[ind]-num[i-k]);
        c += (num[i]-num[ind]);

        int j = ind+1;
        ll aux = (j-(i-k+1))*num[j]-(soma[j-1]-soma[i-k]) + (soma[i]-soma[j])-(i-j)*num[j];
        if (aux <= c)
        {
            c = aux;
            ind = j;
        }

        if (c <= b) return true;
    }
    return false;
}

int busca(void)
{
    int ini = 1, fim = n;
    while (ini <= fim)
    {
        int mid = (ini+fim)>>1;

        if (mid == n && ok(mid)) return n;
        else if (mid == n)
        {
            fim = mid-1;
            continue;
        }

        if (ok(mid) && !ok(mid+1)) return mid;
        else if (ok(mid) && ok(mid+1)) ini = mid+1;
        else if (!ok(mid)) fim = mid-1;
    }
}

int besthub(int r, int l, int x[], ll k)
{
    n = r, b = k;
    for (int i = 1; i <= n; i++)
    {
        num[i] = x[i-1];
        soma[i] = soma[i-1]+num[i];
    }

    return busca();
}
