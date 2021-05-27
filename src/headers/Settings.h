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

#define BULLET_VELOCITY 2000
#define BULLET_SIZE 3
#define RATE_OF_FIRE 0.1

#define SHIP_MATERIAL_PATH  "assets/ship/"
#define SHIP_MODEL_PATH     "assets/ship/ship.obj"
#define SHIP_TEXTURE_PATH   "assets/ship/ship.png"
#define BULLET_TEXTURE_PATH "assets/bullets/fireball.png"

// Asteroid
#define ASTEROID_DIVISIONS 50

// Camera
#define CAMERA_BACK_DIST  10
#define CAMREA_UP_DIST    6
#define CAMERA_BACK_DELAY 10
#define CAMREA_FOV        90
#define CAMREA_FAR        25000

// Wall
#define WALL_LINES      5.0f
#define WALL_DIST       1500.0f
#define WALL_TOTAL_DIST WALL_DIST * WALL_LINES
#define WALL_WARN_DIST  0.3f

// Debug Axis
#define AXIS_ACTIVE   false
#define AXIS_DISTANCE 5000.0f

// MISC
#define VIEWPORT_DIM 880
#define GAME_TITLE   "Asteroids Assignment 2"
#define KEY_ESC      27