#define STRIP_PIN 6     
#define NUMLEDS 600     

#define COLOR_DEBTH 3
//#define CRT_OFF
#include "IRLremote.h"
#define pinIR 2
#include <microLED.h>   // easy library
microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2818, ORDER_GRB, CLI_AVER> strip;

#define RIGHT 0xC4CC0E61
#define LEFT 0xC1B74961
#define UP 0x4B0CC61
#define DOWN 0xA9F6DE61
#define OK 0x9251CA61
#define ZERO 0x7A426661
#define ONE 0x772DA161
#define TWO 0x1C73B361
#define THREE 0x195EEE61
#define FOUR 0xB01FF161
#define FIVE 0xAD0B2C61
#define SIX 0x8F3D0561
#define BLUE 0x1CC03061
#define RED 0x1FD4F561
#define STROBOPLUS 0x25FE0861
#define STROBOMINUS 0x5BDB9361
#define STROBOFRICPLUS 0xEA5AAE61
#define STROBOFIRCMINUS 0x3DA31C61

CHashIR IRLremote;

long int currentTime;
long int timer;
long int showTimer;
static short int view;
int globalPos;
int pos;
float speedVal;
bool StayAnimation;
bool ShowBool;
bool StartStop;
bool delayChanged;
bool fadeChanged;
bool addStrobo;
int globalFade;
int globalDelay;
byte numberOfAnimation;
byte stroboBright;
byte stroboFric;


struct HSV
{
  float h;
  float s;
  float v;
};
struct myHSV
{
  float H;
  float S;
  float V;
};

struct myRGB
{
  byte R;
  byte G;
  byte B;
};

int beatSin(int amplitude, float argStep, float phase, float timeStep);
HSV rgb2hsv(byte red, byte green, byte blue);
myRGB HSV2RGB(float h, float s, float v);
myHSV RGB2HSV(byte r, byte g, byte b);
void fadeToBlack(int fadeStep);
void rootFadeToBlack(int fadeStep);
byte randSparkle();
void movingDots();
void movingDots2();
void movingDots3();
void fillStrip();
void moveDots();
void Strobo();
void Strobos();
void candle();

typedef void (*SimplePatternList[])();

SimplePatternList Animation = { moveDots, movingDots, movingDots2, fillStrip, movingDots3, Strobo, candle };

void setup() {
  addStrobo = false;
  stroboBright = 255;
  stroboFric = 10;
  StartStop = true;
  //Serial.begin(9600);
  globalFade = 1;
  globalDelay = 20;
  StayAnimation = false;
  timer = millis();
  globalPos = 0;
  pos = 0;
  currentTime = millis();
  numberOfAnimation = 0;
  speedVal = 1;
  strip.setBrightness(255);
  strip.fill(mBlue);
  //Serial.begin(9600);
  IRLremote.begin(2);
}

