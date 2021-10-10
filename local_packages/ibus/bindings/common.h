#ifndef IBUS_IME_COMMON_H
#define IBUS_IME_COMMON_H

#define CONCAT(a, b) a ## b

#define RETURN_UNDEFINED \
    napi_value function_result; \
    napi_get_undefined(env, &function_result); \
    return function_result

#define OBJ_WRAP(propertyValue, wrappedStruct) \
    napi_value js_object; \
    napi_create_object(env, &js_object); \
 \
    napi_value property_key_name; \
    napi_create_string_utf8(env, "_ibusObjType", NAPI_AUTO_LENGTH, &property_key_name); \
 \
    napi_value property_value; \
    napi_create_string_utf8(env, propertyValue, NAPI_AUTO_LENGTH, &property_value); \
    napi_set_property(env, js_object, property_key_name, property_value); \
 \
    napi_wrap(env, js_object, (void *) wrappedStruct, NULL, NULL, NULL)

#define RETURN_OBJ_WRAP(propertyValue, wrappedStruct) \
    OBJ_WRAP(propertyValue, wrappedStruct); \
    return js_object

#define EXTRACT_KEY_INIT \
    size_t str_size; \
    size_t str_size_read

#define EXTRACT_KEY_PROPERTY(suffix, keyName) \
    napi_value CONCAT(property_, suffix); \
    napi_create_string_utf8(env, keyName, NAPI_AUTO_LENGTH, &CONCAT(property_, suffix)); \
 \
    napi_value CONCAT(value_, suffix); \
    napi_get_property(env, opts_obj, CONCAT(property_, suffix), &CONCAT(value_, suffix))

#define EXTRACT_KEY_STR(suffix, keyName, resultName) \
    EXTRACT_KEY_PROPERTY(suffix, keyName); \
    napi_get_value_string_utf8(env, CONCAT(value_, suffix), NULL, 0, &str_size); \
 \
    str_size += 1; \
    char * resultName = (char*)calloc(str_size + 1, sizeof(char)); \
    napi_get_value_string_utf8(env, CONCAT(value_, suffix), resultName, str_size, &str_size_read)

#define EXTRACT_KEY_UNWRAP(suffix, keyName, resultType, resultName) \
    EXTRACT_KEY_PROPERTY(suffix, keyName); \
    resultType * resultName =  NULL; \
    napi_unwrap(env, CONCAT(value_, suffix), (void **)&resultName)

#define EXTRACT_KEY_INT(suffix, keyName, resultName) \
    EXTRACT_KEY_PROPERTY(suffix, keyName); \
    int resultName = -1; \
    napi_get_value_int32(env, CONCAT(value_, suffix), &resultName)

#define EXTRACT_KEY_BOOL(suffix, keyName, resultName) \
    EXTRACT_KEY_PROPERTY(suffix, keyName); \
    bool resultName = FALSE; \
    napi_get_value_bool(env, CONCAT(value_, suffix), &resultName)

#endif
