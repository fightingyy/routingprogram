#include<iostream>
#include"Mesh.h"
#include"Message.h"
#include"common.h"
#include"SpaningTree.h"
#include<time.h>
#include<vector>
#include<math.h>
#include<map>
using namespace std;


void UpdateNextNodeTree(vector<Flits> & flit, int nodeId){
	for(vector<Flits>::size_type sz = 0; sz < flit.size(); sz++){
		flit[sz].queueNextId.push(nodeId);
	}
}

void UpdateNextVcTree(vector<Flits> & flit, int vc){
	for(vector<Flits>::size_type sz = 0; sz < flit.size(); sz++){
		flit[sz].queueNextVc.push(vc);
	}
}


vector<int> ComputeLabelTree(int id, int dim, int n){
	vector<int> tempLabel;
	for(int i = 0; i < dim - 1; i++){
		int temp = id % n;
		tempLabel.push_back(temp);
		id = id / n;
	}
	tempLabel.push_back(id);
	return tempLabel;
}



vector<int> ComputeOffsetTree(int cur, int dst, int dim, int n){//ÿά�ϵ�offset
	vector<int> curlabel, dstlabel, offlabel;
	offlabel.resize(dim);
	dstlabel = ComputeLabelTree(dst, dim, n);
	curlabel = ComputeLabelTree(cur, dim, n);
	for(int i = 0; i < dim; i++){
		offlabel[i] = dstlabel[i] - curlabel[i];
	}
	return offlabel;
}

 
int SelectNextNodeAndVcTree(vector<Node>& mesh, Link (*link)[K*K], int messClass, int lastvc, int n, int curnode, int dstnode, int lastnode, int & vc){
	int nextnode = mesh[curnode].adaptiveRT[dstnode];
	int r = rand() % 2;
	if (r == 0){
		if (link[curnode][nextnode].vc1Buf == 0){
			vc = 1;
			return nextnode;
		}
		if (link[curnode][nextnode].vc0Buf == 0){
			vc = 0;
			return nextnode;
		}
	}
	else{
		if (link[curnode][nextnode].vc0Buf == 0){
			vc = 0;
			return nextnode;
		}
		if (link[curnode][nextnode].vc1Buf == 0){
			vc = 1;
			return nextnode;
		}
	}
	return -1;
}

void ReleaseVcTree(int Vc, int node1, int node2, Link (*link)[K*K]){
	if(Vc == 0){
		link[node1][node2].vc0Buf = 0;
	}
	else{
		link[node1][node2].vc1Buf = 0;
	}
}

void ReleaseBwTree(int node1, int node2, Link (*link)[K*K]){
	link[node1][node2].BW = 0;
}

void RouteStepTree(list<Message>::iterator it, int i){

	it->flit[i].lastNode = it->flit[i].curNode;
	it->flit[i].curNode = it->flit[i].queueNextId.front();   
	it->flit[i].lastVc = it->flit[i].queueNextVc.front();
	it->flit[i].queueNextId.pop();
	it->flit[i].queueNextVc.pop();
}

bool TestBwOccupyTree(int curnode, int nextnode, Link (*link)[K*K]){
	if(link[curnode][nextnode].BW == 0){
		link[curnode][nextnode].BW = 1;
		return true;
	}
	else{
		return false;
	}
}

