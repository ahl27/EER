/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef TESTPROJECTWORLDOBSERVER_H
#define TESTPROJECTWORLDOBSERVER_H

#include "Observers/WorldObserver.h"

class World;

class testProjectWorldObserver : public WorldObserver
{
	protected:
		
	public:
		testProjectWorldObserver( World *__world );
		~testProjectWorldObserver();
				
		void initPre();
        void initPost();

        void stepPre();
        void stepPost();
		
};

#endif

