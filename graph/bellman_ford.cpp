#include<iostream>
#include<cstdio>
#include<set>
#include<queue>
#include<cstring>
#include<math.h>
#include<map>
#include<string>
#include<climits>
#include<algorithm>
using namespace std;

#define pb push_back
#define pii pair<int,int>
#define ll long long
#define pll pair<long,long>
#define vi vector<int>
#define vii vector<pii>
#define vll vector<ll>
#define MOD 1000000007
#define mem(x,y) memset(x,y,sizeof x)
#define MAX 1000000000000000000

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
bool check(int N,int pos){  return (bool) (N&(1<<pos));}

///graph input: first line - v,e,source, next e lines - edges and weights
/*
5 5 0
  0 1 1
  0 2 10
  1 3 2
  2 3 -10
  3 4 3
  */

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int V,E,source;
    cin>>V>>E>>source;

    vector<vii> AdjLst(V,vii());
    for(int i=0;i<E;i++){
        int u,v,w;
        cin>>u>>v>>w;
        AdjLst[u].pb(pii(v,w));///directed graph....
    }

    vi dist(V,INT_MAX);
    dist[source]=0;
    int dir[V];
    dir[source]=-1;
    for(int i=1;i<=V-1;i++){///overall O(VE): worst case

        bool flag=false;

        for(int u=0;u<V;u++){
                int siz=AdjLst[u].size();
            for(int j=0;j<siz;j++){
                    pii v=AdjLst[u][j];
                if(dist[u]+v.second<dist[v.first]){
                    dist[v.first]=dist[u]+v.second;
                    dir[v.first]=u;
                    flag=true;
                }
            }
        }

        if(!flag) break;///breaks if all distances are relaxed maximally
    }

    ///checking if negative cycle exists or not
    bool isNegativeCycle=false;

    for(int i=0;i<V;i++){
        int siz=AdjLst[i].size();
        for(int j=0;j<siz;j++){
            pii v=AdjLst[i][j];

            if(dist[i]+v.second<dist[v.first]){
                isNegativeCycle=true;
                break;
            }
        }
        if(isNegativeCycle) break;
    }

    cout<<boolalpha<<isNegativeCycle<<endl;
    ///print distances
    if(!isNegativeCycle){
        for(int i=0;i<V;i++)cout<<dist[i]<<" ";
    }
    cout<<endl;

    return 0;
}
