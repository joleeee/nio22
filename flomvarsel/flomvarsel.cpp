#include <iostream>
#include <vector>
#include <assert.h>
#include <queue>
#include <climits>

using namespace std;

#define MAXN 1000

int H, W;
int HM[MAXN][MAXN];
int lwst[MAXN][MAXN];

int
main() {
	scanf("%d %d", &H, &W);
	for(size_t y = 0; y < H; ++y) {
		for(size_t x = 0; x < W; ++x) {
			int h;
			scanf("%d", &h);
			HM[y][x] = h;
			lwst[y][x] = INT_MAX;
		}
	}

	typedef pair<int,pair<int,int>> pq;
	auto PQ = priority_queue<pq, vector<pq>, greater<pq>>();
	for(size_t y = 0; y < H; ++y) {
		for(size_t x = 0; x < W; ++x) {
			int s;
			scanf("%d", &s);
			if(s == 1) {
				PQ.push({HM[y][x],{y,x}});
			}
		}
	}

	while(PQ.size()) {
		auto q = PQ.top();
		PQ.pop();
		auto h = q.first;
		auto co = q.second;
		auto y = co.first, x = co.second;
		if(h >= lwst[y][x])
			continue;

		if(h < lwst[y][x]) {
			lwst[y][x] = h;
			if(y > 0) {
				int h2 = max(HM[y-1][x], h);
				if(h2 >= h) // TODO add lwst check
					PQ.push({h2, {y-1, x}});
			}
			if(y < H-1) {
				int h2 = max(HM[y+1][x], h);
				if(h2 >= h) // TODO add lwst check
					PQ.push({h2, {y+1, x}});
			}
			if(x > 0) {
				int h2 = max(HM[y][x-1], h);
				if(h2 >= h) // TODO add lwst check
					PQ.push({h2, {y, x-1}});
			}
			if(x < W-1) {
				int h2 = max(HM[y][x+1], h);
				if(h2 >= h) { // TODO add lwst check
					PQ.push({h2, {y, x+1}});
				}
			}
		}
	}

	int cnt = 0;
	for(size_t y = 0; y < H; ++y) {
		for(size_t x = 0; x < W; ++x) {
			auto v = lwst[y][x];
			auto h = HM[y][x];
			cnt += v > h;
		}
	}
	printf("%d\n", cnt);
}
