#include <ibus.h>
#include <node_api.h>

#include "common.h"
#include "custom_ime.h"

napi_value EngineCommitText(napi_env env, napi_callback_info info);
napi_value EngineDescGetAuthor(napi_env env, napi_callback_info info);
napi_value EngineDescGetDescription(napi_env env, napi_callback_info info);
napi_value EngineDescGetHotkeys(napi_env env, napi_callback_info info);
napi_value EngineDescGetLanguage(napi_env env, napi_callback_info info);
napi_value EngineDescGetLayout(napi_env env, napi_callback_info info);
napi_value EngineDescGetLicense(napi_env env, napi_callback_info info);
napi_value EngineDescGetLongname(napi_env env, napi_callback_info info);
napi_value EngineDescGetName(napi_env env, napi_callback_info info);
napi_value EngineDescGetRank(napi_env env, napi_callback_info info);
napi_value EngineDescGetSetup(napi_env env, napi_callback_info info);
napi_value EngineDescGetSymbol(napi_env env, napi_callback_info info);
napi_value EngineDescGetTextdomain(napi_env env, napi_callback_info info);
napi_value EngineDescGetVersion(napi_env env, napi_callback_info info);
napi_value EngineGetName(napi_env env, napi_callback_info info);
napi_value EngineHideAuxiliaryText(napi_env env, napi_callback_info info);
napi_value EngineHideLookupTable(napi_env env, napi_callback_info info);
napi_value EngineHidePreeditText(napi_env env, napi_callback_info info);
napi_value EngineNew(napi_env env, napi_callback_info info);
napi_value EngineRegisterProperties(napi_env env, napi_callback_info info);
napi_value EngineShowAuxiliaryText(napi_env env, napi_callback_info info);
napi_value EngineShowLookupTable(napi_env env, napi_callback_info info);
napi_value EngineShowPreeditText(napi_env env, napi_callback_info info);
napi_value EngineUpdateAuxiliaryText(napi_env env, napi_callback_info info);
napi_value EngineUpdateLookupTable(napi_env env, napi_callback_info info);
napi_value EngineUpdatePreeditText(napi_env env, napi_callback_info info);
