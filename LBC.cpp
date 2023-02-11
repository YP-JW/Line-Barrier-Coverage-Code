#include<bits/stdc++.h>
using namespace std;
int n,flag=0,flag1=0,c;
long long int acount=0,acount1=0;
long long int M=0; 
double L,r;
const int maxn=400000;
double x[maxn],y[maxn],l1[maxn],g1[maxn],l2[maxn],g2[maxn];
double D1=DBL_MAX,D2=DBL_MIN; 
vector<int>mi,S; 
vector<double>mx,v;
vector<double>Dd;
struct LL
{
	int num;
	double li;
}Li[maxn];
bool cmp(LL a,LL b)
{
	return a.li<b.li;
}
struct LR
{
	long long int l1,r1;
	long long int l2,r2;
	long long int mij; 
}L1[maxn];
struct DD
{
	double Di;
	int ID;
}D[maxn];
bool cmp1(DD a,DD b)
{
	return a.Di<b.Di;
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
	c=5*n;
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
void fl(int k)
{
	int h;
	double d,b;
	h=D[k].ID;
	//cout<<L1[h].l1<<" "<<L1[h].r1<<" ";
	if(L1[h].l1<=L1[h].r1)
	{
		b=(L1[h].l1+L1[h].r1)/2*r/c;
		d=sqrt((x[h]-b)*(x[h]-b)+y[h]*y[h]);
	}
	else
	{
		d=0;
		L1[h].mij=0;
		acount++;
	}
	//cout<<d<<" "<<D[k].ID<<endl;
	D[k].Di=d;
	return ;
}
void fr(int k)
{
	int h;
	double d,b;
	h=D[k].ID;
	//cout<<L1[h].l1<<" "<<L1[h].r1<<" ";
	if(L1[h].l2<=L1[h].r2)
	{
		b=(L1[h].l2+L1[h].r2)/2*r/c;
		d=sqrt((x[h]-b)*(x[h]-b)+y[h]*y[h]);
	}
	else
	{
		d=0;
		L1[h].mij=0; 
		acount++;
	}
	//cout<<d<<" "<<D[k].ID<<endl;
	D[k].Di=d;
	return ;
}
int findmid()
{
	int i,h;
	double Mij=0;
	for(i=acount+1;i<=n;i++)
	{
		h=D[i].ID;
		Mij=Mij+L1[h].mij;
		if(Mij>=M/2)
		break;
	}
	return i;
}
void cal_D1()
{
	int i,h;
	double di;
	acount=0;acount1=0,M=0;
	for(i=1;i<=n;i++)
	{
		L1[i].l1=0;
		L1[i].r1=x[i]*c/r;
		if(L1[i].r1>=L1[i].l1)
		L1[i].mij=L1[i].r1-L1[i].l1+1;
		else
		L1[i].mij=0;
		M=M+L1[i].mij;
		D[i].ID=i;
		fl(i);
	}
	sort(D+1,D+n+1,cmp1);
	acount1=acount;
	while(M!=0)
	{
		int mid=findmid();
		di=D[mid].Di;
		h=D[mid].ID;
		if(algorithm1(di+1e-8))
		{
			D1=min(D1,di);
			for(i=mid;i<=n;i++)
			{
				h=D[i].ID;
				L1[h].l1=(L1[h].l1+L1[h].r1)/2+1;
				M=M-(L1[h].mij-(L1[h].r1-L1[h].l1+1));
				L1[h].mij=L1[h].r1-L1[h].l1+1;
				fl(i);
			}
		}
		else
		{
			D2=max(D2,di);
			for(i=acount+1;i<=mid;i++)
			{
				h=D[i].ID;
				L1[h].r1=(L1[h].l1+L1[h].r1)/2-1;
				M=M-(L1[h].mij-(L1[h].r1-L1[h].l1+1));
				L1[h].mij=L1[h].r1-L1[h].l1+1;
				fl(i);
			}
		}
		sort(D+acount1+1,D+n+1,cmp1);
		acount1=acount;
	}
	acount=0;acount1=0,M=0;
	for(i=1;i<=n;i++)
	{
		L1[i].l2=x[i]*c/r+1;
		L1[i].r2=L*c/r;
		if(L1[i].r2>=L1[i].l2)
		L1[i].mij=L1[i].r2-L1[i].l2+1;
		else
		L1[i].mij=0;
		M=M+L1[i].mij;
		D[i].ID=i;
		fr(i);
	}
	sort(D+1,D+n+1,cmp1);
	acount1=acount;
	while(M!=0)
	{
		int mid=findmid();
		di=D[mid].Di;
		h=D[mid].ID;
		if(algorithm1(di+1e-8))
		{
			//cout<<"Y"<<endl;
			D1=min(D1,di);
			for(i=mid;i<=n;i++)
			{
				h=D[i].ID;
				L1[h].r2=(L1[h].l2+L1[h].r2)/2-1;
				M=M-(L1[h].mij-(L1[h].r2-L1[h].l2+1));
				L1[h].mij=L1[h].r2-L1[h].l2+1;
				fr(i);
			}
		}
		else
		{
			//cout<<"N"<<endl;
			D2=max(D2,di);
			for(i=acount+1;i<=mid;i++)
			{
				h=D[i].ID;
				L1[h].l2=(L1[h].l2+L1[h].r2)/2+1;
				M=M-(L1[h].mij-(L1[h].r2-L1[h].l2+1));
				L1[h].mij=L1[h].r2-L1[h].l2+1;
				fr(i);
			}
		}
		sort(D+acount1+1,D+n+1,cmp1);
		acount1=acount;
	} 
	for(i=1;i<=n;i++)
	{
		D[i].Di=abs(y[i]);
	}
	sort(D,D+n+1,cmp1);
	int left=1,right=n;
	while(left<=right)
	{
		int mid=(left+right)/2;
		di=D[mid].Di;
		if(algorithm1(di+1e-8))
		{
			D1=min(D1,di);
			right=mid-1;
		}
		else
		{
			D2=max(D2,di);
			left=mid+1;
		}
	 } 
	return ;
}
struct LG
{
	int i;
	int point;
 };
vector<LG> arr[100000];
void cal_D2()
{
	int i,j,t1,t2,t=0,m;
	double q1,q3; 
	double q2,di;
	S.clear();
	LG lg;
	lg.i=0;lg.point=0;
	for(i=1;i<=n;i++)
	{
		l2[i]=x[i]-sqrt(D1*D1-y[i]*y[i])-r;
		g2[i]=x[i]+sqrt((D1*D1-y[i]*y[i]))+r;
		g1[i]=x[i]+sqrt((D2*D2-y[i]*y[i]))+r;
		l1[i]=x[i]-sqrt((D2*D2-y[i]*y[i]))-r;
		if(l1[i]>=0||g1[i]<=L)
		{
			S.push_back(i);
			m=ceil((l1[i]/(2*r)-floor(l1[i]/(2*r)))/(2*r)*c); 
			lg.i=i;lg.point=1;
			arr[m].push_back(lg);
			m=ceil((l2[i]/(2*r)-floor(l2[i]/(2*r)))/(2*r)*c); 
			lg.i=i;lg.point=1;
			arr[m].push_back(lg);
			m=ceil((g1[i]/(2*r)-floor(g1[i]/(2*r)))/(2*r)*c); 
			lg.i=i;lg.point=2;
			arr[m].push_back(lg);
			m=ceil((g2[i]/(2*r)-floor(g2[i]/(2*r)))/(2*r)*c); 
			lg.i=i;lg.point=2;
			arr[m].push_back(lg);
		}
		
	}
	m=ceil(c/2/r);
	Dd.push_back(D1);
	for(t=0;t<=m+1;t++)
	{
		for(i=0;i<arr[t].size();i++)
	{
		
		t1=arr[t][i].i;
		for(j=0;j<arr[t].size();j++)
		{
			t2=arr[t][j].i;
			q3=floor((l1[t2]-g1[t1])/(2*r));
				//cout<<l2[t2]<<" "<<g2[t1]<<" "<<q1<<" "<<q2<<" "<<q3<<endl;
				if(l1[t2]>=g1[t1])
				{
					//cout<<"q1="<<q1<<" q3="<<q3<<endl;
					di=sqrt((x[t2]-x[t1]-2*r-2*r*q3)*(x[t2]-x[t1]-2*r-2*r*q3)/4+(y[t2]*y[t2]-y[t1]*y[t1])*(y[t2]*y[t2]-y[t1]*y[t1])/(4*(x[t2]-x[t1]-2*r-2*r*q3)*(x[t2]-x[t1]-2*r-2*r*q3))+(y[t2]*y[t2]+y[t1]*y[t1])/2);
					//cout<<di<<" ";
					if(di<D1&&di>D2)
					Dd.push_back(di);
				}
		}
	}
	arr[t].clear();
	}
	
	for(i=0;i<S.size();i++)
	{
		j=S[i];
		q1=ceil(l2[j]/(2*r));q3=floor(l1[j]/(2*r));
		if(q1==q3)
		{
			//cout<<x[j]<<" "<<y[j]<<" "<<q1<<" "<<q3<<endl;
			di=sqrt((x[j]-q3*2*r-r)*(x[j]-q3*2*r-r)+y[j]*y[j]);
			if(di<D1&&di>D2)
			Dd.push_back(di);
		}
		q1=ceil((L-g2[j])/(2*r));q3=floor((L-g1[j])/(2*r));
		if(q1==q3)
		{
			//cout<<x[j]<<" "<<y[j]<<" "<<q1<<" "<<q3<<endl;
			di=sqrt((x[j]-(L-q3*2*r-r))*(x[j]-(L-q3*2*r-r))+y[j]*y[j]);
			if(di<D1&&di>D2)
			Dd.push_back(di);
		}
	}
	return;
}
void cal_D3()
{
	int left=0,right=Dd.size()-1,mid;
	int i;
	double dh;
	sort(Dd.begin(),Dd.end());
//	for(i=0;i<Dd.size();i++)
//	printf("%.8lf\n",Dd[i]);
	while(left<=right)
	{
		mid=(left+right)/2;
		dh=Dd[mid];
		if(algorithm1(dh+1e-8))
		{
			D1=min(D1,dh);
			right=mid-1;
		}
		else
		left=mid+1;
	}
	return;
}
int main()
{
	srand((unsigned)time(NULL));
	double d;
	int temp,i;
	char tmp[100];
	freopen("3.LBC_result.txt","w",stdout);
	sprintf(tmp,"input.txt",temp);
	freopen(tmp,"r",stdin);
	in_put();
	//freopen(tmp,"w",stdout);
	flag=0;flag1=0;
	D1=DBL_MAX,D2=DBL_MIN;
	mx.clear();mi.clear();v.clear();Dd.clear();acount=0,acount1=0;
	clock_t start,finish;
	start=clock();
	cal_D1();
	//printf("D2=%.15lf   D1=%.15lf\n",D1,D2);
	cal_D2();
	cal_D3();
	finish=clock();
	printf("t=%.5lf D=",(double)(finish-start)/CLOCKS_PER_SEC);
	printf("%.5lf\n",D1);
	mi.clear(),mx.clear();
	flag1=1;flag=1;
	algorithm1(D1+1e-6);
	fclose(stdout);
	return 0;
}
