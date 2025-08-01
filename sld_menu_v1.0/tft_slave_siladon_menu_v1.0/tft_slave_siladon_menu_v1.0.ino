#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h> // Core graphics library

#include <Wire.h>
 
// Define Slave I2C Address
#define SLAVE_ADDR 5
 
// Define Slave answer size
#define ANSWERSIZE 3
 
// Define string with response to Master
 
#define LCD_RESET 1 // Can alternately just connect to Arduino's reset pin
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
 
// Assign human-readable names to some common 16-bit color values:
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define DARKGREY 0x7BEF  // You can adjust this for contrast

// resolution is around 300 * 280
 
MCUFRIEND_kbv tft;

String read_but = "";

bool menuShown = false;
bool menu_condition_show = false;
bool menu_side = false;

int current_condition = 1;
int max_condition = 2; 

int current_side = 1;
int max_side = 2;

int currentOption = 1; // start with Option 1
const int maxOptions = 3;

String condition_name[2] = {"01 Dry", "02 Moist"};
String side_name[2] = {"01 Front","02 Back"};
String option_name[3] = {"01 Small", "02 Medium", "03 Large"};


void showCondition() {
  tft.fillScreen(BLACK);
  tft.setTextSize(3);

  int buttonWidth = 200;
  int buttonHeight = 40;
  int spacing = 10;

  int x = (240 - buttonWidth) / 2;
  int y = 30;

  for (int i = 1; i <= max_condition; i++) {
    int buttonY = y + (i - 1) * (buttonHeight + spacing);

    if (current_condition == i) {
      tft.fillRect(x, buttonY, buttonWidth, buttonHeight, DARKGREY);
      tft.setTextColor(BLACK);
    } else {
      tft.fillRect(x, buttonY, buttonWidth, buttonHeight, BLACK);
      tft.setTextColor(WHITE);
    }

    tft.setCursor(x + 30, buttonY + 10);
    tft.print(condition_name[i-1]);
  }
}

void showSide() {
  tft.fillScreen(BLACK);
  tft.setTextSize(3);

  int buttonWidth = 200;
  int buttonHeight = 40;
  int spacing = 10;

  int x = (240 - buttonWidth) / 2;
  int y = 30;

  for (int i = 1; i <= max_side; i++) {
    int buttonY = y + (i - 1) * (buttonHeight + spacing);

    // Fix here: use current_side
    if (current_side == i) {
      tft.fillRect(x, buttonY, buttonWidth, buttonHeight, DARKGREY);
      tft.setTextColor(BLACK);
    } else {
      tft.fillRect(x, buttonY, buttonWidth, buttonHeight, BLACK);
      tft.setTextColor(WHITE);
    }

    tft.setCursor(x + 30, buttonY + 10);
    tft.print(side_name[i-1]);
  }
}

void showMenu() {
  tft.fillScreen(BLACK);
  tft.setTextSize(3);

  int buttonWidth = 200;
  int buttonHeight = 40;
  int spacing = 10;

  int x = (240 - buttonWidth) / 2;
  int y = 30;

  for (int i = 1; i <= maxOptions; i++) {
    int buttonY = y + (i - 1) * (buttonHeight + spacing);

    if (currentOption == i) {
      tft.fillRect(x, buttonY, buttonWidth, buttonHeight, DARKGREY);
      tft.setTextColor(BLACK);
    } else {
      tft.fillRect(x, buttonY, buttonWidth, buttonHeight, BLACK);
      tft.setTextColor(WHITE);
    }

    tft.setCursor(x + 30, buttonY + 10);
    tft.print("Option " + String(i));
  }
}

// Call this function to change the selection and update the UI
void highlightOption(int to) {
  if (to != currentOption) {
    currentOption = to;
    showMenu(); // Redraw menu with updated highlight
  }
}


