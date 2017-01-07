#ifndef Vertical
#define Vertical

#include<iostream>
#include"Mesh.h"
#include"Message.h"
#include"common.h"
#include<time.h>
#include<list>
#include<vector>
#include<math.h>


using namespace std;

vector<int> ComputeOffset(int cur, int dst, int dim, int n);

vector<int> ComputeLabel(int id, int dim, int n);

void Routing(vector<Node> & mesh, list<Message>& message, Link (*link)[K*K], long & cycle, long & arriveMessage, long & totalCycle, int dim, int n);

int Elenew(Link (*link)[K*K], int messClass, int n, int curnode, int nextnode, int & vc);//判断nextnode是否有VC0可以使用

int Ele(Link (*link)[K*K], int messClass, int n, int curnode, int nextnode, int & vc);//判断nextnode是否有VC可以使用，有就返回nextnode

void updateClass(Link (*link)[K*K], list<Message>::iterator it, int curnode, int elevator, int num);

int SelectNextNodeAndVc(Link (*link)[K*K], int messClass, int lastvc, int n, int curnode, int elevator, int lastnode, int & vc);

void ReleaseVc(int Vc, int node1, int node2, Link (*link)[K*K]);//释放buffer

void ReleaseBw(int node1, int node2, Link (*link)[K*K]);//释放链路

void RouteStep(list<Message>::iterator it, int i);//走一步

void UpdateNextNode(vector<Flits> & flit, int nodeId);//将下一步node加入所有的flit的队列中

void UpdateNextVc(vector<Flits> & flit, int vc);//将下一个vc标号加入到所有的flit队列中

bool TestBwOccupy(int curnode, int nextnode, Link (*link)[K*K]);//测试链路是否被占用



#endif