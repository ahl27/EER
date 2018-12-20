/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#include "pucks_vanilla/include/pucks_vanillaController.h"
#include "World/World.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"

using namespace Neural;

pucks_vanillaController::pucks_vanillaController( RobotWorldModel *wm ) : TemplateEEController( wm )
{
    // superclass constructor called before this baseclass constructor.
    resetFitness(); // superconstructor calls parent method.
}

pucks_vanillaController::~pucks_vanillaController()
{
    // superclass destructor automatically called after this baseclass destructor.
}

void pucks_vanillaController::stepController()
{
    TemplateEEController::stepController();
}

void pucks_vanillaController::initController()
{
    TemplateEEController::initController();
}

void pucks_vanillaController::performSelection()
{
    TemplateEEController::performSelection();
}

void pucks_vanillaController::performVariation()
{
    TemplateEEController::performVariation();
}

void pucks_vanillaController::broadcastGenome()
{
    TemplateEEController::broadcastGenome();
}

double pucks_vanillaController::getFitness()
{
    return TemplateEEController::getFitness();
}

void pucks_vanillaController::resetFitness()
{
    TemplateEEController::resetFitness();
}

void pucks_vanillaController::updateFitness()
{
    // nothing to do -- updating is performed in pucks_vanillaController::AgentObserver (automatic event when energy item are captured)
}

void pucks_vanillaController::logCurrentState()
{
    TemplateEEController::logCurrentState();
}
