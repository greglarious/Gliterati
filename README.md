# Gliterati
Library for composing lighting patterns with addressable LEDs controlled by a radio network of Arduino microcontrollers.

## Summary
Utilities to compose and sequence a variety of visual lighting patterns on WS2811/WS2812 addressable LED strips controlled by Arduino-style microcontrollers. All patterns are implemented without use of delay calls via a run method that is called repeatedly to do whatever work is appropriate. This allows convenient integration with other Arduino libraries and I/O needs that can't tolerate long sleeps.

Support for a group of LORA/RFM69 networked lighting controllers managed by a remote node.  This independent controllers each provide portions of a global pixel address-space.  This allows composing coordinated lighting patterns over a large physical area without long distance wiring.  
- The radio protocol includes activating and stopping patterns from a loaded library
- The remote node can send an updated pattern library over the radio link

## Status:
The ideas in this repo are being actively refined as of 04/13/19. Currently in a high rate of change working to have it slightly stable by 05/01/19.

## ToDo: 
- finish and test pattern runner
- actually think about some generic addressing schemes
- refine / add patterns other than fade
- add pattern marshal/unmarshal over radio link
- add radio communication patterns
- describe example physical controller schematic and construction
- add demo videos
