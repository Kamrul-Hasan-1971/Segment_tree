#include<bits/stdc++.h>
using namespace std;
#define           ll                 long long int
#define           MX                 200005
#define           all(v)             v.begin(),v.end()

vector<ll>v1,v2;

ll tree[MX*3], lazy[MX*3];

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

void update_tree( int node, int a, int b, int i, int j,int newValue)
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
    ll n , q , i , inp , inp2 ;
    ll sum = 0;
    scanf("%lld%lld",&n, &q);
    for( i = 0 ; i < n ; i++)
    {
        scanf("%lld",&inp);
        v1.emplace_back(inp);
    }
    sort(all(v1));
    for( i = 0 ; i < q ; i++ )
    {
        scanf("%lld%lld",&inp,&inp2);
        update_tree(1,1,n,inp,inp2,1);
    }
    for( i = 1 ; i <= n ; i++)
    {
        ll x = query_tree(1,1,n,i,i);
        v2.emplace_back(x);
    }
    sort(all(v2));
    for( i = 0 ; i < n ; i++ )
    {
        sum += ( v1[i]*v2[i]);
    }
    printf("%lld\n",sum);
    return 0;
}
//https://codeforces.com/contest/276/problem/C
