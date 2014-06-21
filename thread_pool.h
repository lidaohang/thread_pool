/*
 * thread_pool.h
 *
 * Created on: May 2, 2014
 * Author: root
 */
#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_
#include "thread_locker.h"
#include "thread_sem.h"
#include <list>
#include <cstdio>
#include <exception>
#include <pthread.h>
template<typename T>
class ThreadPool {
public:
        ThreadPool( int thread_number = 1, int max_requests = 10000 );
        ~ThreadPool();
        bool Push( T* request ); //推送任务
private:
        static void* Worker(void* arg);// 工作线程运行的函数
        void Run();
        int m_thread_number; //线程池中到线程数
        int m_max_requests; //请求队列中允许的最大请求数
        pthread_t* m_threads; //描述线程池到数组，其大小为m_thread_number
        std::list< T* > m_workqueue; //队列
        ThreadLocker m_queuelocker; /*保护请求队列的互斥锁*/
        ThreadSem m_queuestat; /*是否有任务需要处理*/
        bool m_stop; /*是否结束线程*/
};
template< typename T >
ThreadPool< T >::ThreadPool( int thread_number, int max_requests ) :
        m_thread_number( thread_number ),
        m_max_requests( max_requests ),
        m_stop( false ),
        m_threads( NULL )
{
    if( ( thread_number <= 0 ) || ( max_requests <= 0 ) )
    {
        throw std::exception();
    }
    m_threads = new pthread_t[ m_thread_number ];
    if( ! m_threads )
    {
        throw std::exception();
    }
    for ( int i = 0; i < thread_number; ++i )
    {
        printf( "create the %dth thread\n", i );
        if( pthread_create( m_threads + i, NULL, Worker, this ) != 0 )
        {
            delete [] m_threads;
            throw std::exception();
        }
        if( pthread_detach( m_threads[i] ) )
        {
            delete [] m_threads;
            throw std::exception();
        }
    }
}
template< typename T >
ThreadPool< T >::~ThreadPool()
{
    delete [] m_threads;
    m_stop = true;
}
template< typename T >
bool ThreadPool< T >::Push( T* request )
{
    m_queuelocker.Lock(); // 工作队列加锁
    if ( m_workqueue.size() > m_max_requests )
    {
        m_queuelocker.Unlock();
        return false;
    }
    m_workqueue.push_back( request );
    m_queuelocker.Unlock();
    m_queuestat.Post();
    return true;
}
template< typename T >
void* ThreadPool< T >::Worker( void* arg )
{
    ThreadPool* pool = ( ThreadPool* )arg;
    pool->Run();
    return pool;
}
template< typename T >
void ThreadPool< T >::Run()
{
    while ( ! m_stop )
    {
        m_queuestat.Wait();
        m_queuelocker.Lock();
        if ( m_workqueue.empty() )
        {
            m_queuelocker.Unlock();
            continue;
        }
        T* request = m_workqueue.front(); //返回链表第一个元素的引用
        m_workqueue.pop_front();// 删除链表头到一个元素
        m_queuelocker.Unlock();
        if ( ! request )
        {
            continue;
        }
        request->process();
    }
}
#endif /* THREAD_POOL_H_ */
