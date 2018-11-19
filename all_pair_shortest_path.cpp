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
#define INF 1e9
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

///Graph input: V E; next E lines edges with weights u, v, w
/*5 9
  0 1 2
  0 2 1
  0 4 3
  1 3 4
  2 1 1
  2 4 1
  3 0 1
  3 2 3
  3 4 5
 */

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int V,E;
    cin>>V>>E;

    int AdjMat[400][400];///this algorithm works if the graph size is small
    ///not more than 400 vertices

    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++)
        {
            AdjMat[i][j]=INF;

        }
        AdjMat[i][i]=0;
    }

    for(int i=0;i<E;i++){
        int u,v,w; cin>>u>>v>>w;
        AdjMat[u][v]=w;///directed graph
    }

    int next[400][400];///keeps the path from any i to any j
    //at first all next[i][j](means the shortest path from i to j) is j

    for(int i=0;i<V;i++) for(int j=0;j<V;j++) next[i][j]=j;

    for(int k=0;k<V;k++){
        for(int i=0;i<V;i++){
            for(int j=0;j<V;j++){
                //AdjMat[i][j]=min(AdjMat[i][j],AdjMat[i][k]+AdjMat[k][j]);
                if(AdjMat[i][j]>AdjMat[i][k]+AdjMat[k][j]) {
                    AdjMat[i][j]=AdjMat[i][k]+AdjMat[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            cout<<i<<"->"<<j<<" "<<AdjMat[i][j]<<endl;
        }
    }

    ///shortest path from u to v

    int u,v;
    cin>>u>>v;
    while(true){
        cout<<u<<" ";
        if(u==v) break;
        u=next[u][v];

    }

    return 0;
}
