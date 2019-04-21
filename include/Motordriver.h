#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H
#include <stdint.h>

void set_up_motordriver();
void ledopstart();
void rotatie_snelheid(char percentage); //0 = niets 100 = full rotation speed


#endif
