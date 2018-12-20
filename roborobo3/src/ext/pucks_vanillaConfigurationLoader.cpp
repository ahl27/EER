#if defined PRJ_PUCKS_VANILLA || !defined MODULAR

#include "Config/pucks_vanillaConfigurationLoader.h"
#include "pucks_vanilla/include/pucks_vanillaWorldObserver.h"
#include "pucks_vanilla/include/pucks_vanillaAgentObserver.h"
#include "pucks_vanilla/include/pucks_vanillaController.h"
#include "WorldModels/RobotWorldModel.h"

pucks_vanillaConfigurationLoader::pucks_vanillaConfigurationLoader()
{
}

pucks_vanillaConfigurationLoader::~pucks_vanillaConfigurationLoader()
{
	//nothing to do
}

WorldObserver* pucks_vanillaConfigurationLoader::make_WorldObserver(World* wm)
{
	return new pucks_vanillaWorldObserver(wm);
}

RobotWorldModel* pucks_vanillaConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* pucks_vanillaConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new pucks_vanillaAgentObserver(wm);
}

Controller* pucks_vanillaConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new pucks_vanillaController(wm);
}

#endif
