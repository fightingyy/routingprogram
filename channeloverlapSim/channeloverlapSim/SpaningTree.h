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

void ReleaseVcTree(int Vc, int node1, int node2, Link (*link)[K*K]);//�ͷ�buffer

void ReleaseBwTree(int node1, int node2, Link (*link)[K*K]);//�ͷ���·

void RouteStepTree(list<Message>::iterator it, int i);//��һ��

void UpdateNextNodeTree(vector<Flits> & flit, int nodeId);//����һ��node�������е�flit�Ķ�����

void UpdateNextVcTree(vector<Flits> & flit, int vc);//����һ��vc��ż��뵽���е�flit������

bool TestBwOccupyTree(int curnode, int nextnode, Link (*link)[K*K]);//������·�Ƿ�ռ��



#endif