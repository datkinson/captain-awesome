/* 
 Panel Control

 
 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached from pin 2 to +5V
 * 10K resistor attached from pin 2 to ground
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
  int pin_one;
  int pin_two;
  int pin_three;
  int power;
} power_states;

power_states power[3];
  
void setup() {
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
  
  // propulsion
  power[1].pin_one = 33;
  power[1].pin_two = 34;
  power[1].pin_three = 35;
  power[1].power = 0;
  
  // weapons
  power[2].pin_one = 36;
  power[2].pin_two = 37;
  power[2].pin_three = 38;
  power[2].power = 0;
}

void loop() {
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
}

void update_power() {
  for (int iteration = 0; iteration < sizeof(power) - 1; iteration++){
    int temp_power = 0;
    if (digitalRead(power[iteration].pin_one) == HIGH){
      temp_power++;
    }
    if (digitalRead(power[iteration].pin_two) == HIGH){
      temp_power++;
    }
    if (digitalRead(power[iteration].pin_three) == HIGH){
      temp_power++;
    }
    power[iteration].power = temp_power;
  }
}

