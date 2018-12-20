/*
 * crossoverConfigurationLoader.h
 */

#ifndef CROSSOVERCONFIGURATIONLOADER_H
#define CROSSOVERCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class crossoverConfigurationLoader : public ConfigurationLoader
{
	private:

	public:
		crossoverConfigurationLoader();
		~crossoverConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};



#endif
