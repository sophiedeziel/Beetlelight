#include <Arduino.h>

#define LED_ARROW_1 2
#define LED_ARROW_2 3
#define LED_ARROW_3 4
#define LED_ARROW_4 5
#define LED_ARROW_5 6
#define LED_ARROW_6 7
#define LED_ARROW_7 8
#define LED_ARROW_8 9
#define LED_ARROW_9 10
#define LED_ARROW_10 11
#define LED_ARROW_11 12
#define LED_ARROW_12 13
#define LED_ARROW_13 A0
#define LED_ARROW_14 A1

#define LED_TOUR_1 A2
#define LED_TOUR_2 A3

#define LED_INSIDE A4
#define BUTTON A5
#define total_tour_frames 10

int current_tour_frame = 0;
int current_arrow_frame = 0;
int current_arrow = -1;
const int debounce_time = 100;
long last_debounce;
bool enabled = false;
bool button_state = false;
bool last_button_state = false;

bool tour_frames[total_tour_frames][2] = {
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

#define total_arrow_lights 15
uint8_t arrow_lights[15] = {
    LED_ARROW_1,
    LED_ARROW_2,
    LED_ARROW_3,
    LED_ARROW_4,
    LED_ARROW_5,
    LED_ARROW_6,
    LED_ARROW_7,
    LED_ARROW_8,
    LED_ARROW_9,
    LED_ARROW_10,
    LED_ARROW_11,
    LED_ARROW_12,
    LED_ARROW_13,
    LED_ARROW_14,
    LED_ARROW_13};

void nextTourFrame()
{
  digitalWrite(LED_TOUR_2, tour_frames[current_tour_frame][0]);
  digitalWrite(LED_TOUR_1, tour_frames[current_tour_frame][1]);

  current_tour_frame++;
  if (current_tour_frame >= total_tour_frames)
  {
    current_tour_frame = 0;
  }
}

void nextArrowFrame()
{
  int frames_per_ligth = 2;
  int buffer_frames = 50;

  current_arrow_frame++;
  if (current_arrow_frame <= buffer_frames)
  {
    // Début de l'animation avec rien
  }
  else if (current_arrow_frame % frames_per_ligth == 0)
  {
    current_arrow++;
    digitalWrite(arrow_lights[current_arrow], LOW);
    for (int i = 0; i <= total_arrow_lights; i++)
    {
      if (i != current_arrow)
      {
        digitalWrite(arrow_lights[i], HIGH);
      }
    }
  }
  if (current_arrow_frame >= (buffer_frames + frames_per_ligth * 14))
  {
    current_arrow_frame = 0;
    current_arrow = -1;
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED_ARROW_1, OUTPUT);
  pinMode(LED_ARROW_2, OUTPUT);
  pinMode(LED_ARROW_3, OUTPUT);
  pinMode(LED_ARROW_4, OUTPUT);
  pinMode(LED_ARROW_5, OUTPUT);
  pinMode(LED_ARROW_6, OUTPUT);
  pinMode(LED_ARROW_7, OUTPUT);
  pinMode(LED_ARROW_8, OUTPUT);
  pinMode(LED_ARROW_9, OUTPUT);
  pinMode(LED_ARROW_10, OUTPUT);
  pinMode(LED_ARROW_11, OUTPUT);
  pinMode(LED_ARROW_12, OUTPUT);
  pinMode(LED_ARROW_13, OUTPUT);
  pinMode(LED_ARROW_14, OUTPUT);

  pinMode(LED_TOUR_2, OUTPUT);
  pinMode(LED_TOUR_1, OUTPUT);

  pinMode(LED_INSIDE, OUTPUT);
  pinMode(BUTTON, INPUT);

  digitalWrite(LED_ARROW_1, HIGH);
  digitalWrite(LED_ARROW_2, HIGH);
  digitalWrite(LED_ARROW_3, HIGH);
  digitalWrite(LED_ARROW_4, HIGH);
  digitalWrite(LED_ARROW_5, HIGH);
  digitalWrite(LED_ARROW_6, HIGH);
  digitalWrite(LED_ARROW_7, HIGH);
  digitalWrite(LED_ARROW_8, HIGH);
  digitalWrite(LED_ARROW_9, HIGH);
  digitalWrite(LED_ARROW_10, HIGH);
  digitalWrite(LED_ARROW_11, HIGH);
  digitalWrite(LED_ARROW_12, HIGH);
  digitalWrite(LED_ARROW_13, HIGH);
  digitalWrite(LED_ARROW_14, HIGH);

  digitalWrite(LED_TOUR_2, HIGH);
  digitalWrite(LED_TOUR_1, HIGH);

  digitalWrite(LED_INSIDE, LOW);
}

void loop()
{
  if (millis() - last_debounce > debounce_time)
  {
    last_debounce = millis();
    bool reading = digitalRead(BUTTON);

    if (reading != button_state)
    {
      button_state = reading;

      if (reading == true)
      {
        enabled = !enabled;
      }
    }
  }

  last_button_state = button_state;

  if (enabled)
  {
    nextTourFrame();
    nextArrowFrame();
  }
  delay(20);
}
