#include<bits/stdc++.h>
using namespace std;
#define           ll               long long int
#define           zero(a)            memset(a,0,sizeof a)
#define           MX                100005
#define           output             freopen("output.txt","wt", stdout)

char ara[MX],cc[3];
ll tree[MX*3] , lazy[MX*3];
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
    ll T, n, q, i,left, right , j;
    char ch ;
    scanf("%lld",&T);
    for( i = 1 ; i <= T ; i++ )
    {
        zero(tree);
        zero(lazy);
        scanf("%s",ara);
        ll l = strlen(ara);
        scanf("%lld",&q);
        printf("Case %lld:\n",i);
        for( j = 1 ; j <= q ; j++ )
        {
            scanf("%s",cc);
            if(cc[0]=='I')
            {
                scanf("%lld%lld",&left,&right);
                update_tree(1,1,l,left,right,1);
            }
            else
            {
                scanf("%lld",&right);
                ll x = query_tree(1,1,l,right,right);
                ch = ara[right-1];
                if(x%2==1)
                {
                    if(ch=='0') ch = '1';
                    else ch = '0';
                }
                ll res = ch - '0';
                printf("%lld\n",res);
            }
        }
    }
    return 0 ;
}
//http://lightoj.com/volume_showproblem.php?problem=1080
