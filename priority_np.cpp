#include<stdio.h>
#include<stdlib.h>
struct priority{
	int id;
	int arrival;
	int burst;
	int waiting;
	int turnaround;
	int pro;
	
};
int main(){
	int i,j,n;
	int sum=0,k=1,min,bt=0,tat=0,mini;
	printf("Enter the number of process: ");
	scanf("%d",&n);
	struct priority p[n];
	for(i=0;i<n;i++){
		p[i].id=i+1;
		printf("Enter the arrival time of process %d:  ",i+1);
		scanf("%d",&p[i].arrival);
		printf("Enter the burst time of process %d : ",i+1);
		scanf("%d",&p[i].burst);
		printf("Enter the priority of process %d : ",i+1);
		scanf("%d",&p[i].pro);
	}
	//sort by arrival
	for(i=0;i<n;i++){
		for(j=0;j<n-i-1;j++){
			if(p[j].arrival > p[j+1].arrival){
				struct priority temp=p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
		}
	}
	for(i=0;i<n;i++){
		bt += p[i].burst;
		min = p[k].burst;
		mini = p[k].pro;
		for(j=k;j<n;j++){
			if(bt >= p[j].arrival && p[j].pro < mini){
				struct priority temp=p[k];
				p[k]=p[j];
				p[j]=temp;
			}
		}
		k++;
	}
	p[0].waiting=0;
	int total_waiting=0;
	int total_turnaround=0;
	for(i=1;i<n;i++){
		sum += p[i-1].burst;
		p[i].waiting = sum - p[i].arrival;
		total_waiting += p[i].waiting;
	}
	for(i=0;i<n;i++){
		tat += p[i].burst;
		p[i].turnaround = tat - p[i].arrival;
		total_turnaround += p[i].turnaround; 
	}
		printf("Process\t\tPriority\t\tBurst Time\t\tArrival Time\t\tWaiting Time\t\tTurn-Around Time\n");

	for(i=0;i<n;i++)
	{

		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].id,p[i].pro,p[i].burst,p[i].arrival,p[i].waiting,p[i].turnaround);
	}
}
