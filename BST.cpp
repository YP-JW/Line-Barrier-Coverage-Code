#include<bits/stdc++.h>
using namespace std;
int n,flag=0,flag1=0;
double L,r;
const int maxn=500005;
double x[maxn],y[maxn],l1[maxn],g1[maxn];
double D1=DBL_MAX,D2=DBL_MIN; 
vector<int>mi;
vector<double>mx;
struct LL
{
	int num;
	double li;
}Li[maxn];
bool cmp(LL a,LL b)
{
	return a.li<b.li;
}
struct Node{
	double gi;
	int i;
	bool operator < (const Node& x) const{
	return gi>x.gi;
	}
}Gi;
priority_queue<Node> que;
void clearque(){
	priority_queue<Node> empty;
	swap(empty,que);
}
void in_put()
{
	int i;
	cin>>n;
	for(i=1;i<=n;i++)
		cin>>x[i]>>y[i];
	cin>>r;
	cin>>L;
	return ;
}
bool algorithm1(double d)
{
	clearque();
	int i,k=1,j,a=0;
	double ll,s=0;
	for(i=1;i<=n;i++)
	{
		l1[i]=0;g1[i]=0; 
		if(fabs(y[i])>d)
			l1[i]=-DBL_MAX;
		else
		{
			l1[i]=x[i]-sqrt(d*d-y[i]*y[i])-r;
			g1[i]=x[i]+sqrt((d*d-y[i]*y[i]))+r;
		}
		Li[i].num=i;
		Li[i].li=l1[i];
	}
	sort(Li+1,Li+n+1,cmp);
	while(s<L)
	{
		for(i=k;i<=n;i++)
		{
			if(Li[i].li<=s)
			{
				k++;
				j=Li[i].num;
				Gi.gi=g1[j];
				Gi.i=j;
				if(Gi.gi>s)
				que.push(Gi); 
			}
			else
				break;
		}
		while(que.size()!=0)
		{
			Gi=que.top();
			j=Gi.i;
			if(Gi.gi<s)
				que.pop();
			else
			break;
		}
		if(que.size()!=0)
		{
			Gi=que.top();
			j=Gi.i;
			s=min(s+2*r,Gi.gi);
			if(flag==1)
			{
				mx.push_back(s-r);
				mi.push_back(j);
			}
			que.pop();
		}
		else
		{
			if(k>n)
			break;
			j=Li[k].num;
			ll=Li[k].li;
			s=ll+2*r;
			if(flag==1)
			{
				mx.push_back(s-r);
				mi.push_back(j);
			}
			a=1;
			k++;
		}
	}
	if(flag1==1)
	{
		for(i=0;i<mx.size();i++)
		cout<<"("<<mi[i]<<" ,"<<mx[i]<<")"<<" ";
		cout<<endl;
	}
	if(a==1||s<L)
		return false;
	else
		return true;
}
int main()
{
	srand((unsigned)time(NULL));
	double d;
	int temp,i;
	char tmp[100];
	freopen("1.BST_result.txt","w",stdout);
	sprintf(tmp,"input.txt",temp);
	freopen(tmp,"r",stdin);
	in_put();
	//freopen(tmp,"w",stdout);
	flag=0;flag1=0;
	D1=DBL_MAX,D2=DBL_MIN;
	mx.clear();mi.clear();
	clock_t start,finish;
	start=clock(); 
	long double left=0,right=1e+100,mid,lr;
	double k;
	lr=right-left;
	while(lr>1e-10)
	{
		mid=(left+right)/2;
		if(algorithm1(mid))
		{
			k=mid;
			right=mid;
		}
		else
		{
			left=mid;
		}
		lr=right-left;
	}
	finish=clock();
	printf("t=%.5lf D=",(double)(finish-start)/CLOCKS_PER_SEC);
	printf("%.5lf\n",k);
	flag1=1;flag=1;
	algorithm1(k);
	fclose(stdout);
	return 0;
}
