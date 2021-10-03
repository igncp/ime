#include <node_api.h>
#include <stdio.h>

// https://nodejs.org/api/n-api.html

napi_value FnWithCallback(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    napi_value cb = args[0];
    napi_value argv[1];
    napi_create_string_utf8(env, "hello world", NAPI_AUTO_LENGTH, argv);
    napi_value global;
    napi_get_global(env, &global);
    napi_value result;
    napi_call_function(env, global, cb, 1, argv, &result);

    napi_value function_result;
    napi_get_undefined(env, &function_result);
    return function_result;
}

napi_value Init(napi_env env, napi_value exports)
{
    napi_value fn;

    napi_create_function(env, NULL, 0, FnWithCallback, NULL, &fn);

    napi_set_named_property(env, exports, "functionWithCallback", fn);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
