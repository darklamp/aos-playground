
#ifndef SYNC_QUEUE_H_
#define SYNC_QUEUE_H_

#include <list>
#include <mutex>
#include <condition_variable>

// NB: since this is a template class, its implementation has to go in the header file!
template<typename T>
class SynchronizedQueue
{
public:
    SynchronizedQueue() {}
    
    void put(const T & data);
    
    T get();
    
    size_t size();

private:
    // This forbids the copy operation
    SynchronizedQueue(const SynchronizedQueue &)=delete;
    // This forbids the = operator from being used (it tells the compiler not to allow it)
    SynchronizedQueue & operator=(const SynchronizedQueue &)=delete;
    
    std::list<T> queue;
    std::mutex myMutex;
    std::condition_variable myCv;
};

template<typename T>
void SynchronizedQueue<T>::put(const T& data)
{
    std::unique_lock<std::mutex> lck(myMutex);
    queue.push_back(data);
    myCv.notify_one();
}
template<typename T>
T SynchronizedQueue<T>::get()
{
    std::unique_lock<std::mutex> lck(myMutex);
    while(queue.empty()) myCv.wait(lck);
    T result=queue.front();
    queue.pop_front();
    return result;
}

template<typename T>
size_t SynchronizedQueue<T>::size()
{
    std::unique_lock<std::mutex> lck(myMutex);
    return queue.size();
}

#endif // SYNC_QUEUE_H_
