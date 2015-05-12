Poïesis game

Grow, complexify, survive.

Authors: Matheus Portela, Henrique Porath and Sofia de Faveri.
Contact: matheus.v.portela@gmail.com

===============================================================================
BUILD INSTRUCTIONS:

Poïesis uses GNU Make for building the project. Simply run the following
command in your command prompt:

$ make

The Makefile used is authored by Michael Crawford and is publicly available at:
https://github.com/mbcrawfo/GenericMakefile/blob/master/cpp/Makefile

===============================================================================
RUN INSTRUCTIONS:

After building the project, you can run the game with the following command:

$ ./Poiesis
===============================================================================
ARCHITECTURE:

Poïesis employs a layered architecture, where each layer can only use the
interface provided by lower layers (preferebly, the immediately lower layer)
and offer an interface to higher layers.

The implemented layers are described below, from lower to higher level.

0) Operating system: This is the basic layer, which manages the entire computer
system. Poïesis is intended to be run in personal computers and laptops using
any Unix-like system.

1) Third-party SDKs: Developed by other teams and companies, provide
functionality to the system. These SDKs must always be wrapped by an adapter to
avoid high coupling of the project and reduce changes costs.
    * STL: Standard Template Library. Default library with C++, provides useful
generic containers.
    * SDL: Simple DirectMedia Layer. Provides functionality for low-level
graphics, audio, device I/O, fonts and timers.

2) Adapters: This layer is intended to provide a platform independence to the
system, both from operating system and from third-party libraries. Hence, it
provides a single point to change when libraries publish newer versions that
are incompatible to the previous one or even when running in other OS.
    * Collections: Data structures that are used in the entire system, such as
lists and maps.
    * Timer: Class to provide clock-like features.
    * Graphic adapter: 
    * Audio adapter: 
    * Font adapter: 
    * File system: 