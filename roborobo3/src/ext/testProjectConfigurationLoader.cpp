#if defined PRJ_TESTPROJECT || !defined MODULAR

#include "Config/testProjectConfigurationLoader.h"
#include "testProject/include/testProjectWorldObserver.h"
#include "testProject/include/testProjectAgentObserver.h"
#include "testProject/include/testProjectController.h"
#include "WorldModels/RobotWorldModel.h"


testProjectConfigurationLoader::testProjectConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

testProjectConfigurationLoader::~testProjectConfigurationLoader()
{
	//nothing to do
}

WorldObserver* testProjectConfigurationLoader::make_WorldObserver(World* wm)
{
	return new testProjectWorldObserver(wm);
}

RobotWorldModel* testProjectConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* testProjectConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new testProjectAgentObserver(wm);
}

Controller* testProjectConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new testProjectController(wm);
}


#endif
