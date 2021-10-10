#include "engine.h"

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

#define ENGINE_DESC_GET_FN(fnName, ibus_fn) \
napi_value fnName(napi_env env, napi_callback_info info) \
{ \
    size_t argc = 1; \
    napi_value args[argc]; \
    napi_get_cb_info(env, info, &argc, args, NULL, NULL); \
    IBusEngineDesc * engineDesc =  NULL; \
\
    napi_unwrap(env, args[0], (void **)&engineDesc); \
\
    const gchar * engine_prop = ibus_fn(engineDesc); \
\
    napi_value engine_prop_value; \
    napi_create_string_utf8(env, engine_prop, NAPI_AUTO_LENGTH, &engine_prop_value); \
\
    return engine_prop_value; \
}

// https://ibus.github.io/docs/ibus-1.5/IBusEngineDesc.html#ibus-engine-desc-get-author
ENGINE_DESC_GET_FN(EngineDescGetAuthor, ibus_engine_desc_get_author)

// https://ibus.github.io/docs/ibus-1.5/IBusEngineDesc.html#ibus-engine-desc-get-description
ENGINE_DESC_GET_FN(EngineDescGetDescription, ibus_engine_desc_get_description)

// https://ibus.github.io/docs/ibus-1.5/IBusEngineDesc.html#ibus-engine-desc-get-hotkeys
ENGINE_DESC_GET_FN(EngineDescGetHotkeys, ibus_engine_desc_get_hotkeys)

// https://ibus.github.io/docs/ibus-1.5/IBusEngineDesc.html#ibus-engine-desc-get-language
ENGINE_DESC_GET_FN(EngineDescGetLanguage, ibus_engine_desc_get_language)

// https://ibus.github.io/docs/ibus-1.5/IBusEngineDesc.html#ibus-engine-desc-get-layout
ENGINE_DESC_GET_FN(EngineDescGetLayout, ibus_engine_desc_get_layout)

// https://ibus.github.io/docs/ibus-1.5/IBusEngineDesc.html#ibus-engine-desc-get-license
ENGINE_DESC_GET_FN(EngineDescGetLicense, ibus_engine_desc_get_license)

// https://ibus.github.io/docs/ibus-1.5/IBusEngineDesc.html#ibus-engine-desc-get-longname
ENGINE_DESC_GET_FN(EngineDescGetLongname, ibus_engine_desc_get_longname)

// https://ibus.github.io/docs/ibus-1.5/IBusEngineDesc.html#ibus-engine-desc-get-name
ENGINE_DESC_GET_FN(EngineDescGetName, ibus_engine_desc_get_name)

// https://ibus.github.io/docs/ibus-1.5/IBusEngineDesc.html#ibus-engine-desc-get-rank
napi_value EngineDescGetRank(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    IBusEngineDesc * engineDesc =  NULL;

    napi_unwrap(env, args[0], (void **)&engineDesc);

    guint engine_rank = ibus_engine_desc_get_rank(engineDesc);

    napi_value engine_rank_value;
    napi_create_uint32(env, engine_rank, &engine_rank_value);

    return engine_rank_value;
}

// https://ibus.github.io/docs/ibus-1.5/IBusEngineDesc.html#ibus-engine-desc-get-setup
ENGINE_DESC_GET_FN(EngineDescGetSetup, ibus_engine_desc_get_setup)

// https://ibus.github.io/docs/ibus-1.5/IBusEngineDesc.html#ibus-engine-desc-get-symbol
ENGINE_DESC_GET_FN(EngineDescGetSymbol, ibus_engine_desc_get_symbol)

// https://ibus.github.io/docs/ibus-1.5/IBusEngineDesc.html#ibus-engine-desc-get-textdomain
ENGINE_DESC_GET_FN(EngineDescGetTextdomain, ibus_engine_desc_get_textdomain)

// https://ibus.github.io/docs/ibus-1.5/IBusEngineDesc.html#ibus-engine-desc-get-version
ENGINE_DESC_GET_FN(EngineDescGetVersion, ibus_engine_desc_get_version)

// https://ibus.github.io/docs/ibus-1.5/IBusEngine.html#ibus-engine-get-name
napi_value EngineGetName(napi_env env, napi_callback_info info)
{
    const gchar * engine_name = ibus_engine_get_name((IBusEngine *) &custom_ime_engine);

    napi_value engine_name_value;
    napi_create_string_utf8(env, engine_name, NAPI_AUTO_LENGTH, &engine_name_value);

    return engine_name_value;
}

// https://ibus.github.io/docs/ibus-1.5/IBusEngine.html#ibus-engine-hide-auxiliary-text
napi_value EngineHideAuxiliaryText(napi_env env, napi_callback_info info)
{
    ibus_engine_hide_auxiliary_text((IBusEngine *) &custom_ime_engine);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusEngine.html#ibus-engine-hide-lookup-table
napi_value EngineHideLookupTable(napi_env env, napi_callback_info info)
{
    ibus_engine_hide_lookup_table((IBusEngine *) &custom_ime_engine);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusEngine.html#ibus-engine-hide-preedit-text
napi_value EngineHidePreeditText(napi_env env, napi_callback_info info)
{
    ibus_engine_hide_lookup_table((IBusEngine *) &custom_ime_engine);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusEngine.html#ibus-engine-register-properties
napi_value EngineRegisterProperties(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusPropList * list =  NULL;
    napi_unwrap(env, args[0], (void **)&list);

    ibus_engine_register_properties((IBusEngine *) &custom_ime_engine, list);

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

// https://ibus.github.io/docs/ibus-1.5/IBusEngine.html#ibus-engine-show-preedit-text
napi_value EngineShowPreeditText(napi_env env, napi_callback_info info)
{
    ibus_engine_show_preedit_text((IBusEngine *) &custom_ime_engine);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusEngine.html#ibus-engine-update-auxiliary-text
napi_value EngineUpdateAuxiliaryText(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    size_t str_size;
    napi_get_value_string_utf8(env, args[0], NULL, 0, &str_size);
    str_size += 1;

    char *text_opt  = (char*)calloc(str_size + 1, sizeof(char));
    size_t str_size_read;
    napi_get_value_string_utf8(env, args[0], text_opt, str_size, &str_size_read);

    IBusText *text = ibus_text_new_from_string(text_opt);

    bool is_visible;
    napi_get_value_bool(env, args[1], &is_visible);

    ibus_engine_update_auxiliary_text (
        (IBusEngine *) &custom_ime_engine,
        text,
        is_visible
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
    size_t argc = 3;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    size_t str_size;
    napi_get_value_string_utf8(env, args[0], NULL, 0, &str_size);
    str_size += 1;

    char *text_opt  = (char*)calloc(str_size + 1, sizeof(char));
    size_t str_size_read;
    napi_get_value_string_utf8(env, args[0], text_opt, str_size, &str_size_read);

    IBusText *text = ibus_text_new_from_string(text_opt);

    guint32 cursor_pos;
    napi_get_value_uint32(env, args[1], &cursor_pos);

    bool is_visible;
    napi_get_value_bool(env, args[2], &is_visible);

    ibus_engine_update_preedit_text(
        (IBusEngine *) &custom_ime_engine,
        text,
        cursor_pos,
        is_visible
    );

    free(text_opt);

    RETURN_UNDEFINED;
}
