#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <string>
#include <set>
#include <complex>
using namespace std;

#define all(v)                      v.begin(), v.end()
#define dist2D(x1, y1, x2, y2)            ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
#define dist3D(x1, y1, z1, x2, y2, z2)    ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2))
#define EPS                         1e-16
#define endl                        "\n"
#define FastIO                      ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define FI                          freopen("in.txt", "r", stdin)
#define FO                          freopen("out.txt", "w", stdout)
#define fap(x)                      cout << "WTH: " << x << endl
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

/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
using namespace __gnu_pbds;
typedef tree<int,null_type, less<int>, rb_tree_tag,
        tree_order_statistics_node_update> ordered_set;

//os.order_of_key(v): returns how many elements strictly less than v
//os.find_by_order(k - 1): returns kth smallest element's iterator
*/

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

ll Set(ll N, int pos) { return N = N | (1LL << pos); }
int reset(int N, int pos){ return N = N & ~ (1 << pos); }
bool check(ll N, int pos){ return (bool) (N & (1LL << pos)); }

///=======================================template=======================================///

bool isPresent(vi &ara, int val) {
    int k = 0, n = siz(ara);
    for (int i = n / 2; i >= 1; i >>= 1) {
        while (i + k < n and ara[i + k] <= val)
            k += i;
    }
    return (ara[k] == val);
}

int leftmost(vi &ara, int val) {
    int k = -1, n = siz(ara);
    for (int i = n >> 1; i >= 1; i >>= 1) {
        while (k + i < n - 1 and ara[k + i] < val)
            k += i;
    }
    return (ara[k + 1] == val ? k + 1 : -1);
}

int rightmost(vi &ara, int val) {
    int k = 0, n = siz(ara);
    for (int i = n >> 1; i >= 1; i >>= 1) {
        while (k + i < n and ara[k + i] <= val)
            k += i;
    }
    return (ara[k] == val ? k : -1);
}

/// max element in an increasing and then decreasing array

int maxVal(vi &ara) {
    int k = -1, n = siz(ara);
    for (int i = n >> 1; i >= 1; i >>= 1) {
        while (k + i < n - 1 and ara[k + i] < ara[k + i + 1])
            k += i;
    }
    return ++k;
}

/// smallest element in a shifted sorted array

int smallest(vi &ara) {
    int k = -1, n = siz(ara);
    for (int i = n >> 1; i >= 1; i >>= 1) {
        while (k + i < n and ara[k + i] > ara[n - 1])
            k += i;
    }
    return ++k;
}

int main() {

    int ara[] = {1, 3, 6, 7, 3, 2, 1};
    cout << "maxVal: ";
    vi arr(ara, ara + 7);
    cout << arr[maxVal(arr)] << endl;
    int ara1[] = {1, 2, 1};
    vi arr1(ara1, ara1 + 3);
    cout << arr1[maxVal(arr1)] << endl;
    int ara2[] = {1, 2, 3, 4};
    arr1.assign(ara2, ara2 + 4);
    cout << arr1[maxVal(arr1)] << endl;
    int ara3[] = {5, 4, 3, 2, -1};
    arr1.assign(ara3, ara3 + 5);
    cout << arr1[maxVal(arr1)] << endl;

    cout << "smallest: ";
    int ara4[] = {5, 6, 8, 9, 9, 1, 1, 2, 2};
    arr1.assign(ara4, ara4 + 9);
    cout << arr1[smallest(arr1)] << endl;
    int ara5[] = {5, 6, 8, 9, 9};
    arr1.assign(ara5, ara5 + 5);
    cout << arr1[smallest(arr1)] << endl;

    cout << "rightmost: ";
    int ara6[]={9, 9, 9, 9, 9, 9, 19, 20, 20, 20};
    arr1.assign(ara6, ara6 + 10);
    cout << rightmost(arr1, 20) << endl;
    cout << rightmost(arr1, 9) << endl;
    cout << rightmost(arr1, 19) << endl;
    cout << rightmost(arr1, -1) << endl;
    cout << rightmost(arr1, 21) << endl;

    cout << "leftmost: ";
    cout << leftmost(arr1, 20) << endl;
    cout << leftmost(arr1, 9) << endl;
    cout << leftmost(arr1, 19) << endl;
    cout << leftmost(arr1, -1) << endl;
    cout << leftmost(arr1, 21) << endl;

    cout << "isPresent: ";
    cout << boolalpha;
    cout << isPresent(arr1, 20) << endl;
    cout << isPresent(arr1, 9) << endl;
    cout << isPresent(arr1, 19) << endl;
    cout << isPresent(arr1, -1) << endl;
    cout << isPresent(arr1, 21) << endl;

    return 0;
}
