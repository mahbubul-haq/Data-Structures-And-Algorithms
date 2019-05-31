#include <bits/stdc++.h>
using namespace std;

#define dist2D(x1,y1,x2,y2)         ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))
#define dist3D(x1,y1,z1,x2,y2,z2)   ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2))
#define EPS                         1e-12
#define FastIO                      ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define FI                          freopen("in.txt","r",stdin)
#define FO                          freopen("out.txt","w",stdout)
#define fap(x)                      cout<<"WTH: "<<x<<endl
#define ff                          first
#define fof(i,x,y)                  for(int i=x;i<(int)y;i++)
#define fob(i,x,y)                  for(int i=x;i>=(int)y;i--)
#define INF                         100000
#define ld                          long double
#define ll                          long long
#define mem(x,y)                    memset(x,y,sizeof x)
#define mp                          make_pair
#define msi                         map<string,int>
#define mii                         map<int,int>
#define mis                         map<int,string>
#define MOD                         1000000007
#define PI                          acos(-1.0)
#define PQ                          priority_queue
#define pb                          push_back
#define pib                         pair<int,bool>
#define pii                         pair<int,int>
#define pll                         pair<ll,ll>
#define sfi(x)                      scanf("%d",&x)
#define sfii(x,y)                   scanf("%d%d",&x,&y)
#define sfiii(x,y,z)                scanf("%d%d%d",&x,&y,&z)
#define siz(x)                      (int)x.size()
#define sortv(v)                    sort(v.begin(),v.end())
#define ss                          second
#define ull                         unsigned long long
#define umsi                        unordered_map<string,int>
#define umii                        unordered_map<int,int>
#define umis                        unordered_map<int,string>
#define vb                          vector<bool>
#define vi                          vector<int>
#define vvi                         vector<vi>
#define vii                         vector<pii>
#define vvii                        vector<vii>
#define vll                         vector<ll>
#define vpll                        vector<pll>

template<class T> class compare{
public:
    bool operator()(pair<T,T> &x,pair<T,T> &y){
        if(x.first==y.first){
            return x.ss>y.ss;
        }
        return x.ff>y.ff;
    }
};

template<class T> ostream& operator<<(ostream &os,const pair<T,T> &a) { os<<a.ff<<" "<<a.ss; }
template<class T> void print(vector<T> &vec){
    for(int i=1;i<siz(vec);i++) cout<<vec[i]<<" ";cout<<endl;
}
template<class T> void print(set<T> &s) {
    for(auto it: s) cout<<it<<" "; cout<<endl;
}
template<class T> void print(list<T> &lst) {
    for(auto it: lst) cout<<it<<" "; cout<<endl;
}
template<class T> ll power(T a,int b){
    ll po=1; while(b--) po*=a; return po;
}

template<class T> pair<T,T> operator+(const pair<T,T> &a,const pair<T,T> &b){ return {a.ff+b.ff,a.ss+b.ss}; }
template<class T> pair<T,T> operator-(const pair<T,T> &a,const pair<T,T> &b){ return {a.ff-b.ff,a.ss-b.ss}; }
template<class T> pair<T,T> operator*(const pair<T,T> &a,const pair<T,T> &b){ return {a.ff*b.ff,a.ss*b.ss}; }
template<class T> pair<T,T> operator%(const pair<T,T> &a,const pair<T,T> &b){ return {a.ff%b.ff,a.ss%b.ss}; }
template<class T,class U> pair<T,T> operator+(const pair<T,T> &a,const U &b){ return { a.ff+b,a.ss+b}; }
template<class T,class U> pair<T,T> operator*(const pair<T,T> &a,const U &b){ return { a.ff*b,a.ss*b}; }

int Set(int N,int pos) { return N=N|(1<<pos); }
int reset(int N,int pos){ return N=N&~(1<<pos);}
bool check(int N,int pos){  return (bool) (N&(1<<pos));}

///=======================================template=======================================//

class item{
public:
    int key,prior,cnt;
    item *left,*right;
    item(int key,int prior):key(key),prior(prior),cnt(1),left(NULL),right(NULL){}
};

typedef item* pitem;

int cnt(pitem t){
    return t? t->cnt:0;
}
void upd_cnt(pitem t){
    if(t)
        t->cnt=1+cnt(t->left) +cnt(t->right);
}

void split(pitem t,int key,pitem &left,pitem &right){
    if(!t) left=right=NULL;
    else if(key<=t->key)
        split(t->left,key,left,t->left),right=t;
    else split(t->right,key,t->right,right), left=t;
    upd_cnt(t);
}

void insert(pitem &t,pitem it){
    if(!t) t=it;
    else if(it->prior >= t->prior){
        split(t,it->key,it->left,it->right), t=it;
    }
    else insert(it->key <= t->key? t->left: t->right,it);
    upd_cnt(t);
}

void merge(pitem &t,pitem left,pitem right){
    if(!left or !right){
        t=left? left: right;
    }
    else if(left->prior >= right->prior){
        merge(left->right,left->right,right), t=left;
    } else
        merge(right->left,left,right->left), t=right;
    upd_cnt(t);
}

void erase(pitem &t,int key){
    if(t->key == key){
        merge(t,t->left,t->right);
    }
    else erase(key<t->key? t->left: t->right,key);
    upd_cnt(t);
}

pitem unite(pitem left, pitem right){///upd_cnt not added
    if(!left or !right) return left? left: right;
    if(left->prior <=right->prior)  swap(left,right);
    pitem lt,rt;
    split(right,left->key,lt,rt);
    left->left=unite(left->left,lt);
    left->right=unite(left->right,rt);
    return left;
}

void inorder(pitem &t){
    if(t){
        inorder(t->left);
        cout<<t->key<<" "<<t->prior<<" "<<t->cnt;
        if(t->left) cout<<" L: "<<t->left->key;
        if(t->right) cout<<" R: "<<t->right->key;
        cout<<endl;
        inorder(t->right);
    }
}

void heapify(pitem t){
    if(!t) return;
    pitem max=t;
    if(t->left!=NULL and t->left->prior >=max->prior)
        max=t->left;
    if(t->right!=NULL and t->right->prior >=max->prior)
        max=t->right;
    if(max!=t){
        swap(t->prior,max->prior);
        heapify(max);
    }
}

pitem build(int * a,int n){
    if(n==0) return NULL;
    int mid=n>>1;
    pitem t=new item(a[mid],rand()%20);
    t->left=build(a,mid);
    t->right=build(a+mid+1,n-mid-1);
    heapify(t);
    return t;
}

int main()
{
    //FI;FO;
    FastIO;
    srand(time(NULL));

    int a[10];

    for(int i=0;i<10;i++){
        cin>>a[i];
    }

    sort(a,a+10);

    pitem root=build(a,10);

    inorder(root);

    return 0;
}
