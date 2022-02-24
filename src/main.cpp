#include <Arduino.h>

#define LED_TOUR_1 8
#define LED_TOUR_2 9
#define BUTTON 12
#define total_frames 10

int current_frame = 0;
const int debounce_time = 100;
long last_debounce;
bool enabled = false;
bool button_state = false;
bool last_button_state = false;

bool frames[total_frames][2] = {
  {true, false},
  {true, false},
  {true, false},
  {false, true},
  {false, true},
  {false, true},
  {false, true},
  {false, true},
  {false, false},
  {false, false},
  };

void nextFrame() {
  digitalWrite(LED_TOUR_2, !frames[current_frame][0]);
  digitalWrite(LED_TOUR_1, !frames[current_frame][1]);

  current_frame++;
  if(current_frame >= total_frames){
    current_frame = 0;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_TOUR_2, OUTPUT);
  pinMode(LED_TOUR_1, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop() {
  if (millis() - last_debounce > debounce_time) {
    last_debounce = millis();
    bool reading = digitalRead(BUTTON);

    if (reading != button_state) {
      button_state = reading;

      if(reading == true) {
        enabled = !enabled;
      }
    }
  }

  last_button_state = button_state;

  if(enabled) {
    nextFrame();
  }
  delay(20);
}
