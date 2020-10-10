// Codeforces 1132E - Knapsack
// Lúcio Cardoso

/* Solution:

Not 100% sure if this solution is actually right.

Let aux[1] = min(cnt[1], w). Notice the possible amounts of 1s that are optimal to use are
(aux[1], aux[1]-1, ..., aux[1]-8). After fixing the amount of used 1s and subtracting it from w, 
use the same logic for 2, 3, ..., 8, bruteforcing the amounts used for such numbers.

Complexity: O(8^8)

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll qtd[9];
ll aux[9];
ll fora[9];

int main(void)
{
	ll w;
	cin >> w;

	for (int i = 1; i <= 8; i++)
		cin >> qtd[i];

	ll ans = 0;

	aux[1] = min(qtd[1], w);

	for (fora[1] = 0; fora[1] <= min(aux[1], 8ll); fora[1]++)
	{
		ll s = w-(aux[1]-fora[1]);

		aux[2] = min(qtd[2], s/2ll);

		for (fora[2] = 0; fora[2] <= min(aux[2], 8ll); fora[2]++)
		{
			s -= 2ll*(aux[2]-fora[2]);

			aux[3] = min(qtd[3], s/3ll);

			for (fora[3] = 0; fora[3] <= min(aux[3], 8ll); fora[3]++)
			{
				s -= 3ll*(aux[3]-fora[3]);

				aux[4] = min(qtd[4], s/4ll);

				for (fora[4] = 0; fora[4] <= min(aux[4], 8ll); fora[4]++)
				{
					s -= 4ll*(aux[4]-fora[4]);

					aux[5] = min(qtd[5], s/5ll);

					for (fora[5] = 0; fora[5] <= min(aux[5], 8ll); fora[5]++)
					{
						s -= 5ll*(aux[5]-fora[5]);

						aux[6] = min(qtd[6], s/6ll);

						for (fora[6] = 0; fora[6] <= min(aux[6], 8ll); fora[6]++)
						{
							s -= 6ll*(aux[6]-fora[6]);

							aux[7] = min(qtd[7], s/7ll);

							for (fora[7] = 0; fora[7] <= min(aux[7], 8ll); fora[7]++)
							{
								s -= 7ll*(aux[7]-fora[7]);

								aux[8] = min(qtd[8], s/8ll);

								for (fora[8] = 0; fora[8] <= min(aux[8], 8ll); fora[8]++)
								{
									s -= 8ll*(aux[8]-fora[8]);

									ans = max(ans, -s+w);

									s += 8ll*(aux[8]-fora[8]);
								}

								s += 7ll*(aux[7]-fora[7]);
							}

							s += 6ll*(aux[6]-fora[6]);
						}

						s += 5ll*(aux[5]-fora[5]);
					}

					s += 4ll*(aux[4]-fora[4]);
				}

				s += 3ll*(aux[3]-fora[3]);
			}

			s += 2ll*(aux[2]-fora[2]);
		}
	}

	printf("%lld\n", ans);
}
