void Mux_setup() {
  pinMode(Mux_S0, OUTPUT);
  pinMode(Mux_S1, OUTPUT);
  pinMode(Mux_S2, OUTPUT);
  pinMode(Mux_S3, OUTPUT);
  Mux_SIG_setup();
}

void Mux_SIG_setup() {
  pinMode(Mux_SIG, INPUT);
}

void Mux_switch(int pin) {
  int s0 = bitRead(pin, 0);
  int s1 = bitRead(pin, 1);
  int s2 = bitRead(pin, 2);
  int s3 = bitRead(pin, 3);
  digitalWrite(Mux_S0, s0);
  digitalWrite(Mux_S1, s1);
  digitalWrite(Mux_S2, s2);
  digitalWrite(Mux_S3, s3);
}

void Mux_func(int pin) {
  Mux_SIG_setup();
  PID_autotune();
  switch (pin) {
    case  0:
      button_check(0, MuxButtonPin0, HeatingTime_0, PreHeatingTemp_0, AtuneTemp_0);
      Led_change(MuxGreLedPin0, GreLED_en[0], aTune_fin);
      PID0_Control();
      break;
    case  1:
      button_check(1, MuxButtonPin1, HeatingTime_1, PreHeatingTemp_1, AtuneTemp_1);
      Led_change(MuxGreLedPin1, GreLED_en[1], aTune_fin);
      PID1_Control();
      break;
    case  2:
      button_check(2, MuxButtonPin2, HeatingTime_2, PreHeatingTemp_2, AtuneTemp_2);
      Led_change(MuxGreLedPin2, GreLED_en[2], aTune_fin);
      PID2_Control();
      break;
    case  3:
      button_check(3, MuxButtonPin3, HeatingTime_3, PreHeatingTemp_3, AtuneTemp_3);
      Led_change(MuxGreLedPin3, GreLED_en[3], aTune_fin);
      PID3_Control();
      break;
  }
}

