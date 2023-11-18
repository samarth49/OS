//optimal page replacement
#include <bits/stdc++.h>
using namespace std;
int predict(int pages[],vector<int>&fr,int pn,int index){
	int res =-1;
	int farthest=-1;
	int i,j;
	for(i=0;i<fr.size();i++){
		for(j=index;j<pn;j++){
			if(fr[i] == pages[j]){
				if(farthest > j){
					j=farthest;
					
				}
				res=i;
				break;
			}
		}
		if(j==pn){
			return i;
		}
	}
		(res == -1 ) ? 0 : res;
}
bool search(int key,vector<int>fr){
	int i;
	for(i=0;i<fr.size();i++){
		if(fr[i] == key)
			return true;
	}
	return false;
}
void optimal(int pages[],int pn,int fn){
	vector<int> fr;
	int hit = 0;
	int i,j;
	for(i=0;i<pn;i++){
		//page found hit ++s
		if(search(pages[i],fr)){
			hit++;
			continue;
		}
		//if page not found in frame
		if(fr.size() < fn){
			fr.push_back(pages[i]);
		}
		else{
			int j = predict(pages,fr,pn,i+1);
			fr[j]=pages[i];
		}
	}
	cout<<"Hits = "<<hit<<endl;
	cout<<"Page Fault = "<<pn-hit<<endl;
}
int main(){
	int pages[] = {1, 3, 0, 3, 5, 6, 3 };
	int pn = sizeof(pages)/sizeof(pages[0]);
	int fn = 3;
	optimal(pages,pn,fn);
}
