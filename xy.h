/* IGEEK Autopilot @version 0.x
@link    https://github.com/kabuki-starship/igeek.autopilot.git
@file    /xy.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough; all right reserved (R). 
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, You can 
obtain one at https://mozilla.org/MPL/2.0/. */

#include <module_config.h>
#ifndef INCLUDED_KABUKI_CRABS_XY
#define INCLUDED_KABUKI_CRABS_XY 1

namespace _ {

enum {
  kXYRight = 0,   //< Direction 0: Right @ 0 degrees.
  kXYUpperRight,  //< Direction 1: Upper Right @ 45 degrees.
  kXYUp,          //< Direction 2: Up @ 90 degrees.
  kXYUpperLeft,   //< Direction 3: Upper Left @ 135 degrees.
  kXYLeft,        //< Direction 4: Left @ 180 degrees.
  kXYLowerLeft,   //< Direction 5: Lower Left @ 225 degrees.
  kXYDown,        //< Direction 6: Down @ 270 degrees.
  kXYLowerRight,  //< Direction 7: Lower Right @ 315 degrees.
  kXYCenter,      //< Direction 7: Center @ i degrees.
};

/* 4-bit aligned Acronym Strings for the directions.
@code
R, UR, U, LR, R, LR, D, LR
@endcode */
const CH1* XYDirectionAcronyms();

/* Decodes an XY quadrant packed in +/0/- format.
@param quad The quadrant.
@param value If value < 0 then only the lower angle node has been traversed. If
value == 0 then only the higher value node has been traversed. If value > 0 then
both nodes have been traversed. */
const CH1* XYDirectionString(SI4 direction);

const CH1* XYDirectionAcronyms();

void XYDirectionHistoryPrint(SI4 bits);

/* Gets the dx and dy values for the given direction.
@return DeltaX.
@param  a  The a-axis.
@param  dy DeltaY. */
SI4 XYVector(SI4 a, SI4& dy);

/* Gets the direction based on in the dx and dy.
@return A direction.
@param  dx Delta x.
@param  dy Delta y. */
SI4 XYDirection(SI4 dx, SI4 dy);

}  //< namespace _

#endif  //< #ifndef INCLUDED_KABUKI_CRABS_XY
