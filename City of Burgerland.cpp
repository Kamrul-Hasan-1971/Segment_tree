#include<bits/stdc++.h>
using namespace std;
#define           ll                 unsigned long long int
#define           MX                 100005
#define           all(v)             v.begin(),v.end()

ll ara[MX+3];
vector<ll>tree[4*MX+1],sum[4*MX+1];

void merge_tree(ll node, ll left, ll right )
{
    ll i = 0, j = 0 ;

    while( i < tree[left].size() && j < tree[right].size())
    {
        if( tree[left][i] <= tree[right][j])
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
    sum[node].emplace_back(tree[node][0]);
    for( j = 1 ; j < tree[node].size() ; j++)
    {
        sum[node].emplace_back(sum[node].back()+tree[node][j]);
    }
}

void built_tree( ll node, ll a, ll b )
{
    if( a == b )
    {
        tree[node].emplace_back(ara[a]) ;
        sum[node].emplace_back(ara[a]);
        return ;
    }
    ll left = node << 1 ;
    ll right = ( node << 1)+ 1 ;
    ll mid = ( a + b ) / 2 ;

    built_tree( left, a, mid ) ;
    built_tree( right, mid+1, b ) ;
    merge_tree(node,left,right);
}

ll query_tree( ll node, ll a, ll b, ll i, ll j,ll key)
{
    if( a>b || i > b || j < a )
        return 0 ;
    if( a >= i  && b <= j )
    {
        int x = upper_bound(all(tree[node]),key)-tree[node].begin();
        if(x==0) return 0 ;
        return (x*key)-sum[node][x-1];
    }

    ll left = node << 1 ;
    ll right = ( node << 1)+ 1 ;
    ll mid = ( a + b ) / 2 ;
    ll ret1 = query_tree( left, a, mid, i, j, key) ;
    ll ret2 = query_tree( right, mid+1, b, i, j,key) ;
    return ret1+ret2 ;
}


int main()
{

    ll i, n, j,inp,a,b,m,k;
    scanf("%lld%lld", &n,&m ) ;
    for( i = 1 ; i <= n ; i++ )
    {
        scanf("%lld",&ara[i]);
    }

    built_tree( 1, 1, n ) ;

    for( j = 1 ; j <= m ; j++)
    {
        scanf("%lld%lld%lld",&a,&b,&k);
        ll x = query_tree(1,1,n,a,b,k);
        printf("%lld\n",x);
    }
    return 0 ;
}
//https://toph.co/p/city-of-burgerland
