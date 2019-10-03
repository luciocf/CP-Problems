// POI 2010 - Pilots
// Lúcio Cardoso

// 1. The condition for an interval [l, r] is the same as maximum(l...r)-minimum(l...r) <= t.

// 2. Thus, for a fixed r, the leftmost possible l is certainly >= than the leftmost l for (r-1).
// Therefore, we can use two pointers.

// 3. Now, the problem is reduced to:

//	* Erasing an element from the back
//  * Inserting an element
//  * Querying min/max

// We can use a min/max queue to solve the problem in O(n);

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 3e6+10;

struct MinQueue
{
	int l, r;
	deque<pii> dq;

	void init(void) {l = r = 0;}

	void push(int x)
	{
		while (dq.size() > 0 && dq.back().first >= x)
			dq.pop_back();

		dq.push_back({x, r++});
	}

	void pop(void)
	{
		if (dq.size() > 0 && dq.front().second == l)
			dq.pop_front();

		l++;
	}

	int getmin(void) {return dq.front().first;}
};

struct MaxQueue
{
	int l, r;
	deque<pii> dq;

	void init(void) {l = r = 0;}

	void push(int x)
	{
		while (dq.size() > 0 && dq.back().first <= x)
			dq.pop_back();

		dq.push_back({x, r++});
	}

	void pop(void)
	{
		if (dq.size() > 0 && dq.front().second == l)
			dq.pop_front();

		l++;
	}

	int getmax(void) {return dq.front().first;}
};

int n;
int a[maxn];

int main(void)
{
	int t;
	scanf("%d %d", &t, &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	MinQueue mn;
	mn.init();

	MaxQueue mx;
	mx.init();

	int ptr = 1, ans = 1;
	for (int r = 1; r <= n; r++)
	{
		mn.push(a[r]); mx.push(a[r]);

		while (mx.getmax()-mn.getmin() > t)
		{
			mn.pop(); mx.pop();
			++ptr;
		}

		ans = max(ans, r-ptr+1);
	}

	printf("%d\n", ans);
}
