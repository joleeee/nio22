#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long ll;

int
main() {
	int N, K;
	scanf("%d %d", &N, &K);
	assert(K == 1);

	auto A = vector<pair<ll,ll>>();
	ll totvol = 0;
	ll ventetid = 0;
	for(size_t i = 0; i < N; ++i) {
		ll t, v;
		scanf("%lld %lld", &t, &v);
		totvol += v;

		A.push_back({t,v});
	}
	sort(A.begin(), A.end());

	ll lazy_thing = 0;
	typedef pair<ll,ll> pll;
	auto PQ = priority_queue<pll, vector<pll>, greater<pll>>();
	ll last_t = 0;
	for(auto a : A) {
		ll t = a.first, v = a.second;
		lazy_thing -= t;
		ll current_time = last_t;

		while(current_time < t && PQ.size()) {
			auto p = PQ.top();
			auto rem_volume = p.first, rem_time = p.second;
			PQ.pop();

			ll dt = t-current_time;
			if(rem_volume > dt) {
				PQ.push({rem_volume-dt, rem_time});
				fprintf(stderr, "%lldcl -> %lldcl\n", rem_volume, rem_volume-dt);
				break;
			} else {
				current_time += rem_volume;
				lazy_thing += current_time;

				fprintf(stderr, "ferdig %lld\n", current_time);
			}
		}

		//
		PQ.push({v,t});

		last_t = t;
	}
	while(PQ.size()) {
		auto p = PQ.top();
		auto ev = p.first, et = p.second;
		PQ.pop();

		last_t += ev;
		lazy_thing += last_t;
	}
	printf("%lld\n", lazy_thing-totvol);
}
