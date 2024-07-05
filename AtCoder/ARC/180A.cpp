// ARC 180A - ABA and BAB
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

void solve()
{
    int n;
    string s;
    cin >> n >> s;
    
    int ans = 1;
    for (int i = 0; i < n; i++)
    {
        int j = i;
        while (j+1 < n and s[j+1] != s[j])
            j++;
        
        int k = (j-i+2)/2;
        ans = (1ll*ans*k)%mod;

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
//	cin >> tc;
	while (tc--)
	{
		solve();
	}
}

