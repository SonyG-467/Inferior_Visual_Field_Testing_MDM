/*
 * Author :: Sony G
 * Date :: 6th Jan, 2017
 * Code for Sweep
 * Sweep starts in 7th meridian
 * Then moves to daisy meridian corresponding to it
 * After that moves to 19th meridian which is opposite to it until the fixation point
 * Repeats the same  
 */


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN_1            30
#define PIN_2            28
#define PIN_3            11
// How many NeoPixels are attached to the Arduino?
int STRIP_ONE = 13;
int STRIP_TWO = 11;
int DAISY = 72;
int FIXATION_1 = 9;
int FIXATION_2 = 10;
unsigned long cur_millis=0;
int i=0;
int j=STRIP_ONE - 1;
int jj;
unsigned long delayval=1000;
int ll;
int mer[] = {7,19};

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel strip_one = Adafruit_NeoPixel(STRIP_ONE, PIN_1, NEO_GRB + NEO_KHZ800);      //Seventh meridian
Adafruit_NeoPixel strip_two = Adafruit_NeoPixel(STRIP_TWO, PIN_2, NEO_GRB + NEO_KHZ800);      //Nineteenth meridian
Adafruit_NeoPixel daisy = Adafruit_NeoPixel(DAISY, PIN_3, NEO_GRB + NEO_KHZ800);              //Daisy meridian corresponding to Seventh meridian
void setup() {

  ll=daisyConverter(7); // To get the corresponding meridian in Daisy of the Given merdian
  Serial.println(ll);
  jj = 3 * ll;
  cur_millis=millis();
  strip_one.begin(); // This initializes the NeoPixel library.
  strip_two.begin();
  daisy.begin();
  Serial.begin(9600);
}


void loop() {
  //strip_one.clear();
  strip_two.setPixelColor(FIXATION_1,strip_two.Color(100,0,0));   // Fixing the Fixtion LEDs 
  strip_two.setPixelColor(FIXATION_2,strip_two.Color(100,0,0));
  strip_two.show(); // To display it all the time

  if((j) >= 0 && j < 888 )  // Within the range of Strip-7 LEDs 
  {
      if(millis() - cur_millis <= delayval)   // To wait for given time i.e. delayval(1000) = 1 sec
      {}
      else
      {
        Serial.println("outside");
        Serial.println(j);
          Serial.print("In one");
          Serial.println(j);
          strip_one.clear();
          strip_two.clear();
          //strip_two.show();
           for(int k=0;k < FIXATION_1;k++)
           {
             strip_two.setPixelColor(k,strip_two.Color(0,0,0)); //Lit off all the LEDs of Strip-19
           }
           strip_two.show();
           Serial.println(j);
          strip_one.setPixelColor(j,strip_one.Color(0,0,100));    //Sweep on Strip-7
           Serial.println(j);
          //strip_one.setPixelColor(STRIP_ONE-1,strip_one.Color(0,0,100));
          //strip_one.setPixelColor(STRIP_ONE-2,strip_one.Color(0,0,100));
          strip_one.show();
          cur_millis = millis();  // Assigns current time
          j = j - 1;    
        }
     }

     //Sweep in Daisy
      if(j < 0) // Out of Strip-7
      {
          if(millis() - cur_millis <= delayval)   // To wait for given time
          {
            
          }
          else
          {
           strip_one.clear();
           for(int j=0;j<STRIP_ONE;j++)
           {
             strip_one.setPixelColor(j,strip_one.Color(0,0,0)); // Clears Strip - 7 before starting the sweep in Daisy
           }
           strip_one.show();
            Serial.println("Daisy cleared");
           for(int k = 0; k < DAISY; k++)
           {
             daisy.setPixelColor(k,daisy.Color(0,0,0));   // Clears thee Daisy
           }
            daisy.show();
            
           if(jj < 3 * (ll + 1))
           {
             daisy.setPixelColor(jj,daisy.Color(0,100,0));  // Sweep in Daisy
           }
           daisy.show();
           Serial.println(jj);
           cur_millis = millis();
           jj = jj + 1;
          
           if(jj >= 3*(ll+1))
           {
              ll=daisyConverter(19);
              Serial.print("Next daisy meridian :: ");
              Serial.println(ll);
              
              jj = 3 * (ll+1);
              j= 888;   //Assign random to break the condition
           }
          }
      }

      if( j == 888 )
      {
        Serial.println("Daisy part 2");
        if(millis() - cur_millis <= delayval)   // To wait for given time
          {
            
          }
          else
          {
            daisy.clear();
            Serial.println("Daisy cleared");
           for(int k = 0; k < DAISY; k++)
           {
             daisy.setPixelColor(k,daisy.Color(0,0,0));   // Clears thee Daisy
           }
            daisy.show();
            
           if(jj > 3 * ll )
           {
             daisy.setPixelColor(jj,daisy.Color(0,100,0));  // Sweep in Daisy
           }
           daisy.show();
           Serial.println(jj);
           cur_millis = millis();
           jj = jj - 1;
          
           if(jj == 3 * ll)
           {
              j= 999;   //Assign random to break the condition
           }
          }
      }
      //Sweep in Strip-19
      if ( j == 999 )
      {
/*for (int jj = 3 * ll; ; jj++) {
                   daisy.setPixelColor(jj,daisy.Color(0,100,0));
               }
                daisy.show();*/
           if(millis() - cur_millis <= delayval)
          {}
          else
          {
           Serial.print("In two");
           Serial.println(i);
           for(int k = 0; k < DAISY; k++)
           {
             daisy.setPixelColor(k,daisy.Color(0,0,0)); //Clears the Daisy
           }
            daisy.show();
          // strip_one.setBrightness(br);
           strip_two.clear();
           strip_two.setPixelColor(i,strip_two.Color(0,0,100)); //Sweep in Strip-19
           //strip_two.setPixelColor(i+1,strip_two.Color(0,0,100));
           //strip_two.setPixelColor(i+2,strip_two.Color(0,0,100));
           i=i+1;
          // STRIP_ONE = -1;  
           strip_two.show();
           //delay(delayval);
           cur_millis = millis();
           if(i == (STRIP_TWO - 1))
           {
             Serial.println("in inner if"); 
             //Reassigning the values to the normal to repear the same action
             j=STRIP_ONE;
             i=0;
             ll=daisyConverter(7);
             jj = 3 * ll;
           }
         }
       }   
    


    /*ll=daisyConverter(11);
    Serial.println(ll);
     for (int jj = 3 * ll; jj < 3 * (ll + 1); jj++) {
       daisy.setPixelColor(jj,daisy.Color(0,100,0));
   }
   daisy.show();*/
}
int daisyConverter(int n) {
  // converts the given meridian into the daisy "meridian"
  if (n < 8) {
    return 7 - n;
  } else {
    return -n + 31;
  }
}

