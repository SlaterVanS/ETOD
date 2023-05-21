#pragma once
#include "ETOD/Core/Base.h"
#include "ETOD/Core/Application.h"
#include "ETOD/Version/VersionControl.h"
#include "ETOD/Version/VersionConsole.h"

#ifdef ETOD_PLATFORM_WINDOWS

extern ETOD::Application* ETOD::CreateApplication(ApplicationCommandLineArgs args);


#define ETOD_BUILD_ID version // Get Version from VersionConsole

std::string version = ETOD::VersionConsoleToEntryPoint();

int main(int argc, char** argv)
{
	ETOD::Log::Init();
	ETOD_CORE_WARN("��ʼ����־ϵͳ! ");
	ETOD_INFO(" EToD Engine ���������! ");
	ETOD_CORE_TRACE("EToD Engine 2D {}", ETOD_BUILD_ID);

	ETOD_PROFILE_BEGIN_SESSION("Startup", "EToDProfile-Startup.json");
	auto app = ETOD::CreateApplication({ argc, argv });
	ETOD_PROFILE_END_SESSION();

	ETOD_PROFILE_BEGIN_SESSION("Runtime", "EToDProfile-Runtime.json");
	app->Run();
	ETOD_PROFILE_END_SESSION();

	ETOD_PROFILE_BEGIN_SESSION("Startup", "EToDProfile-Shutdown.json");
	delete app;
	ETOD_PROFILE_END_SESSION();
}

#endif