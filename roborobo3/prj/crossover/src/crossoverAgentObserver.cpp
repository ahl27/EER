/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#include "crossover/include/crossoverAgentObserver.h"
#include "WorldModels/RobotWorldModel.h"
#include "RoboroboMain/roborobo.h"

crossoverAgentObserver::crossoverAgentObserver( RobotWorldModel *wm ) : TemplateEEAgentObserver ( wm )
{
    // superclass constructor called before
}

crossoverAgentObserver::~crossoverAgentObserver()
{
    // superclass destructor called before
}

/*
 * Manage energy wrt. foraging (if energy management is activated in parameter files)
 *
 */
void crossoverAgentObserver::step()
{
    // * update energy if needed
    if ( gEnergyLevel && _wm->isAlive() )
    {
        _wm->substractEnergy(1);
        assert( _wm->getEnergyLevel() >= 0 );
        if ( _wm->getEnergyLevel() == 0 )
            _wm->setAlive(false);
    }
        
    TemplateEEAgentObserver::step();
}
