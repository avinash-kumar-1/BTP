#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;

int llength;
int len;
double avg[1000];
struct rank{
    int id;
    double val;
};
rank Rank[1000];
vector<int> adj[1000], pat[1000];
double dtc[1000];
double data[1000][1000];
double cost[1000][50];
double rate[50][50];
double comm[1000][1000];
double scheduler[1000][5];
double avl[50];
double est[50],eft[50];

void ACC(int n,int p)
{
    for(int i=0;i<n;i++)
    {
        double sm = 0;
        for(int j=0;j<p;j++) sm += cost[i][j];
        avg[i] = sm / double(p);
    }
}


void AVG_COMP(int task,int processor)
{
    for(int i=0;i<task;i++)
    {
        for(int j=0;j<adj[i].size();j++)
        {
            int v = adj[i][j];

            double t = 0.0;
            for(int x=0;x<processor;x++)
                for(int y=0;y<processor;y++)
            {
                if(x == y)continue;
                t += data[i][v] / rate[x][y];
            }
            comm[i][v] = t / (processor*processor-processor);
        }
    }
}
void RANK_CALCULATE(int n,int p)
{
    for(int i=0;i<n;i++)
    {
        Rank[i].id = i;
        Rank[i].val = 0.0;
    }
    for(int i=0;i<n;i++)
    {
        Rank[i].val = avg[i];
        double dtc = 0.0;
        for(int j=0;j<adj[i].size();j++)
        {
            int v = adj[i][j];
            dtc += comm[i][v];
        }
        double drc = 0.0;
        for(int j=0;j<pat[i].size();j++)
        {
            int v = pat[i][j];
            drc = max(drc , Rank[v].val);
        }
        Rank[i].val += (drc + dtc);
    }
}

double EST(int u,int p)
{
    if(pat[u].size() == 0)return avl[p];
    double t = 0;
    for(int i=0;i<pat[u].size();i++)
    {
        int v = pat[u][i];
        int q = scheduler[v][0];
        t =  max(t, scheduler[v][2] + data[v][u] / rate[q][p]);
    }
    return max(avl[p],t);
}
void PETS(int n,int p)
{   //len=-1;
    for(int i=0;i<p;i++)avl[i] = 0.0;
    for(int i=0;i<n;i++)
    {
        int u = Rank[i].id;
        for(int j=0;j<p;j++)
        {
            est[j] = EST(u,j);
            eft[j] = cost[u][j] + est[j];
        }
        int pj=0;
        for(int j=1;j<p;j++)
        {
            if(eft[j]<eft[pj])pj=j;
        }
        scheduler[u][0]=pj;
        scheduler[u][1]=est[pj];
        scheduler[u][2]=eft[pj];
        avl[pj]=eft[pj];
    }
}
bool compare(rank x, rank y)
{
    return x.val < y.val;
}
int main()
{
     freopen("input2.txt","r",stdin);
     freopen("output2.txt","w",stdout);

    int task, processor;
    cin >> task >> processor;
    int edges, w;
    cin >> edges;

    for(int i=0;i<task;i++)
        for(int j=0;j<task;j++)data[i][j]=0;
    while(edges --)
    {
        int x, y;
        if( x == y)continue;
        cin >> x >> y >> w;
        adj[x].push_back(y);
        pat[y].push_back(x);
        data[x][y]=w;
    }
    // input computation cost
    for(int i=0;i<task;i++)
    {
        for(int j=0;j<processor;j++)cin >> cost[i][j];
    }
    // input rate
    llength=77;
    for(int i=0;i<processor;i++)
        for(int j=0;j<processor;j++)cin >> rate[i][j];

    // ---------------------------------------------------------------------

    ACC(task, processor);
/*
    for(int i=0;i<task;i++) cout << avg[i]<<" ";
    cout<<endl; */

    AVG_COMP(task,processor);
/*
    for(int i=0;i<task;i++)
    {
        for(int j=0;j<adj[i].size();j++)
        {
            int v = adj[i][j];
            cout<<i<<" "<<v<<" "<<comm[i][v]<<endl;
        }
    }
    cout<<endl;
    */

    RANK_CALCULATE(task,processor);
    sort(Rank,Rank+task,compare);

    //for(int i=0;i<task;i++)cout<<Rank[i].id<<" ";
    cout<<endl;
    PETS(task,processor);
    //cout<<"ranks"<<" "<<endl;
    cout<<"scheduling on processors"<<endl;
    cout<<"task no. "<<"proc_no." <<" st_time "<<"end_time"<<endl;
    for(int i=0;i<task;i++)
    {
        int u = Rank[i].id;
        cout<< u << "       " << scheduler[u][0] << "          " << scheduler[u][1] << "       " << scheduler[u][2]<<endl;
    }
    //cout<<"makespan :  "<<llength<<endl;
    return 0;
}
