/* IGEEK Autopilot @version 0.x
@link    https://github.com/kabuki-starship/igeek.autopilot.git
@file    /mazeagent.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough; all right reserved (R). 
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, You can 
obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <_config.h>

#ifndef INCLUDED_KABUKI_AI_MAZEAGENT
#define INCLUDED_KABUKI_AI_MAZEAGENT 1

namespace _ {

void Print(const CH1* AString);
void Print(CH1 c = kLF);
void Print(CH1 c, CH1 d);
void Print(const CH1* AString, SI4 value);
void Print(SI4 value);
SI4 ToLower(SI4 c);
SI4 ToUpper(SI4 c);
SI4 CInKey();
BOL CInState(SI4 vk_code);
void Pause(const CH1* message = nullptr);
BOL Assert(BOL condition);
BOL AssertHandle(const CH1* file, SI4 line);

#define ASSERT(condition) \
  if (Assert(condition)) _::AssertHandle(__FILE__, __LINE__)

// Function pointer for getting static mazes and their height.
typedef const CH1** (*MazeLoader)(SI4& height);

// Example maze with function pointer.
const CH1** Maze1(SI4& height);

CH1* PreprocessMaze(MazeLoader get_maze, SI4& width, SI4& height);

/*
# Allowed Moves
Our ASCII robot car takes up 2 characters that cannot be diagonal. */
struct Maze {
  CH1* tiles;
  SI4 width, height, number;

  Maze(MazeLoader get_maze = Maze1, SI4 number = 1);
  Maze(CH1* tiles, SI4 width, SI4 height, SI4 number);
  BOL IsValid();
  ~Maze();
  CH1* Get(SI4 x, SI4 y);
  BOL Set(SI4 x, SI4 y, CH1 c);
  BOL Move(SI4 x, SI4 y, SI4 new_x, SI4 new_y);
  BOL CanMove(SI4 x, SI4 y);
  BOL IsEnd(SI4 x, SI4 y);
  BOL Find(SI4& x, SI4& y, CH1 c);
  BOL FindStart(SI4& x, SI4& y, SI4& dx, SI4& dy);
  BOL FindFinish(SI4& x, SI4& y);
  void Print(SI4 iteration = 0);
};

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

struct MazeAgent;

typedef SI4 (*PolicyPilot)(MazeAgent* agent);

SI4 PolicyPilotManual(MazeAgent* agent);

SI4 PolicyPilotDepthFirstRoundRobin(MazeAgent* agent);

/* Simple stack AI agent for solving simple mazes with 8 directions.
In order to better pack the data, the visited directions in the stack search
are that each quadrant contains two paths where quad_n is zero if neither path
has been traversed, it's -1 if the lower value angle path has been visited and
+1 if both nodes have been visited.
Speed will always be either -1, 0, or +1, and direction will always be
*/
struct MazeAgent {
  enum { kStackSize = 1024 };

  struct State {
    enum {
      kShutdown = 0,  //< State 0: Shutting Down.
      kBooting,       //< State 1: booting.
      kWaiting,       //< Not doing anything.
      kTurning,       //< Turning.
      kMoving,        //< Moving without stepping.
      kStuck,         //< Stuck on this path.
      kError,         //< Can't find a solution.
    };

    static const CH1* Label(SI4 state);

    SI4 state,    //< State variable.
        x,        //< X-axis position.
        y,        //< Y-axis position.
        a,        //< A-axis position.
        speed_y,  //< Speed in the Y-axis.
        speed_a,  //< Speed in the X-axis.
        history;  //< History of which of the 8
    State();
    State(const State& other);
    void Set(SI4 new_x, SI4 new_y, SI4 new_a, SI4 new_speed_a = 0,
             SI4 new_speed_y = 0, SI4 new_state = kBooting,
             SI4 new_history = 0);
    const CH1* Label();
    void Print();
    BOL Contains(SI4 other_x, SI4 other_y);
  };

  struct Point2D {
    SI4 x, y;
    Point2D();
    Point2D(State& state);
    Point2D(const Point2D& other);
  };

  PolicyPilot pilot, autopilot;
  State state, next_state, states[kStackSize];
  SI4 stack_height, iteration, shortest_height, init_dx, init_dy;
  Maze maze;
  Point2D shortest_path[kStackSize];

  MazeAgent(PolicyPilot pilot = PolicyPilotManual, MazeLoader get_maze = Maze1,
            SI4 maze_number = 1);
  BOL IsValid();
  BOL ChangeState(SI4 new_state);
  BOL Move(SI4 x, SI4 y, SI4 new_x, SI4 new_y);
  BOL IsLoop(SI4 new_x, SI4 new_y);
  SI4 Update();
  void Turn();
  void TurnLeft();
  void TurnRight();
  void AutopilotToggle();
  void Decelerate();
  void Accellerate();
  void ShutDown();
  void SetAutopilot(PolicyPilot new_pilot);
  BOL IsOnAutopilot();
  void Print();
};

SI4 PolicyPilotManual(MazeAgent* agent);
SI4 PolicyPilotDepthFirstRoundRobin(MazeAgent* agent);

}  //< namespace _

#endif  //< #ifndef INCLUDED_KABUKI_AI_MAZEAGENT
