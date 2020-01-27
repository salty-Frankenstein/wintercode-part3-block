#include<iostream>
#include<fstream>
using namespace std;

int main(){
	int num = 10*5;
	ofstream out("1.blk");
	out<<num<<endl;
	for(int i =1;i<=10;i++){
		for(int j=1; j<=5;j++)
			out<<10+i*30<<' '<<10+j*60<<' '<<(i^j)%4+1<<endl;
	}
	
	return 0;
}
