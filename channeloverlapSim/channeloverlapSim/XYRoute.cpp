#include<iostream>
#include"Mesh.h"
#include"Message.h"
#include"common.h"
#include"XYRoute.h"
#include<time.h>
#include<vector>
#include<math.h>
#include<map>
using namespace std;


void UpdateNextNodeXY(vector<Flits> & flit, int nodeId){
	for(vector<Flits>::size_type sz = 0; sz < flit.size(); sz++){
		flit[sz].queueNextId.push(nodeId);
	}
}

void UpdateNextVcXY(vector<Flits> & flit, int vc){
	for(vector<Flits>::size_type sz = 0; sz < flit.size(); sz++){
		flit[sz].queueNextVc.push(vc);
	}
}


vector<int> ComputeLabelXY(int id, int dim, int n){
	vector<int> tempLabel;
	for(int i = 0; i < dim - 1; i++){
		int temp = id % n;
		tempLabel.push_back(temp);
		id = id / n;
	}
	tempLabel.push_back(id);
	return tempLabel;
}



vector<int> ComputeOffsetXY(int cur, int dst, int dim, int n){//ÿά�ϵ�offset
	vector<int> curlabel, dstlabel, offlabel;
	offlabel.resize(dim);
	dstlabel = ComputeLabelXY(dst, dim, n);
	curlabel = ComputeLabelXY(cur, dim, n);
	for(int i = 0; i < dim; i++){
		offlabel[i] = dstlabel[i] - curlabel[i];
	}
	return offlabel;
}

void ReleaseVcXY(int Vc, int node1, int node2, Link (*link)[K*K]){
	if(Vc == 0){
		link[node1][node2].vc0Buf = 0;
	}
	else{
		link[node1][node2].vc1Buf = 0;
	}
}

void ReleaseBwXY(int node1, int node2, Link (*link)[K*K]){
	link[node1][node2].BW = 0;
}

void RouteStepXY(list<Message>::iterator it, int i){

	it->flit[i].lastNode = it->flit[i].curNode;
	it->flit[i].curNode = it->flit[i].queueNextId.front();   
	it->flit[i].lastVc = it->flit[i].queueNextVc.front();
	it->flit[i].queueNextId.pop();
	it->flit[i].queueNextVc.pop();
}


bool TestBwOccupyXY(int curnode, int nextnode, Link (*link)[K*K]){
	if(link[curnode][nextnode].BW == 0){
		link[curnode][nextnode].BW = 1;
		return true;
	}
	else{
		return false;
	}
}

int SelectNextNodeAndVcXY(Link (*link)[K*K], int messClass, int lastvc, int n, int curnode, int dstnode, int lastnode, int & vc){
	int nodeId;
	vector<int> tempV, curLabel, srcLabel, offLabel, origOffLabel, tempoff1, tempoff2;
	curLabel = ComputeLabelXY(curnode, 2, n);
	offLabel = ComputeOffsetXY(curnode, dstnode, 2, n);
	vector<int> nextnode;
	tempV = curLabel;
	if (offLabel[0] != 0){
		if (offLabel[0] > 0){
			tempV = curLabel;
			tempV[0] ++;
			nodeId = 0;
			for(int i = 0; i < dim; i ++){
				nodeId += (tempV[i] * (int)pow(n, i));
			}
			if(link[curnode][nodeId].vc0Buf == 0){
				vc = 0;
				return nodeId;
			}
			else if(link[curnode][nodeId].vc1Buf == 0){
				vc = 1;
				return nodeId;
			}	
		}
		else{
			tempV = curLabel;
			tempV[0] --;
			nodeId = 0;
			for(int i = 0; i < dim; i ++){
				nodeId += (tempV[i] * (int)pow(n, i));
			}
			if(link[curnode][nodeId].vc0Buf == 0){
				vc = 0;
				return nodeId;
			}
			else if(link[curnode][nodeId].vc1Buf == 0){
				vc = 1;
				return nodeId;
			}
		}
		return -1;
	}
	else if (offLabel[1] != 0){
		if (offLabel[1] > 0){
			tempV = curLabel;
			tempV[1] ++;
			nodeId = 0;
			for(int i = 0; i < dim; i ++){
				nodeId += (tempV[i] * (int)pow(n, i));
			}
			if(link[curnode][nodeId].vc0Buf == 0){
				vc = 0;
				return nodeId;
			}
			else if(link[curnode][nodeId].vc1Buf == 0){
				vc = 1;
				return nodeId;
			}
		}
		else{
			tempV = curLabel;
			tempV[1] --;
			nodeId = 0;
			for(int i = 0; i < dim; i ++){
				nodeId += (tempV[i] * (int)pow(n, i));
			}
			if(link[curnode][nodeId].vc0Buf == 0){
				vc = 0;
				return nodeId;
			}
			else if(link[curnode][nodeId].vc1Buf == 0){
				vc = 1;
				return nodeId;
			}
		}
			return -1;
	}
	return -1;
}


