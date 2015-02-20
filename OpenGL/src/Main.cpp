#include "MyApplication.h"

int main() 
{
	
	Application* theApp = new Application();
	theApp->Run();

	delete theApp;
	return 0;
}