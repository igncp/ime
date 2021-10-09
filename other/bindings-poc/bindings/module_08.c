#include <node_api.h>
#include <stdio.h>
#include <stdlib.h>

// https://nodejs.org/api/n-api.html

napi_value GetObj(napi_env env, napi_callback_info info)
{
    napi_value result_obj;
    napi_create_object(env, &result_obj);

    napi_value property_key_a;
    napi_create_string_utf8(env, "propertyA", NAPI_AUTO_LENGTH, &property_key_a);

    napi_value property_key_b;
    napi_create_string_utf8(env, "propertyB", NAPI_AUTO_LENGTH, &property_key_b);

    napi_value property_value;
    napi_create_uint32(env, 123, &property_value);

    napi_set_property(env, result_obj, property_key_a, property_value);
    napi_set_property(env, result_obj, property_key_b, result_obj); // circular reference

    return result_obj;
}

napi_value Init(napi_env env, napi_value exports)
{
    napi_value fn;

    napi_create_function(env, NULL, 0, GetObj, NULL, &fn);
    napi_set_named_property(env, exports, "getObj", fn);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
