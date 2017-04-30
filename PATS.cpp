#include<iostream>
#include<vector>
#include<bits/stdc++.h>
#include<math.h>
#include<string>
using namespace std;
int adj[1000][1000];
int eft[1000][50];
int est[1000][50];
int aft[1000];
vector <int> parent[1000];
int m_proce[1000];
vector <vector < pair <int ,int> > > g(1000);
 int timep [1001][1001];
 int n,proces;
vector<int>priority;

bool vis[100];

int check()
{
    for(int i=0;i<100;i++)
    {
        vis[i]=false;
    }
}
void bfs(int n)
{    check();
    priority.push_back(n);
     vis[n]=true;
queue<int>q;
 q.push(n);
 //priority[n]=0;
 while(!q.empty())
 {
     int p=q.front();
     q.pop();
     for(int i=0;i<g[p].size();i++)
     {
         if(vis[g[p][i].first]==false)
         {
             priority.push_back(g[p][i].first);
          //   priority[v[p][i]]=priority[p]+1;
             q.push(g[p][i].first);
             vis[g[p][i].first]=true;
         }
     }
 }
}


class proces_slot
{
	public:
		int start_time;
		int end_time;
		int task_no;

};
vector <proces_slot> p_scheduler[100];
int EST(int i, int j)
{
	int comm;
	int par;
	int max_time;
	int temp = 0;;

	max_time = 0;

	for (int k = 0; k < parent[i].size(); k++) {
		par = parent[i][k];
		if(m_proce[par] >= j) {
			temp = aft[par];
		}

		else {
			temp = adj[par][i] + aft[par];
		}

		max_time = max(max_time, temp);
	}
    //
//cout<<"est "<<i<<" "<<j<<" "<<max_time<<endl;
	return max_time;

}

int EFT(int i, int j)
{
    //cout<<"EFT "<<i<<" "<<j<<endl;
		int start_time;
		if(p_scheduler[j].empty()) {
			return est[i][j] + timep[i][j];
		}
		int ok;
		int endtime;
		ok = 1;
		for (int timer = est[i][j]; 1; timer++) {
			ok = 1;
			endtime = timer + timep[i][j];
			for (int k = 0; k < p_scheduler[j].size(); k++) {
				if((timer < p_scheduler[j][k].start_time and endtime > p_scheduler[j][k].start_time) or (timer < p_scheduler[j][k].end_time and (endtime > p_scheduler[j][k].end_time or timer>=p_scheduler[j][k].start_time)) ) {
					ok = 0;
					break;
				}
			}
			if(ok == 1) {
                    //cout<<"eft "<<i<<" "<<j<<" "<<endtime<<endl;
				return endtime;
			}

		}
}

void pats()
{
	int mini;
	mini = INT_MAX;
	int t;
	int mini_eft;
	int length = -1;

	proces_slot temp;
	proces_slot temp2;
	t = priority[0];

	for (int i = 1; i <= proces; i++) {
		est[priority[0]][i] = 0;
		if(mini > timep[t][i]) {
                cout<<i<<" "<<timep[t][i]<<endl;
			mini = timep[t][i];
			m_proce[t] = i;
		}

	}

	temp.start_time = 0;
	temp.end_time = mini;
	temp.task_no = t;

	p_scheduler[m_proce[t]].push_back(temp);

	aft[priority[0]] = mini;
	int i;
	for (int h = 1; h < n; h++) {
		i = priority[h];

		for (int j = 1; j <= proces; j++) {
			est[i][j] = EST(i, j);

		}

		mini_eft = INT_MAX;
		int proces_no = 1;

		for (int j = 1; j <= proces; j++) {
			eft[i][j] = EFT(i, j);
			if(eft[i][j] < mini_eft) {
				mini_eft = eft[i][j];
				proces_no = j;
			}
		}

		m_proce[i] = proces_no;

		temp2.start_time = mini_eft - timep[i][proces_no];
		temp2.end_time = mini_eft;
		aft[i] = mini_eft;
		temp2.task_no = i;
		length = max(mini_eft, length);

		p_scheduler[proces_no].push_back(temp2);

	}

	for (int i = 1; i <= proces; i++) {
		for (int j = 0; j < p_scheduler[i].size(); j++) {
			cout << " task => " << p_scheduler[i][j].task_no << "start time " << p_scheduler[i][j].start_time <<"  "<<p_scheduler[i][j].end_time<<endl;
		}
		cout << endl;

	}

	cout <<"Makespan:"   <<(length) << endl;
}


int main(){

     freopen("input3.txt","r",stdin);
     freopen("output3.txt","w",stdout);
    //cout<<"enter the no of task and Process and relation";
    cin>>n>>proces;
    int no_of_relation;
    //cin>>"Enter the no of relation";
    cin >> no_of_relation;
    int x ,y, z ;
    while(no_of_relation--){
        cin>>x>>y>>z; //x,y edges and z length
        if(x==y)continue;
         parent[y].push_back(x);
        adj[x][y]=z;
        g[x].push_back(make_pair(y,z));
    }
    //cout<<"enter the all edge relation";
    for(int i=1;i<n+1;i++){
        for(int j =1;j<=proces ;j++){
            cin>>timep[i][j];
        }
    }

    bfs(1);
    cout<<"Priority Order:"  <<endl;
    for(int i=0;i<priority.size();i++){
        cout<<priority[i]<<" ";
    }
    pats();
}


/*
10 3 15
1 2 18
1 3 12
1 4 9
1 5 11
1 6 14
2 8 19
2 9 16
3 7 23
4 8 27
4 9 23
5 9 13
6 8 15
7 10 17
8 10 11
9 10 13


14 16 9
13 19 18
11 13 19
13 8 17
12 13 10
13 16 9
7 15 11
5 11 14
18 12 20
21 7 16

*/

























