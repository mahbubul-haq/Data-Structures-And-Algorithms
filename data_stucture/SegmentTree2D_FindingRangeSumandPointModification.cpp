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
#define INF                         100000
#define ld                          long double
#define ll                          long long
#define mem(x,y)                    memset(x,y,sizeof x)
#define mp                          make_pair
#define msi                         map<string,int>
#define mii                         map<int,int>
#define mis                         map<int,string>
#define MOD                         1000000007
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
template<class T> void print(vector<T> &vec){
    for(int i=1;i<siz(vec);i++) cout<<vec[i]<<" ";cout<<endl;
}
template<class T> void print(set<T> &s) {
    for(auto it: s) cout<<it<<" "; cout<<endl;
}
template<class T> void print(list<T> &lst) {
    for(auto it: lst) cout<<it<<" "; cout<<endl;
}
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

///=======================================template=======================================//

class SegmentTree2D{
public:
    vvi st;
    int n,m;
    vvi mat;
    SegmentTree2D(vvi &_mat){
        mat=_mat;
        n=siz(mat);
        m=siz(mat[0]);
        st.assign(4*n+1,vi(4*m+1,0));
        buildx(1,0,n-1);
    }

    int left(int node){ return (node<<1);}
    int right(int node){ return (node<<1)|1;}

    void buildy(int nodex,int Lx,int Rx,int nodey,int L,int R){
        if(L==R){
            if(Lx==Rx)
                st[nodex][nodey]=mat[Lx][L];
            else st[nodex][nodey]=st[left(nodex)][nodey]+st[right(nodex)][nodey];
        }
        else{
            int mid=(L+R)>>1;
            buildy(nodex,Lx,Rx,left(nodey),L,mid);
            buildy(nodex,Lx,Rx,right(nodey),mid+1,R);
            st[nodex][nodey]=st[nodex][left(nodey)]+st[nodex][right(nodey)];
        }
    }

    void buildx(int node,int L,int R){
        if(L!=R){
            int mid=(L+R)>>1;
            buildx(left(node),L,mid);
            buildx(right(node),mid+1,R);
        }
        buildy(node,L,R,1,0,m-1);
    }

    int sumy(int nodex,int node,int L,int R,int ly,int ry){
        if(ly>R or ry< L) return 0;
        if(L>=ly and R<=ry) return st[nodex][node];
        int mid=(L+R)>>1;
        return sumy(nodex,left(node),L,mid,ly,ry)+
                sumy(nodex,right(node),mid+1,R,ly,ry);
    }

    int sumx(int node,int L,int R,int lx,int rx,int ly,int ry){
        if(lx>R or rx < L){
            return 0;
        }
        if(L>=lx and R<=rx) return sumy(node,1,0,m-1,ly,ry);
        int mid=(L+R)>>1;
        return sumx(left(node),L,mid,lx,rx,ly,ry)+sumx(right(node),mid+1,R,lx,rx,ly,ry);
    }

    void updatey(int nodex,int Lx,int Rx,int node,int L,int R,int y,int val){
        if(L>y or R<y) return;
        if(L==R and R==y){
            if(Lx==Rx) st[nodex][node]=val;
            else st[nodex][node]=st[left(nodex)][node]+st[right(nodex)][node];
        }
        else{
            int mid=(L+R)>>1;
            updatey(nodex,Lx,Rx,left(node),L,mid,y,val);
            updatey(nodex,Lx,Rx,right(node),mid+1,R,y,val);
            st[nodex][node]=st[nodex][left(node)]+st[nodex][right(node)];
        }
    }

    void updatex(int node,int L,int R,int x,int y,int val){
        if(L>x or R<x) return;
        if(!(L==R and R==x)){
            int mid=(L+R)>>1;
            updatex(left(node),L,mid,x,y,val);
            updatex(right(node),mid+1,R,x,y,val);
        }
        updatey(node,L,R,1,0,m-1,y,val);
    }
};

int main()
{
    //FI;FO;
    FastIO;

    vvi mat;
    int n,m; cin>>n>>m;

    for(int i=1;i<=n;i++){
        mat.emplace_back();
        for(int j=1;j<=m;j++){
            int x; cin>>x;
            mat.back().pb(x);
        }
    }

    SegmentTree2D st(mat);

    int q;
    cin>>q;
    while(q--){
        int lx,ly,rx,ry;
        int val; cin>>lx>>ly>>rx>>ry>>val;
        cout<<st.sumx(1,0,n-1,lx,rx,ly,ry)<<endl;
        st.updatex(1,0,n-1,lx,ly,val);
    }

    return 0;
}
