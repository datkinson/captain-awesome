/* 
 Panel Control
*/
// set pin numbers:
const int fireButtonPin = 22;
const int ledPin = 13;

// Variables will change:
int ledState = HIGH;
int fireButtonState;
int lastFireButtonState = LOW;

long lastDebounceTime = 0;
long debounceDelay = 50;

String json = "";
String completeState = "";

int update = 0;

// define a struct to contain all of the button information
typedef struct
{
  int pin;
  int previousState;
  int currentState;
} button_states;

button_states buttons[5];

typedef struct
{
  int pin;
  int previousState;
  int currentState;
} switch_states;

switch_states switches[1];

typedef struct
{
  int pin;
  int previousValue;
  int value;
} knob_states;

knob_states knob[4];

typedef struct
{
  int pin_one;
  int pin_two;
  int pin_three;
  int pin_one_state;
  int pin_two_state;
  int pin_three_state;
  int power;
} power_states;

power_states power[3];
  
void setup() {
  Serial.begin(9600);
  pinMode(fireButtonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
  
  
  
  
// initialise the button pins
  // fire button
  buttons[0].pin = 22;
  buttons[0].previousState = LOW;
  buttons[0].currentState = LOW;

  // shield 1 button
  buttons[1].pin = 23;
  buttons[1].previousState = LOW;
  buttons[1].currentState = LOW;
  
  // shield 2 button
  buttons[2].pin = 24;
  buttons[2].previousState = LOW;
  buttons[2].currentState = LOW;
  
  // shield 3 button
  buttons[3].pin = 25;
  buttons[3].previousState = LOW;
  buttons[3].currentState = LOW;
  
  // shield 4 button
  buttons[4].pin = 26;
  buttons[4].previousState = LOW;
  buttons[4].currentState = LOW;
  
//  initialise power sockets
  // shields
  power[0].pin_one = 30;
  power[0].pin_two = 31;
  power[0].pin_three = 32;
  power[0].power = 0;
  power[0].pin_one_state = LOW;
  power[0].pin_two_state = LOW;
  power[0].pin_three_state = LOW;
  
  // propulsion
  power[1].pin_one = 33;
  power[1].pin_two = 34;
  power[1].pin_three = 35;
  power[1].power = 0;
  power[1].pin_one_state = LOW;
  power[1].pin_two_state = LOW;
  power[1].pin_three_state = LOW;
  
  // weapons
  power[2].pin_one = 36;
  power[2].pin_two = 37;
  power[2].pin_three = 38;
  power[2].power = 0;
  power[2].pin_one_state = LOW;
  power[2].pin_two_state = LOW;
  power[2].pin_three_state = LOW;
  
//  Serial.println("Booted");
}

void loop() {
  update = 0;
  // read the state of the switch into a local variable:
  int reading = digitalRead(fireButtonPin);

  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to HIGH),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (reading != lastFireButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != fireButtonState) {
      fireButtonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (fireButtonState == HIGH) {
        ledState = !ledState;
      }
    }
  }
  
  // set the LED:
  digitalWrite(ledPin, ledState);

  // save the reading.  Next time through the loop,
  // it'll be the lastFireButtonState:
  lastFireButtonState = reading;
  update_power();
  if(update > 0){
    Serial.print("Number of changes: ");
    Serial.println(update);
    generate_complete_state();
    Serial.println(completeState);
  }
}

void update_power() {
//  Serial.println(sizeof(power));
  for (int iteration = 0; iteration < 3; iteration++){
    // Set temporary iteration variables
    int previous_power = power[iteration].power;
    int temp_power = 0;
    
    // Update object vales to current state
    power[iteration].pin_one_state = digitalRead(power[iteration].pin_one);
    power[iteration].pin_two_state = digitalRead(power[iteration].pin_two);
    power[iteration].pin_three_state = digitalRead(power[iteration].pin_three);
    
    // Add up total power value
    if (digitalRead(power[iteration].pin_one) == HIGH){
      temp_power++;
    }
    if (digitalRead(power[iteration].pin_two) == HIGH){
      temp_power++;
    }
    if (digitalRead(power[iteration].pin_three) == HIGH){
      temp_power++;
    }
    
    // check if value is different from previous check
    power[iteration].power = temp_power;
    if (previous_power != power[iteration].power){
      update++;
//      Serial.print("Power ");
//      Serial.print(iteration);
//      Serial.print(" has new setting: ");
//      Serial.println(power[iteration].power);

      // Update system with new power reading
//      print_power_table(iteration, power[iteration].pin_one_state, power[iteration].pin_two_state, power[iteration].pin_three_state, power[iteration].pin_one, power[iteration].pin_two, power[iteration].pin_three, power[iteration].power);    
    }

    

    
    
    
    
    
  }
}


void print_power_table(int section, int pin1_value, int pin2_value, int pin3_value, int pin1, int pin2, int pin3, int value){
//  Serial.print("+=== Section - ");
//  Serial.print(section);
//  Serial.println(" ===+");
//  
//  Serial.print("Pin: ");
//  Serial.print(pin1);
//  Serial.print(" = ");
//  Serial.println(pin1_value);
//  
//  Serial.print("Pin: ");
//  Serial.print(pin2);
//  Serial.print(" = ");
//  Serial.println(pin2_value);
//  
//  Serial.print("Pin: ");
//  Serial.print(pin3);
//  Serial.print(" = ");
//  Serial.println(pin3_value);
//  
//  Serial.print("Result: ");
//  Serial.println(value);
//  Serial.println("+===================+\n\n\n");
  
  
  
  json = "{\"power\":\"";
  json += section;
  json += "\",\"value\":\"";
  json += value;
  json += "\"}";
  Serial.print("|");
  Serial.print(json);
  Serial.println("~");
}


void generate_complete_state()
{
  json = "|";
  json += "{\"power\": {\"shields\": \"";
  json += power[0].power;
  json += "\",\"weapons\": \"";
  json += power[1].power;
  json += "\",\"propulsion\": \"";
  json += power[2].power;
  json+= "\"},\"shields\": {\"front\": \"";
  json += buttons[1].currentState;
  json += "\",\"left\": \"";
  json += buttons[2].currentState;
  json += "\",\"right\": \"";
  json += buttons[3].currentState;
  json += "\",\"back\": \"";
  json += buttons[4].currentState;
  json += "\"},\"weapons\": {\"switch\": \"";
  json += switches[1].currentState;
  json += "\",\"fire\": \"";
  json += buttons[0].currentState;
  json += "\",\"left\": \"";
  json += knob[0].value;
  json += "\",\"right\": \"";
  json += knob[1].value;
  json += "\"},\"key\": \"";
  json += switches[0].currentState;
  json += "\"}";
  json += "~";
  completeState = json;
}
