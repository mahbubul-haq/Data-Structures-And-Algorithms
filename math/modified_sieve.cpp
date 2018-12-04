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
#define dist2D(x1,y1,x2,y2) ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))
#define dist3D(x1,y1,z1,x2,y2,z2) ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2))
#define sortv(v) sort(v.begin(),v.end())
#define debugx(x) cout<<"WTH! "<<x<<endl
#define debug(x,y) cout<<x<<" "<<y<<endl

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

vi modified_Sieve(int n){/// count number of different prime factors for all number upto n
    vi numofDiffPf(n+1,0);

    for(int i=2;i<=n;i++){
        if(numofDiffPf[i]==0) {///i is a prime
            for (int j = i; j <= n; j += i) {
                numofDiffPf[j]++;
            }
        }
    }

    return numofDiffPf;

}

vi euler_Phi_with_Modified_sieve(int n){///count number of coprimes for all numbers up to n
    vi numOfCoprimes(n+1,0);

    for(int i=0;i<=n;i++) numOfCoprimes[i]=i-1;
    numOfCoprimes[1]=0;

    for(int i=2;i<=n;i++){
        if(numOfCoprimes[i]==i-1) {///i is a prime
            for (int j = i; j <= n; j += i) {
                numOfCoprimes[j]-=((j-i)/i);
            }
        }
    }

    return numOfCoprimes;

}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n; cin>>n;
    
    ///for details see Halim's CP3

    vi numOfDiffPF=modified_Sieve(n);

    for(int i=1;i<=n;i++) cout<<numOfDiffPF[i]<<" ";

    cout<<endl;

    vi numOfCoprimes=euler_Phi_with_Modified_sieve(n);

    for(int i=1;i<=n;i++) cout<<numOfCoprimes[i]<<" ";

    cout<<endl;

    return 0;
}
