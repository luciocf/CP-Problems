// Codeforces 547A - Mike and Frog
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e6+10;

int pos[maxn];

int main(void)
{
	int m;
	scanf("%d", &m);

	int h1, a1, x1, y1;
	scanf("%d %d %d %d", &h1, &a1, &x1, &y1);

	int h2, a2, x2, y2;
	scanf("%d %d %d %d", &h2, &a2, &x2, &y2);

	vector<int> path1, path2;
	int ini1, ini2;

	memset(pos, -1, sizeof pos);
	int at = h1, qtd = 0;

	while (true)
	{
		if (pos[at] != -1)
		{
			ini1 = pos[at];
			break;
		}

		path1.push_back(at);
		pos[at] = qtd++;

		at = (1LL*at*x1 + 1LL*y1)%m; 
	}

	memset(pos, -1, sizeof pos);
	at = h2, qtd = 0;

	while (true)
	{
		if (pos[at] != -1)
		{
			ini2 = pos[at];
			break;
		}

		path2.push_back(at);
		pos[at] = qtd++;

		at = (1LL*at*x2 + 1LL*y2)%m; 
	}

	if (path1.size() > path2.size())
	{
		swap(path1, path2);
		swap(a1, a2);
		swap(ini1, ini2);
	}

	int at1 = 0, at2 = 0;
	ll ans = 0;

	while (at2 < ini2)
	{
		if (at1 == path1.size()-1) at1 = ini1;
		else ++at1;

		++at2;

		++ans;

		if (path1[at1] == a1 && path2[at2] == a2)
		{
			printf("%lld\n", ans);
			return 0;
		}
	}

	int pos1 = -1, pos2 = -1;

	for (int i = ini1; i < path1.size(); i++)
		if (path1[i] == a1)
			pos1 = i;

	for (int i = ini2; i < path2.size(); i++)
		if (path2[i] == a2)
			pos2 = i;

	if (pos1 == -1 || pos2 == -1)
	{
		printf("-1\n");
		return 0;
	}

	while (at2 != pos2)
	{
		if (at1 == path1.size()-1) at1 = ini1;
		else ++at1;

		if (at2 == path2.size()-1) at2 = ini2;
		else ++at2;

		++ans;
	}

	int c1 = path1.size()-ini1;
	int c2 = path2.size()-ini2;

	int delta = (pos1 >= at1 ? pos1-at1 : c1-(at1-pos1));

	int k = -1;

	for (int i = 0; i < c1; i++)
	{
		if ((1ll*c2*i-1ll*delta)%c1 == 0)
		{
			k = i;
			break;
		}
	}
	if (k == -1)
	{
		printf("-1\n");
		return 0;
	}

	printf("%lld\n", ans+1ll*c2*k);
}
