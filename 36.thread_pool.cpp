#include <iostream>
#include <thread>
#include <functional>
#include <vector>
#include <queue> // 线程安全：临界资源，任务队列（c++提供的容器都是非线程安全的）
#include <mutex>
#include <condition_variable>
#include <map>
using namespace std;

class Task { //将类型不同的函数打包成同一类型的任务类
public:
    template<typename T, typename ...ARGS>
    Task(T func, ARGS... args) {
        this->func = std::bind(func, forward<ARGS>(args)...); //将函数与其参数进行绑定
    }
    void operator()() { // 重载小括号去执行打包好的函数
        this->func();
        return ;
    }
    ~Task() {}

private:
    std::function<void()> func;
};

class ThreadPool {
public:
    ThreadPool(int n = 5)
    : max_threads_num(n),
    m_mutex(),
    m_cond() {}
    
    void start() {
        for (int i = 0 ; i < this->max_threads_num; i++) {
        threads.push_back(new thread(&ThreadPool::worker, this)); //绑定入口函数，创建线程对象并加入到动态数组，绑定this后 start和ThreadPool里面的this指向的是同一个对象。
        }
        return ;
    }

    void worker() {
        std::thread::id id = std::this_thread::get_id();
        is_running[id] = true;
        while (is_running[id]) {
            Task *t = this->getOneTask(); //取任务，getOneTask 要设置成私有权限，因为它会访问到类的私有成员
            (*t)(); //执行任务
            delete t; //释放任务
        }
        return ;
    }

    void stop() { //停止任务机制：我们在任务队列后面添加相应数量的特殊任务，它们的任务就是把线程中的is_running 作为置为false，让对应的线程停止工作，所以在调用stop后，前面的任务会继续执行直到结束，后面的任务将不会再被执行
        for (int i = 0; i < this->max_threads_num; i++) {
            this->addOneTask(&ThreadPool::stop_task, this); //this 为成员方法的隐藏参数
        }
        for (int i = 0; i < this->max_threads_num; i++) {
            threads[i]->join();
            delete threads[i]; // 析构线程对象
        }
        threads.clear(); // 析构动态数组空间
        return ;
    }

    template<typename T, typename ...ARGS> // 添加的任务类型任意，所以使用模板
    void addOneTask(T func, ARGS...args) {
        unique_lock<mutex> lock(m_mutex); //定义了一个局部变量，利用作用域性质。
        //std::cout << std::this_thread::get_id() << " add one task" << std::endl;
        this->task_queue.push(new Task(func, std::forward<ARGS>(args)...));
        m_cond.notify_one(); // 发出信号，唤醒一个被wait阻塞的线程去任务队列取任务
        return ;
    }

private:
    void stop_task() { // 告诉每一个线程该停止运行了
        std::thread::id id = std::this_thread::get_id();
        is_running[id] = false;
        return ;
    } 
    Task *getOneTask() {
        std::unique_lock<mutex> lock(m_mutex); // 抢碗        
        while (task_queue.empty()) {
            //std::cout << std::this_thread::get_id() << " wait one task" << std::endl;
            m_cond.wait(lock); //等待，直到队列中存在任务；在等待的时候会解锁（阻塞之后，解锁mutex给别的线程），唤醒后加锁； 把碗放回去
        } 
        //std::cout << std::this_thread::get_id() << " take one task" << std::endl;
        Task *t = task_queue.front(); //大师傅，已经给碗里装好饭，再把碗拿回来（此时会在加锁）
        task_queue.pop();
        return t;
    }

    int max_threads_num;
    vector<thread *> threads; // 存放线程对象的动态数组
    queue<Task *> task_queue; // 任务队列
    
    std::mutex m_mutex; // 互斥锁
    std::condition_variable m_cond;  // 条件信号量
    std::map<std::thread::id, bool> is_running; //将每个线程的 线程id 与 该线程的运行状态 映射
};


void thread_func1(int a, int b) {
    cout << a << " + " << b << " = " << a + b << endl;
    return ;
}

void thread_func2(int &n) {
    n += 1;
    return ;
}

void task_func(int x) {
    cout << "thread task func" << endl;
    return ;
}

int cnt = 0;

int is_prime(int x) {
    if (x < 2) return 0;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return 0;
    }
    return 1;
}

void count_prime(int l, int r) {
    for (int i = l; i <=r; i++) {
        if (is_prime(i)) __sync_fetch_and_add(&cnt, 1); //
    }
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
    for (int i = 0, j = 1; i < 5; i++, j += 200000) {
        tp.addOneTask(count_prime, j, j + 200000 - 1);
    }
    //tp.addOneTask(task_func, 123);
    
    tp.stop();
    cout << cnt << endl;
    std::cout << "mian end" << endl;
    return 0;
}

