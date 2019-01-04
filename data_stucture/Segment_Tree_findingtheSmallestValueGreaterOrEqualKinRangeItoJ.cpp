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
    vector<multiset<int> > st;
    vi ara;
    int n;

    int left(int node){ return (node<<1);}
    int right(int node){ return (node<<1)+1;}

    void build(int node,int L,int R){
        if(L==R){
            st[node].insert(ara[L]);
        }
        else{
            build(left(node),L,(L+R)/2);
            build(right(node),(L+R)/2+1,R);
            st[node].insert(st[left(node)].begin(),st[left(node)].end());
            st[node].insert(st[right(node)].begin(),st[right(node)].end());
        }

    }
    
    int query(int node,int L,int R,int i,int j,int value){
        if(i>R||j<L) return INF;
        if(L>=i&&R<=j){
            auto it=st[node].lower_bound(value);
            if(it==st[node].end())
                return INF;
            else return *it;
        }
        
        return min(query(left(node),L,(L+R)/2,i,j,value),query(right(node),(L+R)/2+1,R,i,j,value));
    }
    
    void update(int node,int L,int R,int pos,int value){
        st[node].erase(st[node].find(ara[pos]));
        st[node].insert(value);
        
        if(L!=R){
            int mid=(L+R)/2;
            if(pos<=mid){
                update(left(node),L,mid,pos,value);
            }
            else update(right(node),mid+1,R,pos,value);
        }
        else{
            ara[pos]=value;
        }
    }

public:
    SegmentTree(vi _ara){
        ara=_ara;
        n=ara.size();
        st.assign(4*n,multiset<int>());
        build(1,0,n-1);
    }
    int query(int i,int j,int value){
        return query(1,0,n-1,i,j,value);
    }
    void update(int pos,int value){
        update(1,0,n-1,pos,value);
    }
};

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n; cin>>n;
    vi vec; 
    for(int i=0;i<n;i++){
        int x; cin>>x; vec.pb(x);
    }
    SegmentTree st(vec);
    
    while(true){
        int i,j,value;
        cin>>i>>j>>value;
        cout<<st.query(i,j,value)<<endl;
        int pos;
        cin>>pos>>value;
        st.update(pos,value);
    }
    
    return 0;
}
