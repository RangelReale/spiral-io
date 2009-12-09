#include "spiral/application/Application.h"

namespace spiral
{

Application::Options::Options(const std::string& name) :
    spiral::Options(name)
{
}



Application::Application(const Application::Options& conf) : 
	config_(conf)
{ 
}

void Application::run()
{
}

}
