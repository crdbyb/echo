#ifndef _LOCKER_H_
#define _LOCKER_H_
#include <exception>
#include <pthread.h>
#include <cstdio>
#include <semaphore.h>
using namespace std;

//encapsulation semaphore
class sem_locker{
private:
    sem_t m_sem;
 
public:
    //create and init semaphore, report errors by throwing exception because the constructor returns no value	
	sem_locker(){
	if(sem_init(&m_sem,0,0) != 0){
        throw std :: exception();
        }
    }
    //destroy semaphore
    ~sem_locker(){
	sem_destroy(&m_sem);
    }
    //wait semaphore
    bool wait(){
	return sem_wait(&m_sem) == 0;
    }
    //increasing semaphore
    bool add(){
	return sem_post(&m_sem) == 0;
    }
};

//encapsulation the mutex 
class mutex_locker{
private:
    pthread_mutex_t m_mutex;
 
public:
    //create and init the mutex, report errors by throwing exception because the constructor returns no value
    mutex_locker(){
    	if(pthread_mutex_init(&m_mutex, NULL) != 0){
        throw std::exception();
        }
    }
    //destroy the mutex
    ~mutex_locker(){
	pthread_mutex_destroy(&m_mutex);
    }
    //locked
    bool mutex_lock(){
	return pthread_mutex_lock(&m_mutex) == 0;
    }
    //unlock
    bool mutex_unlock(){
	return pthread_mutex_unlock(&m_mutex) == 0;
    }
};
 
//encapsulation cond
class cond_locker
{
private:
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
 
public:
    //create and init cond
    cond_locker(){
	if(pthread_mutex_init(&m_mutex, NULL) != 0){
        throw std::exception();
        }
        if(pthread_cond_init(&m_cond, NULL) != 0){
        //once the constructor has a problem,it should immediately release the resources that have been successfully allocated
        pthread_mutex_destroy(&m_mutex);
        throw std::exception();
        }
    }
    // destroy mutex and cond
    ~cond_locker()
    {
	pthread_mutex_destroy(&m_mutex);
	pthread_cond_destroy(&m_cond);
    }
    //wait cond
    bool wait()
    {
	int ans = 0;
	pthread_mutex_lock(&m_mutex);
	ans = pthread_cond_wait(&m_cond, &m_mutex);
	pthread_mutex_unlock(&m_mutex);
	return ans == 0;
    }
    //wakes up the thread waiting for the condition variable
    bool signal(){
	return pthread_cond_signal(&m_cond) == 0;
    }
 
    //wakes up all the thread waiting for the condition variable
    bool broadcast(){
            return pthread_cond_broadcast(&m_cond) == 0;
    }
};
 
#endif
