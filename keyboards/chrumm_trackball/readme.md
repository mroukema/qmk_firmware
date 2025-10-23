# Chrumm Trackball

![Chrumm Trackball](https://i.imgur.com/hyMUmOO.jpg)

A keyboard + trackball based on @sevmeyer's [Chrumm Keyboard](https://github.com/sevmeyer/chrumm-keyboard)

The Chrumm Trackball adds a mirrored layout and adjusted stagger values plus the addition of a trackball to the original design. This is a handwired design using an Elite-Pi RP2040 microcontroller as opposed to the custom pcb of the original. 

* Keyboard Maintainer: [mroukema](https://github.com/mroukema)
* Hardware Supported: Elite-Pi, RP2040 Community Layout Boards
* [Case and Build Info](https://github.com/mroukema/chrumm-keyboard-trackball)

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb chrumm_keyboard -km default

Flashing example for this keyboard:

    qmk flash -kb chrumm_keyboard -km default
