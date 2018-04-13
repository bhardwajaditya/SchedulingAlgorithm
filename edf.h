#define arrival			0
#define execution 		1
#define deadline		2
#define period			3
#define abs_arrival		4
#define execution_copy 5
#define abs_deadline	6
 
//stucture of a task
typedef struct
{
	int T[7],instance,alive;
 
}task;
 
#define IDLE_TASK_ID 1023 
#define ALL 1
#define CURRENT 0
 
void get_tasks(task *t1,int n,int at[],int bt[],int p[]);
int hyperperiod_calc(task *t1,int n);
float cpu_util(task *t1,int n);
int gcd(int a, int b);
int lcm(int *a, int n);
int sp_interrupt(task *t1,int tmr,int n);
int min(task *t1,int n,int p);
void update_abs_arrival(task *t1,int n,int k,int all);
void update_abs_deadline(task *t1,int n,int all);	
void copy_execution_time(task *t1,int n,int all);
