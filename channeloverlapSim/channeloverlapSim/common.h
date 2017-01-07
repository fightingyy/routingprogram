#ifndef COMMON
#define COMMON

#include<iostream>
#include<list>
#include"Mesh.h"
#include"Message.h"


using namespace std;

extern double Injection;//��ʾÿһ��cycleÿһ��nodeƽ��������flits

extern double InjectionRate;

extern double Saturation;

extern double Throughput;//������

extern double AveDelay;//ƽ��ʱ��

extern long  totalMessage;

extern long arriveMessage;

extern long arriveMessageTree;

extern long totalCycle;

extern long totalCycleTree;

extern double generateFlits;

extern long cycle;

extern double tempFlits;//��λcycle��λnodeƽ��������flits

extern int numAll;//�ڵ���

extern int num, dim;//����ÿһά�ĵ�ĸ����Լ�ά��

void InitializeVar();//��ʼ������

void InitializeVarTree();//��ʼ������

void Initialize(vector<Node> &, int, int);

void ClearLink(Link (*link)[K*K]);   //��ʼ��link

void ClearMessage(list<Message> &);  //��ʼ��message

void ComputeOff(int, int, int, int &, int &);//���������ڵ���x,yά�ϵ�����curnode id,dstnode id,num,xoff,yoff 

void setRouteTable(vector<Node> & mesh, int num, int dim);

#endif
