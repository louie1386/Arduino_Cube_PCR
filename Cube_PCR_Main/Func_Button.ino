void Button_setup() {
  pinMode(Mux_SIG, INPUT);
}

bool button_read(int pin) {
  Button_setup();
  Mux_switch(pin);
  return (digitalRead(Mux_SIG));
}

void button_check_0() {
  button[0] = button_read(MuxButtonPin0);
  if (button[0] == true) {
    if (Heating_Begin[0] == false && Temp_steady[0] == true) {
      buzzer_once();
      LedRG[0] = false;
      HeatingTime_Counter[0] = HeatingTime_0;
      Tar[0] = PreHeatingTemp_0;
      Heating_Begin[0] = true;
    }
    button_disable_counter[0] = button_disable_delay;
  }
  else if (button[0] == false) {
    if (button_disable_counter[0])
      button_disable_counter[0]--;
    else {
      LedRG[0] = false;
      Heating_Begin[0] = false;
      HeatingTime_Counter[0] = (-1);
      if (aTune_en) {
        if (!aTune_fin)
          Tar[0] = AtuneTemp_0;
        else
          Tar[0] = PreHeatingTemp_0;
      }
      else
        Tar[0] = 0;
    }
  }
}

void button_check_1() {
  button[1] = button_read(MuxButtonPin1);
  if (button[1] == true) {
    if (Heating_Begin[1] == false && Temp_steady[1] == true) {
      buzzer_once();
      LedRG[1] = false;
      HeatingTime_Counter[1] = HeatingTime_1;
      Tar[1] = PreHeatingTemp_1;
      Heating_Begin[1] = true;
    }
    button_disable_counter[1] = button_disable_delay;
  }
  else if (button[1] == false) {
    if (button_disable_counter[1])
      button_disable_counter[1]--;
    else {
      LedRG[1] = false;
      Heating_Begin[1] = false;
      HeatingTime_Counter[1] = (-1);
      if (aTune_en) {
        if (!aTune_fin)
          Tar[1] = AtuneTemp_1;
        else
          Tar[1] = PreHeatingTemp_1;
      }
      else
        Tar[1] = 0;
    }
  }
}

void button_check_2() {
  button[2] = button_read(MuxButtonPin2);
  if (button[2] == true) {
    if (Heating_Begin[2] == false && Temp_steady[2] == true) {
      buzzer_once();
      LedRG[2] = false;
      HeatingTime_Counter[2] = HeatingTime_2;
      Tar[2] = PreHeatingTemp_2;
      Heating_Begin[2] = true;
    }
    button_disable_counter[2] = button_disable_delay;
  }
  else if (button[2] == false) {
    if (button_disable_counter[2])
      button_disable_counter[2]--;
    else {
      LedRG[2] = false;
      Heating_Begin[2] = false;
      HeatingTime_Counter[2] = (-1);
      if (aTune_en) {
        if (!aTune_fin)
          Tar[2] = AtuneTemp_2;
        else
          Tar[2] = PreHeatingTemp_2;
      }
      else
        Tar[2] = 0;
    }
  }
}

void button_check_3() {
  button[3] = button_read(MuxButtonPin3);
  if (button[3] == true) {
    if (Heating_Begin[3] == false && Temp_steady[3] == true) {
      buzzer_once();
      LedRG[3] = false;
      HeatingTime_Counter[3] = HeatingTime_3;
      Tar[3] = PreHeatingTemp_3;
      Heating_Begin[3] = true;
    }
    button_disable_counter[3] = button_disable_delay;
  }
  else if (button[3] == false) {
    if (button_disable_counter[3])
      button_disable_counter[3]--;
    else {
      LedRG[3] = false;
      Heating_Begin[3] = false;
      HeatingTime_Counter[3] = (-1);
      if (aTune_en) {
        if (!aTune_fin)
          Tar[3] = AtuneTemp_3;
        else
          Tar[3] = PreHeatingTemp_3;
      }
      else
        Tar[3] = 0;
    }
  }
}
