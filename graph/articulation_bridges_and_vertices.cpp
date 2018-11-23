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

///Graph input: V,E; next E lines edges. Weights are not needed for this algo
/*
 7 7
 1 2
 1 3
 3 4
 3 7
 6 7
 4 6
 5 4

 works both in undirected and directed graphs.
 articulationBridges do not give correct answer for multiedges
 */

vector< vi > AdjLst;
vector<bool> visited;
int dfsroot,numOfChildren;
vector<bool> articulationPoints;
vii articulationBridges;
int times=0;
vi dfs_low,dfs_num,parent;

void articulationPointandBridge(int u){
    dfs_low[u]=dfs_num[u]=++times;

    int siz=AdjLst[u].size();

    for(int i=0;i<siz;i++){
        int v=AdjLst[u][i];

        if(!visited[v]){
            parent[v]=u;
            visited[v]=true;

            if(u==dfsroot) numOfChildren++;
            articulationPointandBridge(v);

            if(dfs_low[v]>=dfs_num[u]) articulationPoints[u]=true;
            if(dfs_low[v]>dfs_num[u]) articulationBridges.pb(pii(u,v));

            dfs_low[u]=min(dfs_low[v],dfs_low[u]);

        }
        else if(v!=parent[u]) dfs_low[u]=min(dfs_low[u],dfs_num[v]);
    }

}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int V,E; cin>>V>>E;
    AdjLst.assign(V+1,vi());///nodes start from 1
    for(int i=0;i<E;i++){
        int u,v;
        cin>>u>>v;
        AdjLst[u].pb(v);
        AdjLst[v].pb(u);///undirected
    }

    visited.assign(V+1,false);
    dfs_low.assign(V+1,INT_MAX);
    dfs_num.assign(V+1,INT_MAX);
    parent.assign(V+1,-1);
    articulationPoints.assign(V+1,false);

    for(int i=1;i<=V;i++){
        if(!visited[i]){
            visited[i]=true;
            dfsroot=i; numOfChildren=0;
            articulationPointandBridge(i);
            if(numOfChildren>1) articulationPoints.pb(i);
        }
    }

    ///articulationVertices
    cout<<"Points: ";

    for(int i=1;i<=V;i++){
        if(articulationPoints[i]) cout<<i<<" ";
    }
    cout<<endl;
    ///articulationBridges
    cout<<"Bridges:";

    for(int i=0;i<articulationBridges.size();i++){
        cout<<articulationBridges[i].first<<" "<<articulationBridges[i].second<<endl;
    }

    return 0;
}
