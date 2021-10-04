#include "custom_engine.h"

struct _IBusCustomImeEngineClass
{
    IBusEngineClass parent;
};

struct _IBusCustomImeEngine
{
    IBusEngine parent;
    IBusLookupTable* table;
    IBusPropList* props;
};

static void ibus_custom_ime_engine_class_init (IBusCustomImeEngineClass *klass);
static void ibus_custom_ime_engine_init (IBusCustomImeEngine *custom_ime_engine);

ImeHandlers ime_handlers = { .key_event = NULL, .env = NULL, .enable = NULL };
IBusCustomImeEngine custom_ime_engine;
IBusLookupTable * custom_ime_lookup_table;

G_DEFINE_TYPE (IBusCustomImeEngine, ibus_custom_ime_engine, IBUS_TYPE_ENGINE)

void ibus_disconnect_cb(IBusBus *bus, gpointer user_data)
{
    g_debug("bus disconnected");
    ibus_quit();
}

static void ibus_custom_ime_engine_disable (IBusEngine *engine)
{
    napi_value cb;
    napi_get_reference_value(ime_handlers.env, ime_handlers.disable, &cb);

    napi_value global;
    napi_get_global(ime_handlers.env, &global);
    napi_call_function(ime_handlers.env, global, cb, 0, NULL, NULL);
}

static void ibus_custom_ime_engine_enable (IBusEngine *engine)
{
    napi_value cb;
    napi_get_reference_value(ime_handlers.env, ime_handlers.enable, &cb);

    napi_value global;
    napi_get_global(ime_handlers.env, &global);
    napi_call_function(ime_handlers.env, global, cb, 0, NULL, NULL);
}

static gboolean ibus_custom_ime_engine_process_key_event (
    IBusEngine *engine,
    guint       keyval,
    guint       keycode,
    guint       modifiers
)
{
    gboolean result = TRUE;
    napi_status status;

    napi_value keyval_return, keycode_return, modifiers_return;
    napi_create_int32(ime_handlers.env, keyval, &keyval_return);
    napi_create_int32(ime_handlers.env, keycode, &keycode_return);
    napi_create_int32(ime_handlers.env, modifiers, &modifiers_return);

    napi_value obj;
    napi_create_object(ime_handlers.env, &obj);

    napi_set_named_property(ime_handlers.env, obj, "keyval", keyval_return);
    napi_set_named_property(ime_handlers.env, obj, "keycode", keycode_return);
    napi_set_named_property(ime_handlers.env, obj, "modifiers", modifiers_return);

    napi_value cb;
    status = napi_get_reference_value(ime_handlers.env, ime_handlers.key_event, &cb);

    if (status != napi_ok)
    {
        printf("Error in the handler reference \n");
    }

    napi_value global;
    napi_get_global(ime_handlers.env, &global);
    napi_call_function(ime_handlers.env, global, cb, 1, &obj, NULL);

    return result;
}

static void ibus_custom_ime_engine_class_init (IBusCustomImeEngineClass *klass)
{
    IBusEngineClass *engine_class = IBUS_ENGINE_CLASS (klass);

    printf("ibus_custom_ime_engine_class_init \n");

    engine_class->disable = ibus_custom_ime_engine_disable;
    engine_class->enable = ibus_custom_ime_engine_enable;
    engine_class->process_key_event = ibus_custom_ime_engine_process_key_event;
}

static void ibus_custom_ime_engine_init (IBusCustomImeEngine * _custom_ime_engine)
{
    printf("ibus_custom_ime_engine_init \n");

    custom_ime_engine = *_custom_ime_engine;

    custom_ime_lookup_table = ibus_lookup_table_new(9, 0, TRUE, FALSE);
    g_object_ref_sink(custom_ime_lookup_table);
}
