/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef TESTPROJECTAGENTOBSERVER_H
#define TESTPROJECTAGENTOBSERVER_H 

#include "Observers/AgentObserver.h"

class RobotWorldModel;

class testProjectAgentObserver : public AgentObserver
{
	public:
		testProjectAgentObserver( );
		testProjectAgentObserver( RobotWorldModel *__wm );
		~testProjectAgentObserver();
				
		void reset();
		void step();
		
};


#endif

