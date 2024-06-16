// ARC 179C - Beware of Overflow
// Lucio Figueiredo

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <cstring>
#include <set>
#include <map>

#define ff first
#define ss second
#define mkp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 1e3+10;

vector<int> mergeSort(int l, int r)
{
	vector<int> a;

	if (r-l+1 == 1)
	{
		a.push_back(l);
		return a;
	}

	int mid = (l+r)/2;

	vector<int> m1, m2;
	m1 = mergeSort(l, mid); m2 = mergeSort(mid+1, r);

	int ptr_l = 0, ptr_r = 0;
	while (ptr_l < m1.size() or ptr_r < m2.size())
	{
		if (ptr_l == m1.size()) a.push_back(m2[ptr_r++]);
		else if (ptr_r == m2.size()) a.push_back(m1[ptr_l++]);
		else
		{
			printf("? %d %d\n", m1[ptr_l], m2[ptr_r]);
			fflush(stdout);
			int x;
			scanf("%d", &x);

			if (x == 1) a.push_back(m1[ptr_l++]);
			else a.push_back(m2[ptr_r++]);
		}
	}

	return a;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	vector<int> a = mergeSort(1, n);

	while (a.size() > 1)
	{
		printf("+ %d %d\n", a[0], a.back());
		fflush(stdout);
		int p;
		scanf("%d", &p);

		if (a.size() == 2)
		{
			printf("!\n");
			fflush(stdout);
			return 0;
		}

		vector<int> aux = a;
		a.clear();

		int ini = 1, fim = (int)aux.size()-2, pos = (int)aux.size()-1;
		while (ini <= fim)
		{
			int mid = (ini+fim)>>1;

			printf("? %d %d\n", p, aux[mid]);
			fflush(stdout);
			int x;
			scanf("%d", &x);

			if (x == 1) fim = mid-1, pos = mid;
			else ini = mid+1;
		}

		for (int i = 1; i < pos; i++)
			a.push_back(aux[i]);
		a.push_back(p);
		for (int i = pos; i < (int)aux.size()-1; i++)
			a.push_back(aux[i]);
	}
}
