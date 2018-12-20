/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#ifndef CROSSOVERWORLDOBSERVER_H
#define CROSSOVERWORLDOBSERVER_H

#include "TemplateEE/include/TemplateEEWorldObserver.h"

class World;

class crossoverWorldObserver : public TemplateEEWorldObserver
{
public:
    crossoverWorldObserver(World *world);
    ~crossoverWorldObserver();
    
    void initPre();
    void initPost();

    void stepPre();
    void stepPost();
    
    void monitorPopulation( bool localVerbose );
};

#endif
