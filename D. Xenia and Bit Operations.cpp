#include<bits/stdc++.h>
using namespace std;
#define           ll                 long long int
#define           MX        200005

struct node
{
    ll val , lvl ;
}tree[MX*3];
ll ara[MX+3];
void built_tree( int node , int a , int b )
{
    if( a == b )
    {
        tree[node].val = ara[a] ;
        tree[node].lvl = 0 ;
        return ;
    }
    int left = node << 1 ;
    int right = ( node << 1)+ 1 ;
    int mid = ( a + b ) / 2 ;
    built_tree( left , a , mid ) ;
    built_tree( right , mid+1 , b ) ;
    tree[node].lvl = tree[right].lvl+1;
    if( tree[node].lvl&1 ) tree[node].val = tree[left].val|tree[right].val;
    else tree[node].val = tree[left].val^tree[right].val;
}

void update_tree( int node , int a , int b , int indx , ll newValue)
{
    if( indx > b  || indx < a ) return ;
    if( a == b) {
        tree[node].val = newValue ;
        return ;
    }
    int left = node << 1 ;
    int right = ( node << 1)+ 1 ;
    int mid = ( a + b ) / 2 ;
    update_tree( left , a , mid , indx ,  newValue ) ;
    update_tree( right , mid+1 , b , indx , newValue ) ;
    if( tree[node].lvl&1 ) tree[node].val = tree[left].val|tree[right].val;
    else tree[node].val = tree[left].val^tree[right].val;
}

int main()
{
    ll i , n , j ,inp , m ,a,b;
    scanf("%lld%lld",&n, &m);
    n = (1<<n);
    for( i = 1 ; i <= n ; i++ )
    {
        scanf("%lld",&ara[i]);
    }
    built_tree(1,1,n);
    for( i = 1 ; i <= m ; i++ )
    {
        scanf("%lld%lld",&a,&b);
        update_tree(1,1,n,a,b);
        printf("%lld\n",tree[1].val);
    }
    return 0 ;
}
//https://codeforces.com/contest/339/problem/D
