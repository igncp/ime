#include <ibus.h>
#include <node_api.h>

#include "common.h"
#include "custom_engine.h"

napi_value PropListAppend(napi_env env, napi_callback_info info);
napi_value PropertyGetState(napi_env env, napi_callback_info info);
napi_value PropertyNew(napi_env env, napi_callback_info info);
napi_value PropertySetState(napi_env env, napi_callback_info info);
