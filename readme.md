# Bot War 2 (ish)
## Description:
Based on the Wireworld cellular automata construct pathways to form brains for battle robots.

### Dependencies:
* SDL
* Meson - Build

## Setup:
`meson setup builddir`

## How to Build:
`cd builddir`
`meson compile && ./botwar`

## Controls
* Clicking the grid will change a cell's state.  
* Space stops and starts the simulation

## Cell colors
* Black - dead
* Red - head
* Blue - tail
* Green - track
* Brown - Motor 1
* Purple - Motor 2