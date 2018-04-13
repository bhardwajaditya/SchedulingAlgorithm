#include<stdio.h>
#include"edf.h"
#include<stdlib.h>
 
 
int timer=0;
 
int main()
{
task *t;
int at[10],bt[10],p[10],i;
int n,hyper_period,active_task_id;
float cpu_utilization;
printf("Enter number of tasks\n");
scanf("%d",&n);
t=malloc(n*sizeof(task));
get_tasks(t,n,at,bt,p);
cpu_utilization = cpu_util(t,n);
printf("CPU Utilization %f\n",cpu_utilization);
 
		if(cpu_utilization<1){
				printf("Tasks can be scheduled\n");
 hyper_period=hyperperiod_calc(t,n);
copy_execution_time(t,n,ALL);
update_abs_arrival(t,n,0,ALL);
update_abs_deadline(t,n,ALL);
 
 
	while(timer<= hyper_period)
	 {
 
 
			 if(sp_interrupt(t,timer,n))
			 {
		 	 active_task_id = min(t,n,abs_deadline);
			 }
 
 
 
		 if(active_task_id==IDLE_TASK_ID)
		 {
		 printf("%d Idle\n", timer);
		 }
 
		 if(active_task_id!=IDLE_TASK_ID)
		 {
 
		 	 if(t[active_task_id].T[execution_copy]!=0)
		 	 	 {
		 	 	 t[active_task_id].T[execution_copy]--;
		 	 	 printf("%d Task %d\n", timer,active_task_id+1);
		 	 	 }
 
		 	 if(t[active_task_id].T[execution_copy]==0)
		 	 	{
		 	 	t[active_task_id].instance++;
		 	 	t[active_task_id].alive = 0;
		 	 	copy_execution_time(t,active_task_id,CURRENT);
		 	 	update_abs_arrival(t,active_task_id,t[active_task_id].instance,CURRENT);
		 	 	update_abs_deadline(t,active_task_id,CURRENT);
		 	 	active_task_id = min(t,n,abs_deadline);
 
		 	 	}
 
 
		 }
		 ++timer;
		 }
 }
			else{
				printf("Schedule is not feasible using earliest deadline first\n");
 
 printf("using sjf:\n");
 sjf(n,p,at,bt);
}
 
 
 
 
free(t);
return 0;
}
