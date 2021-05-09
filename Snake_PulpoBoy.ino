/*                                                                                                                                                                                                                                                                           
 *@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                                                                                                             
 *@@                        =@                                                                                                                             
 *@@    -@@@@@@@@@@@@@@@    =@           --------     --       --   --          ---------       ------                                                     
 *@@    =@@@@@@@@@@@@@@@    =@           =======@@@   @@-     -@@   @@-         ========@@-   @@@=====@@-                                                  
 *@@    -@@@@@@@@@@@@@@@    =@                  -@@   @@-     -@@   @@-                 @@=  -@@      =@=                                                  
 *@@    -@@@@@@@@@@@@@@@    =@           @@@@@@@@=-   @@-      @@   @@-         =@@@@@@@@=   =@=      =@=                                                  
 *@@    =@@@@@@@@@@@@@@@    =@           @@           @@=     -@@   @@-         @@-          -@@      =@=                                                  
 *@@    -@@@@@@@@@@@@@@=    =@           @@           -=@@@@@@@@-   -@@@@@@@@   =@-           =@@@@@@@@=                                                   
 *@@-                     -=@@                                                                                                                             
 *@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                                                                                                             
 *@@@@@@@@@@@@@@@@@@@@@@@@@@@@           @@@@@@@@@@    =@@@@@@@@=    =@=     @@-                                                                           
 *@@@@===@@@@@@@@@@@@@@@@@@@@@           @@      @@-  =@=      =@=    =@@  -@@-                                                                            
 *@@==   ==@@@@@@@@@@==@@-  =@           @@  @@@@@@   =@=      =@=     -@@=@=                                                                              
 *@@--   --@@@@@@@@@=  -@@@@@@           @@      @@-  =@=      =@=       @@=                                                                               
 *@@@@=--@@@@@@@@@@@@@@@@@@@@@           @@@@@@=@@@    @@@@@@@@@@        @@-                                                                               
 *@@@@@@@@@@==@@@@@@@@@@@@@@@@             ------         ----                                                                                             
 *@@@@@@@@@==@@@==@@@@@@=====@                                                                                                                             
 *@@@@@@@@@@@@@@@@@@========@=                                                                                                                             
 *@@@@@@@@@@@@@@@@@@===@@@@@=-                                                                                                                             
 *------------------------                                                                                                                                 
 *                                                                                                                                                                                                        
 *              =-=- --=- --=----- =-=--------   ------- -- -- --- = --------- -- ------------=--                                                             
 *             -   ----- -  ---  ---  ---      - ------   -  --  ----------  - ---- --- -- ---                                                             

 * 
 * _       _______  __    __       ___   .___________. __    __  .______     ______    __  .__   __. .___________.  ______   ____    __    ____ 
 * |  |     |   ____||  |  |  |     /   \  |           ||  |  |  | |   _  \   /  __  \  |  | |  \ |  | |           | /  __  \  \   \  /  \  /   / 
 * |  |     |  |__   |  |__|  |    /  ^  \ `---|  |----`|  |  |  | |  |_)  | |  |  |  | |  | |   \|  | `---|  |----`|  |  |  |  \   \/    \/   /  
 * |  |     |   __|  |   __   |   /  /_\  \    |  |     |  |  |  | |   ___/  |  |  |  | |  | |  . `  |     |  |     |  |  |  |   \            /   
 * |  `----.|  |____ |  |  |  |  /  _____  \   |  |     |  `--'  | |  |      |  `--'  | |  | |  |\   |     |  |     |  `--'  |    \    /\    /    
 * |_______||_______||__|  |__| /__/     \__\  |__|      \______/  | _|       \______/  |__| |__| \__|     |__|      \______/      \__/  \__/     
 *                                                                                                                                                                                                                                                             
 * The code is freely licensed under GPL 3.
 * 
 * You will need the Adafruit GFX and SSD1306 for controlling the display
 * You will also need the Wire and Keypad libraries.
 * 
 * The code was mostly originally written by user asmgabber on Instructables.
 * Then it was ported by LEHAtupointow to PulpoBoy.
 * The original project had a buzzer and 4 buttons. I had to remove the buzzer things, so I could make the code smaller and compaptible with PulpoBoy.
 */


#include <Wire.h>
#include <Keypad.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define DIRUP 1
#define DIRDOWN 2
#define DIRLEFT 3
#define DIRRIGHT 4

