// Codeforces 1361B - Johnny and Grandmaster
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

const int mod = 1e9+7;

int pot(int a, int b)
{
    if (!b) return 1;
    int t = pot(a, b/2);

    if (b&1) return (1ll*a*((1ll*t*t)%mod))%mod;
    return (1ll*t*t)%mod;
}

void solve()
{
    int n, p;
    cin >> n >> p;
    
    vector<int> a(n);

    for (int i = 0; i < n; i++)
        cin >> a[i];

    if (p == 1)
    {
        if (n%2) cout << "1\n";
        else cout << "0\n";
        return;
    }

    sort(all(a));

    int ans = 0, qtd = 0;
    for (int i = n-1; i >= 0; i--)
    {
        ans = (ans + pot(p, a[i]))%mod;
        qtd = 1;
        
        int j;
        for (j = i-1; j >= 0; j--)
        {
            bool ok = 0;
            for (int l = 1; l <= a[j+1]-a[j]; l++)
            {
                if (1ll*qtd*p >= n)
                {
                    ok = 1;
                    break;
                }

                qtd = qtd*p;
            }

            if (ok)
            {
                for (int l = j; l >= 0; l--)
                    ans = (ans - pot(p, a[l]) + mod)%mod;
                
                cout << ans << nl;
                return;
            }

            ans = (ans - pot(p, a[j]) + mod)%mod;
            qtd--;

            if (qtd == 0)
                break;
        }

        i = j;
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

