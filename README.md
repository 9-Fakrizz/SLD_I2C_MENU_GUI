# SLD\_I2C\_MENU\_GUI

**SLD\_I2C\_MENU\_GUI** is a library and example menu system built for Siladon hardware, using I²C-connected LCD (e.g. 16×2/20×4 character display) controlled by an Arduino or ESP32 board. It provides a graphical menu interface navigated via buttons (Up / Down / Select / Back), allowing user interaction with configurable parameters and options.

---

## 📋 Features

* I²C‑based text LCD support (e.g. **LiquidCrystal\_I2C**)
* Tree‑structured menu system with nested submenus
* Navigation buttons: Up, Down, Select, Back
* Display callbacks for executing menu actions
* Low RAM usage (menu structure stored in PROGMEM)
* Customizable menu items and labels

---

## 🚀 Getting Started

### Hardware Requirements

* Microcontroller (Arduino UNO/Nano, or ESP32)
* I²C LCD display (commonly 0x27 or 0x3F address)
* Four pushbuttons wired to GPIO pins
* Optional: pull-up resistors or built-in internal pull-ups

### Wiring Reference

(I am using ESP32 just for testing I2C Communication)

| Component | Connector       | Microcontroller Pin                 |
| --------- | --------------- | ----------------------------------- |
| SDA       | I²C SDA         | e.g. A4 (Arduino) / GPIO 21 (ESP32) |
| SCL       | I²C SCL         | e.g. A5 (Arduino) / GPIO 22 (ESP32) |
| Buttons\* |  Up / Down etc. | User-defined digital pins           |

\* Buttons connected using pull-up configuration (normally HIGH, LOW when pressed).

### Software Installation

1. Clone this repository or download as ZIP.
2. Install required libraries via Arduino IDE:

   * `Wire`
   * `LiquidCrystal_I2C`
3. Move the `SLD_I2C_MENU_GUI` folder into your Arduino libraries folder (or use PlatformIO include).

---

## ❓ Troubleshooting

* **LCD displays garbled or blank output**:

  * Ensure correct I²C address: run an I²C scanner sketch to locate the address (often `0x27` or `0x3F`) ([Reddit][1], [make-it.ca][2], [Arduino++][3], [Random Nerd Tutorials][4], [land-boards.com][5], [Instructables][6]).
  * Adjust contrast potentiometer on the I²C backpack board.
  * Confirm wiring of SDA/SCL and power to LCD.
* **Buttons not registering presses**:

  * Use pull-up resistors (internal or external), digital input set with `INPUT_PULLUP`.
* **Unexpected reset or menu behavior on button sting**:

  * Debounce button input in code or use hardware debouncing (capacitor/resistor).

---

## 📬 Contact

* Report issues or feature requests via the GitHub *Issues* tab.
* For questions, open a discussion or leave a comment in the repository.
* Email: Suphakrit_kongkham@cmu.ac.th

---

[1]: https://www.reddit.com/r/arduino/comments/17aplqo/lcd_i2c_menu/?utm_source=chatgpt.com "LCD I2C Menu : r/arduino"
[2]: https://www.make-it.ca/i2c-lcd-display-on-arduino/?utm_source=chatgpt.com "I2C LCD on Arduino - Easily Setup and Control With An UNO"
[3]: https://arduinoplusplus.wordpress.com/2021/01/16/a-menu-system-for-lcd-modules/?utm_source=chatgpt.com "A Menu System for LCD Modules - Arduino++ - WordPress.com"
[4]: https://randomnerdtutorials.com/esp32-esp8266-i2c-lcd-arduino-ide/?utm_source=chatgpt.com "I2C LCD with ESP32 on Arduino IDE - ESP8266 compatible"
[5]: https://land-boards.com/blwiki/index.php?title=MyMenu&utm_source=chatgpt.com "MyMenu - Land Boards Wiki"
[6]: https://www.instructables.com/Simple-LCD-MENU-Using-Arduino/?utm_source=chatgpt.com "Simple LCD MENU Using Arduino : 6 Steps"
