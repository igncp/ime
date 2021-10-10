#include "share.h"

// https://ibus.github.io/docs/ibus-1.5/ibus-ibusshare.html#ibus-init
napi_value Init(napi_env env, napi_callback_info info)
{
    ibus_init();

    RETURN_UNDEFINED;
}

// https://ibus.github.io/docs/ibus-1.5/ibus-ibusshare.html#ibus-main
napi_value Main(napi_env env, napi_callback_info info)
{
    ibus_main();

    RETURN_UNDEFINED;
}
