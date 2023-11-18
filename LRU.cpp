//LRU
#include<iostream>
#include <unordered_set>
#include <unordered_map>
#include<limits.h>

using namespace std;
int LRU(int pages[],int pn,int frame){
	unordered_set<int> s;
	unordered_map<int,int> index;
	int pagefault=0;
	int val;
	for(int i=0;i<pn;i++){
		if(s.size()<frame){
			if(s.find(pages[i]) == s.end()){
				s.insert(pages[i]);
				pagefault++;
			}
			index[pages[i]]=i;
		}	
		else{
			if(s.find(pages[i])==s.end()){
				int LR = INT_MAX;
				//find page with least recently used
				for(auto it=s.begin();it!=s.end();it++){
					if(index[*it] < LR){
						LR = index[*it];
						val = *it;
					}
				}
				//remove least recently used
				s.erase(val);
				//insert
				s.insert(pages[i]);
				pagefault++;
			}
			index[pages[i]]=i;
		}
	}
	return pagefault;
}
int main(){
	int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
	int pn = sizeof(pages)/sizeof(pages[0]);
	int frame = 4;
	int ans = LRU(pages,pn,frame);
	cout<<"page fault: "<<ans;
}

