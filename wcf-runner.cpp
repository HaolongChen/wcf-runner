#include <Windows.h>
#include <iostream>

typedef int (*WxInitSDKFunc)(bool, int, int*);
typedef int (*WxDestroySDKFunc)();

const bool DEBUG = false;
const int PORT = 10086;

int main() {

	HMODULE hDll = LoadLibraryW(TEXT("sdk.dll"));

	if (hDll == NULL) {
		std::cerr << "Failed to load sdk.dll" << std::endl;
		return 1;
	}

	WxInitSDKFunc WxInitSDK = (WxInitSDKFunc)GetProcAddress(hDll, "WxInitSDK");

	if (WxInitSDK == NULL) {
		std::cerr << "Failed to get WxInitSDK function address" << std::endl;
		FreeLibrary(hDll);
		return 1;
	}

	WxDestroySDKFunc WxDestroySDK = (WxDestroySDKFunc)GetProcAddress(hDll, "WxDestroySDK");

	if (WxDestroySDK == NULL) {
		std::cerr << "Failed to get WxDestroySDK function address" << std::endl;
		FreeLibrary(hDll);
		return 1;
	}

	int status = 0;

	if (WxInitSDK(DEBUG, PORT, &status) != 0) {
		std::cerr << "WxInitSDK failed" << std::endl;
		FreeLibrary(hDll);
		return 1;
	}

	const int END_BITS = (1 << 4 - 1) << 4;

	for (;status | END_BITS;) {

	}

	std::cout << "Status: " << status << std::endl;

	WxDestroySDK();

	FreeLibrary(hDll);

	status = 0;

	return 0;
}