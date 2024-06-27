// Codeforces 1974F - Cutting Game
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

int x[maxn], y[maxn];

void solve()
{
    int n, m, k, t;
    cin >> n >> m >> k >> t;

    set<pii> stR, stC;
    for (int i = 1; i <= k; i++)
    {
        cin >> x[i] >> y[i];

        stR.ins({x[i], i});
        stC.ins({y[i], i});
    }
    
    int ans[2] = {0, 0};
    
    int at = 0;
    int lR = 1, rR = n, lC = 1, rC = m;
    while (t--)
    {
        int qtd = 0;

        char c;
        int v;
        cin >> c >> v;

        if (c == 'U')
        {
            while (stR.size() and stR.begin()->ff <= lR+v-1)
            {
                stC.erase({y[stR.begin()->ss], stR.begin()->ss});
                stR.erase(stR.begin());
                qtd++;
            }
            lR += v;
        }
        else if (c == 'D')
        {
            while (stR.size() and stR.rbegin()->ff >= rR-v+1)
            {
                stC.erase({y[stR.rbegin()->ss], stR.rbegin()->ss});
                stR.erase(*stR.rbegin());
                qtd++;
            }
            rR -= v;
        }
        else if (c == 'L')
        {
            while (stC.size() and stC.begin()->ff <= lC+v-1)
            {
                stR.erase({x[stC.begin()->ss], stC.begin()->ss});
                stC.erase(stC.begin());
                qtd++;
            }
            lC += v;
        }
        else
        {
            while (stC.size() and stC.rbegin()->ff >= rC-v+1)
            {
                stR.erase({x[stC.rbegin()->ss], stC.rbegin()->ss});
                stC.erase(*stC.rbegin());
                qtd++;
            }
            rC -= v;
        }

        ans[at] += qtd;
        at = (at == 0 ? 1 : 0);
    }

    cout << ans[0] << " " << ans[1] << nl;
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
 