int buttonpressed = 0;
const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'4', '3', '2', '1'},
  {'S', 'Q', 'U', 'P'},
  {'D', 'C', 'B', 'A'},
  {'>', '<', '-', '+'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

 // snake ints
byte snakePosX[30]; // array to make body of snake
byte snakePosY[30];

int snakeX=30;     // snake head position
int snakeY=30;
int snakeSize=1;   // snake size count limited to the size of the array

// world ints

uint8_t worldMinX=0;        // these set the limits of the play area
uint8_t worldMaxX=128;
uint8_t worldMinY=10;
uint8_t worldMaxY=63;

// collect scran(food) and position of scran
bool scranAte =0;
uint8_t scranPosX=0;
uint8_t scranPosY=0;

// scores variables
long playscore=0;   
long highscore=30;  // set high score to 3 collect as a starting point



// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// Declaration of the keypad


Keypad buttonPad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

const unsigned char logo[] PROGMEM = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x7F,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x7F,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x60,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x47,0xF9,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x47,0xF9,0x03,0xE4,0x48,0x1E,0x3E,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x47,0xF9,0x00,0x24,0x68,0x03,0x22,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x47,0xF9,0x00,0x24,0x68,0x01,0x22,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x47,0xF9,0x03,0xE4,0x68,0x3F,0x22,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x47,0xF9,0x02,0x04,0x68,0x30,0x22,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x47,0xF9,0x02,0x04,0x4C,0x30,0x22,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x47,0xF9,0x02,0x03,0xC7,0x90,0x3C,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x60,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x7F,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x7F,0xFF,0x03,0xE3,0xC4,0x40,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x7F,0xFF,0x02,0x24,0x64,0xC0,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x77,0xFD,0x02,0x24,0x22,0x80,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x63,0xFD,0x02,0xE4,0x23,0x80,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x63,0xE7,0x02,0x24,0x21,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x77,0xFF,0x03,0xE7,0xE1,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x7F,0xFF,0x03,0xE3,0xC1,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x7E,0xBF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x7F,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x7F,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x7F,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x7F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x01,0x94,0x28,0x04,0x8D,0x14,0xC0,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x88,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};


/*
 * FUNCTIONS
 */


void updateDirection(){
      char padPress = buttonPad.getKey();
      //Serial.println("updatingdirection");
        if(padPress=='+')
           {
              buttonpressed=DIRUP;
              //Serial.println("UP pressed");
         
              
              
          }
        if(padPress=='-')
          {
              buttonpressed=DIRDOWN;
         //     Serial.println("DOWN pressed");
         
              
              
          }

        if(padPress=='<')
          {
              buttonpressed=DIRLEFT;
          //    Serial.println("LEFT pressed");
          
              
              
          }
        if(padPress=='>')
          {
               buttonpressed=DIRRIGHT;
          //     Serial.println("RIGHT pressed");
          
                
                
          }
     }

//--------------------DRAW a random line input colour uint8_t-------------------
void drawALineForMe(uint8_t clr)
            {
                     uint8_t line1X,line1Y,line2X,line2Y=0;
                          // set random co-ordinates for a line then draw it     
                          //  variable         no less      no more
                              line1X = random(worldMinX+1,worldMaxX-1);
                              line1Y = random(worldMinY+1,worldMaxY-1);
                              line2X = random(worldMinX+1,worldMaxX-1);
                              line2Y = random(worldMinY+1,worldMaxY-1);
                           
                              display.drawLine(line1X,line1Y,line2X,line2Y,clr);
            }





//-------------------------- draw the display  routines-----------------------------------

void updateDisplay()  // draw scores and outlines  
    {
           // Serial.println("Update Display");

            display.fillRect(0,0, display.width()-1,8,BLACK);
            display.setTextSize(0);
            display.setTextColor(WHITE);
           
            // draw scores
            display.setCursor(2,1);
            display.print("Score:");
            display.print(String(playscore, DEC));
            display.setCursor(66,1);
            display.print("High:");
            display.print(String(highscore ,DEC));
            // draw play area
            //        pos  1x,1y, 2x,2y,colour
            display.drawLine(0,0,127,0,WHITE); // very top border
            display.drawLine(63,0,63,9,WHITE); // score seperator
            display.drawLine(0,9, 127,9,WHITE); // below text border
            display.drawLine(0,63,127,63,WHITE); // bottom border
            display.drawLine(0,0,0,63,WHITE); // left border
            display.drawLine(127,0,127,63,WHITE); //right border

        

    }

//-------------------------wait for presss loop -------------------------
        void waitForPress()
              {
                bool waiting=0;  // loop ends whjen this is true
                display.clearDisplay();
                while(waiting==0)
                     
                    {

                              char keypadKeyPressed = buttonPad.getKey();
                              drawALineForMe(WHITE); // draw a random white line
                              drawALineForMe(BLACK); // draw a random black line so that the screen not completely fill white
                              display.fillRect(19,20,90,32,BLACK);        // blank background for text
                              display.setTextColor(WHITE);
                              display.setCursor(35,25);
                              display.setTextSize(2); // bigger font
                              display.println("SNAEK");
                                              //    x  y   w  h r  col
                              display.drawRoundRect(33,22,62,20,4,WHITE);   // border Snake
                              display.drawRect(19,20,90,32,WHITE);          // border box  - 3
                              display.setCursor(25,42);
                              display.setTextSize(0);                       // font back to normal
                              display.println("hit any button");
                              display.fillRect(0,0,127,8,BLACK);
                              display.setCursor(10,0);
                              display.print("High Score :");                // display the high score
                              display.print(highscore);
                              display.display();
                              if(keypadKeyPressed){
                                break;
                              }
                      }
                        
                 }
// game over---------------------------------------

