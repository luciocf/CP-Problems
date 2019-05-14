// COI 2016 - Torrent
// Lúcio Cardoso

// Solution:

// 1. Call the two chosen vertices A and B. Root the tree at A. Suppose node B wasn't chosen and let T[u] be the
// smallest amount of time to reach everyone on u's subtree after u was reached. Then we have the following:
// T[u] = max(T[v_i] + i), where v_i is the ith children of u ordered decreasingly by T[v_i]. It's simple to calculate all values
// T with a single DFS, and the answer in this case would be T[A].

// 2. Now, we know that node B is in the tree. Notice that for all nodes who aren't in the subtree of any node on the path A->B, 
// it is always optimal for A to reach it first. Similarly, for all nodes on B's subtree, it is always optimal for B to reach it first.
// Therefore, we can define the last node on the path A->B that A will reach and "cut" this vertex's edge to his parent, separating the tree
// in 2 components. The first component represents all vertices A will reach, while the second one represents all vertices B will reach.
// We can therefore run the DFS on (1) on both components and the answer will be the maximum between them. This algorithm runs in O(n^2).

// 3. Let C_1, C_2, ..., C_p be the vertices on the path A->B, where C_1 = A and C_p = B. Call C_k the first node in the path such
// that when "cutting" this vertex's edge, B's component has a larger cost than A's component. Notice, then, that there are only two
// optimal points for cutting: C_k and C_{k+1}. Cutting C_k gets us the minimal cost when B's component is the greatest and cutting C_{k+1} gets us
// the minimal cost when A's component is the greatest.

// 4. We can find the optimal cutting point using a Binary Search and the previous DFS. The final solution has complexity O(n log n).

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e5+10;

int n;
int A, B;

vector<int> grafo[maxn];
vector<int> path;

bool comp(int a, int b) {return a>b;}
	
// finds path A->B
bool dfs(int u, int p)
{
	if (u == B)
	{
		path.push_back(B);
		return 1;
	}

	for (auto v: grafo[u])
	{
		if (v == p) continue;
		if (!dfs(v, u)) continue;

		path.push_back(u);
		return 1;
	}

	return 0;
}

int solve(int u, int p, int block)
{
	vector<int> child;

	int tt = 0;

	for (auto v: grafo[u])
		if (v != p && v != block)
			child.push_back(solve(v, u, block));

	sort(child.begin(), child.end(), comp);

	for (int i = 0; i < child.size(); i++)
		tt = max(tt, child[i]+i+1);

	return tt;
}

int busca(void)
{
	int ini = 1, fim = path.size()-1, ans = -1;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		int ans1 = solve(A, 0, path[mid]);
		int ans2 = solve(B, 0, path[mid-1]);

		if (ans2 >= ans1) ans = mid-1, ini = mid+1;
		else fim = mid-1;
	}

	return ans;
}

int main(void)
{
	scanf("%d %d %d", &n, &A, &B);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	dfs(A, 0);
	reverse(path.begin(), path.end());

	int opt = busca();

	int ans;

	if (opt == -1)
		ans = solve(A, 0, path[1]);
	else
	{
		ans = solve(B, 0, path[opt]);
		if (opt < path.size()-2)
			ans = min(ans, solve(A, 0, path[opt+2]));
	}

	printf("%d\n", ans);
}
