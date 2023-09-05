//实现文件 src\MyWorker.cc
#include "MyWorker.h"
#include <chrono>
#include <thread>


//构造函数，初始化列表中初始化基类AsyncWorker对象
MyWorker::MyWorker(Napi::Function &callback, int runTime)
    : AsyncWorker(callback), runTime(runTime){};


//执行异步方法，此方法执行完成后会调用OnOK方法
void MyWorker::Execute()
{
    std::this_thread::sleep_for(std::chrono::seconds(runTime));
    if (runTime == 4)
    {
        SetError("failed after 'working' 4 seconds.");
    }
};

//异步方法执行完成
void MyWorker::OnOK()
{
    //创建一个数组对象
    Napi::Array arr = Napi::Array::New(Env(),3);
    arr.Set(Napi::Number::New(Env(), 0), Napi::String::New(Env(), "test1"));
    arr.Set(Napi::Number::New(Env(), 1), Napi::String::New(Env(), "test1"));
    arr.Set(Napi::Number::New(Env(), 2), Napi::Number::New(Env(), 123));
    //把数组对象传递给回调方法
    Callback().Call({Env().Null(), arr});
};
