#include <napi.h>

class ObjectWrapDemo : public Napi::ObjectWrap<ObjectWrapDemo>
{
public:
    ObjectWrapDemo(const Napi::CallbackInfo&);
    Napi::Value Greet(const Napi::CallbackInfo&);

    static Napi::Function GetClass(Napi::Env);

private:
    std::string _greeterName;
};

using namespace Napi;

ObjectWrapDemo::ObjectWrapDemo(const Napi::CallbackInfo& info)
    : ObjectWrap(info)
{
    this->_greeterName = info[0].As<Napi::String>().Utf8Value();
}

Napi::Value ObjectWrapDemo::Greet(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    Napi::String name = info[0].As<Napi::String>();

    printf("Hello %s\n", name.Utf8Value().c_str());
    printf("I am %s\n", this->_greeterName.c_str());

    return Napi::String::New(env, this->_greeterName);
}

Napi::Function ObjectWrapDemo::GetClass(Napi::Env env)
{
    // https://github.com/nodejs/node-addon-api/blob/main/doc/object_wrap.md#defineclass
    return DefineClass(
            env,
            "ObjectWrapDemo",
    {
        ObjectWrapDemo::InstanceMethod("greet", &ObjectWrapDemo::Greet),
    });
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    // https://github.com/nodejs/node-addon-api/blob/main/doc/string.md#new-1
    Napi::String name = Napi::String::New(env, "ObjectWrapDemo");

    exports.Set(name, ObjectWrapDemo::GetClass(env));

    return exports;
}

NODE_API_MODULE(addon, Init)