void XYRouting(vector<Node>& mesh, list<Message>& message, Link (*link)[K*K], long & cycle, long & arriveMessage, long & totalCycle, int dim, int n){
	for(list<Message>::iterator it = message.begin(); it != message.end(); ){
		it->timeForMessage ++;
		int Vc, srcnode, lastnode, curnode, nextnode, dstnode;
		//bool endFlag = false; 
        //���ȿ������һ��flit��������һ��flit�Ѿ����յ㣬�����cycle������message���봦�������ͷ�buffer������ɾ�����message
		int lastFlitId = it->flit.size() - 1;
		Vc = it->flit[lastFlitId].lastVc;
		curnode = it->flit[lastFlitId].curNode;
		lastnode = it->flit[lastFlitId].lastNode;
		dstnode = it->dstNode;

		if(curnode == dstnode){//��Ϣ�����һ��flit�����յ�
	//		cout<<"aaa"<<endl;
			ReleaseVcXY(Vc, lastnode, curnode, link);
			if(!it->warmup){            //Ԥ�ȵ�message��ͳ������
				arriveMessage ++;
				totalCycle += it->timeForMessage;
			}
			it = message.erase(it);
			//it = message.begin();
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
									ReleaseVcXY(Vc, lastnode, curnode, link);
								}
								ReleaseBwXY(curnode, nextnode, link);
								//endFlag = true;
							}
							RouteStepXY(it, i);
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
									ReleaseVcXY(Vc, lastnode, curnode, link);
								}
								ReleaseBwXY(curnode, nextnode, link);
								//endFlag = true;
							}
							RouteStepXY(it, i);
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
						if(i == lastFlitId){   //����ѽڵ������һ���㣬����Ҫ�ͷ���һ�����buffer����һ���㵽��ǰ���BW(������һ��flit��src�Ͳ���Ҫ�ͷ�)��
							nextnode = it->flit[i].queueNextId.front();
							if(curnode != srcnode){
								lastnode = it->flit[i].lastNode;
								Vc =  it->flit[i].lastVc;
								ReleaseVcXY(Vc, lastnode, curnode, link);
							}
							ReleaseBwXY(curnode, nextnode, link);
							//endFlag = true;
						}
						RouteStepXY(it, i);
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
					tempNext = SelectNextNodeAndVcXY(link, it->messageClass, Vc, n, curnode, dstnode, lastnode, vc);
					if(tempNext != -1){  //ѡ·�ɹ�
						UpdateNextNodeXY(it->flit, tempNext);//��Ϣ��ÿ��flit��queueNextId�ж�����tempNext
						UpdateNextVcXY(it->flit, vc);
						if(vc == 0){
							link[curnode][tempNext].vc0Buf = 1;
						}
						else{
							link[curnode][tempNext].vc1Buf = 1;
						}
						it->flit[0].routeNext = true;
						//���BW���У��������һ��
						bool flagBW = TestBwOccupyXY(curnode, tempNext, link);
						if(flagBW){
							it->flit[0].routeNext = false;
							RouteStepXY(it, 0);
						}
					}

				}
				else{   //flit1�Ѿ�ѡ·
					int nextnode = it->flit[0].queueNextId.front();
					bool flagBW = TestBwOccupyXY(curnode, nextnode, link);
					if(flagBW){
						int nextnode = it->flit[0].queueNextId.front();
						it->flit[0].routeNext = false;
						RouteStepXY(it, 0);
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
