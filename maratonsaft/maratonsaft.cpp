#include <iostream>
#include <limits.h>
#include <vector>

using namespace std;

#define MAXN 1048576

int V[MAXN*2],
    H[MAXN*2];

int
leftarm(int idx) {
	while(idx < MAXN) {
		idx *= 2;
	}
	return idx;
}

int
rightarm(int idx) {
	while(idx < MAXN) {
		idx = idx*2+1;
	}
	return idx;
}

void
insert(int val, int* where, int idx) {
	int offset = MAXN;
	int i = offset+idx;
	//fprintf(stderr, "%d korsp. til %d\n", idx, i);
	where[i] = val;
	//fprintf(stderr, "%d = %d\n", i, val);

	// propagate
	do {
		int parent = i/2;
		int lc = parent*2, rc = parent*2+1;
		where[parent] = where[lc] + where[rc];
		//fprintf(stderr, "%d <- %d (*%d + *%d)\n", parent, where[parent], lc, rc);
		i = parent;
	} while(i > 1);
}

int
_sum(int idx, int from, int to, int* where) {
	//printf("_sum( idx=%d, from=%d, to=%d )\n", idx, from, to);
	int child_l = idx*2;
	int child_r = child_l + 1;

	int left_bound = leftarm(idx);
	int right_bound = rightarm(idx);

	if(left_bound == from && right_bound == to)
		return where[idx];

	int child_l_right_bound = rightarm(child_l);
	int child_r_left_bound = leftarm(child_r);

	bool need_left = from <= child_l_right_bound;
	bool need_right = to >= child_r_left_bound;
	if(need_left && need_right) {
		return    _sum(child_l, from, min(to,child_l_right_bound), where)
			+ _sum(child_r, max(from,child_r_left_bound), to, where);
	} else {
		if(need_left) {
			return _sum(child_l, from, min(to,child_l_right_bound), where);
		} else if(need_right) {
			return _sum(child_r, max(from,child_r_left_bound), to, where);
		} else {
			//printf("OOPS");
			return 0;
			exit(1);
		}
	}
}

int
sum(int _from, int _to, int* where) {
	int offset = MAXN;
	int from = offset+_from;
	int to = offset+_to;
	//printf("sum fra %d til %d.\n", from, to);
	return _sum(1, from, to, where);
}


int
main() {
	int N, M, K;
	scanf("%d %d %d", &N, &M, &K);

	//int Vc = 0, Hc = 0;
	//printf("rightarm of %d is %d\n", 1, rightarm(1));
	//printf("rightarm of %d is %d\n", 2, rightarm(2));
	//printf("rightarm of %d is %d\n", 3, rightarm(3));
	//printf("rightarm of %d is %d\n", 12, rightarm(12));

	for(size_t i = 0; i < M; ++i) {
		int x;
		char s;
		scanf("%d %c", &x, &s);

		int antall = 0;

		int over = (x+K-1)/K;
		int under = (x)/K;
		int underp = under*K;
		int overp = over*K;
		int siste = N/K;

		if(s == 'V') {
			// denne er p[ venstre side

			if(over > siste) {
				puts("0");
				//printf("HUFF %d %c\n", x, s);
				continue;
			}

			int v = V[1];
			int h = sum(overp, N, H);
			//printf("v=%d h=%d\n", v, h);

			antall += v + h;

			//V[x] = 1;
			insert(1, V, x);
		} else {
			//H[x] = 1;

			int h = H[1];
			int r = sum(0, underp, V);

			antall += h + r;
			insert(1, H, x);
		}

		//printf("%d -> neste overgang %d\n", x, overp);
		//printf("%d -> neste undergang %d\n", x, underp);

		printf("%d\n", antall);

		// hvor mange nye

		// lagre data til senere
	}
}
