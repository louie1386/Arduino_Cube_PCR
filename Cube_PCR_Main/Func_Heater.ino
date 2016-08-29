void  heater_0_timeout() {
  buzzer_once();
  GreLED_en[0] = true;
  HeatingTime_Counter[0] = (-1);
}

void  heater_1_timeout() {
  buzzer_once();
  GreLED_en[1] = true;
  HeatingTime_Counter[1] = (-1);
}

void  heater_2_timeout() {
  buzzer_once();
  GreLED_en[2] = true;
  HeatingTime_Counter[2] = (-1);
}

void  heater_3_timeout() {
  buzzer_once();
  GreLED_en[3] = true;
  HeatingTime_Counter[3] = (-1);
}
