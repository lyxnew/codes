#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

#define fly(...) fprintf(stderr, __VA_ARGS__)

using namespace std;
typedef long long LL;

const int maxn = 1000005;
const int MOD = 1e9 + 9;

void readint(int& x)
{
	int t = getchar(); x = 0;
	while(t < '0' || t > '9') t = getchar();
	while(t >= '0' && t <= '9') {
		x = (x << 1) + (x << 3) + t - '0';
		t = getchar();
	}
}

void print(LL x)
{
	if(x == 0) {
		putchar('0');
		return ;
	}
	int s[30], t = 0;
	while(x) {
		s[t++] = x % 10;
		x /= 10;
	}
	while(t--)
		putchar(s[t] + '0');
}

int n, tot;
struct pp
{
	int p, t;
	bool operator < (const pp& r) const {
		return p < r.p || (p == r.p && t < r.t);
	}
}prime[maxn] = {0};

void kill(int x)
{
	int m = floor(sqrt(x) + 0.5);
	if((x & 1) == 0) {
		prime[++tot].p = 2;
		while((x & 1) == 0) {
			++prime[tot].t;
			x >>= 1;
		}
	}
	for(int i = 3; i <= m; i += 2) {
		if(x % i == 0) {
			prime[++tot].p = i;
			while(x % i == 0) {
				++prime[tot].t;
				x /= i;
			}
		}
	}
	if(x ^ 1) {
		prime[++tot].p = x;
		++prime[tot].t;
	}
}

LL power_mod(LL t, LL k)
{
	LL x = 1;
	while(k) {
		if(k & 1)
			x = x * t % MOD;
		t = t * t % MOD;
		k >>= 1;
	}
	return x;
}

LL s[1000];
LL ans;

void calc(int l, int r)
{
	LL p = prime[l].p;
	LL res = 1;
	s[0] = 1;
	for(int i = 1; i <= prime[r].t; ++i)
		s[i] = s[i-1] * p % MOD;
	for(int i = 1; i <= prime[r].t; ++i)
		s[i] = (s[i] + s[i-1]) % MOD;
	for(int i = l; i <= r; ++i)
		res = res * s[prime[i].t] % MOD;
	res = (res - 1 + MOD) % MOD;
	res = res * (p-1) % MOD;
	res = res * power_mod(p, MOD-2) % MOD;
	res = (res + 1) % MOD;
	ans = ans * res % MOD;
}

void init()
{
	int a;
	readint(n);
	for(int i = 1; i <= n; ++i) {
		readint(a);
		kill(a);
	}
}

void work()
{
	int last = 1; ans = 1;
	sort(prime+1, prime+tot+1);
	for(int i = 1; i <= tot; ++i)
		if(i == tot || prime[i].p != prime[i+1].p) {
			calc(last, i);
			last = i+1;
		}
	print(ans);
}

int main()
{
	freopen("best.in", "r", stdin);
	freopen("best.out", "w", stdout);
	
	init();
	work();
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
