// <<these constants are use to assign the Arduino Due pin>>
// LED light
const int ledPins = 6; // LED pins
const int LEDPin_start = 4;
const int forceSensorPins = 54; // Force sensor pins
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
  Serial.begin(115200);
  randomSeed(analogRead(0));
  
  pinMode(ledPins, OUTPUT);
  pinMode(forceSensorPins, INPUT);
  
  

  //printing the header
  Serial.print("time(ms)"); 
  Serial.print(", "); 
  Serial.print("sensor"); 
  Serial.print(", "); 
  Serial.print("LED"); 
  Serial.print(", "); 
  Serial.println("Time delay");
  delay (5000); // small delay before the start of the experiment
  digitalWrite(LEDPin_start, HIGH);
}

void loop() {
  int randomLED;
  int sensorReading;
  

  int LEDstate = random(0, 2);
  if (LEDstate == 0) {
    int sensorReading =0;
    int LEDStates = 0;
    // code to print out the reading
    current_time = millis() - experiment_start_time;
    String sensor_out = String(current_time) + spacer +
                        String(sensorReading) + spacer +
                        String(LEDStates) + spacer +
                        String(reactionTime);
    Serial.println(sensor_out);
  }
  else {
    // Record the start time
    unsigned long startTime = millis();
    // Turn on the randomly selected LED
    digitalWrite(ledPins, HIGH);
    LEDStates = 1;
    unsigned long reactionTime = 0 ;
    // Wait for 1 second
    while (millis() - startTime < 1000) {
      
      // Check if any force sensor reading has changed
      
      int sensorReading = analogRead(forceSensorPins);
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
  }
  
  // illuminate the LED for 2 seconds
  delay(2000);
  // Turn off the randomly selected LED
  digitalWrite(ledPins, LOW); 
  // Delay 1 second before next iteration
  delay(1000);
}