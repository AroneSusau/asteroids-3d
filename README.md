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

## Arena
It is recommended that you set `ASTEROID_ACTIVE` to `false` in the settings file while testing the arena.
### Easy
Fly directly into the wall and observe your death.
### Medium
Fly close to the wall and observe the colour change, move away and see the color change back... magic.
### Hard
Look around the world and observe the beauty.

## Spaceship Model
### Easy
The ship and its 'Wings' have different material properties.
### Medium
The ship is fully textured map upon observation.
### Hard
Move the mouse both horizontally and vertically to observe the wing flaps change directions depending on mouse orientation.

## Asteroid Model
Please set `ASTEROID_ACTIVE` to `false` and `ASTEROID_DEBUG` to `true` in the settings file while testing the asteroid model.
### Easy
Rotate around the asteroid and view the different lighting angles.
### Medium
Please view the `Asteroid` class [here](src/main/Asteroid.cpp) and review the custom sphere generation. Code relating to the generation of a sphere was repurposed from the following [article](http://www.songho.ca/opengl/gl_sphere.html#:~:text=In%20order%20to%20draw%20the,triangle%20strip%20cannot%20be%20used).

### Hard
Rerun the application while viewing the debug asteroid to see it change perturbation and irregularity.

## Asteroid Movement
Please set `ASTEROID_ACTIVE` to `false` and `ASTEROID_DEBUG` to `true` in the settings file while testing the asteroid medium and hard movement features.
### Easy
Let the game run with its default settings and move to different positions in the arena. The asteroids will spawn randomly and set its initial velocity values to fly directly to the ship position. Keep in mind that an asteroid might fly up behind you and boop you if you're stationary for too long.
### Medium
For asteroid spin, turn off asteroid generation and enable the debug asteroid and observe. For asteroid wall collision allow the game to run as per usual with default settings and observe the asteroids.
### Hard
For asteroid to asteroid collision allow the game to run as per usual with default settings and observe the asteroids.

## Lighting
### Easy
Set `LIGHTING_DEBUG` to `true` then `false` to observe the general lighting differences.
### Medium
The world positional lighting is a faint red-ish aura to resemble the skybox theme. It is positioned such that it appears to be coming from the sun in the skybox panel.
### Hard
The animated light souce is the ships headlight, which is white in colour. Turn on the debug asteroid and move around it to see it in action better.

## Bullets & Shooting
### Easy
Fly around the scene and press spacebar to see the bullets following along. Enable the debug asteroid and fire at it until it is destroyed.
### Medium
Set `BULLET_VELOCITY` to zero and tap spacebar once to view a single bullet animation play out. Revert the bullet velocity setting and shoot the bullet asteroid to observe the health bar decline until destruction.
### Hard
Set `BULLET_VELOCITY` to zero and tap spacebar once to view a single bullet animation play out.

## Explosions
### Medium
Enable the debug asteroid and shoot until destruction to observe the destruction animation.
### Hard
Enable the debug asteroid and shoot until destruction to observe the destruction animation. Also fly the ship into any wall to observe the death explosion animation.

## Camera & Ship Movement
### Easy
As you fly move the mouse about the screen to observe the changes in orientation without.
### Medium
As the ship increases in velocity, the camera will slide backwards and return forwards as the ship slows down.
### Hard
As you fly, move the mouse about the screen to observe the ship models rotation in space. As the ships velocity is increased, the camera will shift its `look_at` values backwards to simulated a delay.

# Asset Citation

| Asset | Citation |
|-------|----------|
| `Asteroid Textures` | Provided By Course |
| `Fireball Textures` | Provided By Course |
| `Explosion Sprite Sheets` | [link](https://opengameart.org/art-search?keys=explosion) |
| `Ship Explosion` | [link](https://opengameart.org/content/2d-explosion-animations-frame-by-frame) |
| `Ship Model & Texture` | Provided By Course |
| `Skybox Texture` | [link](http://wwwtyro.github.io/space-3d/#animationSpeed=1&fov=80&nebulae=true&pointStars=true&resolution=1024&seed=1a553z8s3oi&stars=true&sun=true) |