#include "IllustratorSDK.h"

#if defined(__GNUC__)
#pragma GCC visibility push(default)
#endif

extern "C" ASAPI ASErr PluginMain(char* caller, char* selector, void* message);

#if defined(__GNUC__)
#pragma GCC visibility pop
#endif

extern "C"
{
	AIUnicodeStringSuite* sAIUnicodeString = NULL;
	SPBlocksSuite* sSPBlocks = NULL;
}

extern "C" ASAPI ASErr PluginMain(char* caller, char* selector, void* message)
{
	ASErr error = kNoErr;
	SPBasicSuite* sSPBasic = ((SPMessageData*)message)->basic;

	if (sSPBasic->IsEqual(caller, kSPInterfaceCaller)) {

		AIUserSuite *sAIUser = NULL;
		error = sSPBasic->AcquireSuite(kAIUserSuite, kAIUserSuiteVersion, (const void**)&sAIUser);
		error = sSPBasic->AcquireSuite(kAIUnicodeStringSuite, kAIUnicodeStringSuiteVersion, (const void**)&sAIUnicodeString);
		error = sSPBasic->AcquireSuite(kSPBlocksSuite, kSPBlocksSuiteVersion, (const void**)&sSPBlocks);

		if (sSPBasic->IsEqual(selector, kSPInterfaceStartupSelector)) {
			sAIUser->MessageAlert(ai::UnicodeString("Hello World!"));
		}
		else if (sSPBasic->IsEqual(selector, kSPInterfaceShutdownSelector)) {
			sAIUser->MessageAlert(ai::UnicodeString("Goodbye World!"));
		}

		error = sSPBasic->ReleaseSuite(kAIUserSuite, kAIUserSuiteVersion);
		error = sSPBasic->ReleaseSuite(kAIUnicodeStringSuite, kAIUnicodeStringSuiteVersion);
	}
	return error;
}