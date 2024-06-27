// Codeforces 1396B - Stoned Game
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

void solve()
{
    int n;
    cin >> n;
    
    vector<int> a(n+1);
    int s = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        s += a[i];
    }

    bool ok = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] > s/2)
        {
            ok = 1;
            break;
        }
    }

    if (ok or s%2)
    {
        cout << "T\n";
        return;
    }
    cout << "HL\n";
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
 
