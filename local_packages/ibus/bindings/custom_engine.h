#ifndef IBUS_IME_CUSTOM_ENGINE_H
#define IBUS_IME_CUSTOM_ENGINE_H

#include <node_api.h>
#include <glib/gstdio.h>
#include <ibus.h>

typedef struct ImeHandlers
{
    napi_env env;
    napi_ref key_event;
} ImeHandlers;

typedef struct _IBusCustomImeEngine IBusCustomImeEngine;
typedef struct _IBusCustomImeEngineClass IBusCustomImeEngineClass;

extern ImeHandlers ime_handlers;
extern IBusCustomImeEngine custom_ime_engine;

void ibus_disconnect_cb(IBusBus *bus, gpointer user_data);

GType ibus_custom_ime_engine_get_type();

#endif
