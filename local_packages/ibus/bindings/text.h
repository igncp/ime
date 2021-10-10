#include <ibus.h>
#include <node_api.h>

#include "common.h"

napi_value AttrForegroundNew(napi_env env, napi_callback_info info);
napi_value AttrListAppend(napi_env env, napi_callback_info info);
napi_value AttrListNew(napi_env env, napi_callback_info info);
napi_value AttributeNew(napi_env env, napi_callback_info info);
napi_value TextNewFromString(napi_env env, napi_callback_info info);
napi_value TextSetAttributes(napi_env env, napi_callback_info info);
