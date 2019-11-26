#include <bits/stdc++.h>
using namespace std;

#define all(v)                      v.begin(), v.end()
#define Chrono                      chrono::steady_clock::now().time_since_epoch().count()
#define dist2D(x1, y1, x2, y2)            ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
#define dist3D(x1, y1, z1, x2, y2, z2)    ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2))
#define EPS                         1e-15
#define endl                        "\n"
#define FastIO                      ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define FI                          freopen("in.txt", "r", stdin)
#define FO                          freopen("out.txt", "w", stdout)
#define ff                          first
#define INF              1000000000000000000
#define ld                          long double
#define ll                          long long
#define mem(x,y)                    memset(x, y, sizeof x)
#define mp                          make_pair
#define msi                         map<string, int>
#define mii                         map<int, int>
#define mis                         map<int, string>
#define MOD                         1000000007
#define PI                          acos(-1.0)
#define PQ                          priority_queue
#define pb                          push_back
#define pib                         pair<int, bool>
#define pii                         pair<int, int>
#define pll                         pair<ll, ll>
#define present(c, x)               ((c).find(x) != (c).end())
#define sfi(x)                      scanf("%d", &x)
#define sfii(x,y)                   scanf("%d %d", &x, &y)
#define sfiii(x,y,z)                scanf("%d %d %d", &x, &y, &z)
#define siz(x)                      (int)x.size()
#define ss                          second
#define timeTaken                   endd = clock(); cout << (double) (endd - beginn) / CLOCKS_PER_SEC * 1000 << endl
#define timeInit                    clock_t beginn = clock(), endd
#define ull                         unsigned long long
#define umsi                        unordered_map<string, int>
#define umii                        unordered_map<int, int>
#define umis                        unordered_map<int, string>
#define vb                          vector<bool>
#define vi                          vector<int>
#define vvi                         vector<vi>
#define vii                         vector<pii>
#define vvii                        vector<vii>
#define vll                         vector<ll>
#define vvll                        vector<vll>
#define vpll                        vector<pll>
#define bug(...)                    cerr << __PRETTY_FUNCTION__ << " - " << __LINE__ << " : (" << #__VA_ARGS__ << ") = ("; _Print(__VA_ARGS__);
template<class T> void _Print(T &&x) { cerr << x << ")" << endl; }
template<class T, class ...S> void _Print(T &&x, S &&...y) { cerr << x << ", "; _Print(y...); }


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
using namespace __gnu_pbds;
typedef tree<int,null_type, less<int>, rb_tree_tag,
        tree_order_statistics_node_update> ordered_set;

//os.order_of_key(v): returns how many elements strictly less than v
//os.find_by_order(k - 1): returns kth smallest element's iterator


template<class T> class compare {
public:
    bool operator() (pair<T, T> &x, pair<T, T> &y) {
        if (x.first == y.first) {
            return x.ss > y.ss;
        }
        return x.ff > y.ff;
    }
};

template<class T> ostream &operator<<(ostream &os, const pair<T, T> &a) { return os << a.ff << " " << a.ss; }
ll power(ll a, int b) {
    ll po = 1;
    while (b) {
        if (b & 1)
            po *= a;
        a *= a;
        b >>= 1;
    }
    return po;
}

template<class T> pair<T, T> operator+(const pair<T, T> &a, const pair<T, T> &b) { return {a.ff + b.ff, a.ss + b.ss}; }
template<class T> pair<T, T> operator-(const pair<T, T> &a, const pair<T, T> &b) { return {a.ff - b.ff, a.ss - b.ss}; }
template<class T> pair<T, T> operator*(const pair<T, T> &a, const pair<T, T> &b) { return {a.ff * b.ff, a.ss * b.ss}; }
template<class T> pair<T, T> operator%(const pair<T, T> &a, const pair<T, T> &b) { return {a.ff % b.ff, a.ss % b.ss}; }
template<class T, class U> pair<T, T> operator+(const pair<T, T> &a, const U &b) { return {a.ff + b, a.ss + b}; }
template<class T, class U> pair<T, T> operator*(const pair<T, T> &a, const U &b) { return {a.ff * b, a.ss * b}; }

