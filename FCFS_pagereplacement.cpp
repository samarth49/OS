//FCFS page replacement algorithm
#include<stdio.h>
int main(){
	int pagefault=0,frames,pages;
	printf("Enter the number of pages: ");
	scanf("%d",&pages);
	printf("Enter the number of frames: ");
	scanf("%d",&frames);
	int memory[frames];
	int queue[frames];
	int i=0;
	for(i=0;i<frames;i++){
		memory[i]=-1;
		queue[i]=-1;
	}
	printf("Enter the sequence of page reference: ");
	for(i=0;i<pages;i++){
		int page;
		scanf("%d",&page);
		int found=0;
		int j;
		for(j=0;j<frames;j++){
			if(memory[j]==page){
				found=1;
				break;
			}
		}
		if(!found){
			int replacedPage = queue[0];
			memory[0]=page;
			//update the queue
			for(j=0;j<frames-1;j++){
				memory[j]=memory[j+1];
			}
			memory[frames-1]=page;
			pagefault++;
		}
		//display current state
		printf("Memory: ");
		for(j=0;j<frames;j++){
			if(memory[j]==-1){
				printf(" - ");
			}
			else{
				printf("%2d ",memory[j]);
			}
		}
		printf("\n");
	}
	printf("Total pageFaults is %d:  ",pagefault);
	return 0;
	
}
