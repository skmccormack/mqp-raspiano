 #define COLOR_CYCLE 15000   // length of color cycle in [units]
 #define MASTER             // determine whether this is a master or slave board
 // #define SLAVE

 float color_base[3] = {1, 0, 0};                                               //starting color
 float color_target[3] = {1, 1, 0};                                             //color to cycle to
 volatile float color_array[3] = {color_base[0], color_base[1], color_base[2]}; //current display color
 int color_output[3] = {0, 0, 0};                                               //PWM output
 volatile int c = 0;                                                            //counter for color change
 int vol = 0;

void setup() {
  //configure analog input
  pinMode(A1, INPUT);

  #ifdef MASTER
  pinMode(2, OUTPUT);
  #endif

  #ifdef SLAVE
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), UpdateColor, RISING);
  #endif
  
  //configure and initialize gpio 6,7, and 8
  pinMode(9, OUTPUT);
  analogWrite(9, color_output[0]);
  pinMode(10, OUTPUT);
  analogWrite(10, color_output[1]);
  pinMode(11, OUTPUT);
  analogWrite(11, color_output[2]);
  
  //begin serial device
  Serial.begin(115200);
}

void loop() {
  //take a reading
  vol = analogRead(A1)/4;

  //assign brightness based on analog value * color array
  color_output[0] = vol*color_array[0];
  color_output[1] = vol*color_array[1];
  color_output[2] = vol*color_array[2];

  //transmit PWM signal
  analogWrite(9, color_output[0]);
  analogWrite(10, color_output[1]);
  analogWrite(11, color_output[2]);

  //change color
  #ifdef MASTER
  UpdateColor();
  digitalWrite(2, HIGH);
  digitalWrite(2, LOW);
  #endif
}

void UpdateColor() {
  if (c<COLOR_CYCLE){
    color_array[0] += (color_target[0]-color_base[0])/COLOR_CYCLE;
    color_array[1] += (color_target[1]-color_base[1])/COLOR_CYCLE;
    color_array[2] += (color_target[2]-color_base[2])/COLOR_CYCLE;
    c++;
  } else if (c<COLOR_CYCLE*2){
    color_array[0] += -(color_target[0]-color_base[0])/COLOR_CYCLE;
    color_array[1] += -(color_target[1]-color_base[1])/COLOR_CYCLE;
    color_array[2] += -(color_target[2]-color_base[2])/COLOR_CYCLE;
    c++;
  } else {
    color_array[0] = color_base[0];
    color_array[1] = color_base[1];
    color_array[2] = color_base[2];
    c=0;
  }
}
