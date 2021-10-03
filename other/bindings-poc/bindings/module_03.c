#include <node_api.h>
#include <stdio.h>
#include <stdlib.h>

static napi_ref fn_holder = NULL;

// https://nodejs.org/api/n-api.html

napi_value CallRegisteredGlobalFn(napi_env env, napi_callback_info info)
{
    napi_value cb;
    napi_get_reference_value(env, fn_holder, &cb);

    napi_value global;
    napi_get_global(env, &global);
    napi_call_function(env, global, cb, 0, NULL, NULL);

    napi_value function_result;
    napi_get_undefined(env, &function_result);

    return function_result;
}

napi_value RegisterGlobalFn(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    napi_value cb = args[0];

    napi_create_reference(env, cb, 1, &fn_holder);

    napi_value function_result;
    napi_get_undefined(env, &function_result);

    return function_result;
}

napi_value Init(napi_env env, napi_value exports)
{
    napi_value fn_register_global_fn, fn_call_registered_global_fn;

    napi_create_function(env, NULL, 0, RegisterGlobalFn, NULL, &fn_register_global_fn);
    napi_create_function(env, NULL, 0, CallRegisteredGlobalFn, NULL, &fn_call_registered_global_fn);

    napi_set_named_property(env, exports, "registerGlobalFn", fn_register_global_fn);
    napi_set_named_property(env, exports, "callRegisteredGlobalFn", fn_call_registered_global_fn);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
