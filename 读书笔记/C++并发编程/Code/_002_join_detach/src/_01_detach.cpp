#include <iostream>
#include <thread>

struct func
{
    int &i;
    func(int &i_) : i(i_) {}

    // () 操作符重载，可以避免代码中出现函数指针
    void operator()()
    {
        for (unsigned j = 0; j < 1000; ++j)
        {
            do_something(i);
        }
    }

    void do_something(int &i)
    {
        std::cout << i << std::endl;
    }
};

void oops1()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach();
}