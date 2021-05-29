#pragma once

// Ship
#define MAX_ADVANCE  3500
#define MAX_STRAFE   300

#define MAX_ROLL  100
#define MAX_PITCH 10
#define MAX_YAW   10

#define ADVANCE_ACCEL 45
#define STRAFE_ACCEL  1

#define ADVANCE_DECELERATION 0.998
#define STRAFE_DECELERATION  0.9

#define ROLL_DECELERATION  0.9
#define PITCH_DECELERATION 0.9
#define YAW_DECELERATION   0.9

#define SHIP_LOOK_X 20
#define SHIP_LOOK_Y 20
#define SHIP_LOOK_ACCEL 2

#define SHIP_MATERIAL_PATH  "assets/ship/"
#define SHIP_MODEL_PATH     "assets/ship/ship.obj"
#define SHIP_TEXTURE_PATH   "assets/ship/ship.png"

// Cannon & Bullets
#define BULLET_VELOCITY 2500
#define BULLET_ROTATION 180

#define BULLET_SIZE     10
#define RATE_OF_FIRE    0.10
#define BULLET_DAMAGE   20

#define FRAMES_PER_SECOND   24.0f
#define BULLET_TEXTURE_ROWS 6.0f
#define BULLET_TEXTURE_COLS 6.0f
#define BULLET_START_FRAME  0.0f
#define BULLET_END_FRAME    23.0f

#define BULLET_TEXTURE_PATH "assets/bullets/fireball_ani.png"

// Asteroid
#define ASTEROID_DIVISIONS    15
#define ASTEROID_HEALTH_SCALE 100
#define ASTEROID_MIN_RADIUS   500
#define ASTEROID_MAX_RADIUS   2000

#define ASTEROID_DEBUG         true
#define ASTEROID_HEALTH_BAR_ON true

#define ASTEROID_TEXT_1 "assets/asteroids/asteroid1.jpg"
#define ASTEROID_TEXT_2 "assets/asteroids/asteroid2.jpg"
#define ASTEROID_TEXT_3 "assets/asteroids/asteroid3.jpg"
#define ASTEROID_TEXT_4 "assets/asteroids/asteroid4.jpg"

// Asteroid Generation
#define ASTEROID_ACTIVE       false
#define ASTEROID_SPAWN_RATE   5
#define ASTEROID_SPAWN_NEXT   0
#define ASTEROID_SPAWN_AMOUNT 1 
#define ASTEROID_SPAWN_MAX    20
#define ASTEROID_SPAWN_DIST   20000
#define ASTEROID_MIN_VELOCITY 3000
#define ASTEROID_MAX_VELOCITY 5000
#define ASTEROID_MIN_ROTATION 50
#define ASTEROID_MAX_ROTATION 100

// Camera
#define CAMERA_BACK_DIST  7
#define CAMREA_UP_DIST    4
#define CAMERA_BACK_DELAY 7
#define CAMREA_FOV        90
#define CAMREA_FAR        25000

// Wall
#define WALL_LINES      5.0f
#define WALL_DIST       1500.0f
#define WALL_TOTAL_DIST WALL_DIST * WALL_LINES
#define WALL_WARN_DIST  0.4f

// Debug Axis
#define AXIS_ACTIVE   false
#define AXIS_DISTANCE 5000.0f

// ENVIRONMENT
#define ENABLE_SKYBOX true
#define ENABLE_FOG    true

// MISC
#define GAME_TITLE   "Asteroids Assignment 2"
#define FULL_SCREEN  true
#define VIEWPORT_DIM 800
#define KEY_ESC      27