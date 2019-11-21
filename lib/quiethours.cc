#include <napi.h>

#ifdef _WIN32
#include <windows.h>
#include <malloc.h>
#include <stdio.h>
#else
#include <stdbool.h>
#endif

#define PREFERENCE_KEY TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Notifications\\Settings")

Napi::Boolean Method(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
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

  return Napi::Boolean::New(env, isQuietHours);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "isQuietHours"),
              Napi::Function::New(env, Method));
  return exports;
}

NODE_API_MODULE(quiethours, Init)

