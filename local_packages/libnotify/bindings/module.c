#include <node_api.h>
#include <string.h>
#include <glib-object.h>
#include <glib.h>
#include <glib/gstdio.h>
#include <stdlib.h>
#include <signal.h>
#include <libnotify/notify.h>

// https://nodejs.org/api/n-api.html

static void show_message(const char* summary, const char* details) {
  if (!notify_init("libnotify")) {
    g_error("notify_init failed");
    exit(1);
  }
  NotifyNotification* notice = notify_notification_new(summary, details, NULL);
  notify_notification_show(notice, NULL);
  g_object_unref(notice);
}

napi_value Send(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value argv[argc];

  size_t message_max_size = 250;
  char * message = (char*)calloc(message_max_size + 1, sizeof(char));
  size_t copied_size;

  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  napi_get_value_string_utf8(env, argv[0], message, message_max_size, &copied_size);

  show_message(message, NULL);

  napi_value function_result;
  napi_get_undefined(env, &function_result);
  return function_result;
}

napi_value Init(napi_env env, napi_value exports) {
  napi_value fn;

  napi_create_function(env, NULL, 0, Send, NULL, &fn);
  napi_set_named_property(env, exports, "send", fn);

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
