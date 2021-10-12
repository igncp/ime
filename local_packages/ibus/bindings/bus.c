#include "bus.h"

// https://ibus.github.io/docs/ibus-1.5/IBusBus.html#ibus-bus-current-input-context
napi_value BusCurrentInputContext(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusBus * bus =  NULL;
    napi_unwrap(env, args[0], (void **)&bus);

    gchar * context_name = ibus_bus_current_input_context(bus);

    napi_value context_name_value;
    napi_create_string_utf8(env, context_name, NAPI_AUTO_LENGTH, &context_name_value);

    g_free(context_name);

    return context_name_value;
}

// https://ibus.github.io/docs/ibus-1.5/IBusBus.html#ibus-bus-get-connection
napi_value BusGetConnection(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusBus * bus =  NULL;
    napi_unwrap(env, args[0], (void **)&bus);

    GDBusConnection * connection = ibus_bus_get_connection(bus);

    RETURN_OBJ_WRAP("GDBusConnection", connection);
}

// https://ibus.github.io/docs/ibus-1.5/IBusBus.html#ibus-bus-is-connected
napi_value BusIsConnected(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusBus * bus =  NULL;
    napi_unwrap(env, args[0], (void **)&bus);

    gboolean is_connected = ibus_bus_is_connected(bus);

    napi_value is_connected_value;
    napi_get_boolean(env, is_connected, &is_connected_value);
    return is_connected_value;
}

// https://ibus.github.io/docs/ibus-1.5/IBusBus.html#ibus-bus-list-engines
napi_value BusListEngines(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusBus * bus =  NULL;
    napi_unwrap(env, args[0], (void **)&bus);

    GList * engines = ibus_bus_list_engines(bus);

    napi_value engines_value;
    napi_create_array_with_length(env, 0, &engines_value);

    uint index = 0;
    for (; engines; engines = g_list_next (engines))
    {
        IBusEngineDesc *engine_desc = IBUS_ENGINE_DESC(engines->data);

        OBJ_WRAP("IBusEngineDesc", engine_desc);

        napi_set_element(env, engines_value, index, js_object);

        index += 1;
    }

    return engines_value;
}

void ibus_disconnect_cb(IBusBus *bus, gpointer user_data)
{
    g_debug("bus disconnected");
    ibus_quit();
}

// https://ibus.github.io/docs/ibus-1.5/IBusBus.html#ibus-bus-new
napi_value BusNew(napi_env env, napi_callback_info info)
{
    IBusBus * bus = ibus_bus_new();

    // @TODO: reconsider if is better to add this from another place
    g_signal_connect(bus, "disconnected", G_CALLBACK(ibus_disconnect_cb), NULL);

    RETURN_OBJ_WRAP("IBusBus", bus);
}

// https://ibus.github.io/docs/ibus-1.5/IBusBus.html#ibus-bus-request-name
napi_value BusRequestName(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusBus * bus =  NULL;
    napi_unwrap(env, args[0], (void **)&bus);

    size_t str_size;
    napi_get_value_string_utf8(env, args[1], NULL, 0, &str_size);
    str_size += 1;

    size_t str_size_read;
    char * component_name  = (char*)calloc(str_size + 1, sizeof(char));
    napi_get_value_string_utf8(env, args[1], component_name, str_size, &str_size_read);

    guint32 request_result = ibus_bus_request_name(bus, component_name, 0);

    free(component_name);

    napi_value result_value;
    napi_create_int32(env, request_result, &result_value);
    return result_value;
}

// https://ibus.github.io/docs/ibus-1.5/IBusFactory.html#ibus-factory-add-engine
napi_value FactoryAddEngine(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusFactory * factory =  NULL;
    napi_unwrap(env, args[0], (void **)&factory);

    size_t str_size;
    napi_get_value_string_utf8(env, args[1], NULL, 0, &str_size);
    str_size += 1;

    size_t str_size_read;
    char * engine_name  = (char*)calloc(str_size + 1, sizeof(char));
    napi_get_value_string_utf8(env, args[1], engine_name, str_size, &str_size_read);

    ibus_factory_add_engine(factory, engine_name, (ibus_custom_ime_engine_get_type()));

    free(engine_name);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusFactory.html#ibus-factory-create-engine
napi_value FactoryCreateEngine(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusFactory * factory =  NULL;
    napi_unwrap(env, args[0], (void **)&factory);

    size_t str_size;
    napi_get_value_string_utf8(env, args[1], NULL, 0, &str_size);
    str_size += 1;

    size_t str_size_read;
    char * engine_name  = (char*)calloc(str_size + 1, sizeof(char));
    napi_get_value_string_utf8(env, args[1], engine_name, str_size, &str_size_read);

    IBusEngine * engine = ibus_factory_create_engine(factory, engine_name);

    free(engine_name);

    RETURN_OBJ_WRAP("IBusEngine", engine);
}

// https://ibus.github.io/docs/ibus-1.5/IBusFactory.html#ibus-factory-new
napi_value FactoryNew(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    GDBusConnection * connection =  NULL;
    napi_unwrap(env, args[0], (void **)&connection);

    IBusFactory * factory = ibus_factory_new(connection);

    RETURN_OBJ_WRAP("IBusFactory", factory);
}


// https://ibus.github.io/docs/ibus-1.5/IBusInputContext.html#ibus-input-context-get-input-context
napi_value InputContextGetInputContext(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    size_t str_size;
    size_t str_size_read;

    napi_get_value_string_utf8(env, args[0], NULL, 0, &str_size);
    str_size += 1;
    char * content  = (char*)calloc(str_size + 1, sizeof(char));
    napi_get_value_string_utf8(env, args[0], content, str_size, &str_size_read);

    GDBusConnection * connection =  NULL;
    napi_unwrap(env, args[1], (void **)&connection);

    IBusInputContext * input_context = ibus_input_context_get_input_context(content, connection);

    RETURN_OBJ_WRAP("IBusInputContext", input_context);
}
