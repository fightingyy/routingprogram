#ifndef MESSAGE
#define MESSAGE

#include<iostream>
#include<cmath>
#include<vector>
#include<queue>
#include<time.h>
#include"Mesh.h"

//#include"VerticalRoute.h"

using namespace std;

vector<int> ComputeOffset(int cur, int dst, int dim, int n);


class Flits{
public:
	queue<int> queueNextId;
	queue<int> queueNextVc;
	int srcNode, curNode, dstNode;
	int nextNode, lastNode;
	int bufferid;
	bool routeNext;
	int lastVc;
	Flits(){
		routeNext = false;
		lastVc = -1;
	}
};

class Message{
public:
	int messageClass; //用以确定这个消息属于什么类型
	vector<Flits> flit;
	int computeClass(Link (*link)[K*K], int srcnode, int dstnode, int num);//计算消息的类型，属于虚拟网络中的哪类，一共有8类
	int transposeIJK(int srcnode, int num);//将x,y换位后的nodeid，x->y,y->x
	int transposeMinusIJK(int srcnode, int num);
	unsigned long timeForMessage;//用于记录每个message一共花了多长的时间
	bool warmup;//用于标记这个message是不是预热包
	int length; 
	int srcNode, curNode, dstNode, nextNode, lastNode;
	int bufferid;
	Message(vector<Node> mesh, int NodeNum, int num){

		warmup = false;
		length = 16;
		flit.resize(16);
		timeForMessage = 0;

		//		用于uniform
		srcNode = (abs(rand()%NodeNum));
		dstNode = (abs(rand()%NodeNum));
		while(srcNode == dstNode){
			srcNode = (abs(rand()%NodeNum));
			dstNode = (abs(rand()%NodeNum));
		}

		// 用于 transpose
		/*srcNode = (abs(rand()%NodeNum));
		dstNode = transposeIJK(srcNode, num);
		while (srcNode == dstNode){
			srcNode = (abs(rand()%NodeNum));
			dstNode = transposeIJK(srcNode, num);
		}*/

		/*srcNode = (abs(rand()%NodeNum));
		dstNode = transposeMinusIJK(srcNode, num);
		while (srcNode == dstNode){
			srcNode = (abs(rand()%NodeNum));
			dstNode = transposeIJK(srcNode, num);
		}*/

		curNode = srcNode;
		for(vector<Flits>::size_type s = 0; s < flit.size(); s++){
			flit[s].srcNode = srcNode;
			flit[s].curNode = curNode;
			flit[s].dstNode = dstNode;
			flit[s].lastNode = -1;
			flit[s].nextNode = -1;//表示还没有选路
		}

		messageClass = -1;
		//messageClass = computeClass(srcNode, dstNode, num);
	}
};

#endif


