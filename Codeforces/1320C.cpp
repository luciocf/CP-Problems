// Codeforces 1320C - World of Darkraft: Battle for Azathoth
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

const int maxn = 2e5+10;
const int maxv = 1e6+10;
const int inf = 2e9+10;
const ll infll = 2e18+10;

ll tree[4*maxv], lazy[4*maxv];

void flush(int node, int l, int r)
{
    if (!lazy[node]) return;

    if (l != r)
    {
        lazy[2*node] += lazy[node];
        lazy[2*node+1] += lazy[node];
    }

    tree[node] += lazy[node];
    lazy[node] = 0;
}

void upd(int node, int l, int r, int a, int b, int v)
{
    flush(node, l, r);
    if (l > b or r < a) return;
    if (l >= a and r <= b)
    {
        lazy[node] += 1ll*v;
        flush(node, l, r);
        return;
    }

    int mid = (l+r)>>1;

    upd(2*node, l, mid, a, b, v); upd(2*node+1, mid+1, r, a, b, v);
    tree[node] = max(tree[2*node], tree[2*node+1]);
}

pii a[maxn], b[maxn];
int suf[maxn];
pair<pii, int> mons[maxn];

void solve()
{
    int n, m, p;
    cin >> n >> m >> p;

    for (int i = 1; i <= n; i++)
        cin >> a[i].ff >> a[i].ss;

    for (int i = 1; i <= m; i++)
        cin >> b[i].ff >> b[i].ss;

    for (int i = 1; i <= p; i++)
        cin >> mons[i].ff.ff >> mons[i].ff.ss >> mons[i].ss;

    sort(a+1, a+n+1); sort(b+1, b+m+1); sort(mons+1, mons+p+1);

    suf[n] = a[n].ss;
    for (int i = n-1; i >= 1; i--)
        suf[i] = min(suf[i+1], a[i].ss);
    
    int ptr = m, mn = b[m].ss;
    for (int i = maxv-1; i >= 1; i--)
    {
        while (ptr > 1 and b[ptr-1].ff > i)
            mn = min(mn, b[ptr-1].ss), ptr--;
        
        if (b[ptr].ff <= i) upd(1, 1, maxv-1, i, i, -inf);
        else upd(1, 1, maxv-1, i, i, -mn);
    }

    ptr = 1, mn = inf;
    ll ans = -suf[1];
    for (int i = 1; i <= m; i++)
        mn = min(mn, b[i].ss);
    ans -= mn;

    for (int i = 1; i <= p; i++)
    {
        upd(1, 1, maxv-1, mons[i].ff.ss, maxv-1, mons[i].ss);

        while (ptr <= n and a[ptr].ff <= mons[i].ff.ff)
            ptr++;
        
        if (ptr > n) break;
        
        flush(1, 1, maxv-1);
        ans = max(ans, tree[1] - 1ll*suf[ptr]);
    }

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

