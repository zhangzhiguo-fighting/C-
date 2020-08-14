#include <iostream>
#include <thread>
#include <functional>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

class Task {
public:
    template<typename T, typename ...ARGS>
    Task(T func, ARGS... args) {
        this->func = std::bind(func, forward<ARGS>(args)...); //将函数与其参数进行绑定
    }
    void operator()() {
        this->func();
        return ;
    }

private:
    function<void()> func;
};


class ThreadPool {
public:
    ThreadPool(int n = 5)
    : is_running(false), max_threads_num(n), m_mutex(), m_cond() {}
    
    void start() {
        unique_lock<mutex> lock(m_mutex);
        if (is_running) return ;
        is_running = true;
        for (int i = 0 ; i < this->max_threads_num; i++) {
        threads.push_back(new thread(&ThreadPool::worker, this)); //绑定入口函数
        }
        return ;
    }
    
    Task *get_one_task() {
        unique_lock<mutex> lock(m_mutex);
        while(Tasks.empty() && is_running) {
            m_cond.wait(lock);
        }
        Task *t = nullptr;
        if (!Tasks.empty() && is_running) {
            t = Tasks.front();
            Tasks.pop();
        }
        return t;
    }

    void worker() {
        while (is_running) {
            Task *t = get_one_task();
            if (t != nullptr) {
                //t->run;
            }
        }
        return ;
    }
    

    void stop() {
        if (is_running == false) return;
        is_running = false;
        for (int i =0; i < this->max_threads_num; i++) {
            threads[i]->join();
            delete threads[i]; // 析构线程对象
        }
        threads.clear(); // 析构动态数组空间
        return ;
    }

private:
    bool is_running;
    int max_threads_num;
    vector<thread *> threads;
    queue<Task *> Tasks;
    mutex m_mutex;
    condition_variable m_cond;
};


void thread_func1(int a, int b) {
    cout << a << " + " << b << " = " << a + b << endl;
    return ;
}

void thread_func2(int &n) {
    n += 1;
    return ;
}

int main() {
    Task t1(thread_func1, 3, 4);
    Task t2(thread_func1, 5, 6);
    Task t3(thread_func1, 7, 8);
    t1(), t2(), t3();
    int n = 0;

    Task t4(thread_func2, ref(n));
    t4(), t4(), t4();
    cout << n << endl;

    ThreadPool tp(6);
    tp.start();
    tp.stop();
    return 0;
}

