#include "service.h"

// https://ibus.github.io/docs/ibus-1.5/IBusService.html#ibus-service-get-object-path
napi_value ServiceGetObjectPath(napi_env env, napi_callback_info info)
{
    IBusEngine * engine = (IBusEngine *)&custom_ime_engine;
    IBusService * service = &engine->parent;
    const gchar * object_path = ibus_service_get_object_path(service);

    napi_value object_path_value;
    napi_create_string_utf8(env, object_path, NAPI_AUTO_LENGTH, &object_path_value);

    return object_path_value;
}

// https://ibus.github.io/docs/ibus-1.5/IBusService.html#ibus-service-new
napi_value ServiceNew(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    GDBusConnection * connection =  NULL;
    napi_unwrap(env, args[0], (void **)&connection);

    size_t str_size;
    napi_get_value_string_utf8(env, args[1], NULL, 0, &str_size);
    str_size += 1;

    char *path  = (char*)calloc(str_size + 1, sizeof(char));
    size_t str_size_read;
    napi_get_value_string_utf8(env, args[1], path, str_size, &str_size_read);

    IBusService * service = ibus_service_new(connection, path);

    free(path);

    RETURN_OBJ_WRAP("IBusService", service);
}

// https://ibus.github.io/docs/ibus-1.5/IBusService.html#ibus-service-register
napi_value ServiceRegister(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    GDBusConnection * connection =  NULL;
    napi_unwrap(env, args[0], (void **)&connection);

    IBusEngine * engine = (IBusEngine *)&custom_ime_engine;
    IBusService * service = &engine->parent;
    gboolean is_registered = ibus_service_register(service, connection, NULL);

    napi_value is_registered_value;
    napi_get_boolean(env, is_registered, &is_registered_value);
    return is_registered_value;
}
