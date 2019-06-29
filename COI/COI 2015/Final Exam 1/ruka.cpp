// COI 2015 - Final Exam #1 - Ruka
// Lúcio Cardoso

// Solution is the same as the one described here: http://hsin.hr/2015/ (Final Exam #1) 

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int maxv = 4e8+10;
const int add = 2e8;

map<int, int> bit[2][2];

int vx[maxn], vy[maxn];

stack<int> stk_x[2], stk_y[2];

void upd(int x, int v, int a, int b)
{
	x += add;

	for (; x < maxv; x += (x&-x))
		bit[a][b][x] += v;
}

int soma(int x, int a, int b)
{
	x += add;

	int ans = 0;
	for (; x > 0; x -= (x&-x))
		ans += bit[a][b][x];
	return ans;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	int pref_x = 1, pref_y = 1;

	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &vx[i], &vy[i]);
		pref_x += vx[i], pref_y += vy[i];
	}

	for (int i = n; i > 1; i--)
	{
		pref_x -= vx[i]; pref_y -= vy[i];

		int mn = min(pref_x, pref_x+vx[i]), mx = max(pref_x, pref_x+vx[i]);
		upd(mn, 1, 0, 0); upd(mx, 1, 0, 1);

		stk_x[0].push(mn); stk_x[1].push(mx);

		mn = min(pref_y, pref_y+vy[i]), mx = max(pref_y, pref_y+vy[i]);
		upd(mn, 1, 1, 0); upd(mx, 1, 1, 1);

		stk_y[0].push(mn); stk_y[1].push(mx);
	}

	pref_x = 1, pref_y = 1;

	int ptr = 1, ans = 0, delta_x = 0, delta_y = 0;

	if (min(1+vx[1], 1) < 0 && max(1+vx[1], 1) > 0) ans++;
	if (min(1+vy[1], 1) < 0 && max(1+vy[1], 1) > 0) ans++;

	int m;
	scanf("%d", &m);

	for (int i = 1; i <= m; i++)
	{
		char op;
		scanf(" %c", &op);

		if (op == 'B' && ptr != 1)
		{
			int mn = min(pref_x, pref_x+vx[ptr]), mx = max(pref_x, pref_x+vx[ptr]);
			if (mn < 0 && mx > 0) ans--;

			upd(mn-delta_x, 1, 0, 0); upd(mx-delta_x, 1, 0, 1);
			stk_x[0].push(mn-delta_x); stk_x[1].push(mx-delta_x);

			mn = min(pref_y, pref_y+vy[ptr]), mx = max(pref_y, pref_y+vy[ptr]);
			if (mn < 0 && mx > 0) ans--;

			upd(mn-delta_y, 1, 1, 0); upd(mx-delta_y, 1, 1, 1);
			stk_y[0].push(mn-delta_y); stk_y[1].push(mx-delta_y);

			ptr--;
			pref_x -= vx[ptr], pref_y -= vy[ptr];
		}
		else if (op == 'F' && ptr != n)
		{
			int mn = stk_x[0].top(), mx = stk_x[1].top();
			stk_x[0].pop(); stk_x[1].pop();

			upd(mn, -1, 0, 0); upd(mx, -1, 0, 1);

			mn = stk_y[0].top(), mx = stk_y[1].top();
			stk_y[0].pop(); stk_y[1].pop();

			upd(mn, -1, 1, 0); upd(mx, -1, 1, 1);

			pref_x += vx[ptr], pref_y += vy[ptr], ptr++;

			if (min(pref_x, pref_x+vx[ptr]) < 0 && max(pref_x, pref_x+vx[ptr]) > 0) ans++;
			if (min(pref_y, pref_y+vy[ptr]) < 0 && max(pref_y, pref_y+vy[ptr]) > 0) ans++;
		}
		else if (op == 'C')
		{
			int nx, ny;
			scanf("%d %d", &nx, &ny);

			if (min(pref_x, pref_x+vx[ptr]) < 0 && max(pref_x, pref_x+vx[ptr]) > 0) ans--;
			if (min(pref_y, pref_y+vy[ptr]) < 0 && max(pref_y, pref_y+vy[ptr]) > 0) ans--;

			delta_x += (nx - vx[ptr]), delta_y += (ny - vy[ptr]);
			vx[ptr] = nx, vy[ptr] = ny;

			if (min(pref_x, pref_x+vx[ptr]) < 0 && max(pref_x, pref_x+vx[ptr]) > 0) ans++;
			if (min(pref_y, pref_y+vy[ptr]) < 0 && max(pref_y, pref_y+vy[ptr]) > 0) ans++;
		}
		else if (op == 'Q')
		{
			int tot = ans + soma(-delta_x, 0, 0) + soma(-delta_y, 1, 0);
			tot -= (soma(-delta_x, 0, 1) + soma(-delta_y, 1, 1));

			printf("%d\n", tot);
		}
	}
}
