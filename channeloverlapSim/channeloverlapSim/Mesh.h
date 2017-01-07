#ifndef MESH
#define MESH

#include<iostream>
#include<cmath>
#include<vector>
#include<stack>
#include<String>
#define K 16
using namespace std;

class Link{
public:
	int nextNode,occupied,fault;
	int vc0Buf, vc1Buf;//两个虚拟通道是否被占用
	int BW;//用于表示带宽是否被占用
	Link(){
		BW = 0;
		occupied = 0;
		fault = 0;
		vc0Buf = 0;
		vc1Buf = 0;
	}
};

class Node{
public:
	int nodeid;
	vector<Link> linkout;//对应通向该邻接点的linkout的状态
	vector<int> label;//用于存储每一个节点的标号，三维的时候为(x,y)，nodeid=n*y+x，label[0] is x
	vector<int> dv;
	vector<int> adaptiveRT;
	void ComputeLabel(int, int, int);//first parameter is nodeid,second is the number of nodes in each dimension,last is the number of dimension 
	void ComputeNextId(int, int);
	void ClearIt();
	void initRouteTable();
	Node(){
		dv.resize(K * K);
		adaptiveRT.resize(K * K);
	}
};

#endif


