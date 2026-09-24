#include <LiquidCrystal.h>
#define BUTTON_PIN 9

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte dino[] = { B00000, B00111, B00111, B00100, B00111, B00110, B11100, B00110 };
byte tree[] = { B00100, B01110, B10101, B01110, B10101, B01110, B10101, B00100 };

byte firstPartCup[]= { B00000, B01111, B10111, B01011, B00001, B00001, B00001, B00111 };
byte secondPartCup[] = { B00000, B11110, B11101, B11010, B10000, B10000, B10000, B11100 };

byte firstPartSkull[] = { B00111, B01111, B01001, B01001, B01111, B01110, B00100, B00111 };
byte secondPartSkull[] = { B11100, B11110, B10010, B10010, B11110, B01110, B00100, B11100 };

bool flyingAnimal=false;
bool obstacleJumped=false;

const int setValueCooldown=8;
const int resetValueDurationJump=6;

int durationJump=resetValueDurationJump;
int cooldownJump=0;

int points = 0;
int timedelay=100;

const byte dino_BYTE=byte(0);
  const byte tree_BYTE=byte(1);
  const byte firstPartCup_BYTE=byte(2);
  const byte secondPartCup_BYTE=byte(3);
  const byte firstPartSkull_BYTE=byte(4);
  const byte secondPartSkull_BYTE=byte(5);

void setup() {
  lcd.begin(16, 2);

  lcd.createChar(0,dino);
  lcd.createChar(1,tree);
  lcd.createChar(2,firstPartCup);
  lcd.createChar(3,secondPartCup);
  lcd.createChar(4,firstPartSkull);
  lcd.createChar(5,secondPartSkull);

  

  pinMode(BUTTON_PIN, INPUT_PULLUP); 

  lcd.setCursor(10,0);
  lcd.print("Pts:");

  lcd.setCursor(0,1);
  lcd.write(byte(0));

}

void loop() {
    lcd.setCursor(14,0);
    lcd.print(String(points));

    for(int column=15;column>=0;column--){
        if(points==10)showWinning();
        manageStatus();
        readJumpEvent();
        updateObstaclePosition(column);
        if(column==0){
            if(!flyingAnimal)showLosing();
            else{
                points++;
                lcd.setCursor(14,0);
                lcd.print(String(points));
            } 
        }
    }

}

//Function to update the screen to handle the obstacle frame (appear and disappear)
void updateObstaclePosition(int column){
    lcd.setCursor(column,1);
    lcd.write(tree_BYTE);
    delay(timedelay);
    lcd.setCursor(column,1);
    lcd.write(' ');
}

//Function to handle the jump action
void readJumpEvent(){

    if((cooldownJump==0)&&(digitalRead(BUTTON_PIN)==HIGH)){

        lcd.setCursor(0,0);
        lcd.write(dino_BYTE);
        
        lcd.setCursor(0,1);
        lcd.write(' ');
        flyingAnimal=true;
        cooldownJump=setValueCooldown;

    }

    if(durationJump==0){

        lcd.setCursor(0,0);
        lcd.write(' ');
        lcd.setCursor(0,1);
        lcd.write(dino_BYTE);
        
        flyingAnimal=false;
        durationJump=resetValueDurationJump;
    }

}

//update status when cooldown is running
void manageStatus(){
    if(cooldownJump>0){
        cooldownJump--;
        if(flyingAnimal)durationJump--;
    }
}

//manage the Lose Screen
void showLosing(){
        lcd.setCursor(0,1);
        lcd.write("x");
        lcd.setCursor(0,0);
        lcd.print("LOSE!");
        lcd.write(firstPartSkull_BYTE);
        lcd.write(secondPartSkull_BYTE);
        delay(2000);
        lcd.setCursor(0,0);
        lcd.print("       ");
        points=0;
        lcd.setCursor(0,1);
        lcd.write(dino_BYTE);
}

//manage the Win Screen
void showWinning(){
        lcd.setCursor(0,1);
        lcd.write(dino_BYTE);
        lcd.setCursor(0,0);
        lcd.print("WIN!");
        lcd.write(firstPartCup_BYTE);
        lcd.write(secondPartCup_BYTE);
        delay(2000);
        lcd.setCursor(0,0);
        lcd.print("      ");
        points=0;
        lcd.setCursor(0,1);
        lcd.write(dino_BYTE);
        lcd.setCursor(14,0);
        lcd.print("  ");
}
