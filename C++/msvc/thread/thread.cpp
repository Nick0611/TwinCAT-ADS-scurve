// thread.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
//#include<queue>
#include<windows.h>
#include<stdlib.h>
#include <thread> 
//#include <mutex>
#include <stdexcept>

#include "sync_queue.h"
#include "queuedefine.h"

std::mutex mtx1;
std::mutex mtx2;
std::queue<double> queue_double;

void printThreadID1(int i)
{
	mtx1.lock();
		std::cout << "thread # " << i << '\n';
	//std::lock_guard<std::mutex>lck1(mtx1, std::adopt_lock);
	mtx1.unlock();
	Sleep(10);
}
void printThreadID2(std::queue<double> queue_double)
{
	mtx1.lock();
		std::cout << "thread ! " << queue_double.back() << '\n';
	mtx1.unlock();
	Sleep(10);
}

void testAdoptingConstructor(int i, double j)
{
	std::thread threads[1];
		threads[0] = std::thread(printThreadID1, i);
		std::cout << "thread ! " << j << '\n';
		//threads[1] = std::thread(printThreadID2, queue_double);
		//threads[0].join();
		for (auto& th : threads)
		{
			th.join();
		}
}

void SendPosition()
{
	int i = 0;
	while (1)
	{
		i++;
		//std::cout << i << std::endl;
	}
}

int main()
{
	int i = 0;
	double j = 0;
	//while (true)
	//{
	//	testAdoptingConstructor(i, j);
	//	i++;
	//	j = j + 2;
	//	queue_double.push(j);

	//}
	while (1)
	{
		std::cin >> i;
		if (i == 1)
		{
			std::thread th1(SendPosition);
			while (1);
			th1.join();
		}
		if (i == 2)
		{
			while (1)
			{
				j++;
				std::cout << j << std::endl;
			}
		}
	}
	
	
	
	return 0;
}
//
//struct SAddContext
//{
//	/*SAddContext()
//		:a(0), b(b)
//	{
//
//	}*/
//	int a[2];
//	//int b;
//};
//
//struct SCache10
//{
//	double a1[15]; 
//};
//
//struct SOut10
//{
//	double a1[15];
//};
//
//struct SAddResult
//{
//	SAddResult()
//		:a(0), b(0), result(0)
//	{
//
//	}
//	int a;
//	int b;
//	int result;
//};
//
//int main()
//{
//	moon::sync_queue<SCache10> que1;//main thread - calculate thread
//	moon::sync_queue<SOut10> que2;//calculate thread - print thread
//
//	std::thread calculate([&que1, &que2]() {
//		while (1)
//		{
//			//如果队列为空 ，等待
//			if (que1.size() == 0)
//			{
//				std::this_thread::sleep_for(std::chrono::milliseconds(100));
//			}
//
//			//获取所有异步计算请求
//			auto data = que1.move();
//			for (auto& dat : data)
//			{
//				SOut10 sr;
//				for (int i = 0; i < 15; i++)
//				{
//					sr.a1[i] = dat.a1[i];
//				}
//				que2.push_back(sr);
//			}
//		}
//	});
//
//	std::thread printThread([&que2]() {
//		while (1)
//		{
//			//如果队列为空 ，等待
//			if (que2.size() == 0)
//			{
//				std::this_thread::sleep_for(std::chrono::milliseconds(100));
//			}
//
//			auto data = que2.move();
//			for (auto& dat : data)
//			{
//				for (int i = 0; i < 15; i++)
//				{
//					std::cout << dat.a1[i] << ",";
//				}
//				std::cout << std::endl;
//			}
//		}
//	});
//	static queuedefine queue1;
//	
//	
//	int j = 0;
//	while (1)
//	{
//		double *p1;
//		SCache10 sc;
//		for (int i = 0; i < 20; i++)
//		{
//			queue1.push(j);
//			j++;
//		}
//		p1 = new double[15];
//		p1 = queue1.output(p1);
//		for (int i = 0; i < 15; i++)
//		{
//			sc.a1[i] = p1[i];
//		}
//		delete p1;
//		queue1.pop(); queue1.pop(); queue1.pop(); queue1.pop(); queue1.pop(); queue1.pop(); queue1.pop(); queue1.pop(); queue1.pop(); queue1.pop();
//		queue1.pop(); queue1.pop(); queue1.pop(); queue1.pop(); queue1.pop();
//		que1.push_back(sc);
//	}
//	
//	//int x = 0;
//	//int y = 0;
//
//	//while (std::cin >> x >> y)
//	//{
//	//	SAddContext sc;
//	//	sc.a[0] = x;
//	//	sc.a[1] = y;
//	//	que1.push_back(sc);
//	//}
//};


