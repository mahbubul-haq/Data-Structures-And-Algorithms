#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define pii pair<int,int>
#define ll long long
#define pll pair<long,long>
#define vi vector<int>
#define vii vector<pii>
#define vll vector<ll>
#define MOD 1000000007
#define EPS 1e-7
#define mem(x,y) memset(x,y,sizeof x)
#define MAX 4e18
#define ff(i,a,b) for(int i=(a);i<=(b);i++)
#define fb(i,a,b) for(int i=(a);i>=(b);i--)

class compare{
public:
    bool operator()(pii x,pii y){
        if(x.second==y.second){
            return x.first<y.first;
        }
        return x.second<y.second;
    }
};
int Set(int N,int pos) { return N=N|(1<<pos); }
int reset(int N,int pos){ return N=N&~(1<<pos);}
bool check(int N,int pos){  return (bool) (N&(1<<pos));}

vector< vi > AdjLst;
vi toposort;
vector<bool> visited;

void dfs(int u){

    int siz=AdjLst[u].size();
    visited[u]=true;

    for(int i=0;i<siz;i++){
        int v=AdjLst[u][i];
        if(!visited[v]){
            dfs(v);
        }
    }
    toposort.push_back(u);

}

void dfs1(int u){

    int siz=AdjLst[u].size();
    visited[u]=true;

    for(int i=0;i<siz;i++){
        int v=AdjLst[u][i];
        if(!visited[v]){
            dfs1(v);
        }
    }

}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    ///first do topological sort then dfs

    int V,E; cin>>V>>E;

    AdjLst.assign(V+1,vi());///vertices are numbered from 1 to V
    visited.assign(V+1,false);

    for(int i=1;i<=E;i++){
        int u,v; cin>>u>>v;
        AdjLst[u].pb(v);
    }

    for(int i=1;i<=V;i++){
        if(!visited[i]){
            dfs(i);
        }
    }

    visited.assign(V+1,false);

    int siz=toposort.size();
    int cnt=0;
    for(int i=siz-1;i>=0;i--){
        if(!visited[toposort[i]]){
            cnt++;
            dfs1(toposort[i]);
        }
    }

    cout<<"Number of Connected Components: "<<cnt<<endl;

    return 0;
}
