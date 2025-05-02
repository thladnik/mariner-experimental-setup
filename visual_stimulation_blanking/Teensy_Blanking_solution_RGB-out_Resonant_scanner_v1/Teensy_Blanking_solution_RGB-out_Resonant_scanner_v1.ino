// INPUTS
const int redin1 = 38;
const int redin2 = 35;
const int greenin1 = 37;
const int greenin2 = 34;
const int bluein1 = 36;
const int bluein2 = 33;

const int syncin = 0;

// OUTPUTS
const int redout = 4;
const int greenout = 3;
const int blueout = 2;
const int pmtgateout = 1;

// STATES
int redstate = 0;
int greenstate = 0;
int bluestate = 0;

int sync_sig_last = 0;
int sync_sig_cur = 0;

int led_on_state = 0;
long led_on_start_time_mu = 0;
long led_on_end_time_mu = 0;
int led_on_duration_mu = 8000;

long cur_time_mu = 0;

void setup() {

  pinMode(redin1, INPUT);
  pinMode(redin2, INPUT);
  pinMode(greenin1, INPUT);
  pinMode(greenin2, INPUT);
  pinMode(bluein1, INPUT);
  pinMode(bluein2, INPUT);
  pinMode(syncin, INPUT);
  
  pinMode(redout, OUTPUT);
  pinMode(greenout, OUTPUT);
  pinMode(blueout, OUTPUT);
  pinMode(pmtgateout, OUTPUT);

}

void loop() {
  // Read ScanImage frame sync signal
  sync_sig_cur = digitalReadFast(syncin);

  // Read Lightcrafter LED PWM and EN states
  redstate = digitalReadFast(redin1) && digitalReadFast(redin2);
  greenstate = digitalReadFast(greenin1) && digitalReadFast(greenin2);
  bluestate = digitalReadFast(bluein1) && digitalReadFast(bluein2);

  cur_time_mu = micros();

  // If frame sync signal changes from HIGH to LOW, turn LEDs on
  if(not(sync_sig_cur) && sync_sig_last) {
    led_on_state = HIGH;
    led_on_start_time_mu = cur_time_mu;
    led_on_end_time_mu = led_on_start_time_mu + led_on_duration_mu;
  }

  // Turn LEDs off if current time is not between start and end times
  if(not((led_on_start_time_mu <= cur_time_mu) && (cur_time_mu <= led_on_end_time_mu))) {
    led_on_state = LOW;
  }

  // Set LED pin outputs
  digitalWriteFast(redout, led_on_state && redstate);
  digitalWriteFast(greenout, led_on_state && greenstate);
  digitalWriteFast(blueout, led_on_state && bluestate);

  // (optional) Set PMT gate output (original led_on_state or inverted version, depending on PMT type)
  // digitalWriteFast(pmtgateout, not(led_on_state));
  // digitalWriteFast(pmtgateout, led_on_state);

  sync_sig_last = sync_sig_cur;
  
}
