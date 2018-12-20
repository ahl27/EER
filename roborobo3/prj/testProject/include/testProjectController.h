/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef TESTPROJECTCONTROLLER_H
#define TESTPROJECTCONTROLLER_H

#include "Controllers/Controller.h"
#include "RoboroboMain/common.h"

class RobotWorldModel;

class testProjectController : public Controller
{
	public:
		//Initializes the variables
		testProjectController( RobotWorldModel *__wm );
		~testProjectController();
    
        std::vector<double> _params;
		
		void reset();
		void step();
    
        void monitorSensoryInformation();
    
        std::string inspect( std::string prefix = "" );
};


#endif

