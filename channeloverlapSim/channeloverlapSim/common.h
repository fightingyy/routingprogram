#ifndef COMMON
#define COMMON

#include<iostream>
#include<list>
#include"Mesh.h"
#include"Message.h"


using namespace std;

extern double Injection;//表示每一个cycle每一个node平均产生的flits

extern double InjectionRate;

extern double Saturation;

extern double Throughput;//吞吐量

extern double AveDelay;//平均时延

extern long  totalMessage;

extern long arriveMessage;

extern long arriveMessageTree;

extern long totalCycle;

extern long totalCycleTree;

extern double generateFlits;

extern long cycle;

extern double tempFlits;//单位cycle单位node平均产生的flits

extern int numAll;//节点数

extern int num, dim;//输入每一维的点的个数以及维数

void InitializeVar();//初始化变量

void InitializeVarTree();//初始化变量

void Initialize(vector<Node> &, int, int);

void ClearLink(Link (*link)[K*K]);   //初始化link

void ClearMessage(list<Message> &);  //初始化message

void ComputeOff(int, int, int, int &, int &);//计算两个节点在x,y维上的坐标差，curnode id,dstnode id,num,xoff,yoff 

void setRouteTable(vector<Node> & mesh, int num, int dim);

#endif
