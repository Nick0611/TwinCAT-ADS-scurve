// CircleArray.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "queuedefine.h"
#include<vector>
using namespace std;
int main(int argc, const char * argv[]) {
	// insert code here...
	queuedefine queue;
	double *p;
	p = new double[5];

	for (int i = 0; i < 12; i++)
	{
		queue.push(i);
	}
	p = queue.output(p);
	std::cout << p[0] << ',' << p[1] << ',' << p[2] << ',' << p[3] << ',' << p[4] << std::endl;
	std::cout << p[0] << ',' << p[1] << ',' << p[2] << ',' << p[3] << ',' << p[4] << std::endl;
	delete p;
	//for(int i = 12;i < 22;i++)
	//{
	//    queue.push(i);
	//}
	std::cout << "queue_front is " << queue.front() << endl;
	std::cout << "queue_back is " << queue.back() << endl;
	queue.show();
	return 0;
}

