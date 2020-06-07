#include<bits/stdc++.h>
using namespace std;
#define           ll                 int
#define           MX                 100005
#define           all(v)             v.begin(),v.end()

pair<int,int>ara[MX+3];
vector<int>tree[4*MX+1];
int ans[MX];
void built_tree( int node, int a, int b )
{
    if( a == b )
    {
        tree[node].push_back(ara[a].second) ;
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
    if( a==b ) return tree[node][0];
    int left = node << 1 ;
    int right = ( node << 1)+ 1 ;
    int mid = ( a + b ) / 2 ;
    int last_in_range = upper_bound(all(tree[left]),j)-tree[left].begin();
    int first_in_range = lower_bound(all(tree[left]),i)-tree[left].begin();
    int m = last_in_range-first_in_range;
    if(m>=key) return query_tree( left, a, mid, i, j, key) ;
    else return query_tree( right, mid+1, b, i, j,key-m) ;
}

int main()
{

    int i, n, j,inp,a,b,m,k;
    scanf("%d%d",&n,&m) ;
    for( i = 1 ; i <= n ; i++ )
    {
        scanf("%d",&ara[i].first);
        ara[i].second=i;
        ans[i]=ara[i].first;
    }
    sort(ara+1,ara+n+1);
    built_tree( 1, 1, n ) ;
    for( j = 1 ; j <= m ; j++)
    {
        scanf("%d%d%d",&a,&b,&k);
        int x = query_tree(1,1,n,a,b,k);
        printf("%d\n",ans[x]);
    }
    return 0 ;
}
//https://www.spoj.com/problems/MKTHNUM/
