//
// Created by david on 11/8/2025.
//

#ifndef SOUNDFUGUE_INPUTSTATE_HPP
#define SOUNDFUGUE_INPUTSTATE_HPP

struct InputState {
    bool shiftDown = false;
    bool clickDown = false;
    char firstPressed = '0'; // 's' = shift first, 'c' = click first, '0' = none
};

#endif //SOUNDFUGUE_INPUTSTATE_HPP