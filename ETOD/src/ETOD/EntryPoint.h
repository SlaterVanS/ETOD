#pragma once


#ifdef ETOD_PLATFORM_WINDOWS

extern ETOD::Application* ETOD::CreateApplication();

int main(int argc,char** argv)
{
	ETOD::Log::Init();
	ETOD_CORE_WARN("��ʼ����־ϵͳ!");
	int a = 5;
	ETOD_INFO("���������! ��ǰ����={0}",a);

	auto app = ETOD::CreateApplication();
	app->Run();
	delete app;
}

#endif