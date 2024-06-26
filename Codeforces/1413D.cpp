// Codeforces 1413D - Shurikens
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

struct Op
{
    char op;
    int v;
} event[maxn];

int ind[maxn], num[maxn];

void solve()
{
    int n;
    cin >> n;
    
    int qtd = 0;

    for (int i = 1; i <= 2*n; i++)
    {
        char c;
        cin >> c;

        if (c == '+') event[i] = {'+', 0}, qtd++;
        else
        {
            int x;
            cin >> x;

            event[i] = {'-', x};
            ind[x] = qtd;
        }
    }
    
    set<int> st;
    for (int i = 1; i <= n; i++)
        st.insert(i);
    
    bool ok = 1;
    for (int i = 1; i <= n; i++)
    {
        auto it = st.upper_bound(ind[i]);
        if (it == st.begin())
        {
            ok = 0;
            break;
        }

        it--;
        num[*it] = i;
        st.erase(*it);
    }

    if (!ok)
    {
        cout << "NO\n";
        return;
    }

    qtd = 0;
    st.clear();
    for (int i = 1; i <= 2*n; i++)
    {
        if (event[i].op == '+')
        {
            ++qtd;
            st.insert(num[qtd]);
        }       
        else
        {
            if (*st.begin() != event[i].v)
            {
                ok = 0;
                break;
            }
            else st.erase(event[i].v);
        }
    }

    if (ok)
    {
        cout << "YES\n";
        for (int i = 1; i <= n; i++)
            cout << num[i] << " ";
        cout << nl;
    }
    else cout << "NO\n";
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
 
