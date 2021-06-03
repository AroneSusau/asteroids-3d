# Interactive 3d Graphics & Animation - Assignment 2

| Author | Student # | 
|---------------------|----------|
| Arone Susau         | s3728977 |

# IMPORTANT
This project was built, run and testing on ```macOS Big Sur 11.2.3```.

The project hasn't been tested on a windows or linux machine, so please if possible, run the project on your Macbook Pro.

Thank you in advance.

# Table Of Contents
- [How to Build & Run](#How-to-Build)
- [Controls](#Controls)
- [Feature Summary](#Feature-Summary)
- [Asset Citation](#Asset-Citation)

# How to Build

Please enter the following command into your terminal or shell application to build the program.

```
$ make
```
# Controls
| Action                 | Key                       |
|------------------------|---------------------------|
| Shoot                  | `Space Bar`               |
| Advance / Move Forward | `W`                       |
| Slow Down              | `S`                       |
| Strafe Left            | `A`                       |
| Strafe Right           | `D`                       |
| Roll Left              | `Q`                       |
| Roll Right             | `E`                       |
| Yaw Left / Right       | `Mouse Move Horizontally` |
| Pitch Up / Down        | `Mouse Move Vertically`   |

# Feature Summary

Please review the `Settings.h` file [here](src/headers/Settings.h) which contains most, if not all of the games configuration.

The following section will provide a brief explaination of each of the implemented features and instructions of how to demo or test the individual features.

## Arena: HARD
The arena grid mesh is draw in position at each point along the 6 axis, in its full size. The player warning distance is calculated by the `WALL_WARN_DIST` setting and is `0.4` or `40%` of the wall distance by default. Ship to wall or ship to warning collision distance is calculated by checking if the ship has fallen below the negative or above the positive distance value.

## Spaceship Model: HARD
The ship texturing and material usage was taken from the tutorials and labs. The implementation of the wing flap orientation to demonstrate hierarchical relationships was done by scaling a `gluSolidCube` into a flat plank and nesting the object in a `glPushMatrix` to isolate its rotation and translation amounts.

## Asteroid Model: HARD
The code relating to the generation of a sphere was repurposed from the following [article](http://www.songho.ca/opengl/gl_sphere.html#:~:text=In%20order%20to%20draw%20the,triangle%20strip%20cannot%20be%20used). During the asteroid genreation, each `z` and `y` axis were multiplied by a random amount between `0.55` to `1.0`, to simulate irregularity.

## Asteroid Movement: HARD
Asteroids spawn positions are selected by randomly setting its `x`, `y` and `z` position values to a random amount within the arena and then randomly selecting only one of those axis and pushing that one axis outside of the arena. Asteroid to wall collision is calculated as the asteroid position plus its size to the distance of the wall, if it is overlapping then flip the axis velocity. Asteroid to asteroid collision is similar to the wall collision except between two asteroids, swapping their velocities and applying the new velocity once to avoid any stuck collisions.

## Lighting: HARD
The code relating to the generation of lighting was taken from both the tutorial code and the [Red Book](https://www.glprogramming.com/red/chapter05.html). The animated point light souce was converted into a spot light attached to the front of the ship to simulated head lights. Please note that the world lighting has a slight red aura and the ship headlight is a solid white colour.

## Bullets & Shooting: HARD
The bullets are generated at a position of some small multiple of the ships forward vector. The bullets velocity is calculated as the ships current velocity plus some other amount in the ships forward vector. The bullet billboarding is done by taking the camera position minus the bullet position normalized to get a forward vector. The forward vector is then applied to a `glMultMatrix`, along with the ships up vector and the cross product of both to generate the right vector to manually rotate the bullet texture towards the ship. The bullet animation effect is done by calculating the sprite uv coordinates and storing them in the `Animator` class. The animator class only needs a `SpriteSheet` object which defines the number of rows, columns and the start and end frame for the animation. Animations are then rendered at 60 frames per second.

## Explosions: HARD
The explosion particle effects are essentially the same as the animated textured bullet except the velocities of the particles are generated outwards from their point of origin, rather than away from the ships position. The particles also define whether they are deleted after reaching their end of frames or after a certain period of time.

## Camera & Ship Movement: HARD
In my implementation the camera follows the ship position, adjusting its look at value behind the ship to simulate a visual delay as well as its position to slide back and forth during acceleration/deceleration. For the animated ship roll/pitch/yaw, a new `glPushMatrix` is applied after the ship is rotation in the direction of its forward vector. This is done so that individual `glRotatef` calls can be made on each the `x`, `y` and `z` axis to simulate rotation animation.

# Asset Citation

| Asset | Citation |
|-------|----------|
| `Asteroid Textures` | Provided By Course |
| `Fireball Textures` | Provided By Course |
| `Explosion Sprite Sheets` | [link](https://opengameart.org/art-search?keys=explosion) |
| `Ship Explosion` | [link](https://opengameart.org/content/2d-explosion-animations-frame-by-frame) |
| `Ship Model & Texture` | Provided By Course |
| `Skybox Texture` | [link](http://wwwtyro.github.io/space-3d/#animationSpeed=1&fov=80&nebulae=true&pointStars=true&resolution=1024&seed=1a553z8s3oi&stars=true&sun=true) |