#include <node.h>
#include "nan.h"

#ifdef _WIN32
#include <windows.h>
#include <malloc.h>
#include <stdio.h>
#else
#include <stdbool.h>
#endif

#define PREFERENCE_KEY TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Notifications\\Settings")

NAN_METHOD(Method) {
  Nan::HandleScope scope;
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

  info.GetReturnValue().Set(Nan::New(isQuietHours));
}

NAN_MODULE_INIT(Init) {
  Nan::Set(exports, Nan::New("isQuietHours").ToLocalChecked(),
      Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Method)).ToLocalChecked());
}

NODE_MODULE(quiethours, Init)
