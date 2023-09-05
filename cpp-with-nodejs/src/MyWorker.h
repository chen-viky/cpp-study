//头文件 src\MyWorker.h
#pragma once
#include <napi.h>
class MyWorker : public Napi::AsyncWorker
{
    public:
        MyWorker(Napi::Function &callback, int runTime);
        virtual ~MyWorker(){};
        void Execute();
        void OnOK();
    private:
        int runTime;
};
