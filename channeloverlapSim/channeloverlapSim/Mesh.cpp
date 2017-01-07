#include"Mesh.h"

using namespace std;

void Node::ClearIt(){
	for(vector<Link>::size_type d = 0; d < linkout.size(); d++){
		linkout[d].vc0Buf = 0;
		linkout[d].vc1Buf = 0;
		linkout[d].occupied = 0;
		linkout[d].fault = 0;
		linkout[d].BW = 0;
	}
}

void Node::ComputeLabel(int id, int n, int dim){
	for(int i = 0; i < dim - 1; i++){
		int temp = id % n;
		label.push_back(temp);
		id = id / n;
	}
	label.push_back(id);
}

void Node::ComputeNextId(int n, int dim){
	
	//只设二维的弧
	
	int temp, t1, t2;
	for(int k = 0; k < dim ; k++){
		t1 = 0;
		t2 = 0;
		temp = label[k];
		if(temp != n - 1){
			label[k] =  label[k] + 1;   //某一位标号加1，每次循环x,y的值分别加1
			for(int i = 0; i < dim; i ++){
				t1 += (label[i] * (int)pow(n, i));
			}//for循环结束计算出当前节点的某个相邻节点
			Link * p = new Link;
			(*p).nextNode = t1;
			linkout.push_back(*p);
			label[k] = temp;
		}
		if(temp != 0){
			label[k] =  label[k] - 1;//某一位标号减1;
			for(int i = 0; i < dim; i ++){
				t2 += (label[i] * (int)pow(n, i));
			}
			Link * p = new Link;
			(*p).nextNode = t2;
			linkout.push_back(*p);
			label[k] = temp;
		}
	}//linkout中link的顺序为x+,x-,y+,y-
}
void Node::initRouteTable(){
	for (int i = 0; i < K * K; i++){
		if (i == nodeid){
			dv[i] = 0;
			adaptiveRT[i] = 0;
		}
		else{
			dv[i] = K * K + 1;
			adaptiveRT[i] = -1;
		}
	}
}

