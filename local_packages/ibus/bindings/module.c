#include <node_api.h>

#include "custom_engine.h"
#include "lookup_table.h"
#include "engine.h"
#include "property.h"
#include "text.h"

extern ImeHandlers ime_handlers;
extern IBusCustomImeEngine custom_ime_engine;
extern IBusLookupTable * custom_ime_lookup_table;

napi_value Init(napi_env env, napi_callback_info info)
{
    ibus_init();
    IBusBus *bus = ibus_bus_new();
    g_object_ref_sink(bus);

    if (!ibus_bus_is_connected(bus))
    {
        g_warning("not connected to ibus");
        exit(1);
    }

    g_signal_connect(bus, "disconnected", G_CALLBACK(ibus_disconnect_cb), NULL);

    IBusFactory *factory = ibus_factory_new(ibus_bus_get_connection(bus));
    g_object_ref_sink(factory);

    size_t argc = 3;
    napi_value args[argc];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    size_t str_size_ime, str_size_bus;
    napi_get_value_string_utf8(env, args[0], NULL, 0, &str_size_ime);
    str_size_ime += 1;
    napi_get_value_string_utf8(env, args[1], NULL, 0, &str_size_bus);
    str_size_bus += 1;

    size_t str_size_read_ime, str_size_read_bus;
    char *ime_name  = (char*)calloc(str_size_ime + 1, sizeof(char));
    napi_get_value_string_utf8(env, args[0], ime_name, str_size_ime, &str_size_read_ime);
    char *bus_name  = (char*)calloc(str_size_bus + 1, sizeof(char));
    napi_get_value_string_utf8(env, args[1], bus_name, str_size_bus, &str_size_read_bus);

    napi_value cb = args[2];

    printf("IME name: %.*s\n", (int) str_size_read_ime, ime_name);
    printf("Bus name: %.*s\n", (int) str_size_read_bus, bus_name);

    ibus_factory_add_engine(factory, ime_name, (ibus_custom_ime_engine_get_type()));

    if (!ibus_bus_request_name(bus, bus_name, 0))
    {
        printf("error requesting bus name\n");
        exit(1);
    }

    napi_value global;
    napi_get_global(env, &global);
    napi_value result;
    napi_call_function(env, global, cb, 0, NULL, &result);

    free(ime_name);
    free(bus_name);

    g_object_unref(factory);
    g_object_unref(bus);

    RETURN_UNDEFINED;
}

napi_value Main(napi_env env, napi_callback_info info)
{
    ibus_main();

    RETURN_UNDEFINED;
}

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
    NODE_EXPOSE_FN(EngineCommitText, "engineCommitText");
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
    NODE_EXPOSE_FN(PropertyGetState, "propertyGetState");
    NODE_EXPOSE_FN(PropertyNew, "propertyNew");
    NODE_EXPOSE_FN(PropertySetState, "propertySetState");
    NODE_EXPOSE_FN(RegisterHandlers, "registerHandlers");
    NODE_EXPOSE_FN(TextNewFromString, "textNewFromString");
    NODE_EXPOSE_FN(TextSetAttributes, "textSetAttributes");

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, MainModule)