void loop() {
  
  if(StartStop)
    Animation[numberOfAnimation]();
    
  strip.setBrightness(stroboBright);
  
  if(numberOfAnimation == 0 && millis() - timer > 120000 && !StayAnimation)
  {
    numberOfAnimation = 1;
    
    timer = millis();
  }
  else if(numberOfAnimation == 1 && millis() - timer > 120000 && !StayAnimation)
  {
    numberOfAnimation = 2;
    timer = millis();
  }
  else if(numberOfAnimation == 2 && millis() - timer > 120000 && !StayAnimation)
  {
    numberOfAnimation = 3;
    timer = millis();
  }
  else if(numberOfAnimation == 3 && millis() - timer > 120000 && !StayAnimation)
  {
    numberOfAnimation = 4;
    timer = millis();
  }
  else if(numberOfAnimation == 4 && millis() - timer > 120000 && !StayAnimation)
  {
    numberOfAnimation = 5;
    timer = millis();
  }
  else if(numberOfAnimation == 5 && millis() - timer > 120000 && !StayAnimation)
  {
    numberOfAnimation = 6;
    timer = millis();
  }
  else if(numberOfAnimation == 6 && millis() - timer > 120000 && !StayAnimation)
  {
    numberOfAnimation = 0;
    timer = millis();
  }

  if (IRLremote.available()) {
    auto data = IRLremote.read();
    switch(data.command)
    {
      case OK:
      {
        StayAnimation = !StayAnimation;
        if(StayAnimation)
        {
          strip.fill(mRGB(10,10,0));
        }    
        else
        {
          strip.fill(mRGB(10,0,10));
        }
        break;
      }
      case RIGHT:
      {
        globalFade = constrain(globalFade + 10, 1, 255);
        ShowBool = true;
        showTimer = millis();
        fadeChanged = true;
        break;
      }
      case LEFT:
      {
        globalFade = constrain(globalFade - 10, 1, 255);
        ShowBool = true;
        showTimer = millis();
        fadeChanged = true;
        break;
      }
      case UP:
      {
        globalDelay = constrain(globalDelay + 5, 1, 1000);
        ShowBool = true;
        showTimer = millis();
        delayChanged = true;
        break;
      }
      case DOWN:
      {
        globalDelay = constrain(globalDelay - 5, 1, 1000);
        ShowBool = true;
        showTimer = millis();
        delayChanged = true;
        break;
      }
      case STROBOPLUS:
      {
        stroboBright = constrain(stroboBright + 5, 1, 255);
        break;
      }
      case STROBOMINUS:
      {
        stroboBright = constrain(stroboBright - 5, 1, 255);
        break;
      }
      case STROBOFRICPLUS:
      {
        stroboFric = constrain(stroboFric + 5, 0, 100);
        break;
      }
      case STROBOFIRCMINUS:
      {
        stroboFric = constrain(stroboFric - 5, 0, 100);
        break;
      }
      case ZERO:
      {
        numberOfAnimation = 0;
        break;
      }
      case ONE:
      {
        numberOfAnimation = 1;
        break;
      }
      case TWO:
      {
        numberOfAnimation = 2;
        break;
      }
      case THREE:
      {
        numberOfAnimation = 3;
        break;
      }
      case FOUR:
      {
        numberOfAnimation = 4;
        break;
      }
      case FIVE:
      {
        numberOfAnimation = 5;
        break;
      }
      case SIX:
      {
        numberOfAnimation = 6;
        break;
      }
      case BLUE:
      {
        StartStop = !StartStop;
      }
      case RED:
      {
        addStrobo = !addStrobo;
      }
    }
  }

  if(addStrobo)
  {
   Strobos(); 
  }
  if(ShowBool)
  {
    Show();
  }
  strip.show();   // вывод  
}

void Show()
{
  if(millis() - showTimer > 100)
  {
    ShowBool = false;
    delayChanged = false;
    fadeChanged = false;
  }
  if(delayChanged)
  {
    strip.fill(0, globalDelay/2, mRGB(0,10,30));
  }
  if(fadeChanged)
  {
    strip.fill(0, (int)globalFade/2, mRGB(20,10,20));
  }
  rootFadeToBlack(globalFade);
}
byte randSparkle()
{
  byte add = 0;
  
  byte rnd = (byte)random(0,100);
  if(rnd >= 85)
  {
    add = random(50,100);
  }
  else 
  {
    add = 0;
  }
  return add;
}
void moveDots()
{ 
  byte add = 0;
  short int pos;
  
  pos = beatSin((NUMLEDS/2)-1, 0.005f, 0, globalDelay);

  add = randSparkle();
  strip.leds[pos] = mRGB(50 + add,100 + add,20 + add);
  add = randSparkle();
  strip.leds[NUMLEDS-1-pos] = mRGB(100 + add,50 + add,20 + add);
  
  pos = beatSin((NUMLEDS/2)-1, 0.005f, 1.2, globalDelay);

  add = randSparkle();
  strip.leds[pos] = mRGB(100 + add,20 + add,100 + add);
  add = randSparkle();
  strip.leds[NUMLEDS-1-pos] = mRGB(20 + add,50 + add,100 + add);
  
  //rootFadeToBlack(globalFade);
    //fadeToBlack(globalFade);
  fadeToBlackByHSV(1);
  currentTime = millis();
  
  delay(globalDelay);
}

/*void movingDots()
{  
  int pos;
  
  pos = globalPos;
  
  //strip.clear();
  fadeToBlack(60);
  while(pos >= 0)
  {
    strip.leds[pos] = mRGB(60, 10, 100);
    strip.leds[NUMLEDS - 1 - pos] = mRGB(100, 10, 60);
    pos = pos - 12;
  }
  
  globalPos = constrain(globalPos + (1 * view), 0, NUMLEDS-1);
  
  if(globalPos == NUMLEDS-1)
  {
    view = -1;
  }
  else if(globalPos == 0)
  {
    view = 1;
  }
  delay(30);
}
*/

