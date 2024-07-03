// Codeforces 1352G - Special Permutation
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

    if (n <= 3)
    {
        cout << "-1\n";
        return;
    }

    vector<int> v;
    v.pb(3); v.pb(1); v.pb(4); v.pb(2);

    for (int i = 1; i <= n-4; i++)
    {
        for (auto &x: v)
            ++x;
        
        if (v.back() < 6 and v.back() > 2) v.pb(1);
        else
        {
            vector<int> aux;
            aux.pb(1);
            for (auto x: v)
                aux.pb(x);
            swap(aux, v);
        }
    }

    for (auto x: v)
        cout << x << " ";
    cout << nl;
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

