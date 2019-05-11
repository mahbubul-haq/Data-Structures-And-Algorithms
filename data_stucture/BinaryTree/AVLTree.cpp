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

class Node{
public:
    int key;
    Node *right,*left;
    int height;
};

Node *newNode(int key){
    Node *node=new Node();
    node->key=key;
    node->left=node->right=NULL;
    node->height=1;
    return node;
}

int height(Node *node){
    if(node==NULL) return 0;
    return node->height;
}

int getBalance(Node *node){
    if(node==NULL) return 0;
    return height(node->left)-height(node->right);
}

Node *rightRotate(Node *node){
    Node *x=node->left;
    Node *temp=x->right;

    x->right=node;
    node->left=temp;

    node->height=max(height(node->left),height(node->right))+1;
    x->height=max(height(x->left),height(x->right))+1;

    return x;
}

Node *leftRotate(Node *node){
    Node *x=node->right;
    Node *temp=x->left;
    x->left=node;
    node->right=temp;

    node->height=max(height(node->left),height(node->right))+1;
    x->height=max(height(x->left),height(x->right))+1;

    return x;
}

Node* insert(Node* node,int key){
    if(node==NULL) return newNode(key);
    if(key<node->key)
        node->left=insert(node->left,key);
    else if(key>node->key)
        node->right=insert(node->right,key);
    else return node;///neglect same value in BST

    node->height=1+max(height(node->left),height(node->right));
    int balance=getBalance(node);

    if(balance>1 and key<node->left->key){
        return rightRotate(node);
    }
    if(balance>1 and key>node->left->key){
        node->left=leftRotate(node->left);
        return rightRotate(node);
    }
    if(balance<-1 and key>node->right->key){
        return leftRotate(node);
    }
    if(balance<-1 and key<node->right->key){
        node->right=rightRotate(node->right);
        return leftRotate(node);
    }
    return node;///if balanced
}

Node *minValueNode(Node *node){
    Node *current=node;
    while(current->left!=NULL) current=current->left;

    return current;
}

///deleting node with specified key

Node *deleteNode(Node *node,int key){
    if(node==NULL) return node;
    if(node->key>key){
        node->left=deleteNode(node->left,key);
    }
    else if(key>node->key){
        node->right=deleteNode(node->right,key);
    }
    else{
        if(node->left==NULL or node->right==NULL){
            Node *temp=node->left? node->left:node->right;
            if(temp==NULL){
                temp=node;
                node=NULL;
            }
            else{
                *node=*temp;
            }
            free(temp);
        }
        else{
            Node *temp=minValueNode(node->right);
            node->key=temp->key;
            node->right=deleteNode(node->right,temp->key);
        }
    }

    if(node==NULL){
        return node;
    }
    node->height=1+max(height(node->left),height(node->right));
    int balance=getBalance(node);
    if(balance>1 and getBalance(node->left)>=0){
        return rightRotate(node);
    }
    if(balance>1 and getBalance(node->left)<0){
        node->left=leftRotate(node->left);
        return rightRotate(node);
    }
    if(balance<-1 and getBalance(node->right)<=0){
        return leftRotate(node);
    }
    if(balance<-1 and getBalance(node->right)>0){
        node->right=rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void preorder(Node *node){
    if(node!=NULL) {
        cout << node->key << " ";
        preorder(node->left);
        preorder(node->right);
    }
}

int main()
{
    //FI;FO;
    FastIO;

    Node *root = NULL;

    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);

    preorder(root);
    cout<<endl;


    int q; cin>>q;

    while(q--){
        int x; cin>>x;
        root=insert(root,x);
        int y; cin>>y;
        root=deleteNode(root,y);
        preorder(root);
        cout<<endl;
    }

    return 0;
}
