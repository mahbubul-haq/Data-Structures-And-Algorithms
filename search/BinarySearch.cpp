#include <bits/stdc++.h>
using namespace std;

#define dist2D(x1,y1,x2,y2)         ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))
#define dist3D(x1,y1,z1,x2,y2,z2)   ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2))
#define EPS                         1e-12
#define FastIO                      ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define FI                          freopen("in.txt","r",stdin)
#define FO                          freopen("out.txt","w",stdout)
#define fap(x)                      cout<<"WTH: "<<x<<endl
#define ff                          first
#define fof(i,x,y)                  for(int i=x;i<(int)y;i++)
#define fob(i,x,y)                  for(int i=x;i>=(int)y;i--)
#define INF                         1000000000
#define ld                          long double
#define ll                          long long
#define mem(x,y)                    memset(x,y,sizeof x)
#define mp                          make_pair
#define msi                         map<string,int>
#define mii                         map<int,int>
#define mis                         map<int,string>
#define MOD                         2147483647
#define PI                          acos(-1.0)
#define PQ                          priority_queue
#define pb                          push_back
#define pib                         pair<int,bool>
#define pii                         pair<int,int>
#define pll                         pair<ll,ll>
#define sfi(x)                      scanf("%d",&x)
#define sfii(x,y)                   scanf("%d%d",&x,&y)
#define sfiii(x,y,z)                scanf("%d%d%d",&x,&y,&z)
#define siz(x)                      (int)x.size()
#define sortv(v)                    sort(v.begin(),v.end())
#define ss                          second
#define ull                         unsigned long long
#define umsi                        unordered_map<string,int>
#define umii                        unordered_map<int,int>
#define umis                        unordered_map<int,string>
#define vb                          vector<bool>
#define vi                          vector<int>
#define vvi                         vector<vi>
#define vii                         vector<pii>
#define vvii                        vector<vii>
#define vll                         vector<ll>
#define vpll                        vector<pll>

/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,
        tree_order_statistics_node_update> ordered_set;

//os.order_of_key(v): returns how many elements strictly less than v
//os.find_by_order(k-1): returns kth smallest element's iterator
*/

template<class T> class compare{
public:
    bool operator()(pair<T,T> &x,pair<T,T> &y){
        if(x.first==y.first){
            return x.ss>y.ss;
        }
        return x.ff>y.ff;
    }
};

template<class T> ostream& operator<<(ostream &os,const pair<T,T> &a) { os<<a.ff<<" "<<a.ss; }
template<class T> ll power(T a,int b){
    ll po=1; while(b--) po*=a; return po;
}

template<class T> pair<T,T> operator+(const pair<T,T> &a,const pair<T,T> &b){ return {a.ff+b.ff,a.ss+b.ss}; }
template<class T> pair<T,T> operator-(const pair<T,T> &a,const pair<T,T> &b){ return {a.ff-b.ff,a.ss-b.ss}; }
template<class T> pair<T,T> operator*(const pair<T,T> &a,const pair<T,T> &b){ return {a.ff*b.ff,a.ss*b.ss}; }
template<class T> pair<T,T> operator%(const pair<T,T> &a,const pair<T,T> &b){ return {a.ff%b.ff,a.ss%b.ss}; }
template<class T,class U> pair<T,T> operator+(const pair<T,T> &a,const U &b){ return { a.ff+b,a.ss+b}; }
template<class T,class U> pair<T,T> operator*(const pair<T,T> &a,const U &b){ return { a.ff*b,a.ss*b}; }

int Set(int N,int pos) { return N=N|(1<<pos); }
int reset(int N,int pos){ return N=N&~(1<<pos);}
bool check(int N,int pos){  return (bool) (N&(1<<pos));}

///=======================================template=======================================///

