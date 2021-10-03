#include <node_api.h>

#include "custom_engine.h"

extern ImeHandlers ime_handlers;
extern IBusCustomImeEngine custom_ime_engine;

// https://nodejs.org/api/n-api.html

napi_value Init(napi_env env, napi_callback_info info)
{
    ibus_init();
    IBusBus *bus = ibus_bus_new();
    g_object_ref_sink(bus);

    if (!ibus_bus_is_connected(bus))
    {
        g_warning("not connected to ibus");
        exit(1);
    }

    g_signal_connect(bus, "disconnected", G_CALLBACK(ibus_disconnect_cb), NULL);

    IBusFactory *factory = ibus_factory_new(ibus_bus_get_connection(bus));
    g_object_ref_sink(factory);

    size_t argc = 3;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    size_t str_size_ime, str_size_bus;
    napi_get_value_string_utf8(env, args[0], NULL, 0, &str_size_ime);
    str_size_ime += 1;
    napi_get_value_string_utf8(env, args[1], NULL, 0, &str_size_bus);
    str_size_bus += 1;

    size_t str_size_read_ime, str_size_read_bus;
    char *ime_name  = (char*)calloc(str_size_ime + 1, sizeof(char));
    napi_get_value_string_utf8(env, args[0], ime_name, str_size_ime, &str_size_read_ime);
    char *bus_name  = (char*)calloc(str_size_bus + 1, sizeof(char));
    napi_get_value_string_utf8(env, args[1], bus_name, str_size_bus, &str_size_read_bus);

    napi_value cb = args[2];

    printf("IME name: %.*s\n", (int) str_size_read_ime, ime_name);
    printf("Bus name: %.*s\n", (int) str_size_read_bus, bus_name);

    ibus_factory_add_engine(factory, ime_name, (ibus_custom_ime_engine_get_type()));

    if (!ibus_bus_request_name(bus, bus_name, 0))
    {
        printf("error requesting bus name\n");
        exit(1);
    }

    napi_value global;
    napi_get_global(env, &global);
    napi_value result;
    napi_call_function(env, global, cb, 0, NULL, &result);

    free(ime_name);
    free(bus_name);

    g_object_unref(factory);
    g_object_unref(bus);

    napi_value function_result;
    napi_get_undefined(env, &function_result);
    return function_result;
}

napi_value Main(napi_env env, napi_callback_info info)
{
    ibus_main();

    napi_value function_result;
    napi_get_undefined(env, &function_result);
    return function_result;
}

napi_value RegisterHandlers(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1];
    napi_value provided_key_event;

    napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    napi_value provided_handlers = args[0];

    napi_get_named_property(env, provided_handlers, "keyEvent", &provided_key_event);

    napi_create_reference(env, provided_key_event, 1, &ime_handlers.key_event);

    ime_handlers.env = env;

    napi_value function_result;
    napi_get_undefined(env, &function_result);
    return function_result;
}

// https://ibus.github.io/docs/ibus-1.5/IBusEngine.html#ibus-engine-commit-text
napi_value EngineCommitText(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    size_t str_size;
    napi_get_value_string_utf8(env, args[0], NULL, 0, &str_size);
    str_size += 1;

    char *text_opt  = (char*)calloc(str_size + 1, sizeof(char));
    size_t str_size_read;
    napi_get_value_string_utf8(env, args[0], text_opt, str_size, &str_size_read);

    IBusText *text = ibus_text_new_from_string(text_opt);

    // the text object will be released by ibus
    ibus_engine_commit_text((IBusEngine *) &custom_ime_engine, text);

    free(text_opt);

    napi_value function_result;
    napi_get_undefined(env, &function_result);
    return function_result;
}

napi_value MainModule(napi_env env, napi_value exports)
{

#define NODE_EXPOSE_FN(FnName, fn_name, keyName) \
    napi_value fn_name; \
    napi_create_function(env, NULL, 0, FnName, NULL, &fn_name); \
    napi_set_named_property(env, exports, keyName, fn_name);

    NODE_EXPOSE_FN(Init, fn_init, "init");
    NODE_EXPOSE_FN(Main, fn_main, "main");
    NODE_EXPOSE_FN(RegisterHandlers, fn_register_handlers, "registerHandlers");
    NODE_EXPOSE_FN(EngineCommitText, fn_engine_commit_text, "engineCommitText");

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, MainModule)
