#include "queuedefine.h"
#include <iostream>
#include <string>
using namespace std;

queuedefine::queuedefine()
{
	length = 1;
	array = new double[length];
	queue_front = 0;
	queue_back = 0;
}

queuedefine::~queuedefine()
{
	cout << "Bye" << endl;
}

bool queuedefine::empty_check()
{
	if (queue_front == queue_back)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool queuedefine::miss_check()
{
	if ((queue_front+15) > queue_back)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool queuedefine::full_check()
{
	if ((queue_back + 1) % length == (queue_front%length))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int queuedefine::get_size()
{
	int size;
	int location_start = queue_front % length;
	int location_end = queue_back % length;
	if (location_end > location_start)
	{
		size = location_end - location_start;
	}
	else if (location_start == location_end)
	{
		size = 0;
	}
	else
	{
		size = length - (queue_front%length) + (queue_back%length);
	}
	return size;
}

double & queuedefine::front()
{
	int location = (queue_front + 1) % length;
	return array[location];
}

double & queuedefine::back()
{
	int location = queue_back % length;
	return array[location];
}

void queuedefine::push(const double & element)
{
	int start = queue_front % length;
	//注意：不要写成int end = queue_back % length + 1
	int end = (queue_back + 1) % length;
	if (start == end)
	{
		//cout << "full_check = 1" << endl;
		change_length(2 * length);
		length = 2 * length;

	}
	queue_back = (queue_back + 1) % length;
	array[queue_back] = element;
}

void queuedefine::change_length(int new_length)
{
	double *temp_array = new double[new_length];
	int start = (queue_front + 1) % length;
	if (start < 2)
	{
		copy(array + start, array + start + length - 1, temp_array);
	}
	else
	{
		copy(array + start, array + length, temp_array);
		copy(array, array + queue_back + 1, temp_array + length - start);
	}
	queue_front = 2 * length - 1;
	queue_back = length - 2;
	delete[] array;
	array = temp_array;
}

void queuedefine::pop()
{
	queue_front = (queue_front + 1) % length;
}

void queuedefine::show()
{
	cout << "length is " << length << endl;
	cout << "size is " << get_size() << endl;
	cout << "queue_front is " << queue_front << endl;
	cout << "queue_back is " << queue_back << endl;
	for (int i = 0; i < get_size(); i++)
	{
		int location = (queue_front + i + 1) % length;
		cout << "第" << i + 1 << "个元素在数组的位置为" << location << ",其值为：" << endl;
		cout << array[location] << endl;
	}
}

double* queuedefine::output(double *j)
{
	for (int i = 0; i < 15; i++)
	{
		int location = (queue_front + i + 1) % length;
		j[i] = array[location];
	}
	return j;
}