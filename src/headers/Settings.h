#pragma once

// Ship
#define MAX_ADVANCE  2500
#define MAX_STRAFE   30

#define MAX_ROLL  100
#define MAX_PITCH 10
#define MAX_YAW   10

#define ADVANCE_ACCEL 25
#define STRAFE_ACCEL  1

#define ADVANCE_DECELERATION 0.998
#define STRAFE_DECELERATION  0.9

#define ROLL_DECELERATION  0.9
#define PITCH_DECELERATION 0.9
#define YAW_DECELERATION   0.9

#define SHIP_LOOK_X 70
#define SHIP_LOOK_Y 40
#define SHIP_LOOK_ACCEL 2

#define SHIP_MATERIAL_PATH "assets/ship/"
#define SHIP_MODEL_PATH "assets/ship/ship.obj"
#define SHIP_TEXTURE_PATH "assets/ship/ship.png"

// Camera
#define CAMERA_BACK_DIST  10
#define CAMERA_BACK_DELAY 10
#define CAMREA_UP_DIST    4
#define CAMREA_FOV        80
#define CAMREA_FAR        15000

// Wall
#define WALL_LINES     20.0f
#define WALL_DIST      200.0f
#define WALL_WARN_DIST 0.3f

// Debug Axis
#define AXIS_ACTIVE   true
#define AXIS_DISTANCE 5000.0f

// MISC
#define VIEWPORT_DIM 880
#define GAME_TITLE   "Asteroids Assignment 2"
#define KEY_ESC      27