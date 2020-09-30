#include <M5Stack.h>


#define TFT_GREY 0x5AEB
#define TFT_YELLOW 0XFFE0
#define TFT_BLACK 0x0000


uint32_t targetTime = 0;                    // for next 1 second timeout


static uint8_t conv2d(const char* p); // Forward declaration needed for IDE 1.6.x


//uint8_t hh = conv2d(__TIME__), mm = conv2d(__TIME__ + 3); 
//uint8_t ss = conv2d(__TIME__ + 6); // Get H, M, S from compile time

uint8_t hh = 0, mm = 0, ss = 0, ms = 0;


byte omm = 99, oss = 99 , oms = 99;
byte xcolon = 0, xsecs = 0;
unsigned int colour = 0;
int start = false;
int reset = false;


void setup() {
  //Serial.begin(115200);
  M5.begin();
  // M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(TFT_BLACK);


  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);


  targetTime = millis() + 10;
}


void loop() {
  if(M5.BtnA.wasPressed()) start=true;
  if(M5.BtnB.wasPressed()) start=false;
  if(M5.BtnC.wasPressed())
  {
    hh=0;
    mm=0;
    ss=0;
    ms=0;
    start=false;
  }
  
  if (targetTime < millis() && start) {
    // Set next update for 1 second later
    targetTime = millis() + 10;
    ms++;
    if(ms==100)
    {
      ms = 0;
      oss = ss;
      ss++;
      if(ss>59)
      {
        ss=0;
        omm = mm;
        mm++;
        if(mm>59)
        {
          mm=0;
          hh++;
          if(hh>23)
          {
            hh=0;
          }
        }
      }
    }

//    // Adjust the time values by adding 1 second
//    ss++;              // Advance second
//    if (ss == 60) {    // Check for roll-over
//      ss = 0;          // Reset seconds to zero
//      omm = mm;        // Save last minute time for display update
//      mm++;            // Advance minute
//      if (mm > 59) {   // Check for roll-over
//        mm = 0;
//        hh++;          // Advance hour
//        if (hh > 23) { // Check for 24hr roll-over (could roll-over on13)
//          hh = 0;      // 0 for 24 hour clock, set to 1 for 12 hour clock
//        }
//      }
//    }

        //Update digital time
    int xpos = 0;
    int ypos = 85; // Top left corner to clock text, about half way down
    int ysecs = ypos + 24;

    
    if (omm != mm) { // Redraw hours and minutes time every minute
      omm = mm;
      // Draw hours and minutes
      // Add hours leading zero for 24 hr clock
      if (hh < 10) xpos += M5.Lcd.drawChar('0', xpos, ypos, 8); 
      xpos += M5.Lcd.drawNumber(hh, xpos, ypos, 8);             // Draw hours
      xcolon = xpos; // Save colon coord for later to flash on/off later
      xpos += M5.Lcd.drawChar(':', xpos, ypos - 8, 8);
      // Add minutes leading zero
      if (mm < 10) xpos += M5.Lcd.drawChar('0', xpos, ypos, 8); 
      xpos += M5.Lcd.drawNumber(mm, xpos, ypos, 8);         // Draw minutes
      xsecs = xpos; // Save seconds 'x' position for later display updates
    }

//-----------------------------------------------------------------------------------------------

      if (oss != ss) { // Redraw seconds time every second
        oss = ss;
        xpos = xsecs;
  
  
        if (ss % 2) { // Flash the colons on/off
          // Set colour to grey to dim colon
          M5.Lcd.setTextColor(0x39C4, TFT_BLACK); 
          M5.Lcd.drawChar(':', xcolon, ypos - 8, 8);     // Hour:minute colon
          xpos += M5.Lcd.drawChar(':', xsecs, ysecs, 6); // Seconds colon
          // Set colour back to yellow
          M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);    
        }
        else {
          M5.Lcd.drawChar(':', xcolon, ypos - 8, 8);     // Hour:minute colon
          xpos += M5.Lcd.drawChar(':', xsecs, ysecs, 6); // Seconds colon
        }
        //Draw seconds
        // Add leading zero
        if (ss < 10) xpos += M5.Lcd.drawChar('0', xpos, ysecs, 6); 
        M5.Lcd.drawNumber(ss, xpos, ysecs, 6);       // Draw seconds
    }

//---------------------------------------------------------------------------
    if (oms != ms) { // Redraw seconds time every second
        oms = ms;
        xpos = xsecs;
  
  
        if (ss % 2) { // Flash the colons on/off
          // Set colour to grey to dim colon
          M5.Lcd.setTextColor(0x39C4, TFT_BLACK); 
          M5.Lcd.drawChar(':', xcolon, ypos - 8, 8);     // Hour:minute colon
          xpos += M5.Lcd.drawChar(':', xsecs, ysecs, 6); // Seconds colon
          // Set colour back to yellow
          M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);    
        }
        else {
          M5.Lcd.drawChar(':', xcolon, ypos - 8, 8);     // Hour:minute colon
          xpos += M5.Lcd.drawChar(':', xsecs, ysecs, 6); // Seconds colon
        }
        //Draw seconds
        // Add leading zero
        if (ms < 10) xpos += M5.Lcd.drawChar('0', xpos, ysecs, 6); 
        M5.Lcd.drawNumber(ms, xpos, ysecs, 6);       // Draw seconds
    }

    

    
    
  }

  
}



// function to extract number from compile string (don’t need to understand this for now)
static uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}
