# nECS

A simple ECS I use in my [AxtEngine](https://github.com/dubtcs/AxtEngine).

I wanted to try making my own. Once I heard about the idea of an ECS while working on AxtEngine, I really wanted to know how they worked. I think this was a great way to learn.

This is an improved version that is substantially faster than my [previous attempt](https://github.com/dubtcs/nECS_char) at an ecs.

***This is a learning exercise and should not be used in any serious applications.***

## Setup

Visual Studio 2022 is recommended, as that's the IDE I use to make it in. Premake is used to generate project files.

1. Download the repository with `git clone https://github.com/dubtcs/nECS.git`

2. Run `AAGenerateSolutions.bat` to create VS2022 solution and project files.
    - You can use this any time you make changes to the premake5.lua file or just want new solutions.

## How to use

All functionality is in namespace necs

A basic example can be found [here.](https://github.com/dubtcs/nECS/blob/550ca6502c9e15a9ac37cbb045000e2c6943b4bb/nECS/example.cpp)

