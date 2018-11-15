#include<iostream>
using namespace std;
#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

#define vi vector<int>
#define maxn 1e6
#define pb push_back

bool isPrime[(int)maxn+1];///0 if prime else not prime
vi primes;

void sieve(int n){

    int limit=sqrt(n*1.0)+2;

    primes.pb(2);
    isPrime[1]=true;
    for(int i=4;i<=n;i+=2) isPrime[i]=true;

    for(int i=3;i<=n;i+=2){
        if(!isPrime[i]){
            primes.pb(i);

            if(i<=limit) {
                for (int j = i * i; j  <= n; j += i * 2) {
                    isPrime[j] = true;
                }
            }

        }
    }


}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    sieve(maxn);

    return 0;
}
