#include <iostream>
#include <vector>
#include <assert.h>
#include <list>

using namespace std;

int
main() {
	int K, N;
	scanf("%d %d", &K, &N);
	int sum = 0;
	auto sums = vector<int>();
	for(size_t i = 0; i < N; ++i) {
		int t;
		scanf("%d", &t);
		sum += t;
		sums.push_back(sum);
	}

	//for(auto s : sums) {
		//char err = ' ';
		//if(s < 0)
			//err = '-';
		//if(s > K)
			//err = '+';
		//fprintf(stderr, "S = %d %c\n", s, err);
	//}

	int goffset = 0,
	    missing = 0;
	for(size_t i = 0; i < N; ++i) {
		int v = sums[i] + goffset;
		fprintf(stderr, "S[%lu] = %d | %d\n", i, sums[i], v);
		if(v > K || v < 0) {
			// too big
			// lets try adding more
			int minimum = v;
			int maximum = v;
			size_t tg = i+1;
			for(size_t j = tg; j < N; ++j) {
				int v2 = sums[j] + goffset;
				int _min = min(minimum, v2);
				int _max = max(maximum, v2);
				if(_max - _min > K) {
					// BB too large
					break;
				} else {
					minimum = _min;
					maximum = _max;
				}
				tg = j;
			}
			int flytt = (v > K) ? (K-maximum) : (-minimum);
			goffset += flytt;
			++missing;
			fprintf(stderr, "E      %d (%lu->%lu) o=%d\n", v, i, tg, flytt);
		}
	}

	printf("%d\n", missing);
}
