// Codeforces 1417E - XOR Inverse
// Lucio Figueiredo

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
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

const int maxn = 3e5+10;

struct Node
{
    Node *t[2];
    vector<int> v[2];

    Node()
    {
        t[0] = t[1] = NULL;
    }
} *T;

void add(int x, int ind)
{
    Node *at = T;
    for (int b = 30; b >= 0; b--)
    {
        int k;
        if (x&(1<<b)) at->v[1].pb(ind), k = 1;
        else at->v[0].pb(ind), k = 0;
    
        if (!at->t[k]) at->t[k] = new Node();

        at = at->t[k];
    }
}

int a[maxn];
ll qtd[2][31];

void get(Node *at, int b)
{
    int ptr0 = 0, ptr1 = 0;
    ll qtdInv = 0;

    for (; ptr0 < at->v[0].size(); ptr0++)
    {
        while (ptr1+1 < at->v[1].size() and at->v[1][ptr1+1] < at->v[0][ptr0])
            ptr1++;
        if (ptr1 < at->v[1].size() and at->v[1][ptr1] < at->v[0][ptr0]) qtdInv += ptr1+1;
    }
    qtd[0][b] += qtdInv;
    qtd[1][b] += (1ll*at->v[0].size()*at->v[1].size()-qtdInv);

    if (b > 0 and at->t[0]) get(at->t[0], b-1);
    if (b > 0 and at->t[1]) get(at->t[1], b-1);
}

void solve()
{
    memset(qtd, 0, sizeof qtd);
    T = new Node();

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        add(a[i], i);
    }
    
    get(T, 30);

    int ans = 0;
    ll inv = 0;
    for (int b = 30; b >= 0; b--)
    {
        if (qtd[0][b] > qtd[1][b])
        {
            ans += (1<<b);
            inv += 1ll*qtd[1][b];
        }
        else inv += 1ll*qtd[0][b];
    }
    
    cout << inv << " " << ans << nl;
}

int main(void)
{
	int tc = 1;
//	cin >> tc;
	while (tc--)
	{
		solve();
	}
}
