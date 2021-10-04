// https://nodejs.org/api/n-api.html
#include <node_api.h>

#include "custom_engine.h"

extern ImeHandlers ime_handlers;
extern IBusCustomImeEngine custom_ime_engine;
extern IBusLookupTable * custom_ime_lookup_table;

#define RETURN_UNDEFINED \
    napi_value function_result; \
    napi_get_undefined(env, &function_result); \
    return function_result

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

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusEngine.html#ibus-engine-hide-lookup-table
napi_value EngineHideLookupTable(napi_env env, napi_callback_info info)
{
    ibus_engine_hide_lookup_table((IBusEngine *) &custom_ime_engine);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusEngine.html#ibus-engine-show-auxiliary-text
napi_value EngineShowAuxiliaryText(napi_env env, napi_callback_info info)
{
    ibus_engine_show_auxiliary_text((IBusEngine *) &custom_ime_engine);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusEngine.html#ibus-engine-show-lookup-table
napi_value EngineShowLookupTable(napi_env env, napi_callback_info info)
{
    ibus_engine_show_lookup_table((IBusEngine *) &custom_ime_engine);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusEngine.html#ibus-engine-update-auxiliary-text
napi_value EngineUpdateAuxiliaryText(napi_env env, napi_callback_info info)
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

    ibus_engine_update_auxiliary_text (
        (IBusEngine *) &custom_ime_engine,
        text,
        TRUE /* @TODO */
    );

    free(text_opt);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusEngine.html#ibus-engine-update-lookup-table
napi_value EngineUpdateLookupTable(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    bool is_visible;
    napi_get_value_bool(env, args[0], &is_visible);

    ibus_engine_update_lookup_table(
        (IBusEngine *) &custom_ime_engine,
        custom_ime_lookup_table,
        is_visible
    );

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusEngine.html#ibus-engine-update-preedit-text
napi_value EngineUpdatePreeditText(napi_env env, napi_callback_info info)
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

    ibus_engine_update_preedit_text(
        (IBusEngine *) &custom_ime_engine,
        text,
        0, /* @TODO */
        TRUE /* @TODO */
    );

    free(text_opt);

    RETURN_UNDEFINED;
}

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

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-append-candidate
napi_value LookupTableAppendCandidate(napi_env env, napi_callback_info info)
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
    ibus_lookup_table_append_candidate(custom_ime_lookup_table, text);

    free(text_opt);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-clear
napi_value LookupTableClear(napi_env env, napi_callback_info info)
{
    ibus_lookup_table_clear(custom_ime_lookup_table);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-set-orientation
napi_value LookupTableSetOrientation(napi_env env, napi_callback_info info)
{
    ibus_lookup_table_set_orientation(
        custom_ime_lookup_table,
        IBUS_ORIENTATION_VERTICAL /* @TODO */
    );

    RETURN_UNDEFINED;
}

napi_value Main(napi_env env, napi_callback_info info)
{
    ibus_main();

    RETURN_UNDEFINED;
}

napi_value RegisterHandlers(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1];
    napi_value provided_key_event, provided_enable, provided_disable;

    napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    napi_value provided_handlers = args[0];

    napi_get_named_property(env, provided_handlers, "disable", &provided_disable);
    napi_get_named_property(env, provided_handlers, "enable", &provided_enable);
    napi_get_named_property(env, provided_handlers, "keyEvent", &provided_key_event);

    napi_create_reference(env, provided_disable, 1, &ime_handlers.disable);
    napi_create_reference(env, provided_enable, 1, &ime_handlers.enable);
    napi_create_reference(env, provided_key_event, 1, &ime_handlers.key_event);

    ime_handlers.env = env;

    RETURN_UNDEFINED;
}

napi_value MainModule(napi_env env, napi_value exports)
{

#define NODE_EXPOSE_FN(FnName, fn_name, keyName) \
    napi_value fn_name; \
    napi_create_function(env, NULL, 0, FnName, NULL, &fn_name); \
    napi_set_named_property(env, exports, keyName, fn_name);

    NODE_EXPOSE_FN(EngineCommitText, fn_engine_commit_text, "engineCommitText");
    NODE_EXPOSE_FN(EngineHideLookupTable, fn_engine_hide_lookup_table, "engineHideLookupTable");
    NODE_EXPOSE_FN(EngineShowAuxiliaryText, fn_engine_show_auxiliary_text, "engineShowAuxiliaryText");
    NODE_EXPOSE_FN(EngineShowLookupTable, fn_engine_show_lookup_table, "engineShowLookupTable");
    NODE_EXPOSE_FN(EngineUpdateAuxiliaryText, fn_engine_update_auxiliary_text, "engineUpdateAuxiliaryText");
    NODE_EXPOSE_FN(EngineUpdateLookupTable, fn_engine_update_lookup_table, "engineUpdateLookupTable");
    NODE_EXPOSE_FN(EngineUpdatePreeditText, fn_engine_update_preedit_text, "engineUpdatePreeditText");
    NODE_EXPOSE_FN(Init, fn_init, "init");
    NODE_EXPOSE_FN(LookupTableAppendCandidate, fn_lookup_table_append_candidate, "lookupTableAppendCandidate");
    NODE_EXPOSE_FN(LookupTableClear, fn_lookup_table_clear, "lookupTableClear");
    NODE_EXPOSE_FN(LookupTableSetOrientation, fn_lookup_table_set_orientation, "lookupTableSetOrientation");
    NODE_EXPOSE_FN(Main, fn_main, "main");
    NODE_EXPOSE_FN(RegisterHandlers, fn_register_handlers, "registerHandlers");

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, MainModule)
