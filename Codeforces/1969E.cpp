// Codeforces 1969E - Unique Array
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

const int maxn = 3e5+10;

int tree[4*maxn], lazy[4*maxn];

void flush(int node, int l, int r)
{
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
        lazy[node] += v;
        flush(node, l, r);
        return;
    }

    int mid = (l+r)>>1;

    upd(2*node, l, mid, a, b, v); upd(2*node+1, mid+1, r, a, b, v);

    tree[node] = min(tree[2*node], tree[2*node+1]);
}

int getMn(int node, int l, int r, int a, int b)
{
    flush(node, l, r);
    if (l > b or r < a) return maxn;
    if (l >= a and r <= b) return tree[node];

    int mid = (l+r)>>1;
    return min(getMn(2*node, l, mid, a, b), getMn(2*node+1, mid+1, r, a, b));
}

int a[maxn];
vector<int> pos[maxn];

void solve()
{
    int n;
    cin >> n;

    for (int i = 1; i <= 4*n; i++)
        tree[i] = lazy[i] = 0;

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pos[a[i]].clear();
    }

    int ans = 0, ant = 0;
    for (int r = 1; r <= n; r++)
    {
        while (r <= n)
        {
            int p = (pos[a[r]].size() == 0 ? ant+1 : pos[a[r]].back()+1);

            upd(1, 1, n, p, r, 1);
            
            int p2 = (pos[a[r]].size() >= 2 ? pos[a[r]][pos[a[r]].size()-2]+1 : ant+1);

            if (pos[a[r]].size() >= 1) upd(1, 1, n, p2, pos[a[r]].back(), -1);
            
            pos[a[r]].pb(r);

            if (getMn(1, 1, n, ant+1, r) == 0) break;

            r++;
        }

        for (int i = ant+1; i <= r; i++)
            pos[a[i]].clear();

        if (r <= n) ans++, ant = r;
    }

    cout << ans << nl;
}

int main(void)
{
	cin.tie(0)->sync_with_stdio(0); 
    cin.exceptions(cin.failbit);
    // xor ^ 
    
	int tc = 1;
	cin >> tc;
	while (tc--)
	{
		solve();
	}
}
 
