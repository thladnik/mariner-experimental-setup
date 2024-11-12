// INPUTS
const int redin1 = 38;
const int redin2 = 35;
const int greenin1 = 37;
const int greenin2 = 34;
const int bluein1 = 36;
const int bluein2 = 33;

const int blankin = 0;

// OUTPUTS
const int redout = 4;
const int greenout = 3;
const int blueout = 2;
const int pmtgateout = 1;

// STATES
int redstate = 0;
int greenstate = 0;
int bluestate = 0;

int pmtgatestate_last = 0;
int pmtgatestate_cur = 0;

void setup() {

  pinMode(redin1, INPUT);
  pinMode(redin2, INPUT);
  pinMode(greenin1, INPUT);
  pinMode(greenin2, INPUT);
  pinMode(bluein1, INPUT);
  pinMode(bluein2, INPUT);
  pinMode(blankin, INPUT);
  
  pinMode(redout, OUTPUT);
  pinMode(greenout, OUTPUT);
  pinMode(blueout, OUTPUT);
  pinMode(pmtgateout, OUTPUT);

}

void loop() {
  // Read current blanking state
  // If mirror flyback period signal is used:
  pmtgatestate_cur = not(digitalReadFast(blankin));
  // If laser blanking signal is used: PMT GATE should be LOW while laser is on (HIGH)
  //pmtgatestate_cur = not(digitalReadFast(blankin));

  redstate = digitalReadFast(redin1) && digitalReadFast(redin2);
  greenstate = digitalReadFast(greenin1) && digitalReadFast(greenin2);
  bluestate = digitalReadFast(bluein1) && digitalReadFast(bluein2);

  // If PMT GATE STATE is ON && it was NOT ON during last iteration
  // SWITCH PMT OFF (Set PMT GATE to HIGH)
  if(pmtgatestate_cur && not(pmtgatestate_last)) {
    // Close PMT gate
    digitalWriteFast(pmtgateout, HIGH);
    
    // (optional?) Delay LED ON by rise time of PMT gate
    // HAMAMATSU H11706P-40:
    //  0% -> 90%  230ns
    //  0% -> 100% 400ns
    //delayNanoseconds(400);
  }

  // Write LED pins
  // LEDs should only be HIGH if PMT GATE is HIGH
  digitalWriteFast(redout, pmtgatestate_cur && redstate);
  digitalWriteFast(greenout, pmtgatestate_cur && greenstate);
  digitalWriteFast(blueout, pmtgatestate_cur && bluestate);

  // Switch PMT ON
  if(not(pmtgatestate_cur) && pmtgatestate_last) {
    // Open PMT gate
    digitalWriteFast(pmtgateout, LOW);
  }

  pmtgatestate_last = pmtgatestate_cur;
  
}
