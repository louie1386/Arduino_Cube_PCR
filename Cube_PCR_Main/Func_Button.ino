void Button_setup() {
  pinMode(Mux_SIG, INPUT);
}

bool button_read(int pin) {
  Button_setup();
  Mux_switch(pin);
  return (digitalRead(Mux_SIG));
}

void button_check(int ch, int pin, int heatingTime, double preheatingTemp, double atuneTemp) {
  button[ch] = button_read(pin);
  if (button[ch] == true) {
    if (Heating_Begin[ch] == false) {
      buzzer_once();
      if (Temp_steady[ch] == true) {
        GreLED_en[ch] = false;
        HeatingTime_Counter[ch] = heatingTime;
        Tar[ch] = preheatingTemp;
        Heating_Begin[ch] = true;
        button_disable_counter[ch] = button_disable_delay;
      }
    }
  }
  else if (button[ch] == false) {
    if (button_disable_counter[ch])
      button_disable_counter[ch]--;
    else {
      GreLED_en[ch] = false;
      Heating_Begin[ch] = false;
      HeatingTime_Counter[ch] = (-1);
      if (aTune_en) {
        if (!aTune_fin)
          Tar[ch] = atuneTemp;
        else
          Tar[ch] = preheatingTemp;
      }
      else
        Tar[ch] = 0;
    }
  }
}
