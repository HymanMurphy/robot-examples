/* -----------------------------------------------------------------------------------------------------------------
                                        COPYRIGHT (c) 2009 - 2017
                                         HONEYWELL INC.,
                                        ALL RIGHTS RESERVED

            This software is a copyrighted work and/or information protected as a trade
            secret. Legal rights of Honeywell Inc. in this software are distinct from
            ownership of any medium in which the software is embodied. Copyright or trade
            secret notices included must be reproduced in any copies authorized by
            Honeywell Inc. The information in this software is subject to change without
            notice and should not be considered as a commitment by Honeywell Inc.
----------------------------------------------------------------------------------------------------------------- */

#ifndef UASDK_PRNG_H
#define UASDK_PRNG_H 1

#include "uasdk_includes.h"

namespace uasdk
{

/**
 NOTE: Only suitable for non-cryptographic purposes!
 Initialise the pseudo-random number generator with the given seed.
 @param [in] seed
 */
void PrngInitialise(uint32_t seed);

/**
 NOTE: Only suitable for non-cryptographic purposes.
 Returns a pseudo-random number.
 @return
 A pseudo-random number. NOT suitable for cryptographic applications. 
*/
uint32_t PrngRand();

}

#endif
