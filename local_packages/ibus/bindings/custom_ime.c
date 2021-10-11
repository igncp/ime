#include "custom_ime.h"

struct _IBusCustomImeEngineClass
{
    IBusEngineClass parent;
};

struct _IBusCustomImeEngine
{
    IBusEngine parent;
};

static void ibus_custom_ime_engine_class_init (IBusCustomImeEngineClass *klass);
static void ibus_custom_ime_engine_init (IBusCustomImeEngine *custom_ime_engine);

ImeHandlers ime_handlers = {};
IBusCustomImeEngine custom_ime_engine;

G_DEFINE_TYPE (IBusCustomImeEngine, ibus_custom_ime_engine, IBUS_TYPE_ENGINE)

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

static void ibus_custom_ime_engine_focus_in (IBusEngine *engine)
{
    napi_value cb;
    napi_get_reference_value(ime_handlers.env, ime_handlers.focus_in, &cb);

    napi_value global;
    napi_get_global(ime_handlers.env, &global);
    napi_call_function(ime_handlers.env, global, cb, 0, NULL, NULL);
}

static void ibus_custom_ime_engine_focus_out (IBusEngine *engine)
{
    napi_value cb;
    napi_get_reference_value(ime_handlers.env, ime_handlers.focus_out, &cb);

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
    napi_get_reference_value(ime_handlers.env, ime_handlers.key_event, &cb);

    napi_value global;
    napi_value result_value;
    napi_get_global(ime_handlers.env, &global);
    napi_call_function(ime_handlers.env, global, cb, 1, &obj, &result_value);

    bool fn_result;
    napi_get_value_bool(ime_handlers.env, result_value, &fn_result);

    return fn_result;
}

static void ibus_custom_ime_engine_property_activate(
    IBusEngine *engine,
    const gchar * key,
    guint state
)
{
    napi_value state_return;
    napi_create_int32(ime_handlers.env, state, &state_return);

    napi_value key_return;
    napi_create_string_utf8(ime_handlers.env, key, NAPI_AUTO_LENGTH, &key_return);

    napi_value obj;
    napi_create_object(ime_handlers.env, &obj);

    napi_set_named_property(ime_handlers.env, obj, "state", state_return);
    napi_set_named_property(ime_handlers.env, obj, "key", key_return);

    napi_value cb;
    napi_get_reference_value(ime_handlers.env, ime_handlers.property_activate, &cb);

    napi_value global;
    napi_get_global(ime_handlers.env, &global);
    napi_call_function(ime_handlers.env, global, cb, 1, &obj, NULL);
}

static void ibus_custom_ime_engine_class_init (IBusCustomImeEngineClass *klass)
{
    IBusEngineClass *engine_class = IBUS_ENGINE_CLASS (klass);

    printf("ibus_custom_ime_engine_class_init \n");

    engine_class->disable = ibus_custom_ime_engine_disable;
    engine_class->enable = ibus_custom_ime_engine_enable;
    engine_class->focus_in = ibus_custom_ime_engine_focus_in;
    engine_class->focus_out = ibus_custom_ime_engine_focus_out;
    engine_class->process_key_event = ibus_custom_ime_engine_process_key_event;
    engine_class->property_activate = ibus_custom_ime_engine_property_activate;
}

static void ibus_custom_ime_engine_init (IBusCustomImeEngine * _custom_ime_engine)
{
    printf("ibus_custom_ime_engine_init \n");

    custom_ime_engine = *_custom_ime_engine;
}
