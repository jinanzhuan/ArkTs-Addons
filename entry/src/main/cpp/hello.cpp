// hello.cpp

#include <napi/native_api.h>
#include <hilog/log.h>

// 6. 实现Native侧的CallNative和NativeCallArkTS接口
static napi_value CallNative(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    // 声明参数数组
    napi_value args[2] = {nullptr};
    
    // 获取传入的参数并依次放入参数数组中
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    
    // 依次获取参数
    double value0 = 0;
    double value1 = 0;
    if (napi_ok != napi_get_value_double(env, args[0], &value0) ||
        napi_ok != napi_get_value_double(env, args[1], &value1)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, 0xFF00, "CallNative", "napi_get_value_double failed");
        return nullptr;
    }

    napi_value sum;
    napi_create_double(env, value0 + value1, &sum);
    return sum;
}

static napi_value NativeCallArkTS(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    // 声明参数数组
    napi_value args[1] = {nullptr};
    
    // 获取传入的参数并依次放入参数数组中
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    
    // 创建一个int，作为ArkTS的入参
    napi_value argv = nullptr;
    if (napi_ok != napi_create_int32(env, 2, &argv)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, 0xFF00, "NativeCallArkTS", "napi_create_int32 failed");
        return nullptr;
    }
    
    napi_value result = nullptr;
    napi_call_function(env, nullptr, args[0], 1, &argv, &result);
    
    return result;
}

EXTERN_C_START
// 2. 模块初始化
static napi_value Init(napi_env env, napi_value exports) {
    OH_LOG_Print(LOG_APP, LOG_ERROR, 0xFF00, "Init", "Init");
    // ArkTs接口与C++接口的绑定和映射
    napi_property_descriptor desc[] = {
        {"callNative", nullptr, CallNative, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"nativeCallArkTS", nullptr, NativeCallArkTS, nullptr, nullptr, nullptr, napi_default, nullptr},
    };
    // 在exports对象上挂载两个Native方法
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}

EXTERN_C_END
// 1. 准备模块加载相关信息，将上述Init函数与本模块名等信息记录下来。
static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "entry",
    .nm_priv = nullptr,
    .reserved = {0},
};

extern "C" __attribute__((constructor)) void RegisterDemoModule() {
    napi_module_register(&demoModule);
}