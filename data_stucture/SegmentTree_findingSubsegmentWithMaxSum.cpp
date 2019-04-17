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

class data{
public:
    int ans,sum,pref,suff;
};

class SegmentTree{
    int n;
    vi ara;
    vector< data > st;

    int left(int node){ return (node<<1);}
    int right(int node){ return (node<<1)+1;}

    data make_data(int val){
        data temp;
        temp.suff=temp.pref=temp.ans=max(val,0);
        temp.sum=val;
        return temp;
    }

    data combine( data L,data R){
        data temp;
        temp.sum=L.sum+R.sum;
        temp.pref=max(L.pref,L.sum+R.pref);
        temp.suff=max(R.suff,R.sum+L.suff);
        temp.ans=max(max(L.ans,R.ans),L.suff+R.pref);
        return temp;
    }

    void build(int node,int L,int R){
        if(L==R){
            st[node]=make_data(ara[L]);
        }
        else{
            build(left(node),L,(L+R)/2);
            build(right(node),(L+R)/2+1,R);

            st[node]=combine(st[left(node)],st[right(node)]);
        }
    }

    data query(int node,int L,int R,int i,int j){
        if(i>R||j<L) return make_data(0);
        if(L>=i&&R<=j) return st[node];


        data lef=query(left(node),L,(L+R)>>1,i,j);
        data rig=query(right(node),((L+R)>>1)+1,R,i,j);

        return combine(lef,rig);
    }

    void update(int node,int L,int R,int pos,int value){
        if(pos>R||pos<L) return;
        if(pos==L&&pos==R){
            st[node]=make_data(value);
            return;
        }
        update(left(node),L,(L+R)/2,pos,value);
        update(right(node),(L+R)/2+1,R,pos,value);

        st[node]=combine(st[left(node)],st[right(node)]);
    }

public:
    SegmentTree(vi _ara){
        ara=_ara;
        n=ara.size();
        st.assign(4*n+1,data());
        build(1,0,n-1);
    }
    int query(int i,int j){ return query(1,0,n-1,i,j).ans;}
    void update(int pos,int value){ update(1,0,n-1,pos,value);}
};

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    vi vec;
    int n; cin>>n;

    for(int i=0;i<n;i++){
        int x; cin>>x; vec.pb(x);
    }
    SegmentTree st(vec);
    //for(auto v: vec) cout<<v<<" "; cout<<endl;

    cout<<st.query(0,n-1)<<endl;
    cout<<st.query(4,4)<<endl;
    cout<<st.query(4,5)<<endl;

    st.update(0,10000);
    cout<<st.query(0,n-1)<<endl;
    cout<<st.query(4,4)<<endl;
    cout<<st.query(4,7)<<endl;
    st.update(n-1,20000);

    cout<<st.query(0,n-1)<<endl;
    cout<<st.query(4,4)<<endl;
    cout<<st.query(4,7)<<endl;

    return 0;
}
