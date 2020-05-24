#include<bits/stdc++.h>
using namespace std;
#define  ll       int
#define  MX       1000005
#define  CIN            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
string s1 ;
struct Node{
    int o,c,l;
};
Node tree[MX*3];
Node combine( Node L , Node R )
{
    int p = min(L.o,R.c);
    Node x;
    x.o = L.o+R.o-p;
    x.c = L.c+R.c-p;
    x.l = L.l+R.l+p ;
    return  x;
}

void built_tree( int node , int a , int b )
{
    if( a == b )
    {
        tree[node].o = (s1[a-1]=='(') ;
        tree[node].c = (s1[a-1]==')') ;
        tree[node].l = 0 ;
        return ;
    }
    int left = node << 1 ;
    int right = ( node << 1)+ 1 ;
    int mid = ( a + b ) / 2 ;

    built_tree( left , a , mid ) ;
    built_tree( right , mid+1 , b ) ;
    tree[node] = combine(tree[left] , tree[right] );
}

Node query_tree( int node , int a , int b , int i , int j )
{
    if( i > b || j < a ) return {0,0,0} ;
    if( a >= i  && b <= j ) return tree[node] ;

    int left = node << 1 ;
    int right = ( node << 1)+ 1 ;
    int mid = ( a + b ) / 2 ;
    Node ret1 = query_tree( left , a , mid , i , j ) ;
    Node ret2 = query_tree( right , mid+1 , b , i , j ) ;
    return combine(ret1,ret2);
}
int main()
{
    CIN;
    ll i , n , j ,p,q;
    cin >> s1 >> n;
    ll x = s1.size();
    built_tree(1,1,x);
    for( i = 1 ; i<= n ; i++)
    {
        cin>> p>>q ;
        cout<<2*query_tree(1,1,x,p,q).l<<endl;
    }
    return 0 ;
}
//https://codeforces.com/problemset/problem/380/C
