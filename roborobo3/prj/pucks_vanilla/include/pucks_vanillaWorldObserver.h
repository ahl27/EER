/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#ifndef PUCKS_VANILLAWORLDOBSERVER_H
#define PUCKS_VANILLAWORLDOBSERVER_H

#include "TemplateEE/include/TemplateEEWorldObserver.h"

class World;

class pucks_vanillaWorldObserver : public TemplateEEWorldObserver
{
public:
    pucks_vanillaWorldObserver(World *world);
    ~pucks_vanillaWorldObserver();
    
    void initPre();
    void initPost();

    void stepPre();
    void stepPost();

protected:    
    virtual void monitorPopulation( bool localVerbose = true );
};

#endif
