#include <node_api.h>
#include <stdio.h>
#include <stdlib.h>

// https://nodejs.org/api/n-api.html
//
struct Foo
{
    int bar;
    int baz;
};

void print_foo(struct Foo * foo)
{
    printf("Foo__ bar: %i, baz: %i\n", foo->bar, foo->baz);
}

napi_value WrapObj(napi_env env, napi_callback_info info)
{
    struct Foo * foo = malloc (sizeof (struct Foo));

    foo->bar = 1;
    foo->baz = 2;

    print_foo(foo);

    napi_value js_object;
    napi_create_object(env, &js_object);

    napi_wrap(env,
        js_object,
        (void *) foo,
        NULL,
        NULL,
        NULL);

    return js_object;
}

napi_value UnwrapObj(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    struct Foo * foo =  NULL;

    // This can be called many times, as long as the struct is not freed
    /* napi_unwrap(env, args[0], (void **)&foo); */

    // This will set as NULL the pointer after the first time, even if it is not freed
    napi_remove_wrap(env, args[0], (void **)&foo);

    if (foo == NULL)
    {
        printf("The JS object doesn't wrap a native object\n");
    }
    else
    {
        print_foo(foo);
        free(foo);
    }

    napi_value function_result;
    napi_get_undefined(env, &function_result);

    return function_result;
}

napi_value Init(napi_env env, napi_value exports)
{
    napi_value fn;

    napi_create_function(env, NULL, 0, WrapObj, NULL, &fn);
    napi_set_named_property(env, exports, "wrapObj", fn);

    napi_create_function(env, NULL, 0, UnwrapObj, NULL, &fn);
    napi_set_named_property(env, exports, "unwrapObj", fn);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
