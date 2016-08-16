void  heater_0_timeout() {
  buzzer_once();
  LedRG[0] = true;
  HeatingTime_Counter[0] = (-1);
}

void  heater_1_timeout() {
  buzzer_once();
  LedRG[1] = true;
  HeatingTime_Counter[1] = (-1);
}

void  heater_2_timeout() {
  buzzer_once();
  LedRG[2] = true;
  HeatingTime_Counter[2] = (-1);
}

void  heater_3_timeout() {
  buzzer_once();
  LedRG[3] = true;
  HeatingTime_Counter[3] = (-1);
}
