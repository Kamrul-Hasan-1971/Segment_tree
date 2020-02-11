#include<bits/stdc++.h>
using namespace std;
#define           ll                 long long int
#define           MX                 100010
#define           inf                0x3f3f3f3f
#define           zero(a)            memset(a,0,sizeof a)
#define           output             freopen("output.txt","wt", stdout)


ll tree[MX*3], ara[MX], lazy[MX*3];

ll query_tree( int node, int a, int b, int i, int j )
{
    int left = node << 1 ;
    int right = ( node << 1)+ 1 ;
    int mid = ( a + b ) >> 1 ;
    if( lazy[node]!=0)
    {
        tree[node]+=((b-a+1)*lazy[node]); // Update it
        if(a!=b) //not leaf node.mark it's child as lazy
        {
            lazy[left] += lazy[node]; //mark child as lazy
            lazy[right] += lazy[node]; //mark child as lazy
        }
        lazy[node]=0; // Reset it
    }
    if( a > b || a > j || b < i )
        return 0 ; // Out of range
    if(a>=i && b <= j)
        return tree[node];

    ll q1 = query_tree(left, a, mid, i, j ) ;
    ll q2 = query_tree(right, mid+1, b, i, j ) ;
    return q1+q2 ; // Return final result
}

void update_tree( int node, int a, int b, int i, int j,ll newValue)
{
    int left = node << 1 ;
    int right = ( node << 1)+ 1 ;
    int mid = ( a + b ) >> 1 ;
    if( lazy[node] != 0 )  //This node needs to be updated
    {
        tree[node] += ((b-a+1)*lazy[node]) ; //update it
        if( a!=b )
        {
            lazy[left] += lazy[node]; //mark child as lazy
            lazy[right] += lazy[node]; //mark child as lazy
        }
        lazy[node]=0; //Reset it
    }
    if( a > b || a > j || b < i )
        return ; //current segment is not within range
    if( a>=i && b <=j )
    {
        tree[node]+=((b-a+1)*newValue);
        if(a!=b)// Not leaf node
        {
            lazy[left] += newValue ;
            lazy[right] += newValue ;
        }
        return ;
    }
    update_tree( left, a, mid, i, j, newValue ) ;
    update_tree( right, mid+1, b, i, j, newValue ) ;
    tree[node]=tree[left]+tree[right];
}

int main()
{
    ll  a,i,j,T,N=100000;
    for( i = 2 ; i <= N ; i++ )
    {
        for( j = i ; j <= N ; j+= i )
        {
            ll x = i*j ;
            ll y = (i*(j+1));
            if(y>N) y = N+1 ;
            x++;
            y--;
            if(x>y) break;
            update_tree(1,1,N,x,y,1);
        }
    }
    for( i = 1 ; i <= N ; i++ )
    {
        ara[i]=query_tree(1,1,N,i,i);
    }
    scanf("%lld",&T);
    for( i = 0 ; i < T ; i++ )
    {
        scanf("%lld",&a);
        printf("Query %lld: %lld\n",i+1,ara[a]);
    }
    return 0;
}
//https://toph.co/p/welcome-to-criterion-rounds
