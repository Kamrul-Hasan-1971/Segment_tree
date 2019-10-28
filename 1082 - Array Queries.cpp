#include<bits/stdc++.h>
using namespace std;
#define           ll                 long long int
#define           MX                 100005

ll tree[MX*3],ara[MX+3];

void MakeTree( int node, int start, int endd )
{
    if( start == endd )
    {
        tree[node] = ara[start] ;
        return ;
    }
    int left = node * 2 ;
    int right = ( node * 2 ) + 1 ;
    int mid = ( start + endd ) / 2 ;

    MakeTree( left, start, mid ) ;
    MakeTree( right, mid+1, endd ) ;
    tree[node] = min (tree[left], tree[right] ) ;
}

ll query( int node, int start, int endd, int range1, int range2 )
{
    if( range1 > endd || range2 < start )
        return 1000000 ;
    if( start >= range1  && endd <= range2 )
        return tree[node] ;

    int left = node * 2 ;
    int right = ( node * 2 )+ 1 ;
    int mid = ( start + endd ) / 2 ;
    ll ret1 = query( left, start, mid, range1, range2 ) ;
    ll ret2 = query( right, mid+1, endd, range1, range2 ) ;
    return min(ret1,ret2) ;
}

int main()
{
    ll i, n, j,inp,N ,T ,I ,J , q;

    scanf("%lld",&T);
    for( j = 1 ; j <= T ; j++)
    {
        scanf("%lld%lld", &N , &q ) ;
        for( i = 1 ; i <= N ; i++ )
        {
            scanf("%lld",&ara[i]) ;
        }
        printf("Case %lld:\n",j);
        MakeTree( 1 , 1 , N );
        for( i = 1 ; i <= q ; i++ )
        {
            scanf("%lld%lld",&I, &J);
            printf("%lld\n",query(1 , 1 , N , I , J ));
        }
    }
    return 0 ;
}
//http://www.lightoj.com/volume_showproblem.php?problem=1082
