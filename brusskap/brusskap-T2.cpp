#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

int
main() {
	int K, N;
	//assert(K==1);
	scanf("%d %d", &K, &N);
	int sum = 0, missing = 0;
	vector<int> txns;
	vector<bool> fake;
	for(size_t i = 0; i < N; ++i) {
		int t;
		scanf("%d", &t);
		sum += t;
		if(sum < 0) {
			sum = 0;
			++missing;
		} else if (sum > K) {
			sum = K;
			++missing;
		}
	}
	printf("%d\n", missing);
}
