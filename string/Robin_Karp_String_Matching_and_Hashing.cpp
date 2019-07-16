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
#include <list>
#include <iterator>
using namespace std;

#define pb push_back
#define pii pair<int,int>
#define ll long long
#define pll pair<ll,ll>
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

class compare{
public:
    bool operator()(pii x,pii y){
        if(x.second==y.second){
            return x.first<y.first;
        }
        return x.second<y.second;
    }
};

ostream& operator<<(ostream &os,const pll &a){
    os<<a.first<<" "<<a.second;
}

pll operator+(const pll &a, const ll &b){ return { a.first+b,a.second+b };}
pll operator*(const pll &a,const ll &b){ return {a.first * b,a.second * b};}
pll operator+(const pll &a,const pll &b){ return {a.first+b.first,a.second+b.second};}
pll operator-(const pll &a,const pll &b){ return { a.first-b.first,a.second-b.second};}
pll operator*(const pll &a,const pll &b){ return {a.first*b.first,a.second*b.second};}
pll operator%(const pll &a,const pll &b){ return {a.first%b.first,a.second%b.second};}

int Set(int N,int pos) { return N=N|(1<<pos); }
int reset(int N,int pos){ return N=N&~(1<<pos);}
bool check(int N,int pos){  return (bool) (N&(1<<pos));}

vector< pll > p_pow;
pll mod={1e9+9,1e9+7};///double hashing for low colling probability
pll p={67,71};///both lowercase and uppercase letters

void pow_calc(int siz){///powercalculating

    p_pow[0]={1L,1L};
    for(int i=1;i<siz;i++) p_pow[i]=(p_pow[i-1]*p)%mod;
}

pll compute_hash(string const &text){///find the hash value of a string

    pll hashval={0L,0L};
    int siz=text.size();

    for(int i=1;i<=siz;i++){
        hashval=(hashval+p_pow[siz-i]*(text[i-1]-'A'+1))%mod;
    }

    return hashval;

}

bool findPattern(string const &text,pll patternhash,int patternsiz){///search if the pattern is in the text by hashvalue

    int siz=text.size();
    pll hashval={0L,0L};

    for(int i=1;i<=patternsiz;i++){///we assume that patternsize will be lower than or equal to textsize
        hashval=(hashval+p_pow[patternsiz-i]*(text[i-1]-'A'+1))%mod;
    }

    if(hashval==patternhash) return true;

    for(int i=patternsiz;i<siz;i++){

        hashval=(((mod+hashval-(p_pow[patternsiz-1]*(text[i-patternsiz]-'A'+1))%mod)%mod)*p)%mod+(text[i]-'A'+1);///rolling hash technique
        hashval=hashval%mod;                          ///see Shafayet's blog or rolling hash.(this algorithm is called Robin Carp String matching algorithm

        if(hashval==patternhash) return true;

    }

    return false;

}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    while(true) { ///this loop is for: checking if it is working or not

        string text, pattern;
        cin >> text >> pattern;

        if(text=="EOF")break;

        int siz = pattern.size();
        p_pow.assign(siz + 1, pll());

        pow_calc(siz);

        pll patternhash = compute_hash(pattern);

        bool isFound = findPattern(text, patternhash, siz);

        cout << isFound << endl;
    }

    return 0;
}
