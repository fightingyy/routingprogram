#include"Calculate.h"


float GetAveDelay(long totalCycle, long arriveMessage){  //totalcycle��ʾ���е����message����ʱ��֮��
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