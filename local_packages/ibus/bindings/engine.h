#include <ibus.h>
#include <node_api.h>

#include "common.h"
#include "custom_engine.h"

napi_value EngineCommitText(napi_env env, napi_callback_info info);
napi_value EngineGetName(napi_env env, napi_callback_info info);
napi_value EngineHideAuxiliaryText(napi_env env, napi_callback_info info);
napi_value EngineHideLookupTable(napi_env env, napi_callback_info info);
napi_value EngineHidePreeditText(napi_env env, napi_callback_info info);
napi_value EngineRegisterProperties(napi_env env, napi_callback_info info);
napi_value EngineShowAuxiliaryText(napi_env env, napi_callback_info info);
napi_value EngineShowLookupTable(napi_env env, napi_callback_info info);
napi_value EngineShowPreeditText(napi_env env, napi_callback_info info);
napi_value EngineUpdateAuxiliaryText(napi_env env, napi_callback_info info);
napi_value EngineUpdateLookupTable(napi_env env, napi_callback_info info);
napi_value EngineUpdatePreeditText(napi_env env, napi_callback_info info);
