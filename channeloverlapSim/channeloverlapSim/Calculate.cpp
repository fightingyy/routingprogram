#include"Calculate.h"


float GetAveDelay(long totalCycle, long arriveMessage){  //totalcycle表示所有到达的message所花时间之和
	float temp;
	temp = (float)totalCycle / (float)arriveMessage;
	return temp;
}


float GetThroughput(long arriveMessage, long cycle, long numAll){
	float temp;
	temp = (float)arriveMessage / (float)cycle;
	temp = 16 * temp / (float)numAll;
	return temp;
}