#include <node_api.h>

#include "custom_ime.h"
#include "lookup_table.h"
#include "engine.h"
#include "property.h"
#include "text.h"
#include "share.h"
#include "bus.h"

extern ImeHandlers ime_handlers;
extern IBusCustomImeEngine custom_ime_engine;
extern IBusLookupTable * custom_ime_lookup_table;

napi_value RegisterHandlers(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1];
    napi_value fn_value;

    napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    napi_value provided_handlers = args[0];

#define SET_HANDLER(keyName, handlerRef) \
    napi_get_named_property(env, provided_handlers, keyName, &fn_value); \
    napi_create_reference(env, fn_value, 1, &handlerRef)

    SET_HANDLER("disable", ime_handlers.disable);
    SET_HANDLER("enable", ime_handlers.enable);
    SET_HANDLER("focusIn", ime_handlers.focus_in);
    SET_HANDLER("focusOut", ime_handlers.focus_out);
    SET_HANDLER("keyEvent", ime_handlers.key_event);
    SET_HANDLER("propertyActivate", ime_handlers.property_activate);

    ime_handlers.env = env;

    RETURN_UNDEFINED;
}

napi_value MainModule(napi_env env, napi_value exports)
{
    napi_value fn;

#define NODE_EXPOSE_FN(FnName, keyName) \
    napi_create_function(env, NULL, 0, FnName, NULL, &fn); \
    napi_set_named_property(env, exports, keyName, fn);

    NODE_EXPOSE_FN(AttrForegroundNew, "attrForegroundNew");
    NODE_EXPOSE_FN(AttrListAppend, "attrListAppend");
    NODE_EXPOSE_FN(AttrListNew, "attrListNew");
    NODE_EXPOSE_FN(AttributeNew, "attributeNew");
    NODE_EXPOSE_FN(BusCurrentInputContext, "busCurrentInputContext");
    NODE_EXPOSE_FN(BusGetConnection, "busGetConnection");
    NODE_EXPOSE_FN(BusIsConnected, "busIsConnected");
    NODE_EXPOSE_FN(BusListEngines, "busListEngines");
    NODE_EXPOSE_FN(BusNew, "busNew");
    NODE_EXPOSE_FN(BusRequestName, "busRequestName");
    NODE_EXPOSE_FN(EngineCommitText, "engineCommitText");
    NODE_EXPOSE_FN(EngineDescGetAuthor, "engineDescGetAuthor");
    NODE_EXPOSE_FN(EngineDescGetDescription, "engineDescGetDescription");
    NODE_EXPOSE_FN(EngineDescGetHotkeys, "engineDescGetHotkeys");
    NODE_EXPOSE_FN(EngineDescGetLanguage, "engineDescGetLanguage");
    NODE_EXPOSE_FN(EngineDescGetLayout, "engineDescGetLayout");
    NODE_EXPOSE_FN(EngineDescGetLicense, "engineDescGetLicense");
    NODE_EXPOSE_FN(EngineDescGetLongname, "engineDescGetLongname");
    NODE_EXPOSE_FN(EngineDescGetName, "engineDescGetName");
    NODE_EXPOSE_FN(EngineDescGetRank, "engineDescGetRank");
    NODE_EXPOSE_FN(EngineDescGetSetup, "engineDescGetSetup");
    NODE_EXPOSE_FN(EngineDescGetSymbol, "engineDescGetSymbol");
    NODE_EXPOSE_FN(EngineDescGetTextdomain, "engineDescGetTextdomain");
    NODE_EXPOSE_FN(EngineDescGetVersion, "engineDescGetVersion");
    NODE_EXPOSE_FN(EngineGetName, "engineGetName");
    NODE_EXPOSE_FN(EngineHideAuxiliaryText, "engineHideAuxiliaryText");
    NODE_EXPOSE_FN(EngineHideLookupTable, "engineHideLookupTable");
    NODE_EXPOSE_FN(EngineHidePreeditText, "engineHidePreeditText");
    NODE_EXPOSE_FN(EngineRegisterProperties, "engineRegisterProperties");
    NODE_EXPOSE_FN(EngineShowAuxiliaryText, "engineShowAuxiliaryText");
    NODE_EXPOSE_FN(EngineShowLookupTable, "engineShowLookupTable");
    NODE_EXPOSE_FN(EngineShowPreeditText, "engineShowPreeditText");
    NODE_EXPOSE_FN(EngineUpdateAuxiliaryText, "engineUpdateAuxiliaryText");
    NODE_EXPOSE_FN(EngineUpdateLookupTable, "engineUpdateLookupTable");
    NODE_EXPOSE_FN(EngineUpdatePreeditText, "engineUpdatePreeditText");
    NODE_EXPOSE_FN(FactoryAddEngine, "factoryAddEngine");
    NODE_EXPOSE_FN(FactoryNew, "factoryNew");
    NODE_EXPOSE_FN(Init, "init");
    NODE_EXPOSE_FN(LookupTableAppendCandidate, "lookupTableAppendCandidate");
    NODE_EXPOSE_FN(LookupTableClear, "lookupTableClear");
    NODE_EXPOSE_FN(LookupTableCursorDown, "lookupTableCursorDown");
    NODE_EXPOSE_FN(LookupTableCursorUp, "lookupTableCursorUp");
    NODE_EXPOSE_FN(LookupTableGetCursorInPage, "lookupTableGetCursorInPage");
    NODE_EXPOSE_FN(LookupTableGetCursorPos, "lookupTableGetCursorPos");
    NODE_EXPOSE_FN(LookupTableGetNumberOfCandidates, "lookupTableGetNumberOfCandidates");
    NODE_EXPOSE_FN(LookupTableGetPageSize, "lookupTableGetPageSize");
    NODE_EXPOSE_FN(LookupTablePageDown, "lookupTablePageDown");
    NODE_EXPOSE_FN(LookupTablePageUp, "lookupTablePageUp");
    NODE_EXPOSE_FN(LookupTableSetCursorPos, "lookupTableSetCursorPos");
    NODE_EXPOSE_FN(LookupTableSetCursorVisible, "lookupTableSetCursorVisible");
    NODE_EXPOSE_FN(LookupTableSetLabel, "lookupTableSetLabel");
    NODE_EXPOSE_FN(LookupTableSetOrientation, "lookupTableSetOrientation");
    NODE_EXPOSE_FN(LookupTableSetPageSize, "lookupTableSetPageSize");
    NODE_EXPOSE_FN(LookupTableSetRound, "lookupTableSetRound");
    NODE_EXPOSE_FN(Main, "main");
    NODE_EXPOSE_FN(PropListAppend, "propListAppend");
    NODE_EXPOSE_FN(PropListNew, "propListNew");
    NODE_EXPOSE_FN(PropertyGetState, "propertyGetState");
    NODE_EXPOSE_FN(PropertyNew, "propertyNew");
    NODE_EXPOSE_FN(PropertySetState, "propertySetState");
    NODE_EXPOSE_FN(RegisterHandlers, "registerHandlers");
    NODE_EXPOSE_FN(TextNewFromString, "textNewFromString");
    NODE_EXPOSE_FN(TextSetAttributes, "textSetAttributes");

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, MainModule)