void gameOver()
       {
          uint8_t rectX1,rectY1,rectX2,rectY2;
         
          rectX1=38;
          rectY1=28;
          rectX2=58;
          rectY2=12;
          display.clearDisplay();
          display.setCursor(40,30);
          display.setTextSize(1);
          display.print("GAME ");
          display.print("OVER");
    
          if(playscore>=highscore)   //check to see if score higher than high score
              {  
                highscore=playscore;  //single if statment to update high score
              }

             
          for(int i=0;i<=16;i++)   // this is to draw rectanlges around game over
                {
                  display.drawRect(rectX1,rectY1,rectX2,rectY2,WHITE);
                  Serial.println("if loop");
                  display.display();
                    rectX1-=2;      // shift over by 2 pixels
                    rectY1-=2;
                    rectX2+=4;      // shift over 2 pixels from last point
                    rectY2+=4;
                }
           display.display();

          
                    //Screen Wipe after fame over
                    rectX1=0;   // set start position of line
                    rectY1=0;
                    rectX2=0;
                    rectY2=63;

                for (int i =0;i<=127;i++)
                      {
                           uint8_t cnt=0;
                           display.drawLine(rectX1,rectY1,rectX2,rectY2,BLACK); 
                            rectX1++;
                            rectX2++;
                            display.display();                  
                         
                      }
            display.clearDisplay();
          playscore=0;        // reset snake and player details
          snakeSize=1;
          snakeX=display.width()/2;
          snakeY=display.height()/2;

           waitForPress();        // wait for player to start game

        }

 //-------------------------------------  collision detecion -------------------------------
bool selfCollision()
        {
          for(byte i=4;i<snakeSize;i++)
              {   // see if snake X and Y match == snakePos X and Y return true 1 if so
                  if (snakeX==snakePosX[i]&&snakeY==snakePosY[i])  
                        {
                          return 1; 
                        }
              }
            return 0;
           }





//--------------------- out of area----------------------

    bool outOfArea()
        {
          return snakeX <= worldMinX||snakeX >=worldMaxX ||snakeY<=worldMinY|| snakeY>=worldMaxY;
        }

//------------------------ SCRAN ATE POINT UP ----------------
        bool scranFood()
            {
                  if(snakeX==scranPosX&&snakeY==scranPosY)
                      {
                          playscore=playscore+10;
                              updateDisplay();
                              placeScran();
                            return 1;
                      }
                    else
                      {
                          return 0;
                      }
            }


// --------------------- place the scran -------------------

void placeScran()
     {
        scranPosX=random(worldMinX+1,worldMaxX-1);
        scranPosY=random(worldMinY+1,worldMaxY-1);

     }



// ----------------------- We've got to update the game!-----------------------
void updateGame()     // this updates the game area display
    {
        display.clearDisplay();
        updateDirection();

          display.drawPixel(scranPosX,scranPosY, WHITE);
          scranAte = scranFood();   

            // check snake routines

              if (outOfArea()||selfCollision())
                   {
                      gameOver();
                   }

            // display snake
              for(int i=0;i<snakeSize;i++)
                  {
                    display.drawPixel(snakePosX[i],snakePosY[i],WHITE);
                  }
              
               // remove end pixel as movement occurs
              for(int i=snakeSize;i>0;i--)
                    {
                      snakePosX[i] = snakePosX[i-1];
                      snakePosY[i] = snakePosY[i-1];
                    }
              // add a extra pixel to the snake
              if(scranAte)
                  {
                    snakeSize+=1;
                    snakePosX[snakeSize-1]=snakeX;
                    snakePosY[snakeSize-1]=snakeY;
                  }


            switch(buttonpressed) // was snakeDirection
                  {
                    case DIRUP:
                        snakeY-=1;
                        break;
                    case DIRDOWN:
                        snakeY+=1;
                        break;
                    case DIRLEFT:
                        snakeX-=1;
                        break;
                    case DIRRIGHT:
                        snakeX+=1;
                        break;
                  }

        snakePosX[0] = snakeX;
        snakePosY[0] = snakeY;
        

          updateDisplay();
          display.display();
    }




//-=============================================================================================================
//=============================================================================================
//=================================================================================================================
//===========================================================================================================




void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println("Welcome to ");
  display.display();
  delay(2000);
  display.setTextSize(2);
  display.println("PulpoBoyOS");
  display.display();
  delay(1000);
  display.setTextSize(1);
  display.println();
  display.println("System is booting...");
  display.display();
  delay(5000);
  display.clearDisplay();
  display.display();
  display.drawBitmap(0, 0, logo, 120, 64, 1);
  display.display();
  delay(5000);
  // The "Actual Setup"
  delay(100); // just give stuff a chance to "boot"
  //    Serial.begin(9600);  // uncheck this if you want to see the serial outputs
  display.clearDisplay();   // start with a clean display
  display.setTextColor(WHITE);// set up text color rotation size etc  
  display.setRotation(0); 
  display.setTextWrap(false);
  display.dim(0);         // set the display brighness 
  // Serial.println("Setup Passed");
  waitForPress();    // display the snake start up screen
  placeScran();  // place first bit of food
  
} 


void loop()
{
  //display.clearDisplay(); //clear the display as we want to display anything else but not the dumb thingi.
  updateGame();
  
  
}
