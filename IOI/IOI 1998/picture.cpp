// IOI 1998 - Picture
// Lúcio Cardoso

// Solution:

// 1. Sort the vertical rectangle sides by their x coordinate and walk through them. While doing that,
// also sweep through the horizontal sides sorted by their y coordinate. While sweeping through the
// x coordinates, keep the difference between the previous and current x.

// 2. Use a counter "open" that checks if we're inside a rectangle. When there's a bottom horizontal
// side, add 1 to open. If it's a top horizontal side, subtract 1. If open = 1, add the current
// x segment to the answer (if the horizontal interval is inside this segment).

// 3. Repeat the same process, but now to calculate the perimeter of the vertical segments.

// Complexity: O(n^2).

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e3+10;

struct Rect
{
	int x1, y1, x2, y2;
} rect[maxn];

struct Event
{
	int y, type, ind;
};

int ans;

vector<int> sweepX;
vector<Event> sweepY;

bool comp(Event a, Event b)
{
	if (a.y == b.y) return a.type < b.type;
	return a.y < b.y;
}

void solve(void)
{
	sort(sweepX.begin(), sweepX.end());
	sort(sweepY.begin(), sweepY.end(), comp);

	for (int i = 1; i < sweepX.size(); i++)
	{
		int ax = sweepX[i-1], bx = sweepX[i];
		int open = 0;

		for (auto E: sweepY)
		{
			int ind = E.ind;

			if (rect[ind].x1 >= bx || rect[ind].x2 <= ax) continue;

			if (open == 0) ans += bx-ax;

			if (E.type == 0) open++;
			else open--;

			if (open == 0) ans += bx-ax;
		}
	}
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d %d %d", &rect[i].x1, &rect[i].y1, &rect[i].x2, &rect[i].y2);

		sweepX.push_back(rect[i].x1); sweepX.push_back(rect[i].x2);
		sweepY.push_back({rect[i].y1, 0, i}); sweepY.push_back({rect[i].y2, 1, i});
	}

	solve();

	sweepX.clear(); sweepY.clear();

	for (int i = 1; i <= n; i++)
	{
		swap(rect[i].x1, rect[i].y1);
		swap(rect[i].x2, rect[i].y2);
	}

	for (int i = 1; i <= n; i++)
	{
		sweepX.push_back(rect[i].x1); sweepX.push_back(rect[i].x2);
		sweepY.push_back({rect[i].y1, 0, i}); sweepY.push_back({rect[i].y2, 1, i});
	}

	solve();

	printf("%d\n", ans);
}
