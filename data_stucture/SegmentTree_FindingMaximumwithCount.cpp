#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define pii pair<int,int>
#define ll long long
#define pll pair<ll,ll>
#define vi vector<int>
#define vii vector<pii>
#define vll vector<ll>
#define MOD 1000000007
#define EPS 1e-7
#define mem(x,y) memset(x,y,sizeof x)
#define INF 1e9
#define ff(i,a,b) for(int i=(a);i<=(b);i++)
#define fb(i,a,b) for(int i=(a);i>=(b);i--)
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

class SegmentTree{
    vii st;
    vi ara;
    int n;
    int left(int node){return (node<<1);}
    int right(int node){return (node<<1)+1;}

    pii combine(pii a,pii b){
        if(a.first>b.first){
            return a;
        }
        else if(a.first<b.first){
            return b;
        }
        return pii(a.first,a.second+b.second);
    }

    void build(int node,int L,int R){
        if(L==R){
            st[node]=pii(ara[L],1);
            return;
        }
        build(left(node),L,(L+R)/2);
        build(right(node),(L+R)/2+1,R);

        st[node]=combine(st[left(node)],st[right(node)]);
    }

    pii rmq(int node,int L,int R,int i,int j){
        if(L>j||i>R){
            return pii(-INF,0);
        }
        if(L>=i&&R<=j)return st[node];

        return combine(rmq(left(node),L,(L+R)/2,i,j),rmq(right(node),(L+R)/2+1,R,i,j));
    }
    void update(int node,int L,int R,int pos,int value){
        if(L>pos||pos>R){
            return;
        }
        if(L==pos&&R==pos){
            st[node]=pii(value,1);
            return;
        }
        update(left(node),L,(L+R)/2,pos,value);
        update(right(node),(R+L)/2+1,R,pos,value);
        st[node]=combine(st[left(node)],st[right(node)]);
    }

public:
    SegmentTree(vi _ara){
        ara=_ara;
        n=ara.size();
        st.assign(n*4,pii());
        build(1,0,n-1);
    }
    pii rmq(int i,int j) { return rmq(1,0,n-1,i,j);}
    void update(int pos,int value){ update(1,0,n-1,pos,value);}
};

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n; cin>>n;
    vi vec;
    int input;
    for(int i=0;i<n;i++) cin>>input, vec.pb(input);
    SegmentTree st(vec);

    cout<<st.rmq(0,5)<<endl;
    cout<<st.rmq(0,3)<<endl;
    cout<<st.rmq(2,1)<<endl;
    st.update(0,100);
    cout<<st.rmq(0,vec.size()-1)<<endl;
    st.update(1,100);
    st.update(2,100);
    cout<<st.rmq(0,2)<<endl;

    return 0;
}
