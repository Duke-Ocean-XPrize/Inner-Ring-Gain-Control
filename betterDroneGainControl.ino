#include <Servo.h>
byte THROTTLE = 3; // input voltage from wave function
byte GAIN = 7; // input voltage from wave function

Servo ESC;
float throttle_val;
float gain_val;

void setup() {
  pinMode(THROTTLE, INPUT);  
  pinMode(GAIN, INPUT);  

  ESC.attach(11);
  Serial.begin(115200);
}

float f_clamp(float v, float lo, float hi) {
  if (v<lo) return lo;
  if (v>hi) return hi;
  return v;
}

const int min_micros = 1000;
const int max_micros = 2000;

void loop() {
  throttle_val = pulseIn(THROTTLE, HIGH);
  gain_val = pulseIn(GAIN, HIGH);

  float throttle_f = ((float)(throttle_val - min_micros))/(max_micros-min_micros);
  float gain_f = ((float)(gain_val - min_micros))/(max_micros-min_micros);

  throttle_f = f_clamp(throttle_f,0,1);
  gain_f = f_clamp(gain_f,0,1);

  float out_f = throttle_f * gain_f;

  long out_micros = out_f*(max_micros-min_micros) + min_micros;
  
  ESC.writeMicroseconds(out_micros);
}
