#include <bits/stdc++.h>
using namespace std;

#define dist2D(x1,y1,x2,y2)         ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))
#define dist3D(x1,y1,z1,x2,y2,z2)   ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2))
#define EPS                         1e-10
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
/*
 * Treap: geekforgeeks
 */

#define maxn 100

class Node{
public:
    int key,priority;
    Node *left,*right;
};

Node *newNode(int key){
    Node *node=new Node();
    node->key=key;
    node->priority=rand()%maxn;
    node->left=node->right=NULL;
    return node;
}

Node *Search(Node *node,int key){
    if(node==NULL or node->key==key) return node;
    if(node->key>key) return Search(node->left,key);
    return Search(node->right,key);
}

Node *leftRotate(Node *node){
    Node *temp=node->right,*t2=temp->left;
    temp->left=node;
    node->right=t2;
    return temp;
}

Node *rightRotate(Node *node){
    Node *temp=node->left,*t2=temp->right;
    temp->right=node;
    node->left=t2;
    return temp;
}

Node *Insert(Node *node,int key){
    if(node==NULL) return newNode(key);

    if(key<=node->key){
        node->left=Insert(node->left,key);

        if(node->left->priority> node->priority){
            node=rightRotate(node);
        }
    }
    else{
        node->right=Insert(node->right,key);

        if(node->right->priority> node->priority){
            node=leftRotate(node);
        }
    }

    return node;
}

Node *deleteNode(Node *node,int key){
    if(node==NULL) return node;

    if(key<node->key) node->left=deleteNode(node->left,key);
    else if(key>node->key)
        node->right=deleteNode(node->right,key);
    else if(node->left==NULL){
        Node *temp=node->right;
        delete(node);
        node=temp;
    }
    else if(node->right==NULL){
        Node *temp=node->left;
        delete(node);
        node=temp;
    }
    else if(node->left->priority<node->right->priority){
        node=leftRotate(node);
        node->left=deleteNode(node->left,key);
    }
    else{
        node=rightRotate(node);
        node->right=deleteNode(node->right,key);
    }
    return node;
}

void Inorder(Node *node){
    if(node){
        Inorder(node->left);
        cout<< node->key<<" "<<node->priority;
        if(node->left) cout<<" L: "<<node->left->key;
        if(node->right) cout<<" R: "<<node->right->key;
        cout<<endl;
        Inorder(node->right);
    }
}

int main()
{
    //FI;FO;
    FastIO;
    srand(time(NULL));

    Node *root=NULL;
    root=Insert(root,50);
    root=Insert(root,30);
    root=Insert(root,20);
    root=Insert(root,40);
    root=Insert(root,70);
    root=Insert(root,60);
    root=Insert(root,80);

    Inorder(root);
    cout<<endl;

    root=deleteNode(root,20);
    Inorder(root);
    cout<<endl;

    root=deleteNode(root,30);
    Inorder(root);
    cout<<endl;

    root=deleteNode(root,50);
    Inorder(root);
    cout<<endl;

    Node *temp=Search(root,50);

    if(temp) cout<<"Found"<<endl;
    else cout<<"Not found"<<endl;

    return 0;
}
