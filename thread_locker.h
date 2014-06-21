/*
 * thread_locker.h
 *
 * Created on: May 2, 2014
 * Author: root
 */
#ifndef LOCKER_H_
#define LOCKER_H_
#include <exception>
#include <pthread.h>
class ThreadLocker {
public:
        ThreadLocker()
        {
                if(pthread_mutex_init(&m_mutex,NULL) != 0)
                {
                        throw std::exception();
                }
        }
        ~ThreadLocker()
        {
                pthread_mutex_destroy(&m_mutex);
        }
        //加锁
        bool Lock()
        {
                return pthread_mutex_lock(&m_mutex) == 0;
        }
        //解锁
        bool Unlock()
        {
                return pthread_mutex_unlock(&m_mutex) == 0;
        }
private:
        pthread_mutex_t m_mutex;
};
#endif
