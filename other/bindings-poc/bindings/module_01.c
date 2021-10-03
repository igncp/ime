#include <node_api.h>
#include <stdio.h>

// https://nodejs.org/api/n-api.html

napi_value MyFunction(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    int number = 0;
    napi_value argv[1];

    napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
    napi_get_value_int32(env, argv[0], &number);

    napi_value myNumber;
    number = number * 2;

    napi_create_int32(env, number, &myNumber);

    return myNumber;
}

napi_value Init(napi_env env, napi_value exports)
{
    napi_value fn;

    napi_create_function(env, NULL, 0, MyFunction, NULL, &fn);

    napi_set_named_property(env, exports, "myFunction", fn);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
