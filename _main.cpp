/* IGEEK Autopilot @version 0.x
@link    https://github.com/kabuki-starship/igeek.autopilot.git
@file    /main.cpp

@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough; all right reserved (R). 
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, You can 
obtain one at https://mozilla.org/MPL/2.0/. */

#include "mazeagent.h"
using namespace _;

SI4 main(SI4 args_count, CH1** args) {
  Print("\nPreprocessing Maze...\n");
  SI4 width, height, page_columns = 25;
  CH1* tiles = PreprocessMaze(Maze1, width, height);

  Print("\nTesting Maze...\n");
  Maze maze(tiles, width, height, 1);

  Print("\nCreating Agent...\n");
  MazeAgent agent;
  agent.Print();

  Pause("\nWould you like to edit the default keyboard layout?");

  Print(
      "\nEntering maze.\nControls: A/D moves left/right and W/D moves "
      "forward/stop/backwards.\nPress E to toggle autopilot on/off.\n\n");
  do {  // Main loop just scans for keyboard input.
    for (SI4 i = page_columns; i > 0; --i) Print();
    // Get keyboard input for WASD, Quit, and Pause.
    if (GetAsyncKeyState(VK_)) SI4 key = ToUpper(CInKey());
    switch (key) {
      case 'A': {
        agent.TurnLeft();
        break;
      }
      case 'D': {
        agent.TurnRight();
        break;
      }
      case 'E': {
        agent.AutopilotToggle();
        break;
      }
      case 'P': {
        for (SI4 i = 0xfffffff; i > 0; --i)
          ;
        break;
      }
      case 'Q': {
        agent.ShutDown();
        break;
      }
      case 'S': {
        agent.Decelerate();
        break;
      }
      case 'W': {
        agent.Accellerate();
        break;
      }
    }
  } while (agent.Update());
  Print("\n\nShutdown...");
  return 0;
}
