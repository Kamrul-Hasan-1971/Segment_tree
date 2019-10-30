#include<bits/stdc++.h>
using namespace std;
#define           eb                 emplace_back
#define           zero(a)            memset(a,0,sizeof a)
#define           MX                 100004

vector<int>v1,v2,qury;
int sorted[MX*2] , tree[MX*6], lazy[MX*6];;
int n , q , indx ;
set<int>st;
set<int>::iterator it;

void initialize()
{
    zero(tree);
    zero(lazy);
    v1.clear();
    v2.clear();
    st.clear();
    qury.clear();
}
void compressdArray()
{
    int i = 0 ;
    while(i<n)
    {
        st.insert(v1[i]);
        st.insert(v2[i]);
        i++;
    }
    i=0;
    while( i < q) st.insert(qury[i++]);
    indx = 0 ;
    it = st.begin();
    while(it!=st.end()) sorted[indx++] = *it++;
}

int getCompressedValue(int val)
{
    return lower_bound(sorted,sorted+indx,val)-sorted;
}


void update_tree( int node, int a, int b, int i, int j,int newValue)
{
    int left = node << 1 ;
    int right = ( node << 1)+ 1 ;
    int mid = ( a + b ) >> 1 ;
    if( lazy[node] != 0 )  //This node needs to be updated
    {
        tree[node] +=((b-a+1)*lazy[node]) ; //update it
        if( a!=b )
        {
            lazy[left] += lazy[node]; //mark child as lazy
            lazy[right] += lazy[node]; //mark child as lazy
        }
        lazy[node]=0; //Reset it
    }
    if( a > b || a > j || b < i ) return ; //current segment is not within range
    if( a>=i && b <=j )
    {
        tree[node]+=(b-a+1)*newValue;
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

int query_tree( int node, int a, int b, int i, int j )
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
    if(a>=i && b <= j) return tree[node];
    int q1 = query_tree(left, a, mid, i, j ) ;
    int q2 = query_tree(right, mid+1, b, i, j ) ;
    return q1+q2 ; // Return final result
}

void calculateSeg()
{
    for( int i = 0 ; i < n ; i++ )
    {
        int x = getCompressedValue(v1[i]);
        int y = getCompressedValue(v2[i]);
        update_tree( 1 , 0 , indx-1 , x , y , 1 ) ;
    }
}

int main()
{
    int T , Ak , Bk , i , j , inp ;

    scanf("%d",&T);
    for( i = 1 ; i <= T ; i++ )
    {
        initialize();
        scanf("%d%d",&n,&q);

        for( j = 0 ; j < n ; j++)
        {
            scanf("%d%d",&Ak,&Bk);
            v1.eb(Ak);
            v2.eb(Bk);
        }
        for( j = 0 ; j < q ; j++)
        {
            scanf("%d",&inp);
            qury.eb(inp);
        }

        compressdArray();
        calculateSeg();
        printf("Case %d:\n",i);
        for( j = 0 ; j < q ; j++ )
        {
            int x = getCompressedValue(qury[j]);
            int res = query_tree( 1 , 0 , indx-1 , x , x ) ;
            printf("%d\n",res);
        }
    }
    return 0 ;
}

//http://lightoj.com/volume_showproblem.php?problem=1089
