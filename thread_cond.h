/*
 * thread_cond.h
 *
 * Created on: May 3, 2014
 * Author: root
 */
#ifndef COND_H_
#define COND_H_
#include <pthread.h>
#include <exception>
class ThreadCond
{
public:
        ThreadCond()
        {
                if( pthread_mutex_init( &m_mutex, NULL ) != 0)
                {
                        throw std::exception();
                }
                if( pthread_cond_init( &m_cond, NULL) != 0)
                {
                        //释放资源
                        pthread_mutex_destroy( &m_mutex);
                        throw std::exception();
                }
        }
        //销毁条件变量
        ~ThreadCond()
        {
                pthread_mutex_destroy( &m_mutex );
                pthread_cond_destroy( &m_cond);
        }
        //等待条件变量
        bool Wait()
        {
                int ret = 0;
                pthread_mutex_lock( &m_mutex);
                ret = pthread_cond_wait( &m_cond, &m_mutex );
                pthread_mutex_unlock( &m_mutex );
                return ret == 0;
        }
        //唤醒等待条件变量的线程
        bool Signal()
        {
                return pthread_cond_signal( &m_cond ) == 0;
        }
private:
        pthread_mutex_t m_mutex;
        pthread_cond_t m_cond;
};
#endif /* COND_H_ */
