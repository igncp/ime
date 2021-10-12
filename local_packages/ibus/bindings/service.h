#include <ibus.h>
#include <node_api.h>

#include "common.h"
#include "custom_ime.h"

napi_value ServiceGetObjectPath(napi_env env, napi_callback_info info);
napi_value ServiceNew(napi_env env, napi_callback_info info);
napi_value ServiceRegister(napi_env env, napi_callback_info info);
