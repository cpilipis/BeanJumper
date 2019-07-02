# BeanJumper
A free and open source space exploration game

## Introduction
This game is based on the idea established by a game in another repo of mine, "Nobody's Space". That game was a proof of concept based on me stitching together two games I already had, a basic asteroids game and a 2D platformer of mine.
That project had several shortcomings, however:
- Code from Asteroids and the 2D platformer that I would never use but didn't know how exactly to clean up or remove safely because this game was neither Asteroids nor a platformer in specific
- The two code bases clashed and clearly were not built around eachother, making the code harder to maintain
- I wanted to try a different library from Allegro, one called Raylib, because it seemed easier to distribute games with and is simplified
- The surfaces of planets didn't look like planets. They looked like platformer levels. Everything was a rectangle. Modifying the 2 platformer engine so that not everything was a rectangle was going to be a tremendous amout of work.
- The code just seemed messy and clashy

I wanted to expand my idea into a little more than just a proof of concept, so I decided to rewrite the entire thing from scratch. No old asteroids code at all, no old 2D platformer code at all. I'm starting right at square one for this, as well as using two new libraries for this in place of Allegro and/or my own code:

- Raylib, for game-critical things like graphics, input and output, sound, etc. Is very cross platform, and very easy to build with, considering it's just one header file
- Chipmunk physics, a C-oriented physics engine based on Box2D. Everything else out there prioritized C++ or what have you. I could adapt one of those for my purposes, but Chipmunk seemed easier. I have implemented it into the planetary physics for when you land the ship and want to explore a planet on foot. I have not yet implemented this physics engine into the space exploration gameplay, nor do I intend to.

I may throw Chipmunk Physics out entirely and write my own physics engine (it won't be very realistic if I take this route. That will probably end up being by design.), with my own separating-axis collision theorem. I don't know. I already have the code to reliably separate a polygon into convex bits, I'm just not using it because Chipmunk does it for me automatically. Maybe I'll prefer the realistic physics of Chipmunk, or maybe I'll decide it's not within the theme or gameplay loop of the game I want to build and implement my own wonky solution. Who knows.

## Current features as of 07-01-2019:
- Flying through space
- Locating planets via a red line drawn between your ship and nearby planets
- Landing on planets with the down key
- Exploring a single screen of a planet's terrain

## What needs to be done so far:
- Making planet terrain longer than a screen
- Giving different planets different terrain
- Loading the planets from a file within the game directory, rather than hard coded into the game
- Either procedurally generating universes in game, or writing an external generator that can be used to generate universes and the planets within
- Implementing more complex terrain, with potential for caves and the like via a complex polygon for terrain
- Creating some kind of god mode or editor to manually manipulate terrain, be it in game or via an external program
- Allowing the player to harvest resources from planets
- Implementing "Space Stations" outside of planets where players can buy and sell resources, or use their resources to fabricate items and other resources
- Space stations can just be a GUI at first, but I want them to be explorable on foot at some point.
- Allow ships to be customized as seen in Xpilot - The player is allowed to alter the polygonal shape of the ship from a file, to make the ship their own.
- The area of the ship is calculated to formulate a mass that affects momentum and flight
- Engines, thrusters, etc. must be added to the ship, further affecting not just mass, but also other factors, like fuel and energy consumption, max thrust, capabilities, purposes, etc.
- Multiplayer?

## Current Dependencies
- Raylib
- Chipmunk Physics
- LibMath
That's about it. All these things are cross platform and can run basically anywhere.
