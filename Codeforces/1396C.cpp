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

const int maxn = 1e5+10;

int n;
int a[maxn];

int fq[maxn], mark[maxn];

vector<int> toAdd[maxn];

bool ok(int d)
{
    for (int i = 1; i <= n; i++)
    {
        fq[a[i]] = mark[a[i]] = 0; 
        toAdd[i].clear();
    }

    for (int i = 1; i <= n; i++)
        fq[a[i]]++;

    set<pii> st;
    for (int i = 1; i <= n; i++)
    {
        if (!mark[a[i]])
        {
            mark[a[i]] = 1;
            st.ins({fq[a[i]], a[i]});
        }
    }
    
    for (int i = 1; i <= n; i++)
    {
        while (toAdd[i].size())
        {
            int x = toAdd[i].back();

            st.ins({fq[x], x});

            toAdd[i].pop_back();
        }

        if (st.size() == 0) return 0;
        
        int x = st.rbegin()->ss;
        fq[x]--;
        st.erase(*st.rbegin());

        if (i+d+1 <= n and fq[x] > 0) toAdd[i+d+1].pb(x);
    }

    return 1;
}

void solve()
{
    cin >> n;
    
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    int ini = 1, fim = n, ans = 0;
    while (ini <= fim)
    {
        int mid = (ini+fim)>>1;

        if (ok(mid)) ans = mid, ini = mid+1;
        else fim = mid-1;
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
 
