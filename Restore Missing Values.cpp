#include<bits/stdc++.h>
using namespace std;
#define           ll                 long long int
#define           MX                 100005
#define           inf                0x3f3f3f3f
#define           zero(a)            memset(a,0,sizeof a)


int tree[MX*4], ara[MX], lazy[MX*4],ara2[MX];
vector<int>v[100005];

void build_tree( int node, int a, int b )
{
    if( a > b )
        return ;
    if( a == b )
    {
        tree[node] = ara[a] ;
        return ;
    }
    int left = node << 1 ;
    int right = ( node << 1 ) + 1 ;
    int mid = ( a + b ) >> 1 ;

    build_tree( left, a, mid ) ;
    build_tree( right, mid+1, b ) ;
}

void query_tree( int node, int a, int b)
{
    int left = node << 1 ;
    int right = ( node << 1)+ 1 ;
    int mid = ( a + b ) >> 1 ;
    if( lazy[node]!=0)
    {
        tree[node]=lazy[node];
        if(a!=b)
        {
            lazy[left] = lazy[node];
            lazy[right] = lazy[node];
        }
        lazy[node]=0;
    }
    if( a > b )
        return  ;
    if(a==b)
    {
        ara[a]=tree[node];return ;
    }
    query_tree(left, a, mid) ;
    query_tree(right, mid+1, b) ;
}

void update_tree( int node, int a, int b, int i, int j,ll newValue)
{
    int left = node << 1 ;
    int right = ( node << 1)+ 1 ;
    int mid = ( a + b ) >> 1 ;
    if( lazy[node] != 0 )
    {
        tree[node] = lazy[node];
        if( a!=b )
        {
            lazy[left] = lazy[node];
            lazy[right] = lazy[node];
        }
        lazy[node]=0;
    }
    if( a > b || a > j || b < i )
        return ;
    if( a>=i && b <=j )
    {
        tree[node]=newValue;
        if(a!=b)
        {
            lazy[left] = newValue ;
            lazy[right] = newValue ;
        }
        return ;
    }
    update_tree( left, a, mid, i, j, newValue ) ;
    update_tree( right, mid+1, b, i, j, newValue ) ;
}

int main()
{
    int T, n, q ,j ,i;
    scanf("%d",&T);
    for( j = 1 ; j <= T ; j++)
    {
        scanf("%d%d",&n,&q);
        for(i=1; i<=n; i++){
            scanf("%d",&ara[i]);
            ara2[i]=ara[i];
            v[ara[i]].push_back(i);
        }

        build_tree(1,1,n);
        memset(lazy,0,sizeof(lazy));

        for( i = 1 ; i <= q ; i++)
        {
            if(v[i].size()){
            update_tree(1,1,n,v[i][0],v[i].back(),i);}
        }

        query_tree(1,1,n);
        ll chk=0,chk2=1;
        for( i = 1 ; i <= n ; i++)
        {
            if(ara2[i]!=0)
            {
                if(ara[i]!=ara2[i])
                {
                    chk=1;
                    break;
                }
            }
            if(ara[i]==q)
            {
                chk2=0;
            }
        }
        if(chk2==1 && v[0].size())
        {
            ara[v[0].back()]=q;
            chk2=0;
        }
        if(v[0].size()==n)
        {
            printf("Case %d: YES\n",j);
            for( i = 1 ; i <= n-1 ; i++)
            {
                if(ara[i]==0)ara[i]=1;
                printf("%d ",ara[i]);
            }
            printf("%d\n",q);
        }
        else if(chk==0 && chk2==0 )
        {
            printf("Case %d: YES\n",j);
            for( i = 1 ; i <= n ; i++)
            {
                if(ara[i]==0)ara[i]=1;
                printf("%d ",ara[i]);
            }
            printf("\n");
        }
        else
        {
            printf("Case %d: NO\n",j);
        }
        for( i = 0 ; i <= q ; i++ )
            v[i].clear();
    }
    return 0;
}
//https://toph.co/p/restore-missing-values
