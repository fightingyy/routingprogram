#include<iostream>
#include"Mesh.h"
#include"Message.h"
#include"common.h"
#include"Route.h"
#include<time.h>
#include<vector>
#include<math.h>
#include<map>
using namespace std;



void updateClass(Link (*link)[K*K], list<Message>::iterator it, int curnode, int dstnode, int num){
     it->messageClass = it->computeClass(link, curnode, dstnode, num);
}



void UpdateNextNode(vector<Flits> & flit, int nodeId){
	for(vector<Flits>::size_type sz = 0; sz < flit.size(); sz++){
		flit[sz].queueNextId.push(nodeId);
	}
}

void UpdateNextVc(vector<Flits> & flit, int vc){
	for(vector<Flits>::size_type sz = 0; sz < flit.size(); sz++){
		flit[sz].queueNextVc.push(vc);
	}
}


vector<int> ComputeLabel(int id, int dim, int n){
	vector<int> tempLabel;
	for(int i = 0; i < dim - 1; i++){
		int temp = id % n;
		tempLabel.push_back(temp);
		id = id / n;
	}
	tempLabel.push_back(id);
	return tempLabel;
}



vector<int> ComputeOffset(int cur, int dst, int dim, int n){//ÿά�ϵ�offset
	vector<int> curlabel, dstlabel, offlabel;
	offlabel.resize(dim);
	dstlabel = ComputeLabel(dst, dim, n);
	curlabel = ComputeLabel(cur, dim, n);
	for(int i = 0; i < dim; i++){
		offlabel[i] = dstlabel[i] - curlabel[i];
	}
	return offlabel;
}


int Ele(Link (*link)[K*K], int messClass, int n, int curnode, int nextnode, int & vc){
	if(link[curnode][nextnode].vc0Buf == 0){
		vc = 0;
		return nextnode;
	}
	else if(link[curnode][nextnode].vc1Buf == 0){
		vc = 1;
		return nextnode;
	}
	return -1;
}


int Elenew(Link (*link)[K*K], int messClass, int n, int curnode, int nextnode, int & vc){
	if(link[curnode][nextnode].vc0Buf == 0){
		vc = 0;
		return nextnode;
	}
	return -1;

}
 
