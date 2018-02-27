
#ifndef ADRS_h
#define ADRS_h

#include <iostream>


class ADSR {
public:
	ADSR();
	~ADSR();
		void setADSRrate(float attackRate, float decayRate, float sustainLevel, float releaseRate);
		float process();
    float getOutput();
    int getState();
		void gate(int on);
    void reset();

    enum envState {
        env_idle = 0,
        env_attack,
        env_decay,
        env_sustain,
        env_release
    };

protected:
	int state;
	float output;
	float attackRate;
	float decayRate;
	float releaseRate;
	float sustainLevel;

};



#endif
