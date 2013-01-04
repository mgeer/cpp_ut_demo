#ifndef __UT_SAMPLE_MULTI_THREAD_H__
#define __UT_SAMPLE_MULTI_THREAD_H__
#include <pthread.h>
#include <boost/noncopyable.hpp>
namespace UTSample {
class MutexLock : boost::noncopyable {
public:
	MutexLock() { 
		pthread_mutex_init(&mutex, NULL); 
	}
	~MutexLock() { 
		pthread_mutex_destroy(&mutex); 
	}
	void lock() { 
		pthread_mutex_lock(&mutex); 
	}
	void unlock() { 
		pthread_mutex_unlock(&mutex); 
	}
	pthread_mutex_t* getPthreadMutex() { 
		return &mutex; 
	}
private:
	pthread_mutex_t mutex;
};

class MutexLockGuard : boost::noncopyable {
public:
	explicit MutexLockGuard(MutexLock& mutex) : mutex(mutex) { 
		mutex.lock(); 
	}
	~MutexLockGuard() { 
		mutex.unlock(); 
	}
private:
	MutexLock& mutex;
};

class Condition : boost::noncopyable {
public:
    Condition(MutexLock& mutex) : mutex(mutex) {
        pthread_cond_init(&pcond, NULL); 
    }
    ~Condition() {
        pthread_cond_destroy(&pcond); 
    }
    void wait() {
        pthread_cond_wait(&pcond, mutex.getPthreadMutex()); 
    }
    void notify() {
        pthread_cond_signal(&pcond); 
    }

    void notifyAll() {
        pthread_cond_broadcast(&pcond); 
    }
    private:
        MutexLock& mutex;
        pthread_cond_t pcond;
};
}
#endif

