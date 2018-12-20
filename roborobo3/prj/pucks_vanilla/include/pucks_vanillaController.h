/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#ifndef PUCKS_VANILLACONTROLLER_H
#define PUCKS_VANILLACONTROLLER_H

#include "TemplateEE/include/TemplateEEController.h"

using namespace Neural;

class RobotWorldModel;

class pucks_vanillaController : public TemplateEEController
{
    public:
    
        pucks_vanillaController(RobotWorldModel *wm);
        ~pucks_vanillaController();

        double getFitness();

    protected:
    
        void initController();
        void stepController();
    
        void performSelection();
        void performVariation();
    
        void broadcastGenome();
    
        void resetFitness();
        void updateFitness();

        void logCurrentState();
};


#endif

