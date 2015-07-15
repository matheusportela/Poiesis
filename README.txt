Poïesis game

Grow, complexify, survive.

Authors:
    * Developer: Matheus Portela (10/0017959)
    * Artist: Henrique Porath
    * Musician: Sofia de Faveri.
Contact: matheus.v.portela@gmail.com

===============================================================================
BUILD INSTRUCTIONS:
First of all, it's necessary to download and install the required libraries.
Poïesis uses the following libraries:
    * C++ STL
    * SDL

In Debian-based Linux distributions, these libraries can be installed by the following command:

$ sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev

Poïesis uses GNU Make for building the project. Simply run the following
command in your command prompt:

$ make

The Makefile used is authored by Michael Crawford and is publicly available at:
https://github.com/mbcrawfo/GenericMakefile/blob/master/cpp/Makefile

===============================================================================
RUN INSTRUCTIONS:

After building the project, you need to configure the game path. This can be done by updating the first line of "Configurations.cfg". The required path must point to the directory containing all game resources. Example:

$PATH = /home/portela/idj/resources

Finally, you can run the game with the following command in the project root directory:

$ ./Poiesis
