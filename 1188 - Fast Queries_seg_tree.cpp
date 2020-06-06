#include<bits/stdc++.h>
using namespace std;
#define           ll        int
#define           MX        100002

ll tree[MX*3],ara[MX+3];
ll query_tree( int node , int a , int b , int i , int j )
{
    if( i > b || j < a ) return 0 ;
    if( a >= i  && b <= j ) return tree[node] ;

    int left = node << 1 ;
    int right = ( node << 1)+ 1 ;
    int mid = ( a + b ) / 2 ;
    ll ret1 = query_tree( left , a , mid , i , j ) ;
    ll ret2 = query_tree( right , mid+1 , b , i , j ) ;
    return ret1+ret2 ;
}

void update_tree( int node , int a , int b , int indx , ll newValue)
{
    if( indx > b  || indx < a ) return ;
    if( a == b) {
        tree[node] = newValue ;
        return ;
    }
    int left = node << 1 ;
    int right = ( node << 1)+ 1 ;
    int mid = ( a + b ) / 2 ;
    update_tree( left , a , mid , indx ,  newValue ) ;
    update_tree( right , mid+1 , b , indx , newValue ) ;
    tree[node] = tree[left] + tree[right] ;
}
int main()
{
    ll  a,b,n,q,i,j,T,k;
    scanf("%d",&T);
    for( i = 1 ; i <= T ; i++ )
    {
        scanf("%d%d",&n,&q);
        for( j = 1 ; j <= n ; j++) scanf("%d",&ara[j]);
        vector<ll>v[MX],indx[MX];
        ll ans[MX],last_indx[MX]={0};
        for( j = 1 ; j <= q ; j++)
        {
            scanf("%d%d",&a,&b);
            v[b].emplace_back(a);
            indx[b].emplace_back(j);
        }
        for( j = 1 ; j<= n ; j++)
        {
            if(last_indx[ara[j]]) update_tree(1,1,n,last_indx[ara[j]],0);
            update_tree(1,1,n,j,1);
            last_indx[ara[j]]=j;
            for( k = 0 ; k < v[j].size() ; k++)
                ans[indx[j][k]]= query_tree(1,1,n,v[j][k],j);
        }
        printf("Case %d:\n",i);
        for( j = 1 ; j<= q ; j++) printf("%d\n",ans[j]);
    }
    return 0 ;
}
//http://lightoj.com/volume_showproblem.php?problem=1188
