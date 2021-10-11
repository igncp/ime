#include "lookup_table.h"

#define UNWRAP_TABLE \
    size_t argc = 1; \
    napi_value args[argc]; \
    napi_get_cb_info(env, info, &argc, args, NULL, NULL); \
 \
    IBusLookupTable * table =  NULL; \
    napi_unwrap(env, args[0], (void **)&table)

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-append-candidate
napi_value LookupTableAppendCandidate(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusLookupTable * table =  NULL;
    napi_unwrap(env, args[0], (void **)&table);

    IBusText * text =  NULL;
    napi_unwrap(env, args[1], (void **)&text);

    ibus_lookup_table_append_candidate(table, text);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-clear
napi_value LookupTableClear(napi_env env, napi_callback_info info)
{
    UNWRAP_TABLE;

    ibus_lookup_table_clear(table);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-cursor-down
napi_value LookupTableCursorDown(napi_env env, napi_callback_info info)
{
    UNWRAP_TABLE;

    ibus_lookup_table_cursor_down(table);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-cursor-up
napi_value LookupTableCursorUp(napi_env env, napi_callback_info info)
{
    UNWRAP_TABLE;

    ibus_lookup_table_cursor_up(table);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-get-cursor-in-page
napi_value LookupTableGetCursorInPage(napi_env env, napi_callback_info info)
{
    UNWRAP_TABLE;

    guint cursor_pos = ibus_lookup_table_get_cursor_in_page(table);

    napi_value cursor_pos_value;
    napi_create_uint32(env, cursor_pos, &cursor_pos_value);
    return cursor_pos_value;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-get-cursor-pos
napi_value LookupTableGetCursorPos(napi_env env, napi_callback_info info)
{
    UNWRAP_TABLE;

    guint cursor_pos = ibus_lookup_table_get_cursor_pos(table);

    napi_value cursor_pos_value;
    napi_create_uint32(env, cursor_pos, &cursor_pos_value);
    return cursor_pos_value;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-get-number-of-candidates
napi_value LookupTableGetNumberOfCandidates(napi_env env, napi_callback_info info)
{
    UNWRAP_TABLE;

    guint candidates_num = ibus_lookup_table_get_number_of_candidates(table);

    napi_value candidates_num_value;
    napi_create_uint32(env, candidates_num, &candidates_num_value);
    return candidates_num_value;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-get-page-size
napi_value LookupTableGetPageSize(napi_env env, napi_callback_info info)
{
    UNWRAP_TABLE;

    guint page_size = ibus_lookup_table_get_page_size(table);

    napi_value page_size_value;
    napi_create_uint32(env, page_size, &page_size_value);
    return page_size_value;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-new
napi_value LookupTableNew(napi_env env, napi_callback_info info)
{
    size_t argc = 4;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    guint32 page_size;
    napi_get_value_uint32(env, args[0], &page_size);

    guint32 cursor_pos;
    napi_get_value_uint32(env, args[1], &cursor_pos);

    bool is_visible;
    napi_get_value_bool(env, args[2], &is_visible);

    bool is_round;
    napi_get_value_bool(env, args[3], &is_round);

    IBusLookupTable * lookup_table = ibus_lookup_table_new(page_size, cursor_pos, is_visible, is_round);

    g_object_ref_sink(lookup_table);

    RETURN_OBJ_WRAP("IBusLookupTable", lookup_table);
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-page-down
napi_value LookupTablePageDown(napi_env env, napi_callback_info info)
{
    UNWRAP_TABLE;

    ibus_lookup_table_page_down(table);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-page-up
napi_value LookupTablePageUp(napi_env env, napi_callback_info info)
{
    UNWRAP_TABLE;

    ibus_lookup_table_page_up(table);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-set-cursor-pos
napi_value LookupTableSetCursorPos(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusLookupTable * table =  NULL;
    napi_unwrap(env, args[0], (void **)&table);

    guint32 cursor_pos;
    napi_get_value_uint32(env, args[1], &cursor_pos);

    ibus_lookup_table_set_cursor_pos(table, cursor_pos);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-set-cursor-visible
napi_value LookupTableSetCursorVisible(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusLookupTable * table =  NULL;
    napi_unwrap(env, args[0], (void **)&table);

    bool is_visible;
    napi_get_value_bool(env, args[1], &is_visible);

    ibus_lookup_table_set_cursor_visible(table, is_visible);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-set-label
napi_value LookupTableSetLabel(napi_env env, napi_callback_info info)
{
    size_t argc = 3;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusLookupTable * table =  NULL;
    napi_unwrap(env, args[0], (void **)&table);

    guint32 position;
    napi_get_value_uint32(env, args[1], &position);

    size_t str_size;
    napi_get_value_string_utf8(env, args[2], NULL, 0, &str_size);
    str_size += 1;

    char *text_opt  = (char*)calloc(str_size + 1, sizeof(char));
    size_t str_size_read;
    napi_get_value_string_utf8(env, args[2], text_opt, str_size, &str_size_read);

    IBusText *text = ibus_text_new_from_string(text_opt);

    ibus_lookup_table_set_label(table, position, text);

    free(text_opt);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-set-page-size
napi_value LookupTableSetPageSize(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusLookupTable * table =  NULL;
    napi_unwrap(env, args[0], (void **)&table);

    guint32 page_size;
    napi_get_value_uint32(env, args[1], &page_size);

    ibus_lookup_table_set_page_size(table, page_size);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-set-orientation
napi_value LookupTableSetOrientation(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusLookupTable * table =  NULL;
    napi_unwrap(env, args[0], (void **)&table);

    guint32 orientation;
    napi_get_value_uint32(env, args[1], &orientation);

    ibus_lookup_table_set_orientation(table, orientation);

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/IBusLookupTable.html#ibus-lookup-table-set-round
napi_value LookupTableSetRound(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    IBusLookupTable * table =  NULL;
    napi_unwrap(env, args[0], (void **)&table);

    bool is_round;
    napi_get_value_bool(env, args[1], &is_round);

    ibus_lookup_table_set_round(table, is_round);

    RETURN_UNDEFINED;
}
