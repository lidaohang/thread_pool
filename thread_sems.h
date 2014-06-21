/*
 * thread_sems.h
 *
 * Created on: May 2, 2014
 * Author: root
 */
#ifndef SEMS_H_
#define SEMS_H_
#include <semaphore.h>
#include <exception>
class ThreadSem
{
public:
        ThreadSem()
    {
        if( sem_init( &m_sem, 0, 0 ) != 0 )
        {
            throw std::exception();
        }
    }
    //销毁信号量
    ~ThreadSem()
    {
        sem_destroy( &m_sem );
    }
    //等待信号量
    bool Wait()
    {
        return sem_wait( &m_sem ) == 0;
    }
    //增加信号量
    bool Post()
    {
        return sem_post( &m_sem ) == 0;
    }
private:
    sem_t m_sem;
};
#endif /* SEMS_H_ */
