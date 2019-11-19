#ifndef LINEAR_ACTUATOR_CONTROL_H
#define LINEAR_ACTUATOR_CONTROL_H

#include "mbed.h"

class LinearActuatorControl {
    private:
        PwmOut _linAct1;
        PwmOut _linAct2;
        PwmOut _linAct3;
        PwmOut _linAct4;
        DigitalIn _controlMode;
        DigitalIn _runMode;

        InterruptIn _actBtn1;
        InterruptIn _actBtn2;
        InterruptIn _actBtn3;
        InterruptIn _actBtn4;

        float _idlePositions[4];    //stores values of idle positions, deafult all 0, user defined with setIdlePositions
        float _actPositions[4];           //stores current positions of the actuators, updated by _setActuatorPos

        void _setActuatorPositions(int actuator, float position);     //updates current actuator positions
        void _setActuatorIdlePositions(int actuator, float position); //changes the idle positions
        void _refreshActuators();                                     //sets the pulsewidth of each pwm based on _actPositions
    public:
        //contructor, pins setup for LPC1768 by default so no parameters are needed
        LinearActuatorControl(PinName controlModeSwitch, PinName runModeSwitch, PinName act1pwm, PinName act2pwm, PinName act3pwm, PinName act4pwm, PinName act1btn, PinName act2btn, PinName act3btn, PinName act4btn);

        //user function to command actuators to move, takes any float value from 0 to 1 for the percent extension of the actuator (0.45 = 45% extended)
        void move(float pos1, float pos2, float pos3, float pos4);

        //similar to move, but sets the idle positions for the actuators
        void setIdlePositions(float pos1, float pos2, float pos3, float pos4);

        //used to check the state of the machine, will return true if in auto+run mode
        bool userSequence();
};

#endif