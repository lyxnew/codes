//by lyx
//orz vfk
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define mp make_pair
#define fly(...) fprintf(stderr, __VA_ARGS__)

using namespace std;
typedef long long LL;
typedef pair<LL, int> pli;

const int maxn = 100000 + 5;
const int maxm = 400000 + 5;
const int logn = 20;

void read(int& x)
{
	int t = getchar(); x = 0;
	while(t < '0' || t > '9') t = getchar();
	while(t >= '0' && t <= '9') {
		x = (x << 3) + (x << 1) + t - '0';
		t = getchar();
	}
}

void print(LL x)
{
	if(x == 0) {
		putchar('0');
		return ;
	}
	int a[20] = {0}, t = 0;
	while(x) {
		a[t++] = x % 10;
		x /= 10;
	}
	while(t--) putchar(a[t] + '0');
}

int n, m, Q, _m;
bool isc[maxn];
int first[maxn];
int next[maxm];
struct Edge
{
	int u, v;
	LL w;
	Edge(int u = 0, int v = 0, LL w = 0): u(u), v(v), w(w) {}
	bool operator < (const Edge& r) const {
		return w < r.w;
	}
}edge[maxm], _edge[maxm];

void addedge(int a, int b, int c)
{
	edge[++m] = Edge(a, b, c);
	next[m] = first[a]; first[a] = m;
}

int f[maxn], rank[maxn];
void init_DSU()
{
	for(int i = 1; i <= n; ++i) {
		f[i] = i;
		rank[i] = 0;
	}
}
int getf(int t) { return f[t] == t ? t : f[t] = getf(f[t]); }
int merge(int a, int b)
{
	int fa = getf(a), fb = getf(b);
	if(fa == fb) return 0;
	if(rank[fa] > rank[fb])
		f[fb] = f[fa];
	else if(rank[fa] < rank[fb])
		f[fa] = fb;
	else {
		f[fa] = fb;
		++rank[fb];
	}
	return 1;
}

int near[maxn];
LL dis[maxn];
priority_queue<pli, vector<pli>, greater<pli> > q;
bool book[maxn];

void dijkstra()
{
	memset(dis, 0x3f, sizeof(dis));
	memset(near, 0, sizeof(near));
	for(int i = 1; i <= n; ++i)
		if(isc[i]) {
			dis[i] = 0;
			q.push(mp(0, i));
			near[i] = i;
		}
	for(int aha = 1; aha <= n; ++aha) {
		pli t;
		do {
			t = q.top(); q.pop();
		}while(book[t.second]);
		LL dist = t.first;
		int now = t.second;
		book[now] = 1;
		for(int i = first[now]; i != -1; i = next[i]) {
			if(dis[edge[i].v] > edge[i].w + dist) {
				dis[edge[i].v] = edge[i].w + dist;
				near[edge[i].v] = near[now];
				q.push(mp(dis[edge[i].v], edge[i].v));
			}
			if(near[now] && near[edge[i].v])
				_edge[++_m] = Edge(near[now], near[edge[i].v], dis[edge[i].v] + dis[now] + edge[i].w);
		}
	}
}

int fn[maxn][logn], deep[maxn];
LL fw[maxn][logn];

void dfs(int now)
{
	for(int i = first[now]; i != -1; i = next[i]) {
		if(deep[edge[i].v])
			continue;
		fn[edge[i].v][0] = now;
		fw[edge[i].v][0] = edge[i].w;
		deep[edge[i].v] = deep[now] + 1;
		dfs(edge[i].v);
	}
}

void establish()
{
	memset(first, -1, sizeof(first)); m = 0;
	sort(_edge+1, _edge+_m+1);
	init_DSU();
	for(int i = 1; i <= _m; ++i)
		if(merge(_edge[i].u, _edge[i].v)) {
			addedge(_edge[i].u, _edge[i].v, _edge[i].w);
			addedge(_edge[i].v, _edge[i].u, _edge[i].w);
		}
	for(int i = 1; i <= n; ++i)
		if(isc[i]) {
			deep[i] = 1;
			dfs(i);
			break;
		}
	for(int j = 1; j < logn; ++j)
		for(int i = 1; i <= n; ++i) {
			fn[i][j] = fn[fn[i][j-1]][j-1];
			fw[i][j] = max(fw[i][j-1], fw[fn[i][j-1]][j-1]);
		}
}

LL LCA(int a, int b)
{
	LL maxv = 0;
	if(deep[a] < deep[b])
		swap(a, b);
	for(int i = logn-1; i >= 0; --i)
		if(deep[fn[a][i]] >= deep[b]) {
			maxv = max(maxv, fw[a][i]);
			a = fn[a][i];
		}
	for(int i = logn-1; i >= 0; --i)
		if(fn[a][i] != fn[b][i]) {
			maxv = max(maxv, fw[a][i]);
			maxv = max(maxv, fw[b][i]);
			a = fn[a][i];
			b = fn[b][i];
		}
	if(a ^ b) {
		maxv = max(maxv, fw[a][0]);
		maxv = max(maxv, fw[b][0]);
	}
	return maxv;
}

void init()
{
	int m2, a, b, c;
	memset(first, -1, sizeof(first));
	
	read(n); read(m2); //getchar();
	for(int i = 1; i <= n; ++i)
		isc[i] = (getchar() == '1');
	for(int i = 1; i <= m2; ++i) {
		read(a); read(b); read(c);
		addedge(a, b, c);
		addedge(b, a, c);
	}
}

void work()
{
	int a, b;
	read(Q);
	for(int aha = 1; aha <= Q; ++aha) {
		read(a);
		read(b);
		printf("%lld\n", LCA(a, b));
	}
	
}

int main()
{
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
	
	init();
	dijkstra();
	establish();
	work();
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
