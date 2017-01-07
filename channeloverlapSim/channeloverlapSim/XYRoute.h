#ifndef XYROUTE
#define XYROUTE

#include<iostream>
#include"Mesh.h"
#include"Message.h"
#include"common.h"
#include<time.h>
#include<list>
#include<vector>
#include<math.h>


using namespace std;

vector<int> ComputeOffsetXY(int cur, int dst, int dim, int n);

vector<int> ComputeLabelXY(int id, int dim, int n);

void XYRouting(vector<Node> & mesh, list<Message>& message, Link (*link)[K*K], long & cycle, long & arriveMessage, long & totalCycle, int dim, int n);

int ElenewXY(Link (*link)[K*K], int messClass, int n, int curnode, int nextnode, int & vc);//判断nextnode是否有VC0可以使用

int EleXY(Link (*link)[K*K], int messClass, int n, int curnode, int nextnode, int & vc);//判断nextnode是否有VC可以使用，有就返回nextnode

void updateClassXY(Link (*link)[K*K], list<Message>::iterator it, int curnode, int elevator, int num);

int SelectNextNodeAndVcXY(Link (*link)[K*K], int messClass, int lastvc, int n, int curnode, int elevator, int lastnode, int & vc);

void ReleaseVcXY(int Vc, int node1, int node2, Link (*link)[K*K]);//释放buffer

void ReleaseBwXY(int node1, int node2, Link (*link)[K*K]);//释放链路

void RouteStepXY(list<Message>::iterator it, int i);//走一步

void UpdateNextNodeXY(vector<Flits> & flit, int nodeId);//将下一步node加入所有的flit的队列中

void UpdateNextVcXY(vector<Flits> & flit, int vc);//将下一个vc标号加入到所有的flit队列中

bool TestBwOccupyXY(int curnode, int nextnode, Link (*link)[K*K]);//测试链路是否被占用



#endif