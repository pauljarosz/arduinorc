/*
  MIT License

  Copyright (c) 2016 Paul Jarosz
  Geekout Labs www.geekoutlabs.com

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

/*
 * Read RC receiver PWM signals
 * 
 * Developed for Arduino Nano to control LED lights.  I used interrupts so we dont need to
 * constantly poll the hardware and we get more accurate timings.  Also, by not polling, we
 * get to do other stuff, even if it takes a while to process.
*/
#define RC_PIN 2

unsigned long time = 0;
unsigned long startTime;

//#define _PRODUCTION_

void setup() {
#ifndef _PRODUCTION_
  // Start the serial out (not need one you have timings)
  Serial.begin(115200);
  Serial.println();
#endif

  // call interrupt on every pin state change
  attachInterrupt(digitalPinToInterrupt(RC_PIN), pinChangeIsr, CHANGE);
}

void loop() {
#ifndef _PRODUCTION_
  // serial outs only used to get timings, comment out on production code
  Serial.print("time:\t");
  Serial.print(time, DEC);
  Serial.println();
#endif

  if (time < 1000) {
    // do something
  } else if (time < 1200) {
    // do something else
  }
}

/*
 * the pin changed, so check the status.  If pin went high, get current time, if it went low, get the duration
 */
void pinChangeIsr()
{
  if (digitalRead(RC_PIN)) { // High
    startTime = micros();
  } else {  // pin went low so get duration
    time = micros() - startTime;
  }
}
