# Gliterati
Library for composing lighting patterns with addressable LEDs controlled by a radio network of Arduino microcontrollers.

## Summary
Utilities to compose and sequence a variety of visual lighting patterns on WS2811/WS2812 addressable LED strips controlled by Arduino-style microcontrollers. All patterns are implemented without use of delay calls via a run method that is called repeatedly to do whatever work is appropriate. This allows convenient integration with other Arduino libraries and I/O needs that can't tolerate long sleeps.

Support for a group of LORA/RFM69 networked lighting controllers managed by a remote node.  This independent controllers each provide portions of a global pixel address-space.  This allows composing coordinated lighting patterns over a large physical area without long distance wiring.  
- The radio protocol includes activating and stopping patterns from a loaded library
- The remote node can send an updated pattern library over the radio link

## Status:
The ideas in this repo are being actively refined as of 04/13/19. Currently in a high rate of change working to have it slightly stable by 05/01/19.

## Concepts
#### PixelGroup
A set of pixels to be acted on.  Actions include setting to a color and errasing. PixelGroups are aware of the pattern iteration/completion cycle. Subclasses include:
- AllPixelGroup: every pixel on the strand
- SegmentPixelGroup: pixels between a start and end index
- CollectionPixelGroup: pixels identified by a list of abitrary choices
- NthPixelGroup: every X out of N pixels up to a max index
- MovingPixelGroup: a SegmentPixelGroup where the start and end indexes move each time a pattern finishes

#### G_Color
A color value with functions to fade to a different color and calculate iterations needed to fade to a particular color.  G_Colors are aware of the pattern iteration/completion cycle.

#### Rainbow
A G_Color that cycles through the rainbow on each pattern iteration or completion.

#### LightPattern
An operation performed on a pixel group.  Patterns have a start, a series of iterations, and an end.

#### FadePattern
A LightPattern that iterates from a beginning G_Color to an ending G_Color with an option to return bck to the beginning

#### PatternSequencer
A collection of patterns performed in seriesd from beginning to end and repeated.  Patterns may overlap.


## ToDo: 
- finish and test pattern runner
- actually think about some generic addressing schemes
- refine / add patterns other than fade
- add pattern marshal/unmarshal over radio link
- add radio communication patterns
- describe example physical controller schematic and construction
- add demo videos
