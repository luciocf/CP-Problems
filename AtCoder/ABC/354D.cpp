// ABC 354D - AtCoder Wallpaper
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

int md(int x)
{
    if (x >= 0) return x%4;
    return (4-((4-x)%4))%4;
}

int md2(int x)
{
    if (x >= 0) return x%2;
    return (2-((2-x)%2))%2;
}

void solve()
{
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    
    c--;
    int v0[4] = {2, 1, 0, 1};
    int v1[4] = {1, 2, 1, 0};
    
    ll tot0 = 0, tot1 = 0;
    
    if (c-a+1 <= 100)
    {
        for (int i = a; i <= c; i++)
        {
            tot0 += 1ll*v0[md(i)];
            tot1 += 1ll*v1[md(i)];
        }
    }
    else
    {
        while (md(a) != 0)
        {
            tot0 += 1ll*v0[md(a)];
            tot1 += 1ll*v1[md(a)];
            a++;
        }

        while (md(c) != 3)
        {
            tot0 += 1ll*v0[md(c)];
            tot1 += 1ll*v1[md(c)];
            c--;
        }

        tot0 += 4ll*(c-a+1)/4;
        tot1 += 4ll*(c-a+1)/4;
    }

    ll ans = 1ll*(tot0+tot1)*((d-b)/2ll);
    
    if (md2(b) != md2(d))
    {
        if (md2(b) == 0) ans += tot0;
        else ans += tot1;
    }

    cout << ans << nl;
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

