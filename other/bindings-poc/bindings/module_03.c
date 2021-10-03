#include <node_api.h>
#include <stdio.h>
#include <stdlib.h>

int default_fn()
{
    printf("default_fn \n");
    return 1;
}

struct FnHolder
{
    napi_value * func;
};

static struct FnHolder fn_holder = { .func = NULL };

// https://nodejs.org/api/n-api.html

napi_value CallRegisteredGlobalFn(napi_env env, napi_callback_info info)
{
    printf("CallRegisteredGlobalFn \n");

    napi_value global;
    napi_get_global(env, &global);

    if (fn_holder.func == NULL)
    {
        printf("It is null!\n");
    }
    else
    {
        napi_call_function(env, global, *fn_holder.func, 0, NULL, NULL);
    }

    printf("CallRegisteredGlobalFn After \n");

    napi_value function_result;
    napi_get_undefined(env, &function_result);
    return function_result;
}

napi_value RegisterGlobalFn(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    napi_value obj = args[0];
    napi_value * cb = malloc(10000);

    napi_get_named_property(env, obj, "fn", cb);

    fn_holder.func = cb;

    napi_value global;
    napi_get_global(env, &global);
    napi_call_function(env, global, *fn_holder.func, 0, NULL, NULL);

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
