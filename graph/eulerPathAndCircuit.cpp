#include <bits/stdc++.h>
using namespace std;

#define debug(x) cout<<"WTH: "<<x<<endl
#define dist2D(x1,y1,x2,y2) ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))
#define dist3D(x1,y1,z1,x2,y2,z2) ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2))
#define EPS 1e-12
#define FastIO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define FI freopen("in.txt","r",stdin)
#define FO freopen("out.txt","w",stdout)
#define ff first
#define fof(i,x,y) for(int i=x;i<(int)y;i++)
#define fob(i,x,y) for(int i=x;i>=(int)y;i--)
#define INF 100000
#define ld long double
#define ll long long
#define mem(x,y) memset(x,y,sizeof x)
#define mp make_pair
#define msi map<string,int>
#define mii map<int,int>
#define mis map<int,string>
#define MOD 1000000007
#define PI acos(-1.0)
#define PQ priority_queue
#define pb push_back
#define pib pair<int,bool>
#define pii pair<int,int>
#define pll pair<ll,ll>
#define sfi(x) scanf("%d",&x)
#define sfii(x,y) scanf("%d%d",&x,&y)
#define sfiii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define siz(x) (int)x.size()
#define sortv(v) sort(v.begin(),v.end())
#define ss second
#define umsi unordered_map<string,int>
#define umii unordered_map<int,int>
#define umis unordered_map<int,string>
#define vb vector<bool>
#define vi vector<int>
#define vvi vector<vi>
#define vii vector<pii>
#define vvii vector<vii>
#define vll vector<ll>
#define vpll vector<pll>

template<class T>
class compare{
public:
    bool operator()(pair<T,T> &x,pair<T,T> &y){
        if(x.first==y.first){
            return x.ss>y.ss;
        }
        return x.ff>y.ff;
    }
};

template<class T>
ostream& operator<<(ostream &os,const pair<T,T> &a){
    os<<a.ff<<" "<<a.ss;
}
template<class T>
void print(vector<T> &vec){
    fof(i,0,vec.size()) cout<<vec[i].ss<<" "; cout<<endl;
}
template<class T>
void print(set<T> &s){
    for(auto it: s) cout<<it<<" "; cout<<endl;
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

vector<pair<int,vi> > adjLst;
map<pii,int> isEdge;
stack<int> path;
int V,e,U,vv;
vb visited;

void dfs(int u){
    visited[u]=true;

    fof(i,0,siz(adjLst[u].ss)){
        int v=adjLst[u].ss[i];

        if(!visited[v]){
            dfs(v);
        }
    }
}

bool isConnected(){

    int u=-1;
    for(int i=1;i<=V;i++){
        if(siz(adjLst[i].ss)>=1){
            u=i;
            break;
        }
    }

    if(u==-1) return true;//no edge
    visited.assign(V+1,false);

    dfs(u);

    for(int i=1;i<=V;i++){
        if(visited[i]==false and siz(adjLst[i].ss)!=0) return false;
    }

    return true;
}

void findPath(int u){

    for(int i=adjLst[u].ff;i<siz(adjLst[u].ss);i++){
        int v=adjLst[u].ss[i];
        int mini=min(u,v),maxi=max(u,v);

        if(isEdge[mp(mini,maxi)]){

            adjLst[u].ff++;
            isEdge[mp(mini,maxi)]--;
            findPath(v);

        }
    }
    path.push(u);
}

bool eulerCircuit(){

    if(isConnected()){
        int odd=0;
        for(int i=1;i<=V;i++){
            odd+=(siz(adjLst[i].ss)&1);
        }

        if(odd>0) return false;

        int u=-1;
        for(int i=1;i<=V;i++){
            if(siz(adjLst[i].ss)>=2){
                u=i;
                break;
            }
        }
        if(u==-1) {
            path.push(1);
        }
        else {
            findPath(u);
        }

        return true;

    }
    return false;
}

bool eulerPath(){
    if(isConnected()){
        int odd=0;
        for(int i=1;i<=V;i++){
            odd+=(siz(adjLst[i].ss)&1);
        }

        if(odd==2){
            U=-1;
            for(int i=1;i<=V;i++){
                if((siz(adjLst[i].ss)&1) and U==-1){
                    U=i;
                }
                else if(siz(adjLst[i].ss)&1){
                    vv=i;
                    break;
                }
            }

            adjLst[U].ss.pb(vv);
            adjLst[vv].ss.pb(U);
            isEdge[mp(min(U,vv),max(U,vv))]++;
            findPath(U);
            return true;

        }
        return false;
    }
    return false;
}

int main()
{
    //FI;FO;
    FastIO;

    cin>>V>>e;

    adjLst.assign(V+1,{0,vi()});

    fof(i,0,e){
        int u,v;
        cin>>u>>v;
        adjLst[u].ss.pb(v);
        adjLst[v].ss.pb(u);
        if(u>v) swap(u,v);
        isEdge[pii(u,v)]++;
    }

    if(eulerCircuit()){
        while(!path.empty()){
            cout<<path.top()<<" ";
            path.pop();
        }
        cout<<endl;
    }else cout<<"No Euler Circuit"<<endl;

    if(eulerPath()){

        int u=-1;
        queue<int> q;
        bool flag=true;
        while(!path.empty()){
            int v=path.top();
            path.pop();

            if(u==vv and U==v and flag){
                flag=false;
            }

            if(flag) q.push(v);

            u=v;
            if(!flag) cout<<v<<" ";

        }

        q.pop();

        while(!q.empty()){
            cout<<q.front()<<" ";
            q.pop();
        }

        cout<<endl;

    }
    else cout<<"No Euler Path"<<endl;

    return 0;
}
