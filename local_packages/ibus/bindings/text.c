#include "text.h"

// https://ibus.github.io/docs/ibus-1.5/IBusAttribute.html#ibus-attr-foreground-new
napi_value AttrForegroundNew(napi_env env, napi_callback_info info)
{
    size_t argc = 3;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    guint32 color;
    napi_get_value_uint32(env, args[0], &color);

    guint32 startIndex;
    napi_get_value_uint32(env, args[1], &startIndex);

    guint32 endIndex;
    napi_get_value_uint32(env, args[2], &endIndex);

    IBusAttribute * attr = ibus_attr_foreground_new(color, startIndex, endIndex);

    RETURN_OBJ_WRAP("IBusAttribute", attr);
}

// https://ibus.github.io/docs/ibus-1.5/IBusAttrList.html#ibus-attr-list-append
napi_value AttrListAppend(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusAttrList * list =  NULL;
    napi_unwrap(env, args[0], (void **)&list);

    IBusAttribute * attribute =  NULL;
    napi_unwrap(env, args[1], (void **)&attribute);

    ibus_attr_list_append(list, attribute);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusAttrList.html#ibus-attr-list-new
napi_value AttrListNew(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusAttrList * list = ibus_attr_list_new();

    RETURN_OBJ_WRAP("IBusAttrList", list);
}

// https://ibus.github.io/docs/ibus-1.5/IBusAttribute.html#ibus-attribute-new
napi_value AttributeNew(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    napi_value opts_obj = args[0];

    EXTRACT_KEY_INT(type, "type", c_int_type);
    EXTRACT_KEY_INT(val, "value", c_int_value);
    EXTRACT_KEY_INT(start, "startIndex", c_int_start);
    EXTRACT_KEY_INT(end, "endIndex", c_int_end);

    IBusAttribute * attribute = ibus_attribute_new(c_int_type, c_int_value, c_int_start, c_int_end);

    RETURN_OBJ_WRAP("IBusAttribute", attribute);
}

// https://ibus.github.io/docs/ibus-1.5/IBusText.html#ibus-text-new-from-string
napi_value TextNewFromString(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    size_t str_size;
    size_t str_size_read;

    napi_get_value_string_utf8(env, args[0], NULL, 0, &str_size);
    str_size += 1;
    char * content  = (char*)calloc(str_size + 1, sizeof(char));
    napi_get_value_string_utf8(env, args[0], content, str_size, &str_size_read);

    IBusText * text = ibus_text_new_from_string(content);

    free(content);

    RETURN_OBJ_WRAP("IBusText", text);
}

// https://ibus.github.io/docs/ibus-1.5/IBusText.html#ibus-text-set-attributes
napi_value TextSetAttributes(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusText * text =  NULL;
    napi_unwrap(env, args[0], (void **)&text);

    IBusAttrList * list =  NULL;
    napi_unwrap(env, args[1], (void **)&list);

    ibus_text_set_attributes(text, list);

    RETURN_UNDEFINED;
}
