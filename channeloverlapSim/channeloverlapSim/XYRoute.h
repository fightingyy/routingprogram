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

int ElenewXY(Link (*link)[K*K], int messClass, int n, int curnode, int nextnode, int & vc);//�ж�nextnode�Ƿ���VC0����ʹ��

int EleXY(Link (*link)[K*K], int messClass, int n, int curnode, int nextnode, int & vc);//�ж�nextnode�Ƿ���VC����ʹ�ã��оͷ���nextnode

void updateClassXY(Link (*link)[K*K], list<Message>::iterator it, int curnode, int elevator, int num);

int SelectNextNodeAndVcXY(Link (*link)[K*K], int messClass, int lastvc, int n, int curnode, int elevator, int lastnode, int & vc);

void ReleaseVcXY(int Vc, int node1, int node2, Link (*link)[K*K]);//�ͷ�buffer

void ReleaseBwXY(int node1, int node2, Link (*link)[K*K]);//�ͷ���·

void RouteStepXY(list<Message>::iterator it, int i);//��һ��

void UpdateNextNodeXY(vector<Flits> & flit, int nodeId);//����һ��node�������е�flit�Ķ�����

void UpdateNextVcXY(vector<Flits> & flit, int vc);//����һ��vc��ż��뵽���е�flit������

bool TestBwOccupyXY(int curnode, int nextnode, Link (*link)[K*K]);//������·�Ƿ�ռ��



#endif