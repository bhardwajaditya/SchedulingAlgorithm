#include<stdio.h>
#include"edf.h"
 
void get_tasks(task *t1,int n,int at[],int bt[],int p[])
{
	int i=0;
	while(i<n)
	{
	printf("Enter Task %d parameters\n",i+1);
	printf("Arrival time: ");
	scanf("%d",&t1->T[arrival]);
	printf("Execution time: ");
	scanf("%d",&t1->T[execution]);
	printf("Deadline time: ");
	scanf("%d",&t1->T[deadline]);
	printf("Period: ");
	scanf("%d",&t1->T[period]);
	t1->T[abs_arrival]=0;
	t1->T[execution_copy]=0;
	t1->T[abs_deadline]=0;
	t1->instance =0;
	t1->alive = 0;
 p[i]=i;
 at[i]=t1->T[arrival];
 bt[i]=t1->T[execution];
	t1++;
	i++;
 
	}
}
 
int hyperperiod_calc(task *t1,int n)
{
	int i=0,ht,a[10];
	while(i<n)
 
		{
		a[i]=t1->T[period];
		t1++;
		i++;
		}
	ht=lcm(a,n);
 
	return ht;
}
 
int gcd(int a, int b)
{
 if (b == 0)
	 return a;
 else
 return gcd(b, a%b);
}
 
int lcm(int *a, int n)
{
 int res = 1, i;
 for (i = 0; i < n; i++)
 {
 res = res*a[i]/gcd(res, a[i]);
 }
 return res;
}
 
 
 
int sp_interrupt(task *t1,int tmr,int n)
{
int i=0,n1=0,a=0;
task *t1_copy;
t1_copy=t1;
	while(i<n)
	{
		if(tmr == t1->T[abs_arrival])
			{
			t1->alive = 1;
			a++;
			}
		t1++;
		i++;
	}
 
	t1 =t1_copy;
	i=0;
 
	while(i<n)
	{
		if(t1->alive==0)
			n1++;
			t1++;
			i++;
	}
 
	if(n1==n || a!=0)
	{
		return 1;
	}
 
	return 0;
}
 
void update_abs_deadline(task *t1,int n,int all)
{
int i=0;
		if(all)
		{
			while(i<n)
			{
				t1->T[abs_deadline] = t1->T[deadline] + t1->T[abs_arrival];
				t1++;
				i++;
			}
		}
		else
		{
		t1+=n;
		t1->T[abs_deadline] = t1->T[deadline] + t1->T[abs_arrival];
		}
 
}
 
void update_abs_arrival(task *t1,int n,int k,int all)
{
int i=0;
		if(all)
		{
			while(i<n)
			{
				t1->T[abs_arrival] = t1->T[arrival] + k*(t1->T[period]);
				t1++;
				i++;
			}
		}
		else
		{
		t1+=n;
		t1->T[abs_arrival] = t1->T[arrival] + k* (t1->T[period]);
		}
 
}
 
void copy_execution_time(task *t1,int n,int all)
{
	int i=0;
	if(all)
	{
		while(i<n)
		{
			t1->T[execution_copy] = t1->T[execution];
			t1++;
			i++;
		}
	}
	else
	{
		t1+=n;
		t1->T[execution_copy] = t1->T[execution];
	}
}
 
 
int min(task *t1,int n,int p)
{
	int i=0,min=0x7FFF,task_id=IDLE_TASK_ID;
	while(i<n)
	{
		if(min>t1->T[p] && t1->alive==1)
		{
			min=t1->T[p];
			task_id=i;
		}
		t1++;
		i++;
	}
	return task_id;
}
 
 
float cpu_util(task *t1,int n)
{
	int i=0;
	float cu=0;
	while(i<n)
	{
		cu = cu + (float)t1->T[execution]/(float)t1->T[deadline];
		t1++;
		i++;
	}
	return cu;
 
}
 
 void sjf(int n,int p[],int at[],int bt[])
{
 int wt[20],tat[20],i,j,total=0,pos,temp,att[10],time=0,lag=0,flag[]={1,1,1,1,1,1},ctt=0,tot_tat=0,tot_wt=0,ct[10];
 float avg_wt,avg_tat;
	for(i=0;i<n;i++)
 {
 pos=i;
 for(j=i+1;j<n;j++)
 {
 if(bt[j]<bt[pos])
 pos=j;
 }
 
 temp=bt[i];
 bt[i]=bt[pos];
 bt[pos]=temp;
 
 temp=p[i];
 p[i]=p[pos];
 p[pos]=temp;
 
 temp=at[i];
 at[i]=at[pos];
 at[pos]=temp;
 }
 	for(i=0;i<n;i++)
 att[i]=at[i];
 for(i=0;i<n;i++)
 {
 for(j=i+1;j<n;j++)
 {
 if(att[i]>att[j])
 {
 temp=att[i];
 att[i]=att[j];
 att[j]=temp;
 }
 }
 }
 	if(att[0]==at[0])
 {
 time=at[0];
 while(time!=0)
 {
 lag=lag+1;
 time=time-1;
 }
 ct[0]=lag+bt[0];
 flag[0]=0;
 for(i=0;i<n;i=j)
 {
 for(j=1;j<n;j++)
 {
 if(flag[j]!=0)
 {
 if(at[j]<ct[i])
 {
 ct[j]=ct[i]+bt[j];
 flag[j]=0;
 break;
 }
 }
 }
 }
 }
 else
 {
 	
 for(i=1;i<n;i++)
 {
 if(att[0]==at[i])
 {
 time=at[i];
 while(time!=0)
 {
 lag=lag+1;
 time=time-1;
 }
 ct[i]=lag+bt[i];
 flag[i]=0;
 ctt=ct[i];
 break;
 }
 }
 
 if(at[0]>ctt)
 {
			for(i=1;i<n;i++)
 	{
 		if(at[i]<ctt && flag[i]==1)
 		{
 			ct[i]=ctt+bt[i];
 			flag[i]=0;
 			ctt=ct[i];
 			break;
				}
			}
			printf("%d\n",ctt);
			ct[0]=ctt+bt[0];
			flag[0]=0;
			printf("%d\n",ct[0]);
		}	
 else
		{
			ct[0]=ctt+bt[0];
 	 flag[0]=0;
 }
		for(i=0;i<n;i=j)
 {
 for(j=i+1;j<n;j++)
 {
 if(flag[j]!=0)
 {
 if(at[j]<ct[i])
 {
 ct[j]=ct[i]+bt[j];
 flag[j]=0;
 break;
 }
 }
 }
 }
 } 
 for(i=0;i<n;i++)
 {
 tat[i]=ct[i]-at[i];
 tot_tat+=tat[i];
 wt[i]=tat[i]-bt[i];
 tot_wt+=wt[i];
 }
 avg_tat=(float)tot_tat/(float)n;
 avg_wt=(float)tot_wt/(float)n;
 printf("Process AT\tBT\tCT\tTAT\tWT\n");
 for(i=0;i<n;i++)
 {
 printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i],at[i],bt[i],ct[i],tat[i],wt[i]);
 }
 printf("Average turn-around time:- %.2f\n",avg_tat);
 printf("Average waiting time:- %.2f\n",avg_wt);
	
}
