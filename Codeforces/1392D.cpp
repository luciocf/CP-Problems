// Codeforces 1392D - Omkar and Bed Wars
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

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    
    int qtd = 0, l, r;
    for (l = 0; l < s.size() and s[l] == s[0]; l++)
        qtd++;
    l--;

    for (r = (int)s.size()-1; r > l and s[r] == s[0]; r--)
        qtd++;
    r++;

    if (r == l+1)
    {
        cout << (qtd+2)/3 << nl;
        return;
    }

    int ans = qtd/3;
    for (int i = l+1; i < r; i++)
    {
        int ptr = i;
        qtd = 1;
        while (ptr+1 < r and s[ptr+1] == s[i])
        {
            ptr++;
            qtd++;
        }

        ans += qtd/3;
        i = ptr;
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

