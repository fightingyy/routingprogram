#include<iostream>
#include<fstream>
#include<cmath>
#include"Message.h"
#include"Mesh.h"
#include"Route.h"
#include"Calculate.h"
#include"common.h"
#include"XYRoute.h"
#include"SpaningTree.h"
#include<list>

using namespace std;
Link link[K*K][K*K];
Link linkTree[K*K][K*K];

int main()
{

	ofstream result;
	vector<Node> mesh;

	num = K;
	dim = 2;
	Initialize(mesh, num, dim);
	setRouteTable(mesh, num, dim);

	int t = 0;

	numAll = (int)pow(num, dim);
	for(InjectionRate = 0.01; InjectionRate < 1.0;  ){
//	for(InjectionRate = 0.3; t < 48; t++){
//		mesh[t].hasUpLink = false;
		//tempFlits = InjectionRate * numAll * (2 * num * num * 2 * 2) / numAll;//n平方乘以8除以节点总数=注入率为1时每个节点平均产生的flit
		//tempFlits = InjectionRate * 2 * 4 * num ;

		Saturation = (double)(num * 2 * 2) /(double) (num * num); //注入率为1时每个点每个cycle产生的flit
		tempFlits = InjectionRate * Saturation * num * num;//网络中所有节点每个cycle产生的flit

		list<Message> message;
		list<Message> messageTree;
		InitializeVar();
		InitializeVarTree();

		while(cycle < 30000){
	//		cout<<cycle<<endl;
			generateFlits += tempFlits;

			//if(cycle < 8000)
			while(generateFlits >= 16){
				Message mess(mesh, numAll, num);
				if(cycle <= 10000){
					mess.warmup = true;
				}
				message.push_back(mess);
				messageTree.push_back(mess);
				generateFlits -= 16;
				if(cycle > 10000){
					totalMessage ++;
				}
			}


			/*while(generateFlits >= 16){
				Message mess(mesh, numAll, num);
				if(cycle <= 0){
					mess.warmup = true;
				}
				if(totalMessage < 200){
					message.push_back(mess);
				}

				generateFlits -= 16;
				if(totalMessage < 200 ){
					totalMessage ++;
				}
			}*/



			Routing(mesh, message, link, cycle, arriveMessage, totalCycle, dim, num);
			//XYRouting(mesh, message, link, cycle, arriveMessage, totalCycle, dim, num);
			RoutingTree(mesh, messageTree, linkTree, cycle, arriveMessageTree, totalCycleTree, dim, num);
			cycle ++;
		}

		cout<<InjectionRate<<" "<<totalMessage<<" "<<arriveMessage<<" "<<GetAveDelay(totalCycle, arriveMessage)<<" "<<GetThroughput(arriveMessage, cycle-10000, numAll)<<endl;
		cout<<InjectionRate<<" "<<totalMessage<<" "<<arriveMessageTree<<" "<<GetAveDelay(totalCycleTree, arriveMessageTree)<<" "<<GetThroughput(arriveMessageTree, cycle-10000, numAll)<<endl;

		result.open("uniform16_10000_1.xls",ios::app);
		if(result.is_open()){
			Injection = (double)tempFlits / (double)numAll;
			result<<Injection<<"\t";
			AveDelay = GetAveDelay(totalCycle, arriveMessage);
			Throughput = GetThroughput(arriveMessage, cycle - 10000, numAll);
			result<<AveDelay<<"\t"<<Throughput<<"\t";
			AveDelay = GetAveDelay(totalCycleTree, arriveMessageTree);
			Throughput = GetThroughput(arriveMessageTree, cycle - 10000, numAll);
			result<<AveDelay<<"\t"<<Throughput<<"\t";
			
		}
		result.close();
		ClearLink(link);
		ClearLink(linkTree);
		ClearMessage(message);
		ClearMessage(messageTree);
		if (InjectionRate < 0.61){
			InjectionRate += 0.05;
		}
		else
			InjectionRate += 0.02;
//		mesh[t].hasUpLink = true;
	}//end for
	system("pause");
	return 0;
}

