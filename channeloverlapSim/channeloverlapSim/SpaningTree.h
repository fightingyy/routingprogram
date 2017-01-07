#ifndef Tree
#define Tree

#include<iostream>
#include"Mesh.h"
#include"Message.h"
#include"common.h"
#include<time.h>
#include<list>
#include<vector>
#include<math.h>


using namespace std;

vector<int> ComputeOffsetTree(int cur, int dst, int dim, int n);

vector<int> ComputeLabelTree(int id, int dim, int n);

void RoutingTree(vector<Node> & mesh, list<Message>& message, Link (*link)[K*K], long & cycle, long & arriveMessage, long & totalCycle, int dim, int n);

int SelectNextNodeAndVcTree(vector<Node>& mesh, Link (*link)[K*K], int messClass, int lastvc, int n, int curnode, int elevator, int lastnode, int & vc);

void ReleaseVcTree(int Vc, int node1, int node2, Link (*link)[K*K]);//释放buffer

void ReleaseBwTree(int node1, int node2, Link (*link)[K*K]);//释放链路

void RouteStepTree(list<Message>::iterator it, int i);//走一步

void UpdateNextNodeTree(vector<Flits> & flit, int nodeId);//将下一步node加入所有的flit的队列中

void UpdateNextVcTree(vector<Flits> & flit, int vc);//将下一个vc标号加入到所有的flit队列中

bool TestBwOccupyTree(int curnode, int nextnode, Link (*link)[K*K]);//测试链路是否被占用



#endif