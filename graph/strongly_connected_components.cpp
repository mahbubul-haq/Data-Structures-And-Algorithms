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

///for basics of SCC( Strongly connected components) see Shafayet's blog and and Halim's CP3 book
///Graph input: V, E.
///next E lines u and v... there is an edge from u to v

vector< vi > AdjLst,SCC;
vi dfs_num,dfs_low,Stack;/// stack will have track of visited vertices
vector<bool> visited;
int V,E,dfs_times;

void tarjan_SCC(int u){
    dfs_num[u]=dfs_low[u]=++dfs_times;
    int siz=AdjLst[u].size();

    visited[u]=true;
    Stack.push_back(u);

    for(int i=0;i<siz;i++){

        int v=AdjLst[u][i];

        if(dfs_num[v]==-1) tarjan_SCC(v);

        if(visited[v]) dfs_low[u]=min(dfs_low[u],dfs_low[v]);
    }

    if(dfs_num[u]==dfs_low[u]){///that means u is a root of SCC
        vi tempvec;

        while(true){
            int v=Stack.back(); Stack.pop_back();
            visited[v]=false;

            tempvec.push_back(v);

            if(v==u) break;
        }

        SCC.push_back(tempvec);
    }

}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int V,E; cin>>V>>E;

    AdjLst.assign(V,vi());///vertices are numbered from 0 to V-1


    for(int i=0;i<E;i++){
        int u,v;
        cin>>u>>v;
        AdjLst[u].pb(v);///must be directed for SCC
    }

    dfs_num.assign(V,-1),dfs_low.assign(V,0),visited.assign(V,false);
    dfs_times=0;

    for(int i=0;i<V;i++){
        if(dfs_num[i]==-1){
            tarjan_SCC(i);
        }
    }

    cout<<"NumOfSCC: "<<SCC.size()<<endl;

    for(int i=0;i<SCC.size();i++){

        for(int j=0;j<SCC[i].size();j++){
            cout<<SCC[i][j]<<" ";
        }
        cout<<endl;

    }

    return 0;
}
