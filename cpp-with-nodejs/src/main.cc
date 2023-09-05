#include <napi.h>
#include "MyWorker.h"
Napi::String Hello(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    return Napi::String::New(env, "world"); //返回一个js字符串
}

Napi::Value Add(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    //判断参数个数，如果参数个数小于2则抛出异常    
    if (info.Length() < 2)
    {
        Napi::TypeError::New(env, "Wrong arguments numbers").ThrowAsJavaScriptException();
        return env.Null();
    }
    double result = 0;
    //遍历所有输入参数
    for (int i = 0; i < info.Length(); i++)
    {
        //如果输入参数类型不是数字类型，则抛出异常
        if (!info[i].IsNumber())
        {
            Napi::TypeError::New(env, "Wrong arguments type").ThrowAsJavaScriptException();
            return env.Null();
        }
        //格式化输入参数为浮点类型并累加
        double arg = info[i].As<Napi::Number>().DoubleValue();
        result += arg;
    }
    //把累加结果返回给调用者
    Napi::Number resultVal = Napi::Number::New(env, result);
    return resultVal;
}
Napi::Value AsyncMethod(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    //接收Object类型的参数
    Napi::Object runInfo = info[0].As<Napi::Object>();
    //此Object类型的参数必定包含timeSpan和callBack两个属性
    if (runInfo.Get("timeSpan").IsNothing() || runInfo.Get("callBack").IsNothing()) {
        Napi::TypeError::New(env, "Wrong arguments Type").ThrowAsJavaScriptException();
        return env.Null();
    }
    //timeSpan属性为数字类型
    int timeSpan = runInfo.Get("timeSpan").Unwrap().As<Napi::Number>();
    //callBack属性为回调方法类型
    Napi::Function callback = runInfo.Get("callBack").Unwrap().As<Napi::Function>();
    //实例化自定义的异步处理对象，把timeSpan和callBack传递给异步处理对象
    MyWorker* asyncWorker = new MyWorker(callback, timeSpan);
    //开始执行异步任务
    asyncWorker->Queue();
    //返回一个对象，此对象包含msg属性，msg属性的值为字符串please wait...
    Napi::Object obj = Napi::Object::New(env);
    obj.Set(Napi::String::New(env, "msg"), Napi::String::New(env, "please wait..."));
    return obj;
}


Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    //公开hello方法
    exports.Set(Napi::String::New(env, "hello"), Napi::Function::New(env, Hello));
    exports.Set(Napi::String::New(env, "add"), Napi::Function::New(env, Add));
    exports.Set(Napi::String::New(env, "asyncMethod"), Napi::Function::New(env, AsyncMethod));
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)