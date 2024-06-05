# CircuitPlaygroundBounceGame

This is my final project for Engineering 103 at Oregon State University designed for the Arduino Circuit Playground Express.

## Brief Rules Overview

A light bounces back and forth across the neopiexels on the board.
The goal of the game is hit the button when the light is in the middle (2) positions of the board. 
Each time the button is successfully timed, the score goes up and the game gets faster. 
This continues until you fail, in which the board flashs, beeps, and resets to the start.


## Inputs

Uses buttons on pin 4 and 19
(planned mic sensor)

## Outputs

## To be added

Planned addition of a freeze mechanic, which slows the light and turns it blue for a small amount of time when you blow into the microphone. 
The time this powerup is active scales with current speed.

If I get super fancy -> can only use freeze once per level

## Updated 6/4/24

first working demo
-need to fix debounce for double success/faliures
-flash entire board not just two lights
-use both buttons?
-consider maybe slide switch adds a second game rather than using freeze mechanic?
-if you reach highest possible speed maybe reward with animation and victory sound -> reset
