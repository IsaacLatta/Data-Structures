#include "ThreadPool.h"
#include <iostream>
#include <stdio.h>
#include <cstring>

#define BUFFER_SIZE 128
#define THREAD_COUNT 3

int task(int ret)
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return ret;
}

int main()
{
    ThreadPool pool(THREAD_COUNT);
    std::future<int> res1, res2, res3; 

    res1 = pool.pushWork(task, 1);
    res2 = pool.pushWork(task, 2);
    res3 = pool.pushWork(task, 3);

    std::cout << "Task 1 result: " << res1.get() << "\n";
    std::cout << "Task 2 result: " << res2.get() << "\n";
    std::cout << "Task 3 result: " << res3.get() << "\n";

    return 0;
}

std::mutex print_mutex;

void print(char* s)
{
    std::lock_guard<std::mutex> lock(print_mutex);
    std::cout << s;
}

void example_task(int task_num, int time)
{
    char buffer[BUFFER_SIZE];
    snprintf(buffer, BUFFER_SIZE, "Task:%d is executing\n", task_num);
    print(buffer);
    std::memset(buffer, '\0', BUFFER_SIZE);
    std::this_thread::sleep_for(std::chrono::seconds(time));
    snprintf(buffer, BUFFER_SIZE, "Task:%d is finished\n", task_num);
    print(buffer);
}

int main()
{
    ThreadPool pool(10);
    for(int i = 0; i < 10; i++)
    {
        (void)pool.addTask(example_task, i, 3);
    }
   
    return 0;
}