void receiveEvent() {
  // Read while data received
  byte x;
  while (0 < Wire.available()) {
    x = Wire.read();
  }
  read_but = String(x);
  // Print to Serial Monitor
  Serial.println("Receive event");
  Serial.println("x : "+String(x));


  if(read_but == "9"){
    tft.fillScreen(BLACK);
    tft.setTextColor(WHITE);
    tft.setTextSize(4);
    tft.setCursor(20, 120);
    tft.print("Waiting");
    tft.setCursor(20, 160);
    tft.print("Process.");
  } 
  else if(read_but == "8"){
    tft.fillScreen(BLACK);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.setCursor(20, 120);
    tft.print("Press Button");
    tft.setCursor(20, 160);
    tft.print("to Start");
  }
  else if(read_but == "7"){
    tft.fillScreen(BLACK);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.setCursor(20, 120);
    tft.print("Press Button");
    tft.setCursor(20, 160);
    tft.print("to Setup");
  } 
  else if(read_but == "6"){
    tft.fillScreen(BLACK);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.setCursor(20, 120);
    tft.print("Press Button");
    tft.setCursor(20, 160);
    tft.print("to Stop");
  } 

  /////// menu gui /////


  if(menu_condition_show){

    if (read_but == "1") {
      current_condition++;
      if (current_condition > max_condition) current_condition = 1; // Wrap around
      showCondition();
    } else if (read_but == "2") {
      current_condition--;
      if (current_condition < 1) current_condition = max_condition; // Wrap around
      showCondition();
    } else if (read_but == "3") {
      // tft.fillScreen(BLACK);
      // tft.setTextColor(WHITE);
      // tft.setTextSize(3);
      // tft.setCursor(20, 120);
      // tft.print("Confirmed:");
      // tft.setCursor(20, 160);
      // tft.print(condition_name[current_condition]);
      menu_condition_show = false;
      delay(100);
      menu_side = true;
      showSide();
    }else if (read_but == "5"){
      current_condition = 1;
      current_side = 1;
      currentOption = 1;
    }

  }else if(menu_side){

    if (read_but == "1") {
      current_side++;
      if (current_side > max_side) current_side = 1; // Wrap around
      showSide();
    } else if (read_but == "2") {
      current_side--;
      if (current_side < 1) current_side = max_side; // Wrap around
      showSide();
    } else if (read_but == "3") {
      // tft.fillScreen(BLACK);
      // tft.setTextColor(WHITE);
      // tft.setTextSize(3);
      // tft.setCursor(20, 120);
      // tft.print("Confirmed:");
      // tft.setCursor(20, 160);
      // tft.print(side_name[current_side]);
      menu_side = false;
      delay(100);
      menuShown = true;
      showMenu();
    } else if (read_but == "5"){
      menu_condition_show = true;
      menu_side = false;
      menuShown= false;
      delay(100);
      showCondition();
      current_condition = 1;
      current_side = 1;
      currentOption = 1;
    }

  }
  else if(menuShown) {

    if (read_but == "1") {
      currentOption++;
      if (currentOption > maxOptions) currentOption = 1; // Wrap around
      showMenu();
    } else if (read_but == "2") {
      currentOption--;
      if (currentOption < 1) currentOption = maxOptions; // Wrap around
      showMenu();
    } else if (read_but == "3") {
      Serial.println("Confirmmmmmmmmm!!!!");
      tft.fillScreen(BLACK);
      tft.setTextColor(WHITE);
      tft.setTextSize(3);
      tft.setCursor(20, 100);
      tft.print("CONDITN: " + String(current_condition));      
      tft.setCursor(20, 140);
      tft.print("SIDE: " + String(current_side));
      tft.setCursor(20, 180);
      tft.print("OPTION " + String(currentOption));
      current_side = 1;
      current_condition =1;
      currentOption = 1;
      menuShown = false;
    } else if (read_but == "5"){
      menu_condition_show = false;
      menu_side = true;
      menuShown = false;
      delay(100);
      showSide();
      current_condition = 1;
      current_side = 1;
      currentOption = 1;
    }

  }else{
    // Show/hide menu
    if (read_but == "4") {
      Serial.println("menu level 0");
      menu_condition_show = true;
      showCondition();
    }else if(read_but == "3"){
      Serial.println("menu level 1");
      menu_side = true;
      showSide();
    }else if (read_but == "2") {
      Serial.println("menu level 2");
      menuShown = true;
      showMenu();
    } 
    else if (read_but == "6") {
      Serial.println("show status");
      tft.fillScreen(BLACK);
      tft.setTextColor(WHITE);
      tft.setTextSize(3);
      tft.setCursor(20, 100);
      tft.print("WORKING...");
    } 
  }



  read_but = "0";

}
 
void requestEvent() {
 
  // Setup byte variable in the correct size
  byte response[ANSWERSIZE];
  String answer = String("0");
  // Format answer as array
  for (byte i=0;i<ANSWERSIZE;i++) {
     response[i] = (byte)answer.charAt(i);
  }
  
  // Send response back to Master
  Wire.write(response,sizeof(response));
  
  // Print to Serial Monitor
  Serial.println("Request event");
}




void setup(void) {
  
  // Initialize I2C communications as Slave
  Wire.begin(SLAVE_ADDR);

  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));
    
  tft.reset();

  //Function to run when data requested from master
  Wire.onRequest(requestEvent); 
  //Function to run when data received from master
  Wire.onReceive(receiveEvent);
    
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  tft.fillScreen(BLACK);
  tft.setRotation(2);
  // tft.setTextColor(WHITE);
  // tft.setTextSize(6);
  // Set up Timer1 interrupt

}

void loop(void) {
  //nothing in loop
  //delay(10);
}