#include <node.h>
#include <v8.h>

#include <windows.h>
#include <malloc.h>
#include <stdio.h>

#define PREFERENCE_KEY TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Notifications\\Settings")

using namespace v8;

void Method(const v8::FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  HKEY hKey;
  LPTSTR lpValueName = "NOC_GLOBAL_SETTING_TOASTS_ENABLED";
  DWORD dwDefault = 0x00000000;
  LONG lResult;
  DWORD dwValue, dwType, dwSize = sizeof(dwValue);
  BOOL isQuietHours = true;
  lResult = RegOpenKeyEx(HKEY_CURRENT_USER, PREFERENCE_KEY, 0, KEY_READ, &hKey);

  if (lResult == ERROR_SUCCESS)
  {
    lResult = RegQueryValueEx(hKey, lpValueName, 0, &dwType, (LPBYTE)&dwValue, &dwSize);
    RegCloseKey (hKey);
  }

  if (dwValue != 0x00000000)
  {
    isQuietHours = false;
  }

  args.GetReturnValue().Set(Boolean::New(isolate, isQuietHours));
}

void Init(Handle<Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();
  exports->Set(String::NewFromUtf8(isolate, "isQuietHours"),
      FunctionTemplate::New(isolate, Method)->GetFunction());
}

NODE_MODULE(quiethours, Init)