#include<iostream>
#include"Mesh.h"
#include"Message.h"
#include"common.h"
#include<time.h>
#include<list>
#include<queue>
using namespace std;


double Injection;//表示每一个cycle每一个node平均产生的flits

double InjectionRate;

double Saturation;

double Throughput;//吞吐量

double AveDelay;//平均时延

long  totalMessage;

long arriveMessage;

long arriveMessageTree;

long totalCycle;

long totalCycleTree;

double generateFlits;

long cycle;

double tempFlits;//单位cycle单位node平均产生的flits

int numAll;//节点数

int num, dim;//输入每一维的点的个数以及维数


void Initialize(vector<Node> & mesh, int num, int dim){
	int numAll = (int)pow(num, dim);
	Node tempNode;
	for(int i = 0;i < numAll; i++){
		mesh.push_back(tempNode);
	}
	for(int i = 0;i < numAll; i++){
		mesh[i].nodeid = i;
		mesh[i].ComputeLabel(i, num, dim);
	}
	for(int i = 0; i < numAll; i++){
		mesh[i].ComputeNextId(num, dim);
	}
	for(int i = 0; i < numAll; i++){
		mesh[i].initRouteTable();
	}
}

void InitializeVar(){
	generateFlits = 0.0;
	totalCycle = 0;
	cycle = 0;
	totalMessage = 0;
	arriveMessage = 0;
}

void InitializeVarTree(){
	generateFlits = 0.0;
	totalCycleTree = 0;
	cycle = 0;
	totalMessage = 0;
	arriveMessageTree = 0;
}



void ClearLink(Link (*link)[K*K]){//all links,link[i][j] i is one node's nodeid, j is another node's nodeid
	for(int i = 0; i < (K*K); i++){
		for(int j = 0; j < (K*K); j++){
			link[i][j].BW = 0;
			link[i][j].occupied = 0;
			link[i][j].fault = 0;
			link[i][j].vc0Buf = 0;
			link[i][j].vc1Buf = 0;
		}
	}
}

void ClearMessage(list<Message>& message){
	message.clear();
}


void ComputeOff(int curnode, int dstnode, int num, int & xoff, int & yoff){
	int x1, x2, y1, y2;
	x1 = curnode % num;
	y1 = curnode / num % num;
	x2 = dstnode % num;
	y2 = dstnode / num % num;
	xoff = x2 - x1;
	yoff = y2 - y1;
}

void setRouteTable(vector<Node> & mesh, int num, int dim){
	int numAll = (int)pow(num, dim);
	int  stable;
	int neighbor;
	Node* node = new Node();

	stable = 0;
	while  (!stable ){
		stable = 1;
		for (int i = 0; i < numAll ; i++){
			node = &mesh[i];
			for (int j = 0; j < node->linkout.size(); j++){
				neighbor = node->linkout[j].nextNode;
				for (int k = 0; k < numAll; k++){
					if (node->dv[k] > (mesh[neighbor].dv[k] + 1)){
						stable = 0;
						node->dv[k] = mesh[neighbor].dv[k] + 1 ;
						node->adaptiveRT[k] = neighbor;
					}
				}	
			}
		}
	}
}


