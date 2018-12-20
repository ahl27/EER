#if defined PRJ_CROSSOVER || !defined MODULAR

#include "Config/crossoverConfigurationLoader.h"
#include "crossover/include/crossoverWorldObserver.h"
#include "crossover/include/crossoverAgentObserver.h"
#include "crossover/include/crossoverController.h"
#include "WorldModels/RobotWorldModel.h"

crossoverConfigurationLoader::crossoverConfigurationLoader()
{
}

crossoverConfigurationLoader::~crossoverConfigurationLoader()
{
	//nothing to do
}

WorldObserver* crossoverConfigurationLoader::make_WorldObserver(World* wm)
{
	return new crossoverWorldObserver(wm);
}

RobotWorldModel* crossoverConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* crossoverConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new crossoverAgentObserver(wm);
}

Controller* crossoverConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
    return new crossoverController(wm);
}

#endif
