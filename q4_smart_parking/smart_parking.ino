/*
 *This is a smart parking indicator that uses an ultrasonic sensor to detect if a parking bay is occupied or available. It controls two LEDs and a buzzer to indicate the status of the bay.
*/

#define TRIG_PIN   9
#define ECHO_PIN   10
#define GREEN_LED  3
#define RED_LED    4
#define BUZZER     5

#define OCCUPIED_THRESHOLD_CM  50      /* closer than this means a car is in the bay */
#define ECHO_TIMEOUT_US        30000UL /* stop waiting for an echo after about 5 m */
#define BUZZER_TONE_HZ         1000
#define LOOP_DELAY_MS          300

#define OCCUPIED   1
#define AVAILABLE  0
#define NO_ECHO    -1

/* Sends one ultrasonic pulse and converts the echo time into centimetres */
long read_distance_cm(void)
{
    unsigned long duration;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT_US);
    if (duration == 0) {
        return NO_ECHO; /* nothing in range */
    }
    /* sound travels at 0.034 cm per microsecond, and the pulse goes there and back */
    return (long) (duration * 0.034 / 2.0);
}

/* The occupancy rule in one place so it is easy to change. Returns 1 or 0. */
int is_occupied(long distance_cm)
{
    if (distance_cm > 0 && distance_cm <= OCCUPIED_THRESHOLD_CM) {
        return OCCUPIED;
    }
    return AVAILABLE;
}

/* Drives the three outputs from the decision */
void show_status(int occupied)
{
    if (occupied == OCCUPIED) {
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);
        tone(BUZZER, BUZZER_TONE_HZ);
    } else {
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
        noTone(BUZZER);
    }
}

/* Prints one log line per reading so the behaviour can be checked in the serial monitor */
void log_reading(long distance_cm, int occupied)
{
    Serial.print("Distance: ");
    if (distance_cm == NO_ECHO) {
        Serial.print("out of range");
    } else {
        Serial.print(distance_cm);
        Serial.print(" cm");
    }
    Serial.print(" | Status: ");
    if (occupied == OCCUPIED) {
        Serial.println("OCCUPIED");
    } else {
        Serial.println("AVAILABLE");
    }
}

void setup(void)
{
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    Serial.begin(9600);
    Serial.println("Smart parking indicator ready");
}

void loop(void)
{
    long distance = read_distance_cm();
    int occupied = is_occupied(distance);

    show_status(occupied);
    log_reading(distance, occupied);

    delay(LOOP_DELAY_MS);
}