int SelectNextNodeAndVc(Link (*link)[K*K], int messClass, int lastvc, int n, int curnode, int dstnode, int lastnode, int & vc){
	vector<int> tempV, curLabel, srcLabel, offLabel, origOffLabel, tempoff1, tempoff2;
	int xoff, yoff;
	curLabel = ComputeLabel(curnode, 2, n);
	offLabel = ComputeOffset(curnode, dstnode, 2, n);
	xoff = offLabel[0];
	yoff = offLabel[1];
	vector<int> nextnode;
	tempV = curLabel;
	int r;
	vector<int> tempV1, tempV2, tempV3, tempV4;
	int nodeId1, nodeId2, nodeId3, nodeId4;

	nodeId1 = -1;
	nodeId2 = -1;
	nodeId3 = -1;
	nodeId4 = -1;

	tempV1 = curLabel;
	if (tempV1[0] < num-1){
		tempV1[0] ++;
		nodeId1 = 0;
		for(int i = 0; i < 2; i ++){
			nodeId1 += (tempV1[i] * (int)pow(num, i));
		}
	}
	
	tempV2 = curLabel;
	if (tempV2[0] > 0){
		tempV2[0] --;
		nodeId2 = 0;
		for(int i = 0; i < 2; i ++){
			nodeId2 += (tempV2[i] * (int)pow(num, i));
		}
	}

	tempV3 = curLabel;
	if (tempV3[1] < num-1){
		tempV3[1] ++;
		nodeId3 = 0;
		for(int i = 0; i < 2; i ++){
			nodeId3 += (tempV3[i] * (int)pow(num, i));
		}
	}

	tempV4 = curLabel;
	if (tempV4[1] > 0){
		tempV4[1] --;
		nodeId4 = 0;
		for(int i = 0; i < 2; i ++){
			nodeId4 += (tempV4[i] * (int)pow(num, i));
		}
	}
	switch (messClass)
	{
	case 1://e+x+y+
		r = rand() % 2;
		if(r == 0){
			if(offLabel[0] != 0){//x,1+
				//if(link[curnode][nodeId1].vc1Buf == 0 && link[curnode][nodeId1].BW == 0 || link[curnode][nodeId1].vc1Buf == 0 && link[curnode][nodeId3].vc1Buf == 1){
				if(link[curnode][nodeId1].vc1Buf == 0){
					vc = 1;
					return nodeId1;
				}
			}
			if(offLabel[1] != 0){//y,1+
				//if(link[curnode][nodeId3].vc1Buf == 0 && link[curnode][nodeId3].BW == 0){
				if(link[curnode][nodeId3].vc1Buf == 0){	
					vc = 1;
					return nodeId3;
				}
			}
		}
		else{
			if(offLabel[1] != 0){//y,1+
				if(link[curnode][nodeId3].vc1Buf == 0 && link[curnode][nodeId3].BW == 0 || link[curnode][nodeId3].vc1Buf == 0 && link[curnode][nodeId1].vc1Buf == 1){
				//if(link[curnode][nodeId3].vc1Buf == 0){	
					vc = 1;
					return nodeId3;
				}
			}
			if(offLabel[0] != 0){//x,1+
				if(link[curnode][nodeId1].vc1Buf == 0 && link[curnode][nodeId1].BW == 0){
				//if(link[curnode][nodeId1].vc1Buf == 0){	
					vc = 1;
					return nodeId1;
				}
			}
		}
		break;

	case 2://e+x+y-
		r = rand() % 2;
		if (r == 0){
			if (offLabel[0] != 0){
				tempoff1 = ComputeOffset(lastnode, curnode, 2, n);
				if (tempoff1[1] < 0 || lastvc == 0){
					if (link[curnode][nodeId1].vc0Buf == 0 && link[curnode][nodeId1].BW == 0 || link[curnode][nodeId1].vc0Buf == 0 && link[curnode][nodeId4].vc1Buf == 1){
					//if (link[curnode][nodeId1].vc0Buf == 0 && link[curnode][nodeId1].BW == 0){
					//if (link[curnode][nodeId1].vc0Buf == 0 ){
						vc = 0;
						return nodeId1;
					}
				}
				else{
					if (link[curnode][nodeId1].vc1Buf == 0 && link[curnode][nodeId1].BW == 0 || link[curnode][nodeId1].vc1Buf == 0 && link[curnode][nodeId4].vc1Buf == 1){
					//if (link[curnode][nodeId1].vc1Buf == 0 && link[curnode][nodeId1].BW == 0){	
					//if (link[curnode][nodeId1].vc1Buf == 0){
						vc = 1;
						return nodeId1;
					}
				}
			}
			if (offLabel[1] != 0){
				if (link[curnode][nodeId4].vc1Buf == 0){
					vc = 1;
					return nodeId4;
				}
			}
		}
		else{
			if (offLabel[1] != 0){
				if (link[curnode][nodeId4].vc1Buf == 0 && link[curnode][nodeId4].BW == 0 || link[curnode][nodeId4].vc1Buf == 0 && link[curnode][nodeId1].vc1Buf == 1 && link[curnode][nodeId1].vc0Buf == 1){
				//if (link[curnode][nodeId4].vc1Buf == 0 && link[curnode][nodeId4].BW == 0){
				//if (link[curnode][nodeId4].vc1Buf == 0){	
					vc = 1;
					return nodeId4;
				}
			}
			if (offLabel[0] != 0){
				tempoff1 = ComputeOffset(lastnode, curnode, 2, n);
				if (tempoff1[1] < 0 || lastvc == 0){
					if (link[curnode][nodeId1].vc0Buf == 0){
						vc = 0;
						return nodeId1;
					}
				}
				else{
					if (link[curnode][nodeId1].vc1Buf == 0){
						vc = 1;
						return nodeId1;
					}
				}
			}
		}
		break;

	case 3: //������Ϣ3��e+x-y+,ֻ��yx·��
		if(offLabel[1] != 0){
			if(link[curnode][nodeId3].vc1Buf == 0){
				vc = 1;
				return nodeId3;
			}
		}
		else if(offLabel[0] != 0){
			if(link[curnode][nodeId2].vc1Buf == 0){
				vc = 1;
				return nodeId2;					
			}
		}
		break;

	case 4:  //e+x-y-  
		r = rand() % 2;
		if(r == 0){
			if(offLabel[0] != 0){//x,1+
				if(link[curnode][nodeId2].vc1Buf == 0 && link[curnode][nodeId2].BW == 0 || link[curnode][nodeId2].vc1Buf == 0 && link[curnode][nodeId4].vc1Buf == 1){
				//if(link[curnode][nodeId2].vc1Buf == 0){	
					vc = 1;
					return nodeId2;
				}
			}
			if(offLabel[1] != 0){//y,1+
				//if(link[curnode][nodeId4].vc1Buf == 0 && link[curnode][nodeId4].BW == 0){
				if(link[curnode][nodeId4].vc1Buf == 0){	
					vc = 1;
					return nodeId4;
				}
			}
		}
		else{
			if(offLabel[1] != 0){//y,1+
				if(link[curnode][nodeId4].vc1Buf == 0 && link[curnode][nodeId4].BW == 0 || link[curnode][nodeId4].vc1Buf == 0 && link[curnode][nodeId2].vc1Buf == 1){
				//if(link[curnode][nodeId4].vc1Buf == 0){
					vc = 1;
					return nodeId4;
				}
			}
			if(offLabel[0] != 0){//x,1+
				//if(link[curnode][nodeId2].vc1Buf == 0 && link[curnode][nodeId2].BW == 0){
				if(link[curnode][nodeId2].vc1Buf == 0){	
					vc = 1;
					return nodeId2;
				}
			}
		}
		break;

	case 5://e-x+y+,yx
		if(offLabel[1] != 0){
			if(link[curnode][nodeId3].vc0Buf == 0){
				vc = 0;
				return nodeId3;
			}
		}
		else if(offLabel[0] != 0){
			if(link[curnode][nodeId1].vc0Buf == 0){
				vc = 0;
				return nodeId1;					
			}
		}
		break;

	case 6://e-x-y+
		r = rand() % 2;
		if(r == 0){
			if(offLabel[0] != 0){
				if(link[curnode][nodeId2].vc0Buf == 0 && link[curnode][nodeId2].BW == 0 || link[curnode][nodeId2].vc0Buf == 0 && link[curnode][nodeId3].vc0Buf == 1){
				//if(link[curnode][nodeId2].vc0Buf == 0){	
					vc = 0;
					return nodeId2;
				}
			}
			if(offLabel[1] != 0){
				//if(link[curnode][nodeId3].vc0Buf == 0 && link[curnode][nodeId3].BW == 0){
				if(link[curnode][nodeId3].vc0Buf == 0){	
					vc = 0;
					return nodeId3;
				}
			}
		}
		else{
			if(offLabel[1] != 0){
				if(link[curnode][nodeId3].vc0Buf == 0 && link[curnode][nodeId3].BW == 0 || link[curnode][nodeId3].vc0Buf == 0 && link[curnode][nodeId2].vc0Buf == 1){
				//if(link[curnode][nodeId3].vc0Buf == 0){
					vc = 0;
					return nodeId3;
				}
			}
			if(offLabel[0] != 0){
				//if(link[curnode][nodeId2].vc0Buf == 0 && link[curnode][nodeId2].BW == 0){
				if(link[curnode][nodeId2].vc0Buf == 0){	
					vc = 0;
					return nodeId2;
				}
			}
		}
		break;

	case 7://e-x+y-   
		r = rand() % 2;
		if(r == 0){
			if(offLabel[0] != 0){
				if(link[curnode][nodeId1].vc0Buf == 0 && link[curnode][nodeId1].BW == 0 || link[curnode][nodeId1].vc0Buf == 0 && link[curnode][nodeId4].vc0Buf == 1){
				//if(link[curnode][nodeId1].vc0Buf == 0){	
					vc = 0;
					return nodeId1;
				}
			}
			if(offLabel[1] != 0){
				//if(link[curnode][nodeId4].vc0Buf == 0 && link[curnode][nodeId4].BW == 0){
				if(link[curnode][nodeId4].vc0Buf == 0){	
					vc = 0;
					return nodeId4;
				}
			}
		}
		else{
			if(offLabel[1] != 0){
				if(link[curnode][nodeId4].vc0Buf == 0 && link[curnode][nodeId4].BW == 0 || link[curnode][nodeId4].vc0Buf == 0 && link[curnode][nodeId1].vc0Buf == 1){
				//if(link[curnode][nodeId4].vc0Buf == 0){	
					vc = 0;
					return nodeId4;
				}
			}
			if(offLabel[0] != 0){
				//if(link[curnode][nodeId1].vc0Buf == 0 && link[curnode][nodeId1].BW == 0){
				if(link[curnode][nodeId1].vc0Buf == 0){	
					vc = 0;
					return nodeId1;
				}
			}

		}
		break;

	case 8://e-x-y-
		r = rand() % 2;
		if (r == 0){
			if (offLabel[0] != 0){
				tempoff1 = ComputeOffset(lastnode, curnode, 2, n);
				if (tempoff1[1] < 0 || lastvc == 1){
					if (link[curnode][nodeId2].vc1Buf == 0 && link[curnode][nodeId2].BW == 0 || link[curnode][nodeId2].vc1Buf == 0 && link[curnode][nodeId4].vc0Buf == 1){
					//if (link[curnode][nodeId2].vc1Buf == 0 && link[curnode][nodeId2].BW == 0){	
					//if (link[curnode][nodeId2].vc1Buf == 0){	
						vc = 1;
						return nodeId2;
					}
				}
				else{
					if (link[curnode][nodeId2].vc0Buf == 0 && link[curnode][nodeId2].BW == 0 || link[curnode][nodeId2].vc0Buf == 0 && link[curnode][nodeId4].vc0Buf == 1){
					//if (link[curnode][nodeId2].vc0Buf == 0 && link[curnode][nodeId2].BW == 0){
					//if (link[curnode][nodeId2].vc0Buf == 0){	
						vc = 0;
						return nodeId2;
					}
				}
			}
			if (offLabel[1] != 0){
				if (link[curnode][nodeId4].vc0Buf == 0){
					vc = 0;
					return nodeId4;
				}
			}
		}
		else{
			if (offLabel[1] != 0){
				if (link[curnode][nodeId4].vc0Buf == 0 && link[curnode][nodeId4].BW == 0 || link[curnode][nodeId4].vc0Buf == 0 && link[curnode][nodeId2].vc0Buf == 1 && link[curnode][nodeId2].vc1Buf == 1){
				//if (link[curnode][nodeId4].vc0Buf == 0 && link[curnode][nodeId4].BW == 0){
				//if (link[curnode][nodeId4].vc0Buf == 0){
					vc = 0;
					return nodeId4;
				}
			}
			if (offLabel[0] != 0){
				tempoff1 = ComputeOffset(lastnode, curnode, 2, n);
				if (tempoff1[1] < 0 || lastvc == 1){
					if (link[curnode][nodeId2].vc1Buf == 0){
						vc = 1;
						return nodeId2;
					}
				}
				else{
					if (link[curnode][nodeId2].vc0Buf == 0){
						vc = 0;
						return nodeId2;
					}
				}
			}
		}
		break;

	default:
		break;
	}
	return -1;
}




