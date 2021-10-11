#include <ibus.h>
#include <node_api.h>

#include "common.h"
#include "custom_ime.h"

napi_value LookupTableAppendCandidate(napi_env env, napi_callback_info info);
napi_value LookupTableClear(napi_env env, napi_callback_info info);
napi_value LookupTableCursorDown(napi_env env, napi_callback_info info);
napi_value LookupTableCursorUp(napi_env env, napi_callback_info info);
napi_value LookupTableGetCursorInPage(napi_env env, napi_callback_info info);
napi_value LookupTableGetCursorPos(napi_env env, napi_callback_info info);
napi_value LookupTableGetNumberOfCandidates(napi_env env, napi_callback_info info);
napi_value LookupTableGetPageSize(napi_env env, napi_callback_info info);
napi_value LookupTableNew(napi_env env, napi_callback_info info);
napi_value LookupTablePageDown(napi_env env, napi_callback_info info);
napi_value LookupTablePageUp(napi_env env, napi_callback_info info);
napi_value LookupTableSetCursorPos(napi_env env, napi_callback_info info);
napi_value LookupTableSetCursorVisible(napi_env env, napi_callback_info info);
napi_value LookupTableSetLabel(napi_env env, napi_callback_info info);
napi_value LookupTableSetOrientation(napi_env env, napi_callback_info info);
napi_value LookupTableSetPageSize(napi_env env, napi_callback_info info);
napi_value LookupTableSetRound(napi_env env, napi_callback_info info);
