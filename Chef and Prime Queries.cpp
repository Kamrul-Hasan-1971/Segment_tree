#include<bits/stdc++.h>
using namespace std;
#define           ll                 int
#define           MX                 100005
#define           all(v)             v.begin(),v.end()
#define           pii                pair<int,int>

int ara[MX+3];
vector<pii>tree[3*MX+1],vec[1000006];

bool mark[1000006];
vector<int>prime,sum[3*MX+1];

vector<pii> factorize(int x)
{
    vector<pii>v;
    for(int i=2; i*i<=x; i++)
        if(x%i==0)
        {
            int cnt = 0 ;
            while(x%i==0)
            {
                x/=i;
                cnt++;
            }
            v.emplace_back(pii(i,cnt));
        }
    if(x>1)
        v.emplace_back(pii(x,1));
    return v;
}

struct comp_pair_int
{
    bool operator()(const pair<int,int> &a, const int & b)
    {
        return (a.first < b);
    }
    bool operator()(const ll & a,const pair<int,int> &b)
    {
        return (a < b.first);
    }
};

void merge_tree(ll node, ll left, ll right )
{
    ll i = 0, j = 0 ;

    while( i < tree[left].size() && j < tree[right].size())
    {
        if( tree[left][i].first <= tree[right][j].first)
        {
            tree[node].emplace_back(tree[left][i]);
            i++;
        }
        else
        {
            tree[node].emplace_back(tree[right][j]);
            j++;
        }
    }
    for( ; i < tree[left].size() ; i++ )
    {
        tree[node].emplace_back(tree[left][i]);
    }
    for( ; j < tree[right].size() ; j++ )
    {
        tree[node].emplace_back(tree[right][j]);
    }
    sum[node].emplace_back(tree[node][0].second);
    for( j = 1 ; j < tree[node].size() ; j++)
    {
        sum[node].emplace_back(sum[node].back()+tree[node][j].second);
    }
}

void built_tree( ll node, ll a, ll b )
{
    if( a == b )
    {
        tree[node]=factorize(ara[a]);
        sum[node].emplace_back(tree[node][0].second);
        for( int j = 1 ; j < tree[node].size() ; j++){
            sum[node].emplace_back(tree[node][j].second+sum[node].back()) ;
        }
        return ;
    }
    ll left = node << 1 ;
    ll right = ( node << 1)+ 1 ;
    ll mid = ( a + b ) / 2 ;

    built_tree( left, a, mid ) ;
    built_tree( right, mid+1, b ) ;
    merge_tree(node,left,right);
}

ll query_tree( ll node, ll a, ll b, ll i, ll j,ll start, ll endd)
{
    if( a>b || i > b || j < a )
        return 0 ;
    if( a >= i  && b <= j )
    {
        int x = lower_bound(all(tree[node]),start,comp_pair_int())-tree[node].begin();
        int y = upper_bound(all(tree[node]),endd,comp_pair_int())-tree[node].begin();
        if(y==0) return 0;
        y--;
        int sm = sum[node][y];
        if(x!=0){
            sm -= sum[node][x-1];
        }
        return sm;
    }

    ll left = node << 1 ;
    ll right = ( node << 1)+ 1 ;
    ll mid = ( a + b ) / 2 ;
    ll ret1 = query_tree( left, a, mid, i, j, start, endd) ;
    ll ret2 = query_tree( right, mid+1, b, i, j,start,endd) ;
    return ret1+ret2 ;
}


int main()
{
    int i, n, j,inp,a,b,L,R,X,Y,m,k,q;
    scanf("%d", &n) ;
    for( i = 1 ; i <= n ; i++ )
    {
        scanf("%d",&ara[i]);
    }
    scanf("%d",&q);
    built_tree( 1, 1, n ) ;

    for( j = 1 ; j <= q ; j++)
    {
        scanf("%d%d%d%d",&L,&R,&X,&Y);
        ll x = query_tree(1,1,n,L,R,X,Y);
        printf("%d\n",x);
    }
    return 0 ;
}
//https://www.codechef.com/problems/PRMQ
