#pragma once

#include <mutex>

#ifndef queuedefine_hpp
#define queuedefine_hpp

class queuedefine
{
private:
	double *array;//数组
	int queue_front;//队列头序号
	int queue_back;//队列尾序号
	int length;//数组长度
	std::mutex							m_mutex;
public:

	queuedefine();//环形队列构造函数
	~queuedefine();//环形队列析构函数

	bool empty_check();//检查队列是否为空
	bool full_check();//检查队列是否即将为满队列
	int get_size();//返回队列元素数量
	double & front();//返回队列头元素
	double & back();//返回队列尾元素
	void pop();//出队
	void push(const double & element);//入队element
	void show();//遍历队列
	void change_length(int new_length);//在需要时改变队列长度
	double *output(double *j);
};

#endif /* queuedefine_hpp */

