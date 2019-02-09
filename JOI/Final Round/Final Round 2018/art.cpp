// JOI Final Round 2018 - Art
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 500010;
const ll INF = 1e16+10;

ll soma[MAXN];

pair<ll, ll> num[MAXN];

int main(void)
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> num[i].first >> num[i].second;
    sort(num+1, num+n+1);

    for (int i = 1; i <= n; i++)
        soma[i] = soma[i-1]+num[i].second;

    ll ans = -INF;

    ll aux = -INF;
    int pos = 1;
    for (int i = 1; i <= n; i++)
    {
        if (num[i].second > soma[i]-soma[pos-1]-num[i].first+num[pos].first)
            ans = max(ans, num[i].second), pos = i;
        else
            ans = max(ans, soma[i]-soma[pos-1]-num[i].first+num[pos].first);
    }
    
    cout << ans << "\n";
}
