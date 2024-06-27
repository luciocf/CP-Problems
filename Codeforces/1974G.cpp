// Codeforces 1974G - Money Buys Less Happiness Now
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
    int n, x;
    cin >> n >> x;

    multiset<int> st;
    ll sum = 0;
    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;

        if (i == 1) continue;

        if (sum + 1ll*a <= 1ll*x*(i-1))
        {
            st.ins(a);
            sum += 1ll*a;
        }
        else
        {
            if (st.size() and a < *st.rbegin())
            {
                sum -= 1ll*(*st.rbegin()); sum += 1ll*a;
                st.erase(st.find(*st.rbegin()));
                st.insert(a);
            }
        }
    }
    
    cout << st.size() << nl;
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
 
