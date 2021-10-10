#include "lookup_table.h"

extern IBusLookupTable * custom_ime_lookup_table;

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-append-candidate
napi_value LookupTableAppendCandidate(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusText * text =  NULL;
    napi_unwrap(env, args[0], (void **)&text);

    ibus_lookup_table_append_candidate(custom_ime_lookup_table, text);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-clear
napi_value LookupTableClear(napi_env env, napi_callback_info info)
{
    ibus_lookup_table_clear(custom_ime_lookup_table);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-cursor-down
napi_value LookupTableCursorDown(napi_env env, napi_callback_info info)
{
    ibus_lookup_table_cursor_down(custom_ime_lookup_table);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-cursor-up
napi_value LookupTableCursorUp(napi_env env, napi_callback_info info)
{
    ibus_lookup_table_cursor_up(custom_ime_lookup_table);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-get-cursor-in-page
napi_value LookupTableGetCursorInPage(napi_env env, napi_callback_info info)
{
    guint cursor_pos = ibus_lookup_table_get_cursor_in_page(custom_ime_lookup_table);

    napi_value cursor_pos_value;
    napi_create_uint32(env, cursor_pos, &cursor_pos_value);
    return cursor_pos_value;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-get-cursor-pos
napi_value LookupTableGetCursorPos(napi_env env, napi_callback_info info)
{
    guint cursor_pos = ibus_lookup_table_get_cursor_pos(custom_ime_lookup_table);

    napi_value cursor_pos_value;
    napi_create_uint32(env, cursor_pos, &cursor_pos_value);
    return cursor_pos_value;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-get-number-of-candidates
napi_value LookupTableGetNumberOfCandidates(napi_env env, napi_callback_info info)
{
    guint candidates_num = ibus_lookup_table_get_number_of_candidates(custom_ime_lookup_table);

    napi_value candidates_num_value;
    napi_create_uint32(env, candidates_num, &candidates_num_value);
    return candidates_num_value;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-get-page-size
napi_value LookupTableGetPageSize(napi_env env, napi_callback_info info)
{
    guint page_size = ibus_lookup_table_get_page_size(custom_ime_lookup_table);

    napi_value page_size_value;
    napi_create_uint32(env, page_size, &page_size_value);
    return page_size_value;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-page-down
napi_value LookupTablePageDown(napi_env env, napi_callback_info info)
{
    ibus_lookup_table_page_down(custom_ime_lookup_table);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-page-up
napi_value LookupTablePageUp(napi_env env, napi_callback_info info)
{
    ibus_lookup_table_page_up(custom_ime_lookup_table);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-set-cursor-pos
napi_value LookupTableSetCursorPos(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    guint32 cursor_pos;
    napi_get_value_uint32(env, args[0], &cursor_pos);

    ibus_lookup_table_set_cursor_pos(custom_ime_lookup_table, cursor_pos);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-set-cursor-visible
napi_value LookupTableSetCursorVisible(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    bool is_visible;
    napi_get_value_bool(env, args[0], &is_visible);

    ibus_lookup_table_set_cursor_visible(custom_ime_lookup_table, is_visible);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-set-label
napi_value LookupTableSetLabel(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    guint32 position;
    napi_get_value_uint32(env, args[0], &position);

    size_t str_size;
    napi_get_value_string_utf8(env, args[1], NULL, 0, &str_size);
    str_size += 1;

    char *text_opt  = (char*)calloc(str_size + 1, sizeof(char));
    size_t str_size_read;
    napi_get_value_string_utf8(env, args[1], text_opt, str_size, &str_size_read);

    IBusText *text = ibus_text_new_from_string(text_opt);

    ibus_lookup_table_set_label(custom_ime_lookup_table, position, text);

    free(text_opt);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-set-page-size
napi_value LookupTableSetPageSize(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    guint32 page_size;
    napi_get_value_uint32(env, args[0], &page_size);

    ibus_lookup_table_set_page_size(custom_ime_lookup_table, page_size);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-set-orientation
napi_value LookupTableSetOrientation(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    guint32 orientation;
    napi_get_value_uint32(env, args[0], &orientation);

    ibus_lookup_table_set_orientation(custom_ime_lookup_table, orientation);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-set-round
napi_value LookupTableSetRound(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    bool is_round;
    napi_get_value_bool(env, args[0], &is_round);

    ibus_lookup_table_set_round(custom_ime_lookup_table, is_round);

    RETURN_UNDEFINED;
}
