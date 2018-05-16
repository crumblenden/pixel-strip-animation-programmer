#include "Osc.h"

Oscillator::Oscillator(){};

void Oscillator::setup(int _type, float _period, float _minAmp, float _maxAmp) {
    type = _type;
    period = setPeriod(_period);
    random = 0;
    minAmp = _minAmp;
    maxAmp = _maxAmp;
    position = 0;
    width = 0.5;
    offset = 0.0;
}

int Oscillator::setPeriod(float _period) {
    return floor(_period * 1000000.0);
}

float Oscillator::peek(int _CurrentTimeMicros, float _step, float _stepSpread) {
    
    amplitude = maxAmp - minAmp;
    
    switch(direction) {
        case 0:
            phase = 360.0 - (float( ((int)_step%(int)_stepSpread) / _stepSpread ) * 360.0);
            phase = std::fmod((float((360.0 - (float( ((int)_step%(int)_stepSpread) / _stepSpread ) * 360.0)) + (offset * 360.0))), 360.0);
            
            break;
        case 1:
            phase = std::fmod(((float(((int)_step%(int)_stepSpread)/_stepSpread) * 360.0) + (offset * 360.0)), 360.0);
            break;
        default:;
            break;
    }
    
    
    mill = _CurrentTimeMicros;
    mill += (phase/360 * period);
    time = mill % period;
    
    position = (float(time) / float(period));

    switch(type) { //sin, ramp up, ramp down, square, tri
            
        case SINE:

            tempOut = sin(position * TWO_PI);
            tempOut = (tempOut + 1) / 2;
            tempOut = tempOut * amplitude;
            tempOut = tempOut + minAmp;
            
            //return tempOut;
            break;
            
        case COSINE:
            
            tempOut = cos(position * TWO_PI);
            tempOut = (tempOut + 1) / 2;
            tempOut = tempOut * amplitude;
            tempOut = tempOut + minAmp;
            
            //return tempOut;
            break;
            
        case RAMPUP:
            if(position > 1 - width) {
                
                tempOut = (((position - (1-width)) / width) * amplitude) + minAmp;
                //tempOut = (position * amplitude) + minAmp;
            }
            else {
                tempOut = minAmp;
            }
            //return tempOut;
            break;
            
        case RAMPDOWN:
            if(position > (1-width)) {
            //tempOut = (amplitude - (position * amplitude)) + minAmp;
                tempOut = (amplitude-(((position - (1-width)) / width) * amplitude)) + minAmp;
            }
            else {
                tempOut = minAmp;
            }
            //return tempOut;
            break;
            
        case PULSE:
            if(position < width) {
                tempOut = maxAmp;
            }
            if(position >= width) {
                tempOut = minAmp;
            }
            //return tempOut;
            break;
            
        case TRIANGLE:
            if(position < (width/2)) {
                tempOut = ((position / (width/2)) * amplitude) + minAmp;
            }
            if(position >= (width/2)) {
                tempOut = ((1 - ((position - (width/2)) / (width/2))) * amplitude) + minAmp;
            }
            if(position >= width) {
                tempOut = minAmp;
            }
            //return tempOut;
            break;
            
        default:
            break;
    }
    return tempOut;
}


void Oscillator::update(int _CurrentTimeMicros)
{
    amplitude = maxAmp - minAmp;
    mill = _CurrentTimeMicros;
    time = mill % period;
    time += (phase/360 * period);
    
    
    position = float(time) / float(period);
    
    switch(type) { //sin, ramp up, ramp down, square
            
        case 1:
            tempOut = sin(position * TWO_PI);
            tempOut = (tempOut + 1) / 2;
            tempOut = tempOut * amplitude;
            tempOut = tempOut + minAmp;
            output = tempOut;
            break;
            
        case 2:
            tempOut = (position * amplitude) - amplitude/2;
            output = tempOut;
            break;
            
        case 3:
            tempOut = (amplitude - (position * amplitude)) - amplitude/2;
            output = tempOut;
            break;
            
        case 4:
            if(position < width) {
                output = maxAmp;
            }
            if(position >= width) {
                output = minAmp;
            }
            break;
            
        default:
            break;
    }
}


