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
	int vc0Buf, vc1Buf;//��������ͨ���Ƿ�ռ��
	int BW;//���ڱ�ʾ�����Ƿ�ռ��
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
	vector<Link> linkout;//��Ӧͨ����ڽӵ��linkout��״̬
	vector<int> label;//���ڴ洢ÿһ���ڵ�ı�ţ���ά��ʱ��Ϊ(x,y)��nodeid=n*y+x��label[0] is x
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


