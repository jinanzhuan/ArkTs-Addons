//
// Created on 2024/4/9.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "include/napi.h"
#include <hilog/log.h>
#include "myobject.h"

Napi::String Method(const Napi::CallbackInfo& info) {
    OH_LOG_Print(LOG_APP, LOG_ERROR, 0xFF00, "Method", "Method execute");
    Napi::Env env = info.Env();
    return Napi::String::New(env, "world");
}

Napi::Value Add(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsNumber() || !info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  double arg0 = info[0].As<Napi::Number>().DoubleValue();
  double arg1 = info[1].As<Napi::Number>().DoubleValue();
  Napi::Number num = Napi::Number::New(env, arg0 + arg1);

  return num;
}

Napi::String RunCallback(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Function cb = info[0].As<Napi::Function>();
  Napi::Value value = cb.Call(env.Global(), {Napi::String::New(env, "hello world")});
    return value.As<Napi::String>();
}

Napi::Object CreateObject(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);
    // 声明了一个属性 msg，并赋值为 info[0]
  obj.Set(Napi::String::New(env, "msg"), info[0].ToString());
  return obj;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "hello"), Napi::Function::New(env, Method));
  exports.Set(Napi::String::New(env, "add"), Napi::Function::New(env, Add));
  exports.Set(Napi::String::New(env, "nativeCallback"), Napi::Function::New(env, RunCallback));
  exports.Set(Napi::String::New(env, "createObject"), Napi::Function::New(env, CreateObject));
    MyObject::Init(Napi::Env(env), Napi::Object(env, exports));
  return exports;
}

// NODE_API_MODULE(napitest, Init)

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
  OH_LOG_Print(LOG_APP, LOG_ERROR, 0xFF00, "Init", "object execute");
  Napi::Object object = Init(Napi::Env(env), Napi::Object(env, exports));
  return object;
}
EXTERN_C_END

static napi_module napiTestModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "napitest",
    .nm_priv = nullptr,
    .reserved = {0},
};

extern "C" __attribute__((constructor)) void RegisterNapiTestModule() { napi_module_register(&napiTestModule); }