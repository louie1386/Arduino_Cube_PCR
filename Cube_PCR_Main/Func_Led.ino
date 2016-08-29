void Led_setup() {
  pinMode(Mux_SIG, OUTPUT);
  pinMode(ReadyLED, OUTPUT);
  digitalWrite(Mux_SIG, LOW);
}

void Led_change(int GLEDpin, bool RG, bool aTuneFin) {
  if (!RG)
    Mux_switch(GLEDpin);
  Led_setup();
  if (aTuneFin)
    digitalWrite(Mux_SIG, HIGH);
  else
    digitalWrite(Mux_SIG, LOW);
}

void Led_ON(int pin) {
  digitalWrite(pin, HIGH);
}

void Led_OFF(int pin) {
  digitalWrite(pin, LOW);
}

void ReadyLed_chk() {
  bool ReadyLED_en = true;
  int preheating_Temp[4] = {PreHeatingTemp_0, PreHeatingTemp_1, PreHeatingTemp_2, PreHeatingTemp_3};
  if (aTune_fin) {
    for (int i = 0; i < 4; i++) {
      if (button[i] == false && Temp[i] < (preheating_Temp[i] - TempTarRange)) {
        ReadyLED_en = false;
      }
    }
  }
  else
    ReadyLED_en = false;
  if (ReadyLED_en)
    Led_ON(ReadyLED);
}

