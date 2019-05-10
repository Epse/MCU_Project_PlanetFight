#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "dwenguinoBoard.h"
#include "dwenguinoLCD.h"
#include "Motordriver.h"

// PinD0

// Globale variabelen
unsigned int hoog_glb = 3000;
unsigned int laag_glb = 37000;
unsigned int duur_startsignaal = 1500; // (500 = 5 s)
char bool_h_l = 0; //h=1 l=0

void set_up_motordriver()
{
  // PinD0 op output => PWM signaal
  DDRD |= _BV(DD0);
/*
  // set de interrupt op PE4
  EICRB |= _BV(ISC41); // External interrupt control register Deze combinatie voor falling edge detectie.
  EICRB &= ~_BV(ISC40);

  EIMSK |= _BV(INT4); // External interrupt mask register - om interrupt te enabelen */

  SREG |= (1<<7); //globale interrupt enable

  //timer counter1
  // not disable TCNT3
  PRR0 &= ~_BV(PRTIM3);

  /*// enable OC1A: toggle op compare match van counterclock3 output
  TCCR3A |= _BV(COM3A0);
  TCCR3A &= ~_BV(COM3A1);*/

  // CTC mode
  TCCR3A &= ~(_BV(WGM31)|_BV(WGM30));
  TCCR3B |= _BV(WGM32);
  TCCR3B &= ~_BV(WGM33);

  // interupt mask register
  TIMSK3 |= _BV(OCIE3A);

  // reset waarde : 40000 = 20ms => 20000 = 10ms
  OCR3A = 40000;

  // prescaler (delen door 8)
  TCCR3B |= _BV(CS31);
  TCCR3B &= ~(_BV(CS32)|_BV(CS30));

  initBoard();
  initLCD();
  clearLCD();
  backlightOn();
}


//vb hoog = 3000 & laag = 37000 > 1.5ms hoog 18.5ms laag
void pwm_signaal_overrule(int hoog, int laag){
  if (bool_h_l == 1) {
    OCR3A = hoog;
    PORTD|= _BV(DDD0);
    bool_h_l = 0;

  }
  else{
    OCR3A = laag;
    PORTD &= ~_BV(DDD0);
    bool_h_l = 1;
  }
}

// neemt globale hoog_glb en laag_glb binnen
void pwm_signaal(){
  if (bool_h_l == 1) {
    OCR3A = hoog_glb;//hoog_glb;
    PORTD|= _BV(DDD0);
    bool_h_l = 0;
  }
  else{
    OCR3A = laag_glb;//laag_glb;
    PORTD &= ~_BV(DDD0);
    bool_h_l = 1;
  }
}

// smooth overgang  //0 = niets 100 = full rotation speed
void rotatie_snelheid(char percentage){
  // schaal 2000-4000
  unsigned int hoog_doel = (percentage * 20) + 2000;
  unsigned int laag_doel = 40000 - hoog_doel;


  //interpoleer
  if (hoog_glb < hoog_doel) {
    while(hoog_doel > hoog_glb){
      hoog_glb += 1;
      laag_glb -= 1;
      _delay_ms(50);
      // feedback op lcd
      printIntToLCD(hoog_glb,0,0);
      printIntToLCD(laag_glb,1,0);

    }
  } else {
    while(hoog_doel != hoog_glb){
      hoog_glb--;
      laag_glb++;
      _delay_ms(25);
    }
  }
}

ISR( TIMER3_COMPA_vect ){
  // startsignaal
  if (duur_startsignaal > 0) {

    // feedback op lcd
    printIntToLCD(duur_startsignaal,0,0);


    if (duur_startsignaal > 500) {
      //startsignaal: 1ms hoog
      pwm_signaal_overrule(2000, 38000);
    }
    else{
      pwm_signaal_overrule(2320, 37680);
    }

    // stel globale waarden in op startwaarden wanneer klaar
    if (duur_startsignaal == 1) {
      hoog_glb = 2320;
      laag_glb = 37680;
    }
    // tel af
    duur_startsignaal--;
  }
  // normale modus -> neem globale ingestelde waarden aan
  else {
    pwm_signaal();
  }
}
