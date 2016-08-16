void  TempIC_setup() {
  ADC3V3 = analogRead(AREF);
}

double TempIC_get(int pin) {
  double temp = 0, TempIC_base, TempIC_reso;
  ADC3V3 = analogRead(AREF);
  if (TempIC_Type == 0) {
    TempIC_base = TempIC_base_0;
    TempIC_reso = TempIC_reso_0;
  }
  else if (TempIC_Type == 1) {
    TempIC_base = TempIC_base_1;
    TempIC_reso = TempIC_reso_1;
  }
  temp = (double(analogRead(pin)) / ADC3V3 * 3250 - TempIC_base) / TempIC_reso;
  return temp;
}

double Temp_avg(int pin, int times, double diff) {
  double Max = 0, Min = 1000, buff, temp = 0;
  for (int i = 0; i < times; i++) {
    buff = TempIC_get(pin);
    Max = max(Max, buff);
    Min = min(Min, buff);
    temp += buff;
  }
  temp = (temp - Max - Min) / (times - 2);
  return (temp + diff);
}

bool  Temp_check(double Temp, double Tar, int chanel) {
  if (Temp >= (Tar - TempTarRange) && Temp <= (Tar + TempTarRange))
    return true;
  else
    return false;
}

