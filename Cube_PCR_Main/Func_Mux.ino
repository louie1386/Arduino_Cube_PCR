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
  switch (pin) {
    case  0:
      button_check_0();
      Led_change(MuxRedLedPin0, MuxGreLedPin0, LedRG[0], aTune_fin);
      PID0_Control();
      break;
    case  1:
      button_check_1();
      Led_change(MuxRedLedPin1, MuxGreLedPin1, LedRG[1], aTune_fin);
      PID1_Control();
      break;
    case  2:
      button_check_2();
      Led_change(MuxRedLedPin2, MuxGreLedPin2, LedRG[2], aTune_fin);
      PID2_Control();
      break;
    case  3:
      button_check_3();
      Led_change(MuxRedLedPin3, MuxGreLedPin3, LedRG[3], aTune_fin);
      PID3_Control();
      break;
  }
}

