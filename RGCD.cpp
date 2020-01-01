#include<bits/stdc++.h>
using namespace std;
#define           ll                 long long int
#define           MX                 10004
#define           zero(a)            memset(a,0,sizeof a)
#define           gcd(a, b)          __gcd(a,b)


ll tree[MX*4], ara[MX], lazy[MX*4];

void build_tree( int node, int a, int b ) //node=current node, a-b=current range
{
    if( a > b )
        return ; //out of range
    if( a == b ) //Leaf node
    {
        tree[node] = ara[a] ; //initialize value
        return ;
    }
    ll left = node << 1 ;
    ll right = ( node << 1 ) + 1 ;
    ll mid = ( a + b ) >> 1 ;

    build_tree( left, a, mid ) ;
    build_tree( right, mid+1, b ) ;
    tree[node] = gcd(tree[left] , tree[right]);
}

ll query_tree( ll node, ll a, ll b, ll i, ll j )
{
    ll left = node << 1 ;
    ll right = ( node << 1)+ 1 ;
    ll mid = ( a + b ) >> 1 ;
    if( lazy[node]!=1)
    {
        tree[node]*=lazy[node]; // Update it

        if(a!=b) //not leaf node.mark it's child as lazy
        {
            lazy[left] *= lazy[node]; //mark child as lazy
            lazy[right] *= lazy[node]; //mark child as lazy
        }
        lazy[node]=1; // Reset it
    }
    if( a > b || a > j || b < i )
        return 0 ; // Out of range
    if(a>=i && b <= j)
        return tree[node];

    ll q1 = query_tree(left, a, mid, i, j ) ;
    ll q2 = query_tree(right, mid+1, b, i, j ) ;
    return gcd(q1,q2) ; // Return final result
}

void update_tree( ll node, ll a, ll b, ll i, ll j,ll newValue)
{
    ll left = node << 1 ;
    ll right = ( node << 1)+ 1 ;
    ll mid = ( a + b ) >> 1 ;
    if( lazy[node] != 1 )  //This node needs to be updated
    {
        tree[node] *= lazy[node] ; //update it
        if( a!=b )
        {
            lazy[left] *= lazy[node]; //mark child as lazy
            lazy[right] *= lazy[node]; //mark child as lazy
        }
        lazy[node]=1; //Reset it
    }
    if( a > b || a > j || b < i )
        return ; //current segment is not within range
    if( a>=i && b <=j )
    {
        tree[node]*=newValue;
        if(a!=b)// Not leaf node
        {
            lazy[left] *= newValue ;
            lazy[right] *= newValue ;
        }
        return ;
    }
    update_tree( left, a, mid, i, j, newValue ) ;
    update_tree( right, mid+1, b, i, j, newValue ) ;
    tree[node]=gcd(tree[left],tree[right]);
}

int main()
{
    ll n, T, q ,type ,l , r , i , mul ;
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld",&n,&q);
        for(int i=1; i<=n; i++)
            scanf("%lld",&ara[i]);
        for( i = 1 ; i < 40003 ;i++) lazy[i]=1;
        build_tree(1,1,n);
        for( i = 1 ; i <= q ; i++ )
        {
            scanf("%lld",&type);
            if(type==1)
            {
                scanf("%lld%lld",&l,&r);
                printf("%lld\n",query_tree(1,1,n,l+1,r+1));
            }
            else{
                scanf("%lld%lld%lld",&l,&r,&mul);
                update_tree(1,1,n,l+1,r+1,mul);
            }
        }
    }
    return 0;
}
//https://www.codechef.com/problems/RGCD
