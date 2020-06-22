#include<bits/stdc++.h>
using namespace std;
#define           ll        int
#define           MX        1000005

ll tree[MX*3],res[MX];
pair<int,int> ara[MX+3];
void built_tree( int node, int a, int b )
{
    if( a == b )
    {
        tree[node] = 1 ;
        return ;
    }
    int left = node << 1 ;
    int right = ( node << 1)+ 1 ;
    int mid = ( a + b ) / 2 ;
    built_tree( left, a, mid ) ;
    built_tree( right, mid+1, b ) ;
    tree[node] = tree[left] + tree[right] ;
}

ll query_tree( int node, int a, int b, int x)
{
    if(tree[node]<x) return -1;
    if(a==b) return a;
    int left = node << 1 ;
    int right = ( node << 1)+ 1 ;
    int mid = ( a + b ) / 2 ;
    if(tree[left]>=x) return query_tree( left, a, mid, x) ;
    else return query_tree( right, mid+1, b, x-tree[left]) ;
}

void update_tree( int node, int a, int b, int indx, ll newValue)
{
    if( indx > b  || indx < a ) return ;
    if( a == b)
    {
        tree[node] = newValue ;
        return ;
    }
    int left = node << 1 ;
    int right = ( node << 1)+ 1 ;
    int mid = ( a + b ) / 2 ;
    update_tree( left, a, mid, indx,  newValue ) ;
    update_tree( right, mid+1, b, indx, newValue ) ;
    tree[node] = tree[left] + tree[right] ;
}

int main()
{
    ll i, n, j,inp, T,tc=0;
    scanf("%d",&T);
    for(tc=1; tc<=T; tc++)
    {
        int chk=0;
        scanf("%d", &n ) ;
        built_tree(1,1,n);
        for( i = 1 ; i <= n ; i++ ) scanf("%d%d",&ara[i].first,&ara[i].second);
        sort(ara+1,ara+n+1);
        for( i = 1 ; i<= n ; i++)
        {
            int x = ara[i].first , y = ara[i].second+1;
            int z = query_tree(1,1,n,y);
            if(z==-1) {chk=1;break;}
            update_tree(1,1,n,z,0);
            res[z]=x;
        }
        if(chk) printf("Case %d: No ordering possible!\n",tc);
        else{
            printf("Case %d:",tc);
            for( i = 1 ; i<=n ; i++) printf(" %d",res[i]);
            printf("\n");
        }
    }
    return 0 ;
}
//https://toph.co/p/maintain-the-queue
