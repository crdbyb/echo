#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_
 
#include "locker.h"
#include <queue>
#include <stdio.h>
#include <exception>
#include <errno.h>
#include <pthread.h>
#include <iostream>
 
template<class T>
//encapsulated thread pool
class threadpool{
private:
    int thread_number;  //the largest number of threads in the thread pool
    pthread_t *all_threads;   //the threadpool array
    std::queue<T *> task_queue; //requests queue
    mutex_locker queue_mutex_locker;  //the mutex that protects the request queue
    cond_locker queue_cond_locker; //cond
    bool is_stop; //whether to terminate the thread
public:
    threadpool(int thread_num = 20);
    ~threadpool();
    bool append_task(T *task);
    void start();
    void stop();
private:
    //a function run by a worker thread that constantly fetches tasks from the work queue and executes them
    static void *worker(void *arg);
    void run();
    T *getTask();
};

//create the thread pool 
template <class T>
threadpool<T>::threadpool(int thread_num):
	thread_number(thread_num),is_stop(false), all_threads(NULL){
    if(thread_num <= 0)
	printf("threadpool can't init because thread_number = 0");
 
    all_threads = new pthread_t[thread_number];
    if(all_threads == NULL)
    	printf("can't init threadpool because thread array can't new");
}

//destroy the thread pool 
template <class T>
threadpool<T>::~threadpool(){
    delete []all_threads;
    stop();
}
 
template <class T>
void threadpool<T>::stop(){
        is_stop = true;
        queue_cond_locker.broadcast();
}
 
template <class T>
void threadpool<T>::start(){
    for(int i = 0; i < thread_number; ++i){
	if(pthread_create(all_threads + i, NULL, worker, this) != 0){
	    delete []all_threads;
	    throw std::exception();
	}
	if(pthread_detach(all_threads[i])){
	    delete []all_threads;
	    throw std::exception();
	}
    }
}

template <class T>
bool threadpool<T>::append_task(T *task){
    queue_mutex_locker.mutex_lock();    
    bool is_signal = task_queue.empty();
    task_queue.push(task);
    queue_mutex_locker.mutex_unlock();
    if(is_signal){
            queue_cond_locker.signal();
    }
    return true;
}
 
template <class T>
void *threadpool<T>::worker(void *arg){
    threadpool *pool = (threadpool *)arg;
    pool->run();
    return pool;
}
 
template <class T>
T* threadpool<T>::getTask(){
    T *task = NULL;
    queue_mutex_locker.mutex_lock();
    if(!task_queue.empty()){
        task = task_queue.front();
        task_queue.pop();
    }
    queue_mutex_locker.mutex_unlock();
    return task;
}
 
template <class T>
void threadpool<T>::run(){
    while(!is_stop){
        T *task = getTask();
        if(task == NULL)
                queue_cond_locker.wait();
        else{
                task->doit();
		delete task;
	}
    }
}
 
#endif
 