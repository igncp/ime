#include <ibus.h>
#include <node_api.h>

#include "common.h"
#include "custom_ime.h"

napi_value BusCurrentInputContext(napi_env env, napi_callback_info info);
napi_value BusGetConnection(napi_env env, napi_callback_info info);
napi_value BusIsConnected(napi_env env, napi_callback_info info);
napi_value BusListEngines(napi_env env, napi_callback_info info);
napi_value BusNew(napi_env env, napi_callback_info info);
napi_value BusRequestName(napi_env env, napi_callback_info info);
napi_value FactoryAddEngine(napi_env env, napi_callback_info info);
napi_value FactoryNew(napi_env env, napi_callback_info info);
