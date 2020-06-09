#pragma once
#include <queue>
#include <mutex>

template <class T>
class CLockQueue
{
public:
	CLockQueue() 
	{
		m_mutex = std::make_shared<std::mutex>();
	}

	~CLockQueue() 
	{
		m_mutex.reset();
	}

	void Push(T * ptr)
	{
		std::lock_guard<std::mutex> lock(*m_mutex);
		m_queue.push(ptr);
	}

	T * Front()
	{
		std::lock_guard<std::mutex> lock(*m_mutex);
		if (m_queue.empty())
		{
			return NULL;
		}
		T * ptr = m_queue.front();
		
		return ptr;
	}

	void Pop()
	{
		std::lock_guard<std::mutex> lock(*m_mutex);
		m_queue.pop();
	}

private:
	std::queue<T *>				m_queue;
	std::shared_ptr<std::mutex>	m_mutex;
};
