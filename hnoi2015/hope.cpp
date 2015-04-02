#include <cstdio>
#include <cstring>
#include <algorithm>

#define fly(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

const int maxn = 300005;
const int INF = 0x3f3f3f3f;

void readint(int& x)
{
	int t = getchar(); x = 0;
	while(t < '0' || t > '9') t = getchar();
	while(t >= '0' && t <= '9') {
		x = (x << 1) + (x << 3) + t - '0';
		t = getchar();
	}
}

int n, L, type;
int a[maxn], b[maxn], c[maxn];

void init()
{
	readint(type);
	readint(n); readint(L);
	for(int i = 1; i <= n; ++i) {
		readint(a[i]);
		readint(b[i]);
		readint(c[i]);
	}
}

int f[maxn];

void work()
{
	memset(f, INF, sizeof(f));
	a[0] = 0;
	b[0] = 2147483647;
	c[0] = 0;
	f[0] = 0;
	for(int i = 1; i <= n; ++i)
		if(c[i] <= L)
			f[i] = 1;
		else for(int j = i-1; j >= 0 && c[i] - c[j] <= L; --j)
			if(a[i] <= b[j] && b[i] >= a[j])
				f[i] = min(f[i], f[j] + 1);
	for(int i = 1; i <= n; ++i)
		if(f[i] < INF)
			printf("%d\n", f[i]);
		else
			puts("Pool Logig!");
}

int main()
{
	freopen("hope.in", "r", stdin);
	freopen("hope.out", "w", stdout);
	
	init();
	work();
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
