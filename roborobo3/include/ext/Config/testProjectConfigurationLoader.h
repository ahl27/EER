/*
 * testProjectConfigurationLoader.h
 */

#ifndef TESTPROJECTCONFIGURATIONLOADER_H
#define	TESTPROJECTCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class testProjectConfigurationLoader : public ConfigurationLoader
{
	public:
		testProjectConfigurationLoader();
		~testProjectConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};

#endif
