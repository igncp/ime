#ifndef IBUS_IME_CUSTOM_IME_H
#define IBUS_IME_CUSTOM_IME_H

#include <node_api.h>
#include <glib/gstdio.h>
#include <ibus.h>

typedef struct ImeHandlers
{
    napi_env env;
    napi_ref disable;
    napi_ref enable;
    napi_ref focus_in;
    napi_ref focus_out;
    napi_ref key_event;
    napi_ref property_activate;
} ImeHandlers;

typedef struct _IBusCustomImeEngine IBusCustomImeEngine;
typedef struct _IBusCustomImeEngineClass IBusCustomImeEngineClass;

extern ImeHandlers ime_handlers;
extern IBusCustomImeEngine custom_ime_engine;
extern IBusLookupTable * custom_ime_lookup_table;

GType ibus_custom_ime_engine_get_type();

#endif
