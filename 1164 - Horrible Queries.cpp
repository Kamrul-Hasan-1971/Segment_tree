#include<bits/stdc++.h>
using namespace std;
#define           ll                 long long int
#define           MX                 100005
#define           inf                0x3f3f3f3f
#define           zero(a)            memset(a,0,sizeof a)


ll tree[MX*3], ara[MX], lazy[MX*3];

void build_tree( int node, int a, int b ) //node=current node, a-b=current range
{
    if( a > b )
        return ; //out of range
    if( a == b ) //Leaf node
    {
        tree[node] = ara[a] ; //initialize value
        return ;
    }
    int left = node << 1 ;
    int right = ( node << 1 ) + 1 ;
    int mid = ( a + b ) / 2 ;

    build_tree( left, a, mid ) ;
    build_tree( right, mid+1, b ) ;
    tree[node] = tree[left] + tree[right];
}

ll query_tree( int node, int a, int b, int i, int j )
{
    if( lazy[node]!=0)
    {
        tree[node]+=((b-a+1)*lazy[node]); // Update it
        if(a!=b) //not leaf node.mark it's child as lazy
        {
            lazy[node<<1] += lazy[node]; //mark child as lazy
            lazy[(node<<1)+1]+=lazy[node]; //mark child as lazy
        }
        lazy[node]=0; // Reset it
    }
    if( a > b || a > j || b < i )
        return 0 ; // Out of range
    if(a>=i && b <= j)
        return tree[node];
    int left = node << 1 ;
    int right = ( node << 1)+ 1 ;
    int mid = ( a + b ) / 2 ;
    ll q1 = query_tree(left, a, mid, i, j ) ;
    ll q2 = query_tree(right, mid+1, b, i, j ) ;
    return q1+q2 ; // Return final result
}

void update_tree( int node, int a, int b, int i, int j,ll newValue)
{
    if( lazy[node] != 0 )  //This node needs to be updated
    {
        tree[node] += ((b-a+1)*lazy[node]) ; //update it
        if( a!=b )
        {
            lazy[node<<1] += lazy[node]; //mark child as lazy
            lazy[(node<<1)+1]+=lazy[node]; //mark child as lazy
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
            lazy[node<<1] += newValue ;
            lazy[(node<<1)+1] += newValue ;
        }
        return ;
    }
    int left = node << 1 ;
    int right = ( node << 1 )+ 1 ;
    int mid = ( a + b ) / 2 ;
    update_tree( left, a, mid, i, j, newValue ) ;
    update_tree( right, mid+1, b, i, j, newValue ) ;
    tree[node]=tree[left]+tree[right];
}


int main()
{
    ll T, N, C, p, q, v, i,op;
    scanf("%lld",&T);
    for( i = 0 ; i < T ; i++)
    {
        printf("Case %lld:\n",i+1);
        zero(lazy);
        zero(tree);
        scanf("%lld%lld",&N,&C);
        for(int j=1; j<=N; j++)
            ara[j]=0;
        build_tree(1,1,N);
        for(int j = 0 ; j < C ; j++ )
        {
            scanf("%lld",&op);
            if(op==0)
            {
                scanf("%lld%lld%lld",&p,&q,&v);
                p++,q++;
                update_tree(1,1,N,p,q,v);
            }
            else
            {
                scanf("%lld%lld",&p,&q);
                p++,q++;
                printf("%lld\n",query_tree(1,1,N,p,q));
            }
        }
    }
    return 0;
}
//http://lightoj.com/volume_showproblem.php?problem=1164

