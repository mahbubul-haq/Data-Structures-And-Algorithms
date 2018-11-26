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
#include <iomanip>
#include <vector>
#include <stack>
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

#define maxn 1000000

vi primes;
int isPrime[1000000>>5];///is isPrime[x]==0 then prime else not.
void bitwise_sieve(int n){

    int limit = sqrt(n*1.0)+2;

    isPrime[1>>5]=Set(1>>5,1&31);///x%32 and x&31 are same, x/32 and x>>5 are same
    isPrime[0]=Set(0,0);

    primes.pb(2);

    for(int i=4;i<=n;i+=2) isPrime[i>>5]=Set(isPrime[i>>5],i&31);

    for(int i=3;i<=n;i+=2){
        if(!check(isPrime[i>>5],i&31)){
            primes.pb(i);
            if(i<=limit){
                for(int j=i*i;j<=n;j+=i){
                    isPrime[j>>5]=Set(isPrime[j>>5],j&31);
                }
            }
        }
    }

    ///printing the primes up to maxn
    //cout<<primes.size()<<endl;
    //for(int i=0;i<primes.size();i++) cout<<primes[i]<<" ";

}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    bitwise_sieve(maxn);

    return 0;
}
