#include "linearActuatorControl.h"

LinearActuatorControl::LinearActuatorControl(PinName controlModeSwitch = p14, PinName runModeSwitch = p15, PinName act1pwm = p21, PinName act2pwm = p22, PinName act3pwm = p23, PinName act4pwm = p24, PinName act1btn = p17, PinName act2btn = p18, PinName act3btn = p19, PinName act4btn = p20) : _controlMode(controlModeSwitch), _runMode(runModeSwitch), _linAct1(act1pwm), _linAct2(act2pwm), _linAct3(act3pwm), _linAct4(act4pwm), _actBtn1(act1btn), _actBtn2(act2btn), _actBtn3(act3btn), _actBtn4(act4btn) {
    for (int i = 0; i < 4; i++) {
        _idlePositions[i] = 0;
        _actPositions[i] = 0;
    }

    _linAct1.period_ms(20);
    _linAct2.period_ms(20);
    _linAct3.period_ms(20);
    _linAct4.period_ms(20);

}

void LinearActuatorControl::_refreshActuators() {
    if (_runMode) {
        _linAct1.pulsewidth_us(1000*(1+_actPositions[0]));
        _linAct2.pulsewidth_us(1000*(1+_actPositions[1]));
        _linAct3.pulsewidth_us(1000*(1+_actPositions[2]));
        _linAct4.pulsewidth_us(1000*(1+_actPositions[3]));
    } else {
        _linAct1.pulsewidth_us(1000*(1+_idlePositions[0]));
        _linAct2.pulsewidth_us(1000*(1+_idlePositions[1]));
        _linAct3.pulsewidth_us(1000*(1+_idlePositions[2]));
        _linAct4.pulsewidth_us(1000*(1+_idlePositions[3]));
    }
}

void LinearActuatorControl::_setActuatorPositions(int actuator, float position) {
    _actPositions[actuator] = position;
}

void LinearActuatorControl::_setActuatorIdlePositions(int actuator, float position) {
    _idlePositions[actuator] = position;
}

void LinearActuatorControl::setIdlePositions(float pos1, float pos2, float pos3, float pos4) {
    _idlePositions[0] = pos1;
    _idlePositions[1] = pos2;
    _idlePositions[2] = pos3;
    _idlePositions[3] = pos4;
}

bool LinearActuatorControl::userSequence() {
    if (_controlMode && _runMode) {
        return true;
    } 
    return false;
}