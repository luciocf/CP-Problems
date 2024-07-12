// POI 2010 - Sums
// Lúcio Cardoso

// Solution: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/POI/POI10-sums-Mohamed_Nasser.pdf

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

const int maxn = 5e3+10;
const int maxv = 5e4+10;
const int inf = 1e9+10;

int n;
int a[maxn];
int dist[maxv];
bool mark[maxv];

void dijkstra(void)
{
    dist[0] = 0;
    for (int i = 1; i < maxv; i++)
        dist[i] = inf;

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, 0});
    
    while (!pq.empty())
    {
        auto [d, u] = pq.top(); pq.pop();
        if (mark[u]) continue;
        mark[u] = 1;

        for (int i = 2; i <= n; i++)
        {
            int v = (u+a[i])%a[1];

            if (dist[v] > d+a[i])
            {
                dist[v] = d+a[i];
                pq.push({dist[v], v});
            }
        }
    }
}

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    dijkstra();

    int q;
    cin >> q;
    while (q--)
    {
        int x;
        cin >> x;

        if (dist[x%a[1]] <= x) cout << "TAK\n";
        else cout << "NIE\n";
    }
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

