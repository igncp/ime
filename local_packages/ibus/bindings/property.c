#include "property.h"

// https://ibus.github.io/docs/ibus-1.5/IBusPropList.html#ibus-prop-list-append
napi_value PropListAppend(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusProperty * prop =  NULL;

    napi_unwrap(env, args[0], (void **)&prop);

    ibus_prop_list_append(custom_ime_prop_list, prop);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusProperty.html#ibus-property-get-state
napi_value PropertyGetState(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusProperty * prop =  NULL;

    napi_unwrap(env, args[0], (void **)&prop);

    IBusPropState state = ibus_property_get_state(prop);

    napi_value result_state;
    napi_create_uint32(env, state, &result_state);
    return result_state;
}

// https://ibus.github.io/docs/ibus-1.5/IBusProperty.html#ibus-property-new
napi_value PropertyNew(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    napi_value opts_obj = args[0];

    EXTRACT_KEY_INIT;

    EXTRACT_KEY_BOOL(sensitive, "isSensitive", c_boool_is_sensitive);
    EXTRACT_KEY_INT(type, "type", c_int_type);
    EXTRACT_KEY_INT(state, "state", c_int_state);
    EXTRACT_KEY_STR(key, "key", c_string_key);
    EXTRACT_KEY_STR(tooltip, "tooltip", c_string_tooltip);
    EXTRACT_KEY_UNWRAP(label, "label", IBusText, label_text);

    IBusText * tooltip = ibus_text_new_from_string(c_string_tooltip);

    // @TODO: Missing options
    IBusProperty * property = ibus_property_new(
            c_string_key,
            c_int_type,
            label_text,
            NULL,
            tooltip,
            c_boool_is_sensitive,
            TRUE,
            c_int_state,
            NULL
        );

    free(c_string_tooltip);

    RETURN_OBJ_WRAP("IBusProperty", property);
}

// https://ibus.github.io/docs/ibus-1.5/IBusProperty.html#ibus-property-set-state
napi_value PropertySetState(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusProperty * prop =  NULL;

    napi_unwrap(env, args[0], (void **)&prop);

    guint32 new_state;
    napi_get_value_uint32(env, args[1], &new_state);

    ibus_property_set_state(prop, new_state);

    RETURN_UNDEFINED;
}
