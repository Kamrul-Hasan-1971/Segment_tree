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
    tree[node] = tree[left] + tree[right] ;
}

ll query( int node, int start, int endd, int range1, int range2 )
{
    if( range1 > endd || range2 < start )
        return 0 ;
    if( start >= range1  && endd <= range2 )
        return tree[node] ;

    int left = node * 2 ;
    int right = ( node * 2 )+ 1 ;
    int mid = ( start + endd ) / 2 ;
    ll ret1 = query( left, start, mid, range1, range2 ) ;
    ll ret2 = query( right, mid+1, endd, range1, range2 ) ;
    return ret1+ret2 ;
}

void update( int node, int start, int endd, int indx, ll newValue)
{
    if( indx > endd  || indx < start )
        return ;
    if( start == endd)
    {
        printf("%lld\n",tree[node]);
        tree[node] = newValue ;
        return ;
    }
    int left = node * 2 ;
    int right = ( node * 2 ) + 1 ;
    int mid = ( start + endd ) / 2 ;
    update( left, start, mid, indx,  newValue ) ;
    update( right, mid+1, endd, indx, newValue ) ;
    tree[node] = tree[left] + tree[right] ;
}

void update2( int node, int start, int endd, int indx, ll newValue)
{
    if( indx > endd  || indx < start )
        return ;
    if( start == endd)
    {
        tree[node] += newValue ;
        return ;
    }
    int left = node * 2 ;
    int right = ( node * 2 ) + 1 ;
    int mid = ( start + endd ) / 2 ;
    update2( left, start, mid, indx,  newValue ) ;
    update2( right, mid+1, endd, indx, newValue ) ;
    tree[node] = tree[left] + tree[right] ;
}

int main()
{
    ll i, n, j,inp,T,I,J, q,op, money ;

    scanf("%lld",&T);
    for( j = 1 ; j <= T ; j++)
    {
        printf("Case %lld:\n",j);
        scanf("%lld%lld", &n, &q ) ;
        for( i = 1 ; i <= n ; i++ )
        {
            scanf("%lld",&ara[i]) ;
        }
        MakeTree( 1, 1, n ) ;

        for( i = 1 ; i <= q ; i++ )
        {
            scanf("%lld",&op);
            if( op == 1 )
            {
                scanf("%lld",&inp);
                inp++;
                update(1, 1, n, inp, 0 ) ;
            }
            else if( op == 2 )
            {
                scanf("%lld%lld",&inp,&money);
                inp++;
                update2(1, 1, n, inp, money ) ;
            }
            else
            {
                scanf("%lld%lld",&I,&J);
                I++;
                J++;
                printf("%lld\n",query(1, 1, n, I, J ));
            }
        }
    }
    return 0 ;
}
//http://www.lightoj.com/volume_showproblem.php?problem=1112