void movingDots2()
{
  strip.clear();
  for(int i = 0; i < NUMLEDS - view; i++)
  {
    if(i%10 == 0)
      strip.leds[i+view] = mRGB(20, 20, 100);
  }

  view = constrain(view - 1, 0, 10);
  
  if (view == 0)
    view = 10;

  delay(globalDelay);
}
void movingDots3()
{
  strip.clear();
  for(int i = 0; i < NUMLEDS - view; i++)
  {
    if(i%10 == 0)
      strip.leds[i+view] = mRGB(100, 20, 20);
  }

  view = constrain(view - 1, 0, 10);
  
  if (view == 0)
    view = 10;

  delay(globalDelay);
}
void Strobo()
{
  for(int i = 0; i < NUMLEDS; i++)
  {
    strip.leds[i] = mRGB(9,3,6);
  }
  pos = random(0,100);
  if(pos > stroboFric)
  {
    pos = random(0, NUMLEDS-1);

    strip.leds[pos] = mRGB(200,200,200);
  } 
  rootFadeToBlack(globalFade);
  delay(globalDelay);
}
void Strobos()
{
  pos = random(0,100);
  if(pos > stroboFric)
  {
    pos = random(0, NUMLEDS-1);

    strip.leds[pos] = mRGB(200,200,200);
  } 
  //rootFadeToBlack(globalFade);
  //delay(globalDelay);
}

void fillStrip()
{
  speedVal = speedVal + 0.01f;
  pos = constrain(pos + (int)speedVal, 0, NUMLEDS-1);

  if(pos == NUMLEDS-1)
  {
    pos = 0;
    speedVal = 1;
  }
  strip.leds[NUMLEDS-1-pos] = mRGB(50,20,100);

  if(random(0,100) > 65)
  {
    strip.leds[NUMLEDS-1-pos] = mRGB(200,25,155);
  }
  rootFadeToBlack(globalFade);
  delay(globalDelay);
}

void candle()
{
  byte rnd = 0;
  for(int i = 2; i < NUMLEDS-2; i++)
  {
    if(i%16 == 0)
    {
      
      if(random(0, 100) > stroboFric)
      {
        strip.leds[i + random(-1,1)] = mRGB(80,24,2);
      }
      else
      {
        strip.leds[i] = mRGB(20,15,0);
      }

    }
  }
  
  rootFadeToBlack(globalFade);
  delay(globalDelay);
}

void movingDots()
{  
  //globalPos;
  
  //strip.clear();
  rootFadeToBlack(globalFade);
  for(int i = 0; i < NUMLEDS - view; i++)
  {
    if(i%10 == 0)
    {
      if(i < pos)
      {
        strip.leds[i+view] = mWheel(globalPos, 90);
      }
      else
      {
        strip.leds[i+view] = mWheel(globalPos + 200, 90);
      }
    }
      
  }
  
  view = constrain(view - 1, 0, 10);
  
  if (view == 0)
    view = 10;

  pos = constrain(pos - 1, 0, NUMLEDS-1);

  if(pos == 0)
  {
    pos = NUMLEDS-1;
    globalPos = constrain(globalPos+200, 0, 1530);
  }

  if (globalPos == 1530)
    globalPos = 0;
  delay(globalDelay);
}

int beatSin(int amplitude, float argStep, float phase, float timeStep)
{
  static float arg = 0;

  if(millis() - currentTime > 10)
  {
    arg = constrain(arg + argStep, 0, 2 * PI);
    currentTime = millis();
  }

  if(arg == 2 * PI)
    arg = 0;
  return (int)(amplitude*(sin(arg + phase)+1));
}

void rootFadeToBlack(int fadeStep)
{
  for(int i = 0; i < NUMLEDS; i++)
  {
    strip.fade(i, fadeStep);
  }
}
void fadeToBlackByHSV(float fadeStep)
{
  byte r,g,b;
  myHSV hsvLed;
  myRGB rgbLed;
  for(int i = 0; i < NUMLEDS; i++)
  { 
    hsvLed = RGB2HSV(strip.leds[i].r,strip.leds[i].g,strip.leds[i].b);
    
    if(hsvLed.V > 0)
    {
      hsvLed.V = hsvLed.V - fadeStep;
    }
  
    strip.leds[i] = mHSV((byte)hsvLed.H, (byte)hsvLed.S, (byte)hsvLed.V);
  }
}
void fadeToBlackSaveColor(int fadeStep)
{
  byte minimum = 1;
  byte minimumStep = 1;
  byte r,g,b;
  
  for(int i = 0; i < NUMLEDS; i++)
  {
    r = getR(strip.leds[i]);
    g = getG(strip.leds[i]);
    b = getB(strip.leds[i]);

    minimum = minThree(r,g,b);
    
    if(minimum == 0) 
      minimumStep = 1;

    minimumStep = r/minimum;
    r = constrain(r-(minimumStep * fadeStep), 0, 255);
    
    minimumStep = g/minimum;
    g = constrain(g-(minimumStep * fadeStep), 0, 255);
    
    minimumStep = b/minimum;
    b = constrain(b-(minimumStep * fadeStep), 0, 255);

    strip.leds[i] = mRGB(r,g,b);
  }
}