void ReleaseVc(int Vc, int node1, int node2, Link (*link)[K*K]){
	if(Vc == 0){
		link[node1][node2].vc0Buf = 0;
	}
	else{
		link[node1][node2].vc1Buf = 0;
	}
}

void ReleaseBw(int node1, int node2, Link (*link)[K*K]){
	link[node1][node2].BW = 0;
}

void RouteStep(list<Message>::iterator it, int i){

	it->flit[i].lastNode = it->flit[i].curNode;
	it->flit[i].curNode = it->flit[i].queueNextId.front();   
	it->flit[i].lastVc = it->flit[i].queueNextVc.front();
	it->flit[i].queueNextId.pop();
	it->flit[i].queueNextVc.pop();
}




bool TestBwOccupy(int curnode, int nextnode, Link (*link)[K*K]){
	if(link[curnode][nextnode].BW == 0){
		link[curnode][nextnode].BW = 1;
		return true;
	}
	else{
		return false;
	}
}


void Routing(vector<Node>& mesh, list<Message>& message, Link (*link)[K*K], long & cycle, long & arriveMessage, long & totalCycle, int dim, int n){
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
			ReleaseVc(Vc, lastnode, curnode, link);
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
									ReleaseVc(Vc, lastnode, curnode, link);
								}
								ReleaseBw(curnode, nextnode, link);
							}
							RouteStep(it, i);
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
									ReleaseVc(Vc, lastnode, curnode, link);
								}
								ReleaseBw(curnode, nextnode, link);
							}
							RouteStep(it, i);
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
								ReleaseVc(Vc, lastnode, curnode, link);
							}
							ReleaseBw(curnode, nextnode, link);
						}
						RouteStep(it, i);
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
					tempNext = SelectNextNodeAndVc(link, it->messageClass, Vc, n, curnode, dstnode, lastnode, vc);
					if(tempNext != -1){  //ѡ·�ɹ�
						UpdateNextNode(it->flit, tempNext);//��Ϣ��ÿ��flit��queueNextId�ж�����tempNext
						UpdateNextVc(it->flit, vc);
						if(vc == 0){
							link[curnode][tempNext].vc0Buf = 1;
						}
						else{
							link[curnode][tempNext].vc1Buf = 1;
						}
						it->flit[0].routeNext = true;
						//���BW���У��������һ��
						bool flagBW = TestBwOccupy(curnode, tempNext, link);
						if(flagBW){
							it->flit[0].routeNext = false;
							RouteStep(it, 0);
						}
					}

				}
				else{   //flit1�Ѿ�ѡ·
					int nextnode = it->flit[0].queueNextId.front();
					bool flagBW = TestBwOccupy(curnode, nextnode, link);
					if(flagBW){
						int nextnode = it->flit[0].queueNextId.front();
						it->flit[0].routeNext = false;
						RouteStep(it, 0);
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
