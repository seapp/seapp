/**
 * @file	Drop.h
 * @author	Francesco Racciatti <racciatti.francesco@gmail.com>
 *
 * @brief	The class Drop is used to drop packets.
 */


#ifndef DROP_H
#define DROP_H


#include "ActionBase.h"


class Drop : public ActionBase {
    
    private:
        double threshold;

	public:
        Drop(double threshold);
        virtual ~Drop();

		/**
		 * @brief   Drops the packet (depending on the threshold).
         * @param   packet is the packet to drop.
		 */
		void execute(cMessage** packet) const;
    
};

#endif
