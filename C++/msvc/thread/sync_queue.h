#pragma once
#include <mutex>
#include <condition_variable>
#include <cassert>
#include <type_traits>
#include <atomic>
#include<queue>

namespace moon
{
	template<typename T, typename TContainer = std::deque<T>, size_t max_size = 50>
	class sync_queue
	{
	public:
		sync_queue()
			:m_exit(false)
		{
		}

		sync_queue(const sync_queue& t) = delete;
		sync_queue& operator=(const sync_queue& t) = delete;

		void push_back(const T& x)
		{
			std::unique_lock<std::mutex> lck(m_mutex);
			m_notFull.wait(lck, [this] {return m_exit || (m_queue.size() < max_size); });
			m_queue.push_back(x);
		}

		template<typename _Tdata>
		void emplace_back(_Tdata&& v)
		{
			std::unique_lock<std::mutex> lck(m_mutex);
			m_notFull.wait(lck, [this] {return m_exit || (m_queue.size() < max_size); });
			m_queue.emplace_back(std::forward<_Tdata>(v));
		}

		size_t size()
		{
			std::unique_lock<std::mutex> lck(m_mutex);
			return m_queue.size();
			
		}
		
		//替代pop_front
		TContainer move()
		{
			std::unique_lock<std::mutex> lck(m_mutex);
			auto tmp = std::move(m_queue);
			m_notFull.notify_one();
			return std::move(tmp);
		}

		//当程序退出时调用此函数,触发条件变量
		void exit()
		{
			m_exit = true;
		}

	private:
		std::mutex							m_mutex;
		std::condition_variable		m_notFull;
		TContainer							m_queue;
		std::atomic_bool					m_exit;
	};

}