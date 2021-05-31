#pragma once

// SHIP
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
#define SHIP_LOOK_Z 50
#define SHIP_LOOK_ACCEL 1

#define SHIP_MATERIAL_PATH  "assets/ship/"
#define SHIP_MODEL_PATH     "assets/ship/ship.obj"
#define SHIP_TEXTURE_PATH   "assets/ship/ship.png"

// CANNON & BULLETS
#define BULLET_VELOCITY 4500
#define BULLET_ROTATION 180

#define BULLET_SIZE     6
#define RATE_OF_FIRE    0.08
#define BULLET_DAMAGE   50

#define FRAMES_PER_SECOND   60.0f
#define BULLET_TEXTURE_ROWS 6.0f
#define BULLET_TEXTURE_COLS 6.0f
#define BULLET_START_FRAME  0.0f
#define BULLET_END_FRAME    23.0f

#define BULLET_TEXTURE_PATH "assets/bullets/fireball_ani.png"

// ASTEROID
#define ASTEROID_DIVISIONS    15
#define ASTEROID_HEALTH_SCALE 3
#define ASTEROID_MIN_RADIUS   500
#define ASTEROID_MAX_RADIUS   2000

#define ASTEROID_DEBUG         false
#define ASTEROID_HEALTH_BAR_ON true

#define ASTEROID_TEXT_1 "assets/asteroids/asteroid1.jpg"
#define ASTEROID_TEXT_2 "assets/asteroids/asteroid2.jpg"
#define ASTEROID_TEXT_3 "assets/asteroids/asteroid3.jpg"
#define ASTEROID_TEXT_4 "assets/asteroids/asteroid4.jpg"

// ASTEROID GENERATION
#define ASTEROID_ACTIVE       true
#define ASTEROID_SPAWN_RATE   10
#define ASTEROID_SPAWN_NEXT   0
#define ASTEROID_SPAWN_AMOUNT 1 
#define ASTEROID_SPAWN_MAX    20
#define ASTEROID_SPAWN_DIST   15000
#define ASTEROID_MIN_VELOCITY 5000
#define ASTEROID_MAX_VELOCITY 8000
#define ASTEROID_MIN_ROTATION 50
#define ASTEROID_MAX_ROTATION 100

// CAMERA
#define CAMERA_BACK_DIST  7
#define CAMREA_UP_DIST    4
#define CAMERA_BACK_DELAY 7
#define CAMREA_FOV        90
#define CAMREA_FAR        25000

// WALL
#define WALL_LINES      5.0f
#define WALL_DIST       1500.0f
#define WALL_TOTAL_DIST WALL_DIST * WALL_LINES
#define WALL_WARN_DIST  0.4f

// DEBUG AXIS
#define AXIS_ACTIVE   false
#define AXIS_DISTANCE 5000.0f

// ENVIRONMENT
#define ENABLE_SKYBOX  true
#define ENABLE_FOG     true
#define LIGHTING_DEBUG false

// PARTICLES
#define PARTICLE_EXPLOSION_1 "assets/particles/explosion1.png"
#define PARTICLE_EXPLOSION_1_SHEET new SpriteSheet(6.0f, 10.0f, 1.0f, 59.0f)

#define PARTICLE_EXPLOSION_2 "assets/particles/explosion2.png"
#define PARTICLE_EXPLOSION_2_SHEET new SpriteSheet(8.0f, 8.0f, 0.0f, 59.0f)

#define PARTICLE_EXPLOSION_3 "assets/particles/explosion3.png"
#define PARTICLE_EXPLOSION_3_SHEET new SpriteSheet(8.0f, 8.0f, 0.0f, 59.0f)

#define PARTICLE_EXPLOSION_4 "assets/particles/explosion4.png"
#define PARTICLE_EXPLOSION_4_SHEET new SpriteSheet(7.0f, 5.0f, 0.0f, 31.0f)

#define PARTICLE_SHIP_EXPLOSION "assets/particles/ship_explosion.png"
#define PARTICLE_SHIP_EXPLOSION_SHEET new SpriteSheet(8.0f, 8.0f, 0.0f, 63.0f)

#define PARTICLE_FLARE_COUNT        500
#define PARTICLE_FLARE_SIZE_FACTOR  12
#define PARTICLE_FLARE_MIN_VELOCITY 0
#define PARTICLE_FLARE_MAX_VELOCITY 4000

// MISC
#define GAME_TITLE   "Asteroids Assignment 2"
#define FULL_SCREEN  true
#define VIEWPORT_DIM 880
#define KEY_ESC      27
