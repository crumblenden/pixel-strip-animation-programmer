#ifndef __mySketch__Osc__
#define __mySketch__Osc__

#include <math.h>
#include <ofMain.h>

class Oscillator
{
public:
    int period;
    float phase;
    float minAmp;
    float maxAmp;
    float width;
    float offset;
    float output;
    float position;
    int direction;
    int random;
    float tempOut;
    float amplitude;
    int mill;
    int time;
    int type;
    enum Type {SINE, COSINE, RAMPUP, RAMPDOWN, PULSE, TRIANGLE};
    
    void setup(int _type, float _period, float _minAmp, float _maxAmp);
    void update(int _CurrentTimeMicros);
    
    int setPeriod(float _period);
    float peek(int _CurrentTimeMicros, float _step, float _stepSpread);
    
    Oscillator();
};

#endif /* defined(__mySketch__Osc__) */
