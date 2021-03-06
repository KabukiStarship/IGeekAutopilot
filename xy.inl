/* IGEEK Autopilot @version 0.x
@link    https://github.com/kabuki-starship/igeek.autopilot.git
@file    /xy.inl
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough; all right reserved (R). 
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, You can 
obtain one at https://mozilla.org/MPL/2.0/. */

#include <module_config.h"

#include "cxy.h"

#include <conio.h"
#include <windows.h"
#include <iostream>
using namespace std;

namespace _ {

const CH1* XYDirectionAcronyms() {
  // Direction acronyms aligned to a 4-bit boundary.
  static const CH1 kDirectionAcronyms[] = {
      'R', 0,   0, 0,  //
      'U', 'R', 0, 0,  //
      'U', 0,   0, 0,  //
      'U', 'L', 0, 0,  //
      'L', 0,   0, 0,  //
      'L', 'L', 0, 0,  //
      'D', 0,   0, 0,  //
      'L', 'R', 0, 0,  //
      'C', 0,   0, 0,  //
  };
  return kDirectionAcronyms;
}

const CH1* XYDirectionString(SI4 direction) {
  if (direction < 0 || direction >= kXYCenter) direction = kXYCenter;
  return &XYDirectionAcronyms()[direction << 2];  //< << 2 to * 4.
}

void XYDirectionHistoryPrint(SI4 bits) {
  const CH1* dir_Strings = XYDirectionAcronyms();
  for (SI4 i = 0; i < 8; ++i) {
    if ((bits >> i) & 1) {
      Print(&XYDirectionAcronyms()[i]);
      if (i != 7) Print(kLF, ' ');
    }
  }
}

}  //< namespace _