void fadeToBlack(int fadeStep)
{
  byte r,g,b;
  for(int i = 0; i < NUMLEDS; i++)
  {
    r = getR(strip.leds[i]);
    g = getG(strip.leds[i]);
    b = getB(strip.leds[i]);

    r = constrain(r-fadeStep, 0, 255);
    g = constrain(g-fadeStep, 0, 255);
    b = constrain(b-fadeStep, 0, 255);

    strip.leds[i] = mRGB(r,g,b);
  }
}

myHSV RGB2HSV(byte R, byte G, byte B)
{
  float H,S,V;
  float r = R / 255.0f;
  float g = G / 255.0f;
  float b = B / 255.0f;
  float CMax = max(r,max(g,b));
  float CMin = min(r,min(g,b));
  float delta = CMax - CMin;

  if(delta == 0)
  {
    H = 0;
  }
  else if (CMax == r)
  {
    H = 60 * (( (g - b) / delta)); 
  }
  else if (CMax == g)
  {
    H = 60 * (( (b - r) / delta) + 2);
  }
  else if (CMax == b)
  {
    H = 60 * (( (r - g) / delta) + 4);
  }

  if(CMax == 0)
  {
    S = 0;
  }
  else 
  {
    S = delta / CMax;
  }

  V = CMax;

  return { (H/360)*255, S*255, V*255};
}

myRGB HSV2RGB(float h, float s, float v)
{
  float R, G, B;
  float C, X, m;

  C = v * s;
  X = C * (1 - abs( (int)(h/60)%2 - 1 ));
  m = v - C;

  if(0 <= h && h < 60)
  {
    R = C;
    G = X;
    B = 0;
  }
  else if(60 <= h && h < 120)
  {
    R = X;
    G = C;
    B = 0;
  }
  else if(120 <= h && h < 180)
  {
    R = 0;
    G = C;
    B = X;
  }
  else if(180 <= h && h < 240)
  {
    R = 0;
    G = X;
    B = C;   
  }
  else if(240 <= h && h < 300)
  {
    R = X;
    G = 0;
    B = C; 
  }
  else if(300 <= h && h < 360)
  {
    R = C;
    G = 0;
    B = X;
  }
  return { (byte)((R + m) * 255), (byte)((G + m) * 255), (byte)((B + m) * 255)};
}

HSV rgb2hsv(byte red, byte green, byte blue)
{
  float maximum, minimum;
  float r,g,b;
  float chroma;
  
  HSV hsvLed = {};
  
  r = (float)(red) / 255.0f;
  g = (float)(green) / 255.0f;
  b = (float)(blue) / 255.0f;

  
  minimum = min(r,min(g,b));
  maximum = max(r,max(g,b));

  chroma = maximum - minimum;

  hsvLed.v = maximum;

  if(chroma == 0)
  {
    hsvLed.h = 0;
    hsvLed.s = 0;
  }
  else
  {
    if(maximum == red)
    {
      hsvLed.h = 60 * (0 + (g-b)/chroma);
    }
    else if (maximum == green)
    {
      hsvLed.h = 60 * (2 + (b-r)/chroma);
    }
    else if (maximum == blue)
    {
      hsvLed.h = 60 * (4 + (r-g)/chroma);
    }

    if(hsvLed.v > 0)
    {
      hsvLed.s = (float)chroma / hsvLed.v;
    }
    else
    {
      hsvLed.s = 0;
    }
  }

  if(hsvLed.h < 0)
  {
    hsvLed.h = 360 + hsvLed.h;
  }
  
  hsvLed.h = ((hsvLed.h/360.0f)*255);
  hsvLed.s = (hsvLed.s*255);
  hsvLed.v = (hsvLed.v*255);
  
  return hsvLed;
}

byte minThree(byte a, byte b, byte c)
{
  byte minimum = min(a,b);
  minimum = min(minimum, c);
  return minimum;
}
