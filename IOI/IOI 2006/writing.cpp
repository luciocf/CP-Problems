// IOI 2006 - Deciphering the Mayan Writing
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3010;

int freq[60], aux[60];

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++)
	{
		char c;
		scanf(" %c", &c);

		if (c >= 'a' && c <= 'z') freq[c-'a']++;
		else freq[c-'A'+26]++;
	}

	if (m < n)
	{
		char c;
		for (int i = 0; i < m; i++)
			scanf(" %c", &c);
		printf("0\n");
		return 0;
	}

	deque<char> S;

	for (int i = 0; i < n; i++)
	{
		char c;
		scanf(" %c", &c);

		S.push_front(c);

		if (c >= 'a' && c <= 'z') aux[c-'a']++;
		else aux[c-'A'+26]++;
	}

	int ans = 0, qtd_igual = 0;
	for (int i = 0; i < 52; i++)
		if (freq[i] == aux[i]) qtd_igual++;

	if (qtd_igual == 52) ans++;

	for (int i = n; i < m; i++)
	{
		char c = S.back();

		if (c >= 'a' && c <= 'z')
		{
			aux[c-'a']--;
			if (aux[c-'a'] == freq[c-'a']) qtd_igual++;
			else if (aux[c-'a']+1 == freq[c-'a']) qtd_igual--;
		}
		else
		{
			aux[c-'A'+26]--;
			if (aux[c-'A'+26] == freq[c-'A'+26]) qtd_igual++;
			else if (aux[c-'A'+26]+1 == freq[c-'A'+26]) qtd_igual--;
		}

		char d;
		scanf(" %c", &d);
		if (d >= 'a' && d <= 'z')
		{
			aux[d-'a']++;
			if (aux[d-'a'] == freq[d-'a']) qtd_igual++;
			else if (aux[d-'a']-1 == freq[d-'a']) qtd_igual--;
		}
		else
		{
			aux[d-'A'+26]++;
			if (aux[d-'A'+26] == freq[d-'A'+26]) qtd_igual++;
			else if (aux[d-'A'+26]-1 == freq[d-'A'+26]) qtd_igual--;
		}

		S.pop_back(); S.push_front(d);

		if (qtd_igual == 52) ans++;
	}

	printf("%d\n", ans);
}
