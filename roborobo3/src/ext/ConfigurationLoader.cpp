#include "Config/ConfigurationLoader.h"
#include "Config/TemplateWanderConfigurationLoader.h"
#include "Config/TemplateBoidsConfigurationLoader.h"
#include "Config/TemplateRandomwalkConfigurationLoader.h"
#include "Config/TemplateEEConfigurationLoader.h"
#include "Config/TemplateVanillaEEConfigurationLoader.h"
#include "Config/TemplateMedeaConfigurationLoader.h"
#include "Config/testProjectConfigurationLoader.h"
#include "Config/crossoverConfigurationLoader.h"
#include "Config/pucks_vanillaConfigurationLoader.h"
//###DO-NOT-DELETE-THIS-LINE###TAG:INCLUDE###//


ConfigurationLoader::ConfigurationLoader()
{
	//nothing to do
}

ConfigurationLoader::~ConfigurationLoader()
{
	//nothing to do
}

ConfigurationLoader* ConfigurationLoader::make_ConfigurationLoader (std::string configurationLoaderObjectName)
{
	if (0)
	{
		// >>> Never reached
	}
#if defined PRJ_TEMPLATEWANDER || !defined MODULAR
	else if (configurationLoaderObjectName == "TemplateWanderConfigurationLoader" )
	{
		return new TemplateWanderConfigurationLoader();
	}
#endif
#if defined PRJ_TEMPLATEBOIDS || !defined MODULAR
	else if (configurationLoaderObjectName == "TemplateBoidsConfigurationLoader" )
	{
		return new TemplateBoidsConfigurationLoader();
	}
#endif
#if defined PRJ_TEMPLATERANDOMWALK || !defined MODULAR
	else if (configurationLoaderObjectName == "TemplateRandomwalkConfigurationLoader" )
	{
		return new TemplateRandomwalkConfigurationLoader();
	}
#endif
#if defined PRJ_TEMPLATEEE || !defined MODULAR
    else if (configurationLoaderObjectName == "TemplateEEConfigurationLoader" )
    {
        return new TemplateEEConfigurationLoader();
    }
#endif
#if defined PRJ_TEMPLATEVANILLAEE || !defined MODULAR
	else if (configurationLoaderObjectName == "TemplateVanillaEEConfigurationLoader" )
	{
		return new TemplateVanillaEEConfigurationLoader();
	}
#endif
#if defined PRJ_TEMPLATEMEDEA || !defined MODULAR
	else if (configurationLoaderObjectName == "TemplateMedeaConfigurationLoader" )
	{
		return new TemplateMedeaConfigurationLoader();
	}
#endif
#if defined PRJ_TESTPROJECT || !defined MODULAR
	else if (configurationLoaderObjectName == "testProjectConfigurationLoader" )
	{
		return new testProjectConfigurationLoader();
	}
#endif
#if defined PRJ_CROSSOVER || !defined MODULAR
	else if (configurationLoaderObjectName == "crossoverConfigurationLoader" )
	{
		return new crossoverConfigurationLoader();
	}
#endif
#if defined PRJ_PUCKS_VANILLA || !defined MODULAR
	else if (configurationLoaderObjectName == "pucks_vanillaConfigurationLoader" )
	{
		return new pucks_vanillaConfigurationLoader();
	}
#endif
    //###DO-NOT-DELETE-THIS-LINE###TAG:SWITCH###//
	else
	{
		return NULL;
	}

}
