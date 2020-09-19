// Codeforces 1101G - (Zero XOR Subset)-less
// Lúcio Cardoso

/* Solution:

The condition that no set of segments has xor = 0 is true iff the xor sums of any two (distinct) sets of segments are distinct.

Let p[i] be the xor-prefix of i and let the set of chosen segments be [l_1, r_1], [l_2, r_2], ..., [l_k, r_k]. The fact stated above implies that,
for any two (distinct) subsets A and B of {r_1, r_2, ..., r_k}, the xor of p[i] for every i in A is distinct from the xor of p[i] for every i in B.

Thus, if we consider the binary notation of p[i] as a vector in Z^31_2, the fact stated in the second paragraph implies that the set of prefixes
p[r_1], p[r_2], ..., p[r_k] is linearly independent. Thus, to maximize k, it is optimal to choose the set p[r_1], ..., p[r_k] as the basis of the set
of all prefixes.

We can find the basis of a vector space in O(n log maxv).

NOTE: Notice that the prefixes p[r_1], p[r_2], ... p[r_k] have to be non-zero. Thus, if the xor of all elements in the array is 0, the answer is -1.

*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

int n;
int a[maxn];
int p[maxn];

int tam_base;

int b[maxn];

void add(int v)
{
	for (int i = 0; i < 31; i++)
	{
		if (!(v&(1<<i))) continue;

		if (!b[i])
		{
			b[i] = v, ++tam_base;
			break;
		}

		v ^= b[i];
	}
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		p[i] = p[i-1] ^ a[i];
	}

	if (!p[n])
	{
		printf("-1\n");
		return 0;
	}

	for (int i = 1; i <= n; i++)
		add(p[i]);
		
	printf("%d\n", tam_base);	
}
