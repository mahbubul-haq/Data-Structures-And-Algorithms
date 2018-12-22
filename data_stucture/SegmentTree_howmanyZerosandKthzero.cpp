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
    vi st,ara;
    int n;
    int left(int node){ return (node<<1);}
    int right(int node){ return (node<<1)+1;}

    void build(int node,int L,int R){
        if(L==R){
            if(ara[L]==0) st[node]=1;
            else st[node]=0;

        }
        else {
            build(left(node), L, (L + R) / 2);
            build(right(node), (R + L) / 2 + 1, R);
            st[node] = st[left(node)] + st[right(node)];
        }
    }

    int rzeroq(int node,int L,int R,int i,int j){
        if(i>R||j<L) return 0;
        if(L>=i&&R<=j) return st[node];

        int val1=rzeroq(left(node),L,(L+R)/2,i,j);
        int val2=rzeroq(right(node),(R+L)/2+1,R,i,j);
        return val2+val1;
    }

    int kthzero(int node,int L,int R,int k){
        if(k>st[node]||k==0) return -1;

        if(L==R){
            return L;
        }

        int kinleft=st[left(node)];
        if(k<=kinleft){
            return kthzero(left(node),L,(L+R)/2,k);
        }
        else return kthzero(right(node),(L+R)/2+1,R,k-kinleft);

    }

    void update(int node,int L,int R,int i,int value){
        if(i>R||i<L) return ;
        if(i==L&&R==i){
            if(value==0) st[node]=1;
            else st[node]=0;

            return;
        }

        update(left(node),L,(L+R)/2,i,value);
        update(right(node),(L+R)/2+1,R,i,value);
        st[node]=st[left(node)]+st[right(node)];

    }

public:
    SegmentTree(vi _ara){
        ara=_ara;
        n=ara.size();
        st.assign(4*n,0);
        build(1,0,n-1);
    }
    int rzeroq(int i,int j) { return rzeroq(1,0,n-1,i,j);}
    void update(int i,int value){ update(1,0,n-1,i,value);}
    int kthzero(int k){ return kthzero(1,0,n-1,k);}
};

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n; cin>>n;
    vi ara; for(int i=0;i<n;i++) ara.emplace_back(),cin>>ara[i];

    SegmentTree st(ara);

    cout<<st.rzeroq(0,n-1)<<endl;
    cout<<st.rzeroq(3,3)<<endl;
    cout<<st.kthzero(1)<<endl;
    st.update(0,0);
    st.update(n-1,0);
    cout<<st.rzeroq(0,n-1)<<endl;
    cout<<st.kthzero(1)<<endl;
    cout<<st.kthzero(7)<<endl;
    cout<<st.kthzero(0)<<endl;

    return 0;
}