void RoutingTree(vector<Node>& mesh, list<Message>& message, Link (*link)[K*K], long & cycle, long & arriveMessage, long & totalCycle, int dim, int n){
	for(list<Message>::iterator it = message.begin(); it != message.end(); ){
		it->timeForMessage ++;
		int Vc, srcnode, lastnode, curnode, nextnode, dstnode;
		bool endFlag = false; 
        //���ȿ������һ��flit��������һ��flit�Ѿ����յ㣬�����cycle������message���봦�������ͷ�buffer������ɾ�����message
		int lastFlitId = it->flit.size() - 1;
		Vc = it->flit[lastFlitId].lastVc;
		curnode = it->flit[lastFlitId].curNode;
		lastnode = it->flit[lastFlitId].lastNode;
		dstnode = it->dstNode;
		if (it->messageClass == -1)
		{
			it->messageClass=it->computeClass(link, it->srcNode, it->dstNode, n);
		}
		if(curnode == dstnode){//��Ϣ�����һ��flit�����յ�
	//		cout<<"aaa"<<endl;
			ReleaseVcTree(Vc, lastnode, curnode, link);
			if(!it->warmup){            //Ԥ�ȵ�message��ͳ������
				arriveMessage ++;
				totalCycle += it->timeForMessage;
			}
			it = message.erase(it);
		}
		else{
			//��flit1��ʼ���Ѱ���ѽڵ㣬���ѽڵ�Ҫ�������������һ��flit��queueΪ���벻Ϊ�յ����
			if(it->flit[0].queueNextId.empty()){//��һ��flit��queueΪ�յ����
				int tempFlag = -1;
				for(vector<Flits>::size_type i = 1; i < it->flit.size(); i++){  //��ǰ������ѽڵ�
					if(tempFlag == -1){
						bool queueEmpty = it->flit[i].queueNextId.empty();
						if(!queueEmpty){
							tempFlag = it->flit[i].queueNextId.front();//�ҵ����ѽڵ�
							curnode = it->flit[i].curNode;
							srcnode = it->srcNode;
							if(i == lastFlitId){     //����ѽڵ������һ���㣬����Ҫ�ͷ�buffer��BW(������һ��flit��src�Ͳ���Ҫ�ͷ�)��
								nextnode = it->flit[i].queueNextId.front();
								if(curnode != srcnode){
									lastnode = it->flit[i].lastNode;
									Vc =  it->flit[i].lastVc;
									ReleaseVcTree(Vc, lastnode, curnode, link);
								}
								ReleaseBwTree(curnode, nextnode, link);
							}
							RouteStepTree(it, i);
						}
					}
					else{//�ҵ���һ���ѽڵ�֮��
						int t = it->flit[i].queueNextId.front();
						if(t != tempFlag){
							tempFlag = t;
							curnode = it->flit[i].curNode;
							srcnode = it->srcNode;
							if(i == lastFlitId){                   //����ѽڵ������һ���㣬����Ҫ�ͷ�buffer(������һ��flit��src�Ͳ���Ҫ�ͷ�)��
								nextnode = it->flit[i].queueNextId.front();
								if(curnode != srcnode){
									lastnode = it->flit[i].lastNode;
									Vc =  it->flit[i].lastVc;
									ReleaseVcTree(Vc, lastnode, curnode, link);
								}
								ReleaseBwTree(curnode, nextnode, link);
							}
							RouteStepTree(it, i);
						}
					}
				}
			}
			else{//��һ��flit��queue��Ϊ�յ����
				int tempFlag = it->flit[0].queueNextId.front();
				for(vector<Flits>::size_type i = 1; i < it->flit.size(); i++){
					int t = it->flit[i].queueNextId.front();
					if(t != tempFlag){
						tempFlag = t;
						curnode = it->flit[i].curNode;
						srcnode = it->srcNode;
						if(i == lastFlitId){                   //����ѽڵ������һ���㣬����Ҫ�ͷ���һ�����buffer����һ���㵽��ǰ���BW(������һ��flit��src�Ͳ���Ҫ�ͷ�)��
							nextnode = it->flit[i].queueNextId.front();
							if(curnode != srcnode){
								lastnode = it->flit[i].lastNode;
								Vc =  it->flit[i].lastVc;
								ReleaseVcTree(Vc, lastnode, curnode, link);
							}
							ReleaseBwTree(curnode, nextnode, link);
						}
						RouteStepTree(it, i);
					}

				}
			}

			srcnode = it->flit[0].srcNode;
			curnode = it->flit[0].curNode;
			dstnode = it->flit[0].dstNode;
			lastnode = it->flit[0].lastNode;
			Vc = it->flit[0].lastVc;

			//���1  flit1û�е��յ�
			if(curnode != dstnode){
				if(it->flit[0].routeNext == false){//flit1û��ѡ·����Ҫ�ҵ�nextNode
					int tempNext, vc;
					tempNext = -1;
					tempNext = SelectNextNodeAndVcTree(mesh, link, it->messageClass, Vc, n, curnode, dstnode, lastnode, vc);
					if(tempNext != -1){  //ѡ·�ɹ�
						UpdateNextNodeTree(it->flit, tempNext);//��Ϣ��ÿ��flit��queueNextId�ж�����tempNext
						UpdateNextVcTree(it->flit, vc);
						if(vc == 0){
							link[curnode][tempNext].vc0Buf = 1;
						}
						else{
							link[curnode][tempNext].vc1Buf = 1;
						}
						it->flit[0].routeNext = true;
						//���BW���У��������һ��
						bool flagBW = TestBwOccupyTree(curnode, tempNext, link);
						if(flagBW){
							it->flit[0].routeNext = false;
							RouteStepTree(it, 0);
						}
					}

				}
				else{   //flit1�Ѿ�ѡ·
					int nextnode = it->flit[0].queueNextId.front();
					bool flagBW = TestBwOccupyTree(curnode, nextnode, link);
					if(flagBW){
						int nextnode = it->flit[0].queueNextId.front();
						it->flit[0].routeNext = false;
						RouteStepTree(it, 0);
					}
				}
			}
			/*if (endFlag){
				it = message.begin();
				continue;
			}*/
			it ++;
		}//���һ��flit�ĵ�ǰ�ڵ㲻��dstnode

	}//for
}
