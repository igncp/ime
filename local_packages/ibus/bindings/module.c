#include <node_api.h>

#include <glib-object.h>
#include <glib.h>
#include <glib/gstdio.h>
#include <ibus.h>
#include <ibus.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

// https://nodejs.org/api/n-api.html

static void ibus_disconnect_cb(IBusBus *bus, gpointer user_data)
{
    g_debug("bus disconnected");
    ibus_quit();
}

napi_value Init(napi_env env, napi_callback_info info)
{
    ibus_init();
    IBusBus *bus = ibus_bus_new();
    g_object_ref_sink(bus);

    if (!ibus_bus_is_connected(bus))
    {
        g_warning("not connected to ibus");
        exit(0);
    }

    g_signal_connect(bus, "disconnected", G_CALLBACK(ibus_disconnect_cb), NULL);

    IBusFactory *factory = ibus_factory_new(ibus_bus_get_connection(bus));
    g_object_ref_sink(factory);

    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    napi_value cb = args[0];
    napi_value global;
    napi_get_global(env, &global);
    napi_value result;
    napi_call_function(env, global, cb, 0, NULL, &result);

    // @TODO: Find how to handle this
    /* ibus_factory_add_engine(factory, "rime", IBUS_TYPE_RIME_ENGINE); */
    /* if (!ibus_bus_request_name(bus, "im.rime.Rime", 0)) { */
    /* g_error("error requesting bus name"); */
    /* exit(1); */
    /* } */

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

typedef struct _IBusRimeEngine IBusRimeEngine;
typedef struct _IBusRimeEngineClass IBusRimeEngineClass;

struct _IBusRimeEngineClass
{
    IBusEngineClass parent;
};

struct _IBusRimeEngine
{
    IBusEngine parent;
    IBusLookupTable* table;
    IBusPropList* props;
};

static void ibus_rime_engine_class_init (IBusRimeEngineClass *klass);
static void ibus_rime_engine_init (IBusRimeEngine *rime_engine);

G_DEFINE_TYPE (IBusRimeEngine, ibus_rime_engine, IBUS_TYPE_ENGINE)

static gboolean ibus_rime_engine_process_key_event (
    IBusEngine *engine,
    guint       keyval,
    guint       keycode,
    guint       modifiers)
{
    gboolean result = TRUE;
    printf("ibus_rime_engine_process_key_event\n");
    return result;
}

static void ibus_rime_engine_class_init (IBusRimeEngineClass *klass)
{
    IBusEngineClass *engine_class = IBUS_ENGINE_CLASS (klass);

    printf("ibus_rime_engine_class_init \n");

    engine_class->process_key_event = ibus_rime_engine_process_key_event;
}

static void ibus_rime_engine_init (IBusRimeEngine *klass)
{
    printf("ibus_rime_engine_init \n");
}

napi_value MainModule(napi_env env, napi_value exports)
{
    napi_value fn_init, fn_main;

    napi_create_function(env, NULL, 0, Init, NULL, &fn_init);
    napi_create_function(env, NULL, 0, Main, NULL, &fn_main);

    napi_set_named_property(env, exports, "init", fn_init);
    napi_set_named_property(env, exports, "main", fn_main);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, MainModule)
