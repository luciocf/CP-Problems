// POI 2016 - Diligent Johny
// Lúcio Cardoso

// Solution:

// 1. Denote the cost for transforming a permuation P into a permutation Q by P->Q.
// Notice that, for a given permutation P, P->Q = ({N, N-1, ..., 1}->{1, 2, ..., N}) - ({N, N-1, ..., 1}->P).

// 2. Define A(i, j) as the smallest permutation with i digits and with j as leftmost digit and B(i, j) as the 
// greatest permutation with i digits and j as leftmost digit. Also define T(i, j) as A(i, j)->B(i, j-1), for i >= 3.

// 3. Lemma 1: T(i, i) = 2 + ((i-3)/2). For example, let's calculate T(6, 6):
// T(6, 6) = A(6, 6)->B(6, 5) = {6, 1, 2, 3, 4, 5}->{5, 6, 4, 3, 2, 1} = 2 + {5, 6, 2, 3, 4, 1}->{5, 6, 4, 3, 2, 1} = 
// = 2 + {2, 3, 4}->{4, 3, 2} = 2 + floor(3/2) = 3.

// 4. Lemma 2: T(i, i) = T(i, j) for all j with 1 <= j <= i. Now, we will denote T(i, j) as simply T(i).

// 5. Let dp(i) = {i, i-1, ..., 1}->{1, 2, 3, ..., i}. Notice that dp(2) = 1 and that dp(i) = i*dp(i-1) + (i-1)*T(i).
// This is true because we can simplify dp(i) as B(i, i)->A(i, i) + T(i) + B(i, i-1)->A(i, i) + T(i) + ... + B(i, 2)->A(i, 1).

// 6. Now, we know the answer to our problem with a permutation P is equal to dp(N) - B(N, N)->P.
// Denote P = {a_1, a_2, ..., a_N}. Let C(a_i) be the position of a_i in the ordered set containing the elements
// {a_i, a_{i+1}, ..., a_N} (i.e, C(a_i) is the "relative order" of a_i in the set).

// 7. We can observe that B(N, N)->P = B(N, N)->B(N, a_1) + B(N, a_1)->P. However, we can further break down B(N, a_1)->P as
// B(N-1, N-1)->B(N-1, C(a_2)) + B(N-1, C(a_2))->P, since all the permutation from B(N, a_1) until P have a_1 as the leftmost element.
// Therefore, we'll have that: B(N, N)->P = B(N, N)->B(N, C(a_1)) + B(N-1, N-1)->B(N-1, C(a_2)) + ... + B(2, 2)->B(2, C(a_{N-1})).
// Now, notice that B(i, i)->B(i, C(a_{N-i+1})) is equal to (i - C(a_{N-i+1})*dp(i-1) + (i - C(a_{N-i+1}))*T(i).

// 8. Finally, all that's left is to calculate C(a_i). We can do that with a BIT on the numbers {1, 2, ..., N}, first setting the
// values in each position as 1. Aftet that, to calculate C(a_i), we can set all positions a_1, a_2, ..., a_{i-1} as zero and then
// use a range query from 1 until a_i.

// Overall complexity is O(n log n).

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6+10;
const int mod = 1e9+7;

int bit[maxn];

int dp[maxn];

void upd(int x, int v)
{
	for (; x < maxn; x += (x&-x))
		bit[x] += v;
}

int soma(int x)
{
	int ans = 0;
	for (; x > 0; x -= (x&-x))
		ans += bit[x];
	return ans;
}

int T(int i)
{
	return (i == 2 ? 1 : (2 + (i-3)/2));
}

int main(void)
{
	int n;
	scanf("%d", &n);

	vector<int> perm;

	for (int i = 1; i <= n; i++)
	{
		int v;
		scanf("%d", &v);

		perm.push_back(v);
	}

	reverse(perm.begin(), perm.end());

	dp[2] = 1;
	for (int i = 3; i <= n; i++)
		dp[i] = (1ll*i*dp[i-1] + 1ll*T(i)*(i-1))%mod;

	for (int i = 1; i <= n; i++)
		upd(i, 1);

	int ans = 0;
	for (int i = n; i > 1; i--)
	{
		int x = soma(perm[i-1]);

		ans = (1ll*ans + 1ll*dp[i-1]*(i-x) + 1ll*(i-x)*T(i))%mod;

		upd(perm[i-1], -1);
	}

	printf("%d\n", (dp[n]-ans+mod)%mod);
}
