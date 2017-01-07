#include"Message.h"
#include<iostream>

using namespace std;

int Message::computeClass(Link (*link)[K*K], int srcnode, int dstnode, int num){
	int xoff, yoff;
	vector<int> labelSrc, labelDst, tempV1, tempV2, tempV3, tempV4;
	int nodeId1, nodeId2, nodeId3, nodeId4;
	for(int i = 0; i < 1; i++){
		int temp = srcnode % num;
		labelSrc.push_back(temp);
		srcnode = srcnode / num;
	}
	labelSrc.push_back(srcnode);
	for(int i = 0; i < 1; i++){
		int temp = dstnode % num;
		labelDst.push_back(temp);
		dstnode = dstnode / num;
	}
	labelDst.push_back(dstnode);
	xoff = labelDst[0] - labelSrc[0];
	yoff = labelDst[1] - labelSrc[1];

	nodeId1 = -1;
	nodeId2 = -1;
	nodeId3 = -1;
	nodeId4 = -1;

	tempV1 = labelSrc;
	if (tempV1[0] < num-1){
		tempV1[0] ++;
		nodeId1 = 0;
		for(int i = 0; i < 2; i ++){
			nodeId1 += (tempV1[i] * (int)pow(num, i));
		}
	}
	
	tempV2 = labelSrc;
	if (tempV2[0] > 0){
		tempV2[0] --;
		nodeId2 = 0;
		for(int i = 0; i < 2; i ++){
			nodeId2 += (tempV2[i] * (int)pow(num, i));
		}
	}

	tempV3 = labelSrc;
	if (tempV3[1] < num-1){
		tempV3[1] ++;
		nodeId3 = 0;
		for(int i = 0; i < 2; i ++){
			nodeId3 += (tempV3[i] * (int)pow(num, i));
		}
	}

	tempV4 = labelSrc;
	if (tempV4[1] > 0){
		tempV4[1] --;
		nodeId4 = 0;
		for(int i = 0; i < 2; i ++){
			nodeId4 += (tempV4[i] * (int)pow(num, i));
		}
	}

	if(xoff == 0 && yoff > 0){
		int r = rand() % 2;
		if (r == 1){
			//if (link[srcNode][nodeId3].vc1Buf == 0 && link[srcNode][nodeId3].BW == 0 || link[srcNode][nodeId3].vc1Buf == 0 && link[srcNode][nodeId3].vc0Buf == 1){
			if (link[srcNode][nodeId3].vc1Buf == 0 ){	
				int c = rand() % 2;
				if(c == 1){
					return 1;
				}
				else{
					return 3;
				}
			}
			else{
				int c = rand() % 2;
				if(c == 1){
					return 5;
				}
				else{
					return 6;
				}
			}
		}
		else{
			//if (link[srcNode][nodeId3].vc0Buf == 0 && link[srcNode][nodeId3].BW == 0 || link[srcNode][nodeId3].vc0Buf == 0 && link[srcNode][nodeId3].vc1Buf == 1){
			if (link[srcNode][nodeId3].vc0Buf == 0){	
				int c = rand() % 2;
				if(c == 1){
					return 5;
				}
				else{
					return 6;
				}
			}
			else{
				int c = rand() % 2;
				if(c == 1){
					return 1;
				}
				else{
					return 3;
				}
			}
		}
	}
	else if(xoff == 0 && yoff < 0){
		int r = rand() % 2;
		if (r == 1){
			//if (link[srcNode][nodeId4].vc1Buf == 0 && link[srcNode][nodeId4].BW == 0 || link[srcNode][nodeId4].vc1Buf == 0 && link[srcNode][nodeId4].vc0Buf == 1){
			if (link[srcNode][nodeId4].vc1Buf == 0){	
				int c = rand() % 2;
				if(c == 1){
					return 2;
				}
				else{
					return 4;
				}
			}
			else{
				int c = rand() % 2;
				if(c == 1){
					return 7;
				}
				else{
					return 8;
				}
			}
		}
		else{
			//if (link[srcNode][nodeId4].vc0Buf == 0 && link[srcNode][nodeId4].BW == 0 || link[srcNode][nodeId4].vc0Buf == 0 && link[srcNode][nodeId4].vc1Buf == 1){
			if (link[srcNode][nodeId4].vc0Buf == 0){	
				int c = rand() % 2;
				if(c == 1){
					return 7;
				}
				else{
					return 8;
				}
			}
			else{
				int c = rand() % 2;
				if(c == 1){
					return 2;
				}
				else{
					return 4;
				}
			}
		}
	}
	else if(xoff > 0 && yoff == 0){
		int r = rand() % 2;
		if (r == 1){
			//if (link[srcNode][nodeId1].vc1Buf == 0 && link[srcNode][nodeId1].BW == 0 || link[srcNode][nodeId1].vc1Buf == 0 && link[srcNode][nodeId1].vc0Buf == 1){
			if (link[srcNode][nodeId1].vc1Buf == 0){
				int c = rand() % 2;
				if(c == 1){
					return 1;
				}
				else{
					return 2;
				}
			}
			else{
				int c = rand() % 2;
				if(c == 1){
					return 5;
				}
				else{
					return 7;
				}
			}
		}
		else{
			//if (link[srcNode][nodeId1].vc0Buf == 0 && link[srcNode][nodeId1].BW == 0 || link[srcNode][nodeId1].vc0Buf == 0 && link[srcNode][nodeId1].vc1Buf == 1){
			if (link[srcNode][nodeId1].vc0Buf == 0){
				int c = rand() % 2;
				if(c == 1){
					return 5;
				}
				else{
					return 7;
				}
			}
			else{
				int c = rand() % 2;
				if(c == 1){
					return 1;
				}
				else{
					return 2;
				}
			}
		}
	}
	else if(xoff < 0 && yoff == 0){
		int r = rand() % 2;
		if (r == 1){
			//if (link[srcNode][nodeId2].vc1Buf == 0 && link[srcNode][nodeId2].BW == 0 || link[srcNode][nodeId2].vc1Buf == 0 && link[srcNode][nodeId1].vc0Buf == 1){
			if (link[srcNode][nodeId2].vc1Buf == 0){	
				int c = rand() % 2;
				if(c == 1){
					return 3;
				}
				else{
					return 4;
				}
			}
			else{
				int c = rand() % 2;
				if(c == 1){
					return 6;
				}
				else{
					return 8;
				}
			}
		}
		else{
			//if (link[srcNode][nodeId2].vc0Buf == 0 && link[srcNode][nodeId2].BW == 0 || link[srcNode][nodeId2].vc0Buf == 0 && link[srcNode][nodeId1].vc1Buf == 1){
			if (link[srcNode][nodeId2].vc0Buf == 0){
				int c = rand() % 2;
				if(c == 1){
					return 6;
				}
				else{
					return 8;
				}
			}
			else{
				int c = rand() % 2;
				if(c == 1){
					return 3;
				}
				else{
					return 4;
				}
			}
		}
	}
	else if(xoff > 0 && yoff > 0){
		/*int r = rand() % 2;
		if(r == 1){
			if (link[srcNode][nodeId1].vc1Buf == 0 || link[srcNode][nodeId3].vc1Buf == 0){	
				return 1;
			}
			else{
				return 5;
			}
		}
		else{
			if (link[srcNode][nodeId1].vc0Buf == 0 || link[srcNode][nodeId3].vc0Buf == 0){
				return 5;
			}
			else{
				return 1;
			}
		}*/
		return 1;
	}
	else if(xoff > 0 && yoff < 0){
		int r = rand() % 2;
		rand();
		if(r == 1){
			if (link[srcNode][nodeId1].vc1Buf == 0 && link[srcNode][nodeId1].BW == 0 || link[srcNode][nodeId4].vc1Buf == 0 && link[srcNode][nodeId4].BW == 0 || link[srcNode][nodeId1].vc1Buf == 0 && link[srcNode][nodeId1].vc0Buf == 1 || link[srcNode][nodeId4].vc1Buf == 0 && link[srcNode][nodeId4].vc0Buf == 1){
				return 2;
			}
			else{
				return 7;
			}
		}
		else{
			if (link[srcNode][nodeId1].vc0Buf == 0 && link[srcNode][nodeId1].BW == 0 || link[srcNode][nodeId4].vc0Buf == 0 && link[srcNode][nodeId4].BW == 0 || link[srcNode][nodeId1].vc0Buf == 0 && link[srcNode][nodeId1].vc1Buf == 1 || link[srcNode][nodeId4].vc0Buf == 0 && link[srcNode][nodeId4].vc1Buf == 1){
				return 7;
			}
			else{
				return 2;
			}
		}
	}
	else if(xoff < 0 && yoff > 0){
		/*int r = rand() % 2;
		if(r == 1){
			if (link[srcNode][nodeId2].vc1Buf == 0 || link[srcNode][nodeId3].vc1Buf == 0){
				return 3;
			}
			else{
				return 6;
			}
		}
		else{
			if (link[srcNode][nodeId2].vc0Buf == 0 || link[srcNode][nodeId3].vc0Buf == 0){
				return 6;
			}
			else{
				return 3;
			}
		}*/
		return 6;
	}
	else if(xoff < 0 && yoff < 0){
		int r = rand() % 2;
		rand();
		if(r == 1){
			if (link[srcNode][nodeId2].vc1Buf == 0 && link[srcNode][nodeId2].BW == 0 || link[srcNode][nodeId4].vc1Buf == 0 && link[srcNode][nodeId4].BW == 0 || link[srcNode][nodeId2].vc1Buf == 0 && link[srcNode][nodeId2].vc0Buf == 1 || link[srcNode][nodeId4].vc1Buf == 0 && link[srcNode][nodeId4].vc0Buf == 1){
				return 4;
			}
			else{
				return 8;
			}
		}
		else{
			if (link[srcNode][nodeId2].vc0Buf == 0 && link[srcNode][nodeId2].BW == 0 || link[srcNode][nodeId4].vc0Buf == 0 && link[srcNode][nodeId4].BW == 0 || link[srcNode][nodeId2].vc0Buf == 0 && link[srcNode][nodeId2].vc1Buf == 1 || link[srcNode][nodeId4].vc0Buf == 0 && link[srcNode][nodeId4].vc1Buf == 1){
				return 8;
			}
			else{
				return 4;
			}
		}
	}
	else{
		int r = rand() % 8;
		switch (r)
		{
		case 0:
			return 1;
		case 1:
			return 2;
		case 2:
			return 3;
		case 3:
			return 4;
		case 4:
			return 5;
		case 5:
			return 6;
		case 6:
			return 7;
		case 7:
			return 8;
		default:
			return 8;
			break;
		}
	}
}

int Message::transposeIJK(int srcnode, int num){
	int tempnode;
	int dstnode = 0;
	tempnode = srcnode;
	vector<int> label;
	for(int i = 0; i < 1; i++){      //计算标号
		int temp = tempnode % num;
		label.push_back(temp);
		tempnode = tempnode / num;
	}
	label.push_back(tempnode);

	tempnode = label[1];
	label[1] = label[0];
	label[0] = tempnode;


	for(int i = 0; i < 2; i ++){
		dstnode += (label[i] * (int)pow(num, i));
	}

	return dstnode;
}



int Message::transposeMinusIJK(int srcnode, int num){
	int tempnode;
	int dstnode = 0;
	tempnode = srcnode;
	vector<int> label;
	for(int i = 0; i < 1; i++){      //计算标号
		int temp = tempnode % num;
		label.push_back(temp);
		tempnode = tempnode / num;
	}
	label.push_back(tempnode);


	tempnode = label[1];
	label[1] = num - 1 - label[0];
	label[0] = num - 1 - tempnode;


	for(int i = 0; i < 2; i ++){
		dstnode += (label[i] * (int)pow(num, i));
	}

	return dstnode;
}