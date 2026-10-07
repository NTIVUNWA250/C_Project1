# Question 4: Smart parking indicator

Tinkercad link: https://www.tinkercad.com/things/4P8vuOnSpXs/editel?sharecode=SPIey2NlR90mhsagEjt9r-w_EtNnG0skXpQMIqYyUqk

Screenshots: In the screenshot folder having all the tests.

## Block diagram

A great picture is in the screenshots folder too

    +--------------------+      echo time      +---------------------+
    | Ultrasonic sensor  | ------------------> |     Arduino Uno     |
    | HC-SR04            |      (microseconds) |                     |
    | TRIG <- pin 9      |                     | 1. send trigger     |
    | ECHO -> pin 10     |                     | 2. time the echo    |
    +--------------------+                     | 3. convert to cm    |
                                               | 4. compare with     |
                                               |    50 cm threshold  |
                                               +----------+----------+
                                                          |
                                   decision: occupied or available
                                                          |
                          +-------------------------------+-------------------------------+
                          |                               |                               |
                          v                               v                               v
                  +---------------+               +---------------+               +---------------+
                  |  Green LED    |               |   Red LED     |               |    Buzzer     |
                  |  pin 3        |               |   pin 4       |               |    pin 5      |
                  |  ON = free    |               |  ON = taken   |               |  ON = taken   |
                  +---------------+               +---------------+               +---------------+

## Components and wiring

| Component          | Pin on component | Connects to          |
|--------------------|------------------|----------------------|
| HC-SR04 ultrasonic | VCC              | Arduino 5V           |
| HC-SR04 ultrasonic | GND              | Arduino GND          |
| HC-SR04 ultrasonic | TRIG             | Arduino D9           |
| HC-SR04 ultrasonic | ECHO             | Arduino D10          |
| Green LED          | anode (long leg) | 220 ohm resistor, then Arduino D3 |
| Green LED          | cathode          | Arduino GND          |
| Red LED            | anode (long leg) | 220 ohm resistor, then Arduino D4 |
| Red LED            | cathode          | Arduino GND          |
| Piezo buzzer       | positive         | Arduino D5           |
| Piezo buzzer       | negative         | Arduino GND          |

In Tinkercad the HC-SR04 is listed as "Ultrasonic Distance Sensor" with four pins. The three-pin version also works, in which case TRIG and ECHO share one pin and both constants in the code should be set to that pin.

## Role of each component

- Ultrasonic sensor. Sends a short burst of sound when the trigger pin goes high and raises the echo pin for as long as it takes the sound to bounce back. The length of that pulse is the raw measurement.
- Arduino Uno. The controller. It fires the trigger, times the echo pulse with `pulseIn()`, converts the time into centimetres, applies the threshold and sets the output pins.
- Green LED. Lit when the bay is free so a driver can spot it from a distance.
- Red LED. Lit when the bay is taken.
- Buzzer. Sounds while a car is inside the threshold. In a real car park this would warn the driver they are close to the sensor wall.
- Resistors. One 220 ohm resistor in series with each LED keeps the current round 15 mA so neither the LED nor the Arduino pin is overloaded.

## How the sensor data is processed

1. `read_distance_cm()` pulls TRIG low, then high for 10 microseconds, then low again. That tells the sensor to send a pulse.
2. `pulseIn(ECHO_PIN, HIGH, 30000)` waits for ECHO to go high and returns how many microseconds it stayed high. The timeout stops the program hanging if nothing is in range, and in that case the function returns -1.
3. The duration is multiplied by 0.034 cm per microsecond and divided by two, because the sound travels to the car and back.
4. `is_occupied()` returns 1 when the distance is between 1 cm and the 50 cm threshold. A negative value, meaning no echo, counts as available.

## How the Arduino controls the outputs

`show_status()` takes the 1 or 0 decision and sets all three output together so they can never disagree. Occupied means red on, green off and `tone()` running on the buzzer. Available means green on, red off and `noTone()`. Keeping the rule in one function made it easy to test, because the only thing that changes between the two states is one int flag.

Every reading is also printed to the serial monitor as a log line, which is how I checked the distance values during the test cases.

## Threshold

I chose 50 cm. A car parked in a bay normally sits well under half a metre from a sensor mounted on the wall or kerb, while an empty bay gives readings of several metres or no echo at all. That leaves a clear gap on both sides so a passing pedestrian at one or two metres does not trigger the red light.

## Simulation test cases

| Test | Simulated distance | Expected                                   | Observed |
|------|--------------------|--------------------------------------------|----------|
| 1    | 200 cm             | Green ON, Red OFF, Buzzer OFF, AVAILABLE   | [fill in] |
| 2    | 30 cm              | Green OFF, Red ON, Buzzer ON, OCCUPIED     | [fill in] |
| 3    | 50 cm (boundary)   | Green OFF, Red ON, Buzzer ON, OCCUPIED     | [fill in] |
| 4    | 51 cm (just above) | Green ON, Red OFF, Buzzer OFF, AVAILABLE   | [fill in] |

To run a test in Tinkercad, start the simulation, click the ultrasonic sensor and drag the object in its range window to the distance in the table, then check the LEDs, the buzzer icon and the serial monitor line, for example:

    Distance: 30 cm | Status: OCCUPIED