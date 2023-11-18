//fcfs non preemptive 
#include<stdio.h>
#include<stdlib.h>
struct FCFS{
	int id;
	int arrival;
	int burst;
	int start;
	int end;
	int waiting;
	int turnaround;
};
int main(){
	int n;
	printf("\nEnter the numbr of process: ");
	scanf("%d",&n);
	struct FCFS p[n];
	int i,j;
	for(i=0;i<n;i++){
		p[i].id=i+1;
		printf("Enter the Arrival time of process %d: ",i+1);
		scanf("%d",&p[i].arrival);
		printf("Enter the burst time of process %d: ",i+1);
		scanf("%d",&p[i].burst);
	}
	
	//sort according to arrival time 
	for(i=0;i<n-1;i++){
		for(j=0;j<n-i-1;j++){
			if(p[j].arrival > p[j+1].arrival){
				struct FCFS temp = p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
			}
		}
	}
	int current=0;
	int avgwaiting =0;
	for(i=0;i<n;i++){
		if(p[i].arrival > current){
			current=p[i].arrival;
		}
		p[i].start=current;
		p[i].end=current + p[i].burst;
		p[i].waiting = current - p[i].arrival;
		avgwaiting += p[i].waiting;
		p[i].turnaround = p[i].waiting + p[i].burst;
		current = p[i].end;
	}
	
	//display result
	printf("Process\t Arrival Time\t Burst Time\t Waiting Time\t TurnAround Time\n");
	for(i=0;i<n;i++){
		printf("%d\t\t %d\t\t %d\t\t %d\t\t %d\n",p[i].id,p[i].arrival,p[i].burst,p[i].waiting,p[i].turnaround);
	}
	printf("\nAverage waiting time is %d",(avgwaiting/n));
	
	return 0;
}








