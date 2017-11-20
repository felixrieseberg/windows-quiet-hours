#include <node.h>
#include <v8.h>

#ifdef _WIN32
#include <windows.h>
#include <malloc.h>
#include <stdio.h>
#else
#include <stdbool.h>
#endif

#define PREFERENCE_KEY TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Notifications\\Settings")

using namespace v8;

void Method(const v8::FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  bool isQuietHours = false;

  #ifdef _WIN32
  HKEY hKey;
  LPTSTR lpValueName = "NOC_GLOBAL_SETTING_TOASTS_ENABLED";
  LONG lResult;
  DWORD dwValue = sizeof(true);
  DWORD dwType, dwSize = sizeof(dwValue);
  lResult = RegOpenKeyEx(HKEY_CURRENT_USER, PREFERENCE_KEY, 0, KEY_READ, &hKey);

  if (lResult == ERROR_SUCCESS)
  {
    lResult = RegQueryValueEx(hKey, lpValueName, 0, &dwType, (LPBYTE)&dwValue, &dwSize);
    RegCloseKey (hKey);
  }

  if (dwValue == 0x00000000)
  {
    isQuietHours = true;
  }
  #endif

  args.GetReturnValue().Set(Boolean::New(isolate, isQuietHours));
}

void Init(Handle<Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();
  exports->Set(String::NewFromUtf8(isolate, "isQuietHours"),
      FunctionTemplate::New(isolate, Method)->GetFunction());
}

NODE_MODULE(quiethours, Init)