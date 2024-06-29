// Codeforces 1383A - String Transformation 1
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
    string a, b;
    cin >> a >> b;

    bool ok = 1;
    for (int i = 0; i < n; i++)
        if (a[i] > b[i])
            ok = 0;

    if (!ok)
    {
        cout << "-1\n";
        return;
    }
    
    int ans = 0;
    for (int i = 0; i < 20; i++)
    {
        bool done = 1;
        for (int j = 0; j < n; j++)
            if (b[j] != a[j])
                done = 0;

        if (done) break;

        set<int> st;
        for (int j = 0; j < n; j++)
            if (b[j]-'a' == i and a[j] < b[j])
                st.insert(a[j]-'a');

        ans += st.size();

        for (int j = 0; j < n; j++)
            if (a[j] != b[j] and st.find(a[j]-'a') != st.end())
                a[j] = i+'a';
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
 
