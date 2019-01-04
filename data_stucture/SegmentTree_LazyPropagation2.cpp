#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define pii pair<int,int>
#define ll long long
#define pll pair<ll,ll>
#define vi vector<int>
#define vvi vector<vi>
#define vii vector<pii>
#define vvii vector<vii>
#define vll vector<ll>
#define MOD 998244353
#define EPS 1e-7
#define mem(x,y) memset(x,y,sizeof x)
#define INF 1e9
#define dist2D(x1,y1,x2,y2) ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))
#define dist3D(x1,y1,z1,x2,y2,z2) ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2))
#define sortv(v) sort(v.begin(),v.end())

class compare{
public:
    bool operator()(pii x,pii y){
        if(x.second==y.second){
            return x.first<y.first;
        }
        return x.second<y.second;
    }
};

ostream& operator<<(ostream &os,const pll &a){
    os<<a.first<<" "<<a.second;
}

pll operator+(const pll &a, const ll &b){ return { a.first+b,a.second+b };}
pll operator*(const pll &a,const ll &b){ return {a.first*b,a.second*b};}
pll operator+(const pll &a,const pll &b){ return {a.first+b.first,a.second+b.second};}
pll operator-(const pll &a,const pll &b){ return { a.first-b.first,a.second-b.second};}
pll operator*(const pll &a,const pll &b){ return {a.first*b.first,a.second*b.second};}
pll operator%(const pll &a,const pll &b){ return {a.first%b.first,a.second%b.second};}

int Set(int N,int pos) { return N=N|(1<<pos); }
int reset(int N,int pos){ return N=N&~(1<<pos);}
bool check(int N,int pos){  return (bool) (N&(1<<pos));}

///=======================================template=======================================///

class SegmentTree{
    vi ara;
    vii st;
    int n;

    int left(int node) { return (node<<1);}
    int right(int node){ return (node<<1)+1;}

    void build(int node,int L,int R){
        if(L==R){
            st[node]=pii(ara[L],0);
        }
        else{
            int mid=(L+R)/2;
            build(left(node),L,mid);
            build(right(node),mid+1,R);
        }
    }

    void push(int node){
        if(st[node].second){
            st[left(node)]=st[right(node)]=st[node];
            st[left(node)].second=st[right(node)].second=1;
            st[node].second=0;

        }
    }

    void update(int node,int L,int R,int i,int j,int value){
        if(i>R||j<L) return;

        if(L>=i&&R<=j){
            st[node].first=value;
            st[node].second=1;
        }
        else{
            push(node);
            int mid=(L+R)/2;
            update(left(node),L,mid,i,j,value);
            update(right(node),mid+1,R,i,j,value);
        }
    }

    int query(int node,int L,int R,int pos){
        if(L==R){
            return st[node].first;
        }
        push(node);
        int mid=(L+R)/2;
        if(pos<=mid){
            return query(left(node),L,mid,pos);
        }else return query(right(node),mid+1,R,pos);
    }

public:
    SegmentTree(vi _ara){
        ara=_ara;
        n=ara.size();
        st.assign(4*n,pii());
        build(1,0,n-1);
    }
    void update(int i,int j,int value){
        update(1,0,n-1,i,j,value);
    }
    int query(int pos){
        query(1,0,n-1,pos);
    }
};

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    vi vec;
    int n; cin>>n;

    for(int i=0;i<n;i++) {
        int x; cin>>x; vec.pb(x);
    }

    SegmentTree st(vec);

    while(true){
        int pos; cin>>pos;
        if(pos==-1) break;
        cout<<st.query(pos)<<endl;
        int i,j,value;
        cin>>i>>j>>value;
        st.update(i,j,value);

    }

    return 0;
}
