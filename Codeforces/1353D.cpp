// Codeforces 1353D - Constructing the Array
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

int a[maxn];

void solve()
{
    int n;
    cin >> n;

    set<pair<int, pii>> st;
    st.insert({-n, {1, n}});

    for (int i = 1; i <= n; i++)
    {
        auto pp = st.begin()->ss;
        int l = pp.ff, r = pp.ss;
        int mid = (l+r)>>1;
        a[mid] = i;
    
        st.erase(*st.begin());
        if (mid > l) st.insert({-(mid-l), {l, mid-1}});
        if (mid < r) st.insert({-(r-mid), {mid+1, r}});
    }

    for (int i = 1; i <= n; i++)
        cout << a[i] << " ";
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