bool isFound(int ara[],int sz,int key){
    int l=0,r= sz-1;
    while(l<=r){
        int mid=l+(r-l)/2;
        if(ara[mid]==key)
            return true;
        else if(ara[mid]<key){
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    return false;
}

int leftmost(int ara[],int sz,int key){
    int l=0,r= sz-1;
    int ans=-1;
    while(l<=r){
        int mid=l+(r-l)/2;
        if(ara[mid]==key){//for lowerbound ==  ->  >=
            ans=mid;
            r=mid-1;
        }
        else if(ara[mid]<key){
            l=mid+1;
        }
        else
            r=mid-1;
    }
    return ans;
}

int rightmost(int ara[],int sz,int key){
    int l=0,r= sz-1;
    int ans=-1;
    while(l<=r){
        int mid=l+(r-l)/2;
        if(ara[mid]==key){ ///for upperbound ==  ->  >
            ans=mid;
            l=mid+1;
        }
        else if(ara[mid]<key){
            l=mid+1;
        }
        else
            r=mid-1;
    }
    return ans;
}

///smallest element in a shifted sorted array
/// 4 5 6 1 2 3

int smallest(int *ara, int sz){
    int l=0,r= sz-1,n=r;
    while(l<r){
        int mid=l+(r-l)/2;
        if(ara[mid]>ara[n]){
            l=mid+1;
        }
        else if(ara[mid]<=ara[n]){
            r=mid;
        }
    }
    return l;
}

///max element in an increasing and then decreasing array

int maxValue(int *ara,int sz){///duplicate elements not allowed
    int l=0,r= sz-1,n=r;

    while(l<r){
        int mid=l+(r-l)/2;
        if(mid==n){
            return mid;
        }
        else if(ara[mid]<ara[mid+1]){
            l=mid+1;
        }
        else {
            r=mid;
        }
    }
    return l;
}

///binary search for float value

pair<double,int> cubeRoot(double val){
    double l=0,r=val,cnt=0;
    while(true){
        double mid=(l+r)/2,done=mid*mid*mid-val;
        cnt++;

        if(abs(done)<EPS){
            return mp(mid,cnt);
        }
        else if(done<0){
            l=mid;
        }
        else
            r=mid;
    }
}

int main()
{
    //FI;FO;
    FastIO;
    cout<<"cubeRoot: ";
    cout<<fixed<<setprecision(15);
    cout<<cubeRoot(100).ff<<" "<<cubeRoot(100).ss<<endl;
    cout<<cubeRoot(1000).ff<<" "<<cubeRoot(1000).ss<<endl;
    cout<<cubeRoot(999999999).ff<<" "<<cubeRoot(999999999).ss<<endl;

    cout<<"maxValue: ";
    int ara[]={1,3,6,7,3,2,1};
    cout<<ara[maxValue(ara, sizeof(ara)/ sizeof(int))]<<endl;
    int ara1[]={1,2,1};
    cout<<ara1[maxValue(ara1, sizeof(ara1)/ sizeof(int))]<<endl;
    int ara2[]={1,2,3,4};
    cout<<ara2[maxValue(ara2, sizeof(ara2)/ sizeof(int))]<<endl;
    int ara3[]={5,4,3,2,-1};
    cout<<ara3[maxValue(ara3, sizeof(ara3)/ sizeof(int))]<<endl;

    cout<<"smallest: ";
    int ara4[]={5,6,8,9,9,1,1,2,2};
    cout<<ara4[smallest(ara4, sizeof(ara4)/ sizeof(int))]<<endl;
    int ara5[]={5,6,8,9,9};
    cout<<ara5[smallest(ara5, sizeof(ara5)/ sizeof(int))]<<endl;

    cout<<"rightmost: ";

    int ara6[]={9,9,9,9,9,9,19,20,20,20};
    cout<<rightmost(ara6, sizeof(ara6)/ sizeof(int),20)<<endl;
    cout<<rightmost(ara6, sizeof(ara6)/ sizeof(int),9)<<endl;
    cout<<rightmost(ara6, sizeof(ara6)/ sizeof(int),19)<<endl;
    cout<<rightmost(ara6, sizeof(ara6)/ sizeof(int),-1)<<endl;
    cout<<rightmost(ara6, sizeof(ara6)/ sizeof(int),21)<<endl;

    cout<<"leftmost: ";
    cout<<leftmost(ara6, sizeof(ara6)/ sizeof(int),20)<<endl;
    cout<<leftmost(ara6, sizeof(ara6)/ sizeof(int),9)<<endl;
    cout<<leftmost(ara6, sizeof(ara6)/ sizeof(int),19)<<endl;
    cout<<leftmost(ara6, sizeof(ara6)/ sizeof(int),-1)<<endl;
    cout<<leftmost(ara6, sizeof(ara6)/ sizeof(int),21)<<endl;

    cout<<"isFound: ";
    cout<<boolalpha;
    cout<<isFound(ara6, sizeof(ara6)/ sizeof(int),20)<<endl;
    cout<<isFound(ara6, sizeof(ara6)/ sizeof(int),9)<<endl;
    cout<<isFound(ara6, sizeof(ara6)/ sizeof(int),19)<<endl;
    cout<<isFound(ara6, sizeof(ara6)/ sizeof(int),-1)<<endl;
    cout<<isFound(ara6, sizeof(ara6)/ sizeof(int),21)<<endl;

    return 0;
}
