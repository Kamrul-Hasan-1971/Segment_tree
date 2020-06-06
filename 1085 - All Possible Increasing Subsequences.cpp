#include<bits/stdc++.h>
using namespace std;
#define           ll        long long int
#define           MX        100005
#define           mod       1000000007
#define           pii       pair<ll,ll>
ll tree[MX*3];
pii ara[MX+3];
ll query_tree( int node, int a, int b, int i, int j )
{
    if( i > b || j < a )
        return 0 ;
    if( a >= i  && b <= j ) return tree[node] ;
    int left = node << 1 ;
    int right = ( node << 1)+ 1 ;
    int mid = ( a + b ) / 2 ;
    ll ret1 = query_tree( left, a, mid, i, j ) ;
    ll ret2 = query_tree( right, mid+1, b, i, j ) ;
    return (ret1+ret2)%mod ;
}

void update_tree( int node, int a, int b, int indx, ll newValue)
{
    if( indx > b  || indx < a )
        return ;
    if( a == b)
    {
        tree[node] = newValue ;
        return ;
    }
    int left = node << 1 ;
    int right = ( node << 1)+ 1 ;
    int mid = ( a + b ) / 2 ;
    update_tree( left, a, mid, indx,  newValue ) ;
    update_tree( right, mid+1, b, indx, newValue ) ;
    tree[node] = (tree[left] + tree[right])%mod ;
}

int main()
{
    ll i, n, j,inp,t;
    scanf("%lld",&t);
    for( j = 1 ; j<= t ; j++)
    {
        memset(tree,0,sizeof tree);
        scanf("%lld", &n ) ;
        for( i = 1 ; i <= n ; i++ )
        {
            scanf("%lld",&ara[i].first) ;
            ara[i].second=-i;
        }
        sort(ara+1,ara+n+1);
        for( i = 1 ; i <= n ; i++)
        {
            ll indx = -ara[i].second;
            ll cnt = query_tree(1,1,n,1,indx);
            update_tree(1,1,n,indx,cnt+1);
        }
        ll ans = query_tree(1,1,n,1,n);
        printf("Case %lld: %lld\n",j,ans);
    }
    return 0 ;
}
//http://lightoj.com/volume_showproblem.php?problem=1085
