/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "testProject/include/testProjectWorldObserver.h"
#include "World/World.h"
#include "Utilities/Misc.h"
#include "testProject/include/testProjectController.h"
#include "RoboroboMain/roborobo.h"


testProjectWorldObserver::testProjectWorldObserver( World *__world ) : WorldObserver( __world )
{
	_world = __world;
}

testProjectWorldObserver::~testProjectWorldObserver()
{
	// nothing to do.
}

void testProjectWorldObserver::initPre()
{
    // nothing to do.
}

void testProjectWorldObserver::initPost()
{
    // nothing to do.
}

void testProjectWorldObserver::stepPre()
{
    
    // The following code shows an example where every 100 iterations, robots are re-located to their initial positions, and parameters are randomly changed.
    //
    // REMOVE OR COMMENT THE FOLLOWING TO AVOID RESETTING POSITIONS EVERY 100 ITERATIONS
    //
    
    if ( gWorld->getIterations() % 100 == 0 )
    {
        if ( gVerbose && gDisplayMode == 0 )
            std::cout << "Randomizing parameters\n";

        for ( int i = 0 ; i != gWorld->getNbOfRobots() ; i++ )
        {
            Robot *robot = (gWorld->getRobot(i));
            
            (*robot).setCoordReal( 100 + (i*50)%800 , 100 + ( i*50/800 * 50 )  );
            
            testProjectController *controller = ((testProjectController*)(gWorld->getRobot(i)->getController()));
            
            for ( size_t j = 0 ; j != (*controller)._params.size() ; j++ )
            {
                (*controller)._params[(int)j] = random()*2.0-1.0;
            }
        }
    }
    
}

void testProjectWorldObserver::stepPost()
{
    // nothing to do.
}
