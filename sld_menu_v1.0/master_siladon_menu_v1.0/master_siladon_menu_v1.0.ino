#include <Wire.h>

#define SLAVE_ADDR 5
#define ANSWERSIZE 3

void write_i2c(uint8_t b) {
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(b);
  Wire.endTransmission();
}

int menu_level = 0;
int current_condition = 1;
int current_side = 1;
int current_option = 1;
const int max_condition = 2;
const int max_side = 2;
const int max_option = 3;



void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Menu ready: 1=up 2=down 3=back/clear, 4=confirm");
}

void loop() {

start_menu:
  menu_level = 0;
  current_condition = 1;
  current_side = 1;
  current_option = 1;

  // --- SELECT CONDITION ---
  write_i2c(4);
  Serial.print("Select CONDITION: "); Serial.println(current_condition);
  while (true) {
    if (Serial.available() > 0) {
      char key = Serial.read();
      if (key == '1') { // up
        current_condition = (current_condition % max_condition) + 1;
        write_i2c(1);
        Serial.print("Condition: "); Serial.println(current_condition);
      } else if (key == '2') { // down
        current_condition = (current_condition - 2 + max_condition) % max_condition + 1;
        write_i2c(2);
        Serial.print("Condition: "); Serial.println(current_condition);
      } else if (key == '3') { // back on level 0: clear
        Serial.println("clearrrrrrrr");
        write_i2c(5);
        goto start_menu; // restart menu
      } else if (key == '4') { // confirm
        write_i2c(3);
        menu_level = 1;
        break;
      }
      while (Serial.available() > 0) Serial.read();
    }
    delay(200);
  }

  // --- SELECT SIDE ---
  Serial.print("Select SIDE: "); Serial.println(current_side);
  while (true) {
    if (Serial.available() > 0) {
      char key = Serial.read();
      if (key == '1') {
        current_side = (current_side % max_side) + 1;
        write_i2c(1);
        Serial.print("Side: "); Serial.println(current_side);
      } else if (key == '2') {
        current_side = (current_side - 2 + max_side) % max_side + 1;
        write_i2c(2);
        Serial.print("Side: "); Serial.println(current_side);
      } else if (key == '3') { // back to previous menu
        menu_level = 0;
        write_i2c(5);
        goto start_menu;
      } else if (key == '4') { // confirm
        write_i2c(3);
        menu_level = 2;
        break;
      }
      while (Serial.available() > 0) Serial.read();
    }
    delay(200);
  }

  // --- SELECT OPTION ---
  //write_i2c(2);
  Serial.print("Select OPTION: "); Serial.println(current_option);
  while (true) {
    if (Serial.available() > 0) {
      char key = Serial.read();
      if (key == '1') {
        current_option = (current_option % max_option) + 1;
        write_i2c(1);
        Serial.print("Option: "); Serial.println(current_option);
      } else if (key == '2') {
        current_option = (current_option - 2 + max_option) % max_option + 1;
        write_i2c(2);
        Serial.print("Option: "); Serial.println(current_option);
      } else if (key == '3') { // back to previous menu
        menu_level = 1;
        write_i2c(5);
        goto start_menu;
      } else if (key == '4') { // confirm & finish
        write_i2c(3);
        menu_level = 3;
        break;
      }
      while (Serial.available() > 0) Serial.read();
    }
    delay(200);
  }

  // === MENU COMPLETE ===
  write_i2c(6);
  Serial.print("RESULT: ");
  Serial.print(current_condition);
  Serial.print(" ");
  Serial.print(current_side);
  Serial.print(" ");
  Serial.println(current_option);
  delay(2500);

  goto start_menu; // repeat menu forever
}
