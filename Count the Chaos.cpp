#include<bits/stdc++.h>
using namespace std;
#define           ll                 long long int
#define           MX                 100005
#define           all(v)             v.begin(),v.end()

int ara[MX+3];
vector<int>tree[4*MX+1];

void built_tree( int node, int a, int b )
{
    if( a == b )
    {
        tree[node].push_back(ara[a]) ;
        return ;
    }
    int left = node << 1 ;
    int right = ( node << 1)+ 1 ;
    int mid = ( a + b ) / 2 ;

    built_tree( left, a, mid ) ;
    built_tree( right, mid+1, b ) ;
    merge(all(tree[left]),all(tree[right]),back_inserter(tree[node]));
}

ll query_tree( int node, int a, int b, int i, int j,int key)
{
    if( i > b || j < a )
        return 0 ;
    if( a >= i  && b <= j )
    {
        int x = upper_bound(all(tree[node]),key)-tree[node].begin();
        return x;
    }

    int left = node << 1 ;
    int right = ( node << 1)+ 1 ;
    int mid = ( a + b ) / 2 ;
    ll ret1 = query_tree( left, a, mid, i, j, key) ;
    ll ret2 = query_tree( right, mid+1, b, i, j,key) ;
    return ret1+ret2 ;
}

int main()
{

    int i, n, j,inp,a,b,m,k;
    long long int res=0;
    scanf("%d", &n ) ;
    for( i = 1 ; i <= n ; i++ )
    {
        scanf("%d",&ara[i]);
    }
    built_tree( 1, 1, n ) ;
    for( j = 1 ; j < n ; j++)
    {
        res += query_tree(1,1,n,j+1,n,ara[j]);
    }
    printf("%lld\n",res);
    return 0 ;
}
https://toph.co/p/count-the-chaos
