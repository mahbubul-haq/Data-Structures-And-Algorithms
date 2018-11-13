#include<cstdio>
#include<queue>
#include<vector>
#include<climits>

using namespace std;

#define pii pair<int,int>
#define vii vector<pii>
#define vi vector<int>

/// Graph input: first line V,E and source. next E lines edges and weights.
/*5 7 2
  2 1 2
  2 3 7
  2 0 6
  1 3 3
  1 4 6
  3 4 5
  0 4 1
  */
vector< vii > AdjLst; ///stores adjacent nodes and edge weights.

int main(){

    int V,E,source;
    scanf("%d %d %d",&V,&E,&source);

    AdjLst.assign(V,vii()); ///assigns V numbers of vii into AdjLst-nodes start from 0

    for(int i=1;i<=E;i++){
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        AdjLst[u].push_back(pii(v,w));
        ///AdjLst[v].push_back(pii(u,w)); - if undirected
    }

    vi dist(V,INT_MAX);///at first distance of all nodes from source is infinity: there is no path yet.
    priority_queue<pii, vector<pii>, greater<pii> > pq;///sorted increasingly by distance from source;

    dist[source]=0;
    pq.push(pii(0,source));///distance of source is 0;

    while(!pq.empty()){
        pii top=pq.top(); pq.pop();
        int distance=top.first, u=top.second;

        if(distance==dist[u]){///for duplicate u we will take that with lowest dist[u].
            for(int i=0;i<AdjLst[u].size();i++){
                pii v=AdjLst[u][i];
                if(dist[u]+v.second<dist[v.first]){
                    dist[v.first]=dist[u]+v.second;
                    pq.push(pii(dist[v.first], v.first));///duplicate nodes may be pushed.
                }
            }
        }
    }
    ///calculated lowest distances from source for all nodes
    for(int i=0;i<V;i++) printf("Distance of node %d is %d\n",i,dist[i]);

    return 0;
}