int Set(int N, int pos) { return N = N | (1 << pos); }
int reset(int N, int pos){ return N = N & ~ (1 << pos); }
bool check(int N, int pos){ return (bool) (N & (1 << pos)); }

///=======================================template=======================================///

///source : https://cp-algorithms.com/data_structures/segment_tree.html

vvll st, mat;
int n, m;
int left(int node) { return (node << 1); }
int right(int node) { return (node << 1) | 1; }
int mid(int l, int r) { return (l + r) >> 1; }

void buildy(int nodex, int lx, int rx, int nodey, int ly, int ry) {
    if (ly == ry) {
        if (lx == rx) {
            st[nodex][nodey] = mat[lx][ly];
        }
        else st[nodex][nodey] = st[left(nodex)][nodey] + st[right(nodex)][nodey];
    }
    else {
        int md = mid(ly, ry);
        buildy(nodex, lx, rx, left(nodey), ly, md);
        buildy(nodex, lx, rx, right(nodey), md + 1, ry);
        st[nodex][nodey] = st[nodex][left(nodey)] + st[nodex][right(nodey)];
    }
}

void buildx(int nodex, int lx, int rx) {
    if (lx != rx) {
        int md = mid(lx, rx);
        buildx(left(nodex), lx, md);
        buildx(right(nodex), md + 1, rx);
    }
    buildy(nodex, lx, rx, 1, 0, m - 1);
}

ll sumy(int nodex, int nodey, int ly, int ry, int l, int r) {
    if (l > ry or r < ly)
        return 0;
    if (ly >= l and ry <= r)
        return st[nodex][nodey];
    int md = mid(ly, ry);
    return sumy(nodex, left(nodey), ly, md, l, r) +
            sumy(nodex, right(nodey), md + 1, ry, l, r);
}

ll sumx(int nodex, int lx, int rx, int l, int r, int ly, int ry) {
    if (lx > r or rx < l)
        return 0;
    if (lx >= l and rx <= r)
        return sumy(nodex, 1, 0, m - 1, ly, ry);
    int md = mid(lx, rx);
    return sumx(left(nodex), lx, md, l, r, ly, ry) +
            sumx(right(nodex), md + 1, rx, l, r, ly, ry);
}

void updatey(int nodex, int lx, int rx, int nodey, int ly, int ry, int y, int val) {
    if (ly > y or ry < y)
        return;
    if (ly == ry) {
        if(lx == rx)
            st[nodex][nodey] = val;
        else st[nodex][nodey] = st[left(nodex)][nodey] + st[right(nodex)][nodey];
    }
    else {
        int md = mid(ly, ry);
        updatey(nodex, lx, rx, left(nodey), ly, md, y, val);
        updatey(nodex, lx, rx, right(nodey), md + 1, ry, y, val);
        st[nodex][nodey] = st[nodex][left(nodey)] + st[nodex][right(nodey)];
    }
}

void updatex(int nodex, int lx, int rx, int x, int y, int val) {
    if (lx > x or rx < x)
        return;
    if (lx != rx) {
        int md = mid(lx, rx);
        updatex(left(nodex), lx, md, x, y, val);
        updatex(right(nodex), md + 1, rx, x, y, val);
    }
    updatey(nodex, lx, rx, 1, 0, m - 1, y, val);
}

int main() {
    //FI;//FO;
    //FastIO; //timeInit;

    cin >> n >> m;
    mat.resize(n, vll(m));
    st.assign(4 * n, vll(4 * m , 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cin >> mat[i][j];
    }

    buildx(1, 0, n - 1);

    int query;
    cin >> query;

    while (query--) {
        int lx, ly, rx, ry;
        cin >> lx >> ly >> rx >> ry;
        cout << sumx(1, 0, n - 1, lx, rx, ly, ry) << endl;
        int x, y, val;
        cin >> x >> y >> val;
        updatex(1, 0, n - 1, x, y, val);
    }

    //timeTaken;
    return 0;
}
