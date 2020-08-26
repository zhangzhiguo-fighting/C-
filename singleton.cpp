#include <iostream>
#include <mutex>
using namespace std;

class HttpServer {
public:
    static HttpServer *getInstance() { // static 没有对象也能访问该方法
        if (instance == nullptr) { // 双重验证提高多线程是的运行效率，避免每次都上锁（增大了内存消耗）
            std::unique_lock<std::mutex> lock(m_mutex);
            if (instance == nullptr) { // 懒汉模式
                instance = new HttpServer();
            }
        }
        return instance;
    }

private:
    static HttpServer *instance;
    static std::mutex m_mutex;
    HttpServer() {}
    HttpServer(const HttpServer &) = delete;
    ~HttpServer() {}
};

HttpServer *HttpServer::instance = nullptr; // 如果在这直接new一个对象，饿汉模式
std::mutex HttpServer::m_mutex;

int main() {
    HttpServer *t1 = HttpServer::getInstance();
    HttpServer *t2 = HttpServer::getInstance();
    cout << t1 << " " << t2 << endl;
    return 0;

}

