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

int Elenew(Link (*link)[K*K], int messClass, int n, int curnode, int nextnode, int & vc);//�ж�nextnode�Ƿ���VC0����ʹ��

int Ele(Link (*link)[K*K], int messClass, int n, int curnode, int nextnode, int & vc);//�ж�nextnode�Ƿ���VC����ʹ�ã��оͷ���nextnode

void updateClass(Link (*link)[K*K], list<Message>::iterator it, int curnode, int elevator, int num);

int SelectNextNodeAndVc(Link (*link)[K*K], int messClass, int lastvc, int n, int curnode, int elevator, int lastnode, int & vc);

void ReleaseVc(int Vc, int node1, int node2, Link (*link)[K*K]);//�ͷ�buffer

void ReleaseBw(int node1, int node2, Link (*link)[K*K]);//�ͷ���·

void RouteStep(list<Message>::iterator it, int i);//��һ��

void UpdateNextNode(vector<Flits> & flit, int nodeId);//����һ��node�������е�flit�Ķ�����

void UpdateNextVc(vector<Flits> & flit, int vc);//����һ��vc��ż��뵽���е�flit������

bool TestBwOccupy(int curnode, int nextnode, Link (*link)[K*K]);//������·�Ƿ�ռ��



#endif