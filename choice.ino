// <<these constants are use to assign the Arduino Due pin>>
// LED light
const int ledPin_choice[] = {2, 6}; // choice LED 
const int ledPin_j[] = {3, 5}; //Y/N LED
const int LEDPin_start = 4;
const int forceSensor_j[] = {56, 55}; // Force sensor pins
unsigned long reactionTime;

//<<these constants are use to set the parameter for the experiment>>
// total measuring/experiment time = t_step X t_reso
const double t_step=12000; //number of loop/ number of data points in total
const int t_reso= 5; //time resolution (milisec) (Please don't go below 5ms)
String spacer =","; //the seperator will be used in the output file

// <<these variables will change throughout the measurment>>
// time status
int experiment_start_time; //experiment start time delay
double current_time; // time when the data were acquired

//define the series of the state of LED and sensor
int LEDStates;
int sensorReadings;

void setup() {
  Serial.begin(57600);
  delay(1000); // Wait for serial monitor to open
  Serial.flush(); // Clear serial buffer
  randomSeed(analogRead(0));
  
  for (int i = 0; i < 2; ++i){
    pinMode(ledPin_choice[i], OUTPUT);
    pinMode(forceSensor_j[i], INPUT);
  }
  

  //printing the header
  Serial.print("time(ms)"); 
  Serial.print(", "); 
  Serial.print("sensor_Y"); 
  Serial.print(", "); 
  Serial.print("sensor_N"); 
  Serial.print(", "); 
  Serial.print("LED_State"); 
  Serial.print(", "); 
  Serial.println("Time delay");
  delay (5000); // small delay before the start of the experiment
  digitalWrite(LEDPin_start, HIGH);
}

void loop() {
  int sensorReading;
  //illuminate a random LED as choice
  int randomLED = random(0, 2);
  digitalWrite(ledPin_choice[randomLED],HIGH);
  // Record the start time
  unsigned long startTime = millis();
  unsigned long reactionTime = 0 ;
  if (randomLED == 0){
    String LEDStates = "RED";
  }
  else{
    String LEDStates = "BLUE";
  }
  // Wait for 1 second
  while (millis() - startTime < 1000) {    
    // Check if any force sensor reading has changed
    int sensorReading = analogRead(forceSensor_j[randomLED]);
    // If the sensor reading changes, record the sensor and its reading
    if (sensorReading != 0 && reactionTime == 0) {
      // calculate react time
      reactionTime = millis() - startTime;
    }
    //data output
    current_time = millis() - experiment_start_time;
    String sensor_out = String(current_time) + spacer +
                        String(sensorReading) + spacer +
                        String(LEDStates) + spacer +
                        String(reactionTime);
    Serial.println(sensor_out);
  } 

  
  // illuminate the LED for 2 seconds
  delay(2000);
  // Turn off the randomly selected LED
  digitalWrite(ledPin_choice[randomLED], LOW); 
  // Delay 1 second before next iteration
  delay(1000);
}
