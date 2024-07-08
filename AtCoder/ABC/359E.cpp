// AtCoder 359E - Water Tank
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

ll tree[2][4*maxn], lazy[4*maxn];

void flush(int node, int l, int r)
{
    if (!lazy[node]) return;

    if (l != r)
    {
        lazy[2*node] = lazy[node];
        lazy[2*node+1] = lazy[node];
    }

    tree[0][node] = 1ll*(r-l+1)*lazy[node];
    tree[1][node] = lazy[node];
}

void upd(int node, int l, int r, int a, int b, int v)
{
    flush(node, l, r);
    if (l > b or r < a) return;
    if (l >= a and r <= b)
    {
        lazy[node] = v;
        flush(node, l, r);
        return;
    }

    int mid = (l+r)>>1;
    upd(2*node, l, mid, a, b, v); upd(2*node+1, mid+1, r, a, b, v);

    tree[0][node] = tree[0][2*node]+tree[0][2*node+1];
    tree[1][node] = min(tree[1][2*node], tree[1][2*node+1]);
}

int getPos(int node, int l, int r, int v)
{
    flush(node, l, r);
    if (l == r) return l;
    
    int mid = (l+r)>>1;

    flush(2*node, l, mid); flush(2*node+1, mid+1, r);

    if (tree[1][2*node] < v) return getPos(2*node, l, mid, v);
    return getPos(2*node+1, mid+1, r, v);
}

ll getSum(int node, int l, int r, int a, int b)
{
    flush(node, l, r);
    if (l > b or r < a) return 0;
    if (l >= a and r <= b) return tree[0][node];

    int mid = (l+r)>>1;

    return getSum(2*node, l, mid, a, b) + getSum(2*node+1, mid+1, r, a, b);
}

void solve()
{
    int n;
    cin >> n;

    vector<int> a(n+1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int pos = getPos(1, 1, n+1, a[i]);
        
        if (pos >= i)
        {
            ans += 1ll*a[i];
            upd(1, 1, n+1, i, i, a[i]);
        }
        else
        {
            int qtd = i-pos+1;
            ll sum = getSum(1, 1, n+1, pos, i);
            ans += 1ll*qtd*a[i] - sum;
            upd(1, 1, n+1, pos, i, a[i]);
        }

        cout << ans+1 << " ";
    }

    cout << nl;
}

int main(void)
{
	cin.tie(0)->sync_with_stdio(0); 
    cin.exceptions(cin.failbit);
    // xor ^ 
    
	int tc = 1;
	while (tc--)
	{
		solve();
	}
}

