// Codeforces 1335E2 - Three Blocks Palindrome (hard version)
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

vector<int> pos[210];
int qtd[210];

void solve()
{
    int n;
    cin >> n;

    for (int i = 1; i <= 200; i++)
        pos[i].clear();
    
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pos[a[i]].pb(i);
    }

    int ans = 1;
    for (int k = 1; k <= 200; k++)
    {
        int m = pos[k].size();
        if (m <= 1) continue;
        
        for (int i = 1; i <= 200; i++)
            qtd[i] = 0;

        int l, r, sz;
        if (m%2) l = m/2-1, r = m/2+1, sz = m-1;
        else l = m/2-1, r = m/2, sz = m;
            
        int mx = 0;
        for (int i = pos[k][l]+1; i < pos[k][r]; i++)
            qtd[a[i]]++, mx = max(mx, qtd[a[i]]);
        
        ans = max(ans, sz+mx);

        while (l > 0 and r+1 < m)
        {
            for (int i = pos[k][l]; i > pos[k][l-1]; i--)
                qtd[a[i]]++, mx = max(mx, qtd[a[i]]);

            for (int i = pos[k][r]; i < pos[k][r+1]; i++)
                qtd[a[i]]++, mx = max(mx, qtd[a[i]]);
            
            sz -= 2, l--, r++;
            ans = max(ans, sz+mx);
        }
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
 
