//FCFS disk scheduling
#include<stdio.h>
#include<math.h>
int seektime(int arr[],int current,int tp){
	int i,j;
	int ans=0;
	for(i=0;i<tp;i++){
		ans += abs(arr[i]-current);
		current=arr[i];
	}
	return ans;
}
int main(){
	int n;
	printf("Enter the number of tracks: ");
	scanf("%d",&n);
	int current;
	printf("Enter the current track: ");
	scanf("%d",&current);
	int tp;
	printf("Enter the tracks in current process: ");
	scanf("%d",&tp);
	int arr[tp];
	printf("Enter the sequence of tracks: ");
	int i;
	for(i=0;i<tp;i++){
		scanf("%d",&arr[i]);
	}
	int ans=seektime(arr,current,tp);
	printf("the total seek time is %d ",ans);
	return 0;
}

