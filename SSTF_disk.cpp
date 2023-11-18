#include<stdio.h>
#include<math.h>
int main(){
	int i,current,arr[100],count=0,n,tp;
	printf("Enter the number of process: ");
	scanf("%d",&n);
	printf("Enter the sequence of processs: ");
	for(i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	printf("Enter the current position of head: ");
	scanf("%d",&current);
	while(count<n){
		int min=1000,diff,index;
		for(i=0;i<n;i++){
			diff = abs(arr[i] - current);
			if(min > diff){
				min=diff;
				index=i;
			}
		}
		tp+=min;
		current=arr[index];
		arr[index]=1000;
		count++;
	}
	printf("The total seek time is %d ",tp);
	
}
