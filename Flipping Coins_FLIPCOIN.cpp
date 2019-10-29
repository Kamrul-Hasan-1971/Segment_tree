#include<bits/stdc++.h>
using namespace std;
#define           ll                 long long int
#define           MX                 100005


ll tree[MX*3], lazy[MX*3];

void update_tree( int node, int a, int b, int i, int j)
{
    int left = node << 1 ;
    int right = ( node << 1 )+ 1 ;
    int mid = ( a + b ) / 2 ;
    if( lazy[node]== 1 )
    {
        tree[node] = (b-a+1)-tree[node] ;

        if( a!=b )
        {
            lazy[left]  ^= 1 ;
            lazy[right] ^= 1 ;
        }
        lazy[node]=0;
    }

    if( a > j || b < i )  return ;

    if( a >= i && b <= j )
    {
        tree[node]=(b-a+1)-tree[node];
        if(a!=b)
        {
            lazy[left] ^= 1 ;
            lazy[right] ^= 1 ;
        }
        return ;
    }
    update_tree( left, a, mid, i, j) ;
    update_tree( right, mid+1, b, i, j) ;

    tree[node]=tree[left]+tree[right];
}

ll query_tree( int node, int a, int b, int i, int j )
{
    int left = node << 1 ;
    int right = ( node << 1 )+ 1 ;
    int mid = ( a + b ) / 2 ;
    if( lazy[node]==1)
    {
        tree[node]=(b-a+1)-tree[node];
            if(a!=b)
            {
                lazy[left] ^= 1 ;
                lazy[right] ^= 1 ;
            }
            lazy[node]=0;
    }
    if( a > j || b < i ) return 0 ;
    if(a>=i && b <= j){
        return tree[node];
    }
    ll q1 = query_tree(left, a, mid, i, j ) ;
    ll q2 = query_tree(right, mid+1, b, i, j ) ;
    return q1+q2 ;
}

int main()
{
    ll M, N, S_i, E_i, v, i,op;

    scanf("%lld%lld",&N,&M);

    for(int j = 0 ; j < M ; j++ )
    {
        scanf("%lld%lld%lld",&op,&S_i,&E_i);
        if(op==0)
        {
            update_tree(1,0,N-1,S_i,E_i);
        }
        else
        {
            printf("%lld\n",query_tree(1,0,N-1,S_i,E_i));
        }
    }
    return 0;
}
//https://www.codechef.com/problems/FLIPCOIN
