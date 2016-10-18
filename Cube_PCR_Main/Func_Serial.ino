void Serial_setup() {
  Serial.begin(250000);
  Serial.println("");
  Serial.print("Start/Reset (Version: ");
  Serial.print(Version);
  Serial.println(")");
}

void serial_log() {
  for (int i = 0; i < 4; i++) {
    Serial.print("Ch");
    Serial.print(i + 1);
    Serial.print(":[ ");
    serial_LogDoubleAlign(Temp[i]);
    Serial.print(" <");
    serial_LogDoubleAlign(Tar[i]);
    Serial.print(", ");
    serial_LogDoubleAlign(Temp_diff[i]);
    Serial.print(">, ");
    serial_LogDoubleAlign(Volt[i]);
    Serial.print("(byte-V)]--PID(");
    serial_LogDoubleAlign(Kp[i]);
    Serial.print(", ");
    serial_LogDoubleAlign(Ki[i]);
    Serial.print(", ");
    serial_LogDoubleAlign(Kd[i]);
    Serial.print(")--Heating Time(sec): ");
    serial_LogDoubleAlign(HeatingTime_Counter[i]);
    Serial.println(" sec");
  }
  Serial.print("Lower Temp: ");
  Serial.println(Temp[4]);
  Serial.print("Upper Temp: ");
  Serial.println(Temp[5]);
  Serial.println("");
}

void serial_LogDoubleAlign(double value) {
  if (value > 0)
  {
    if (value < 10)
      Serial.print("  ");
    else if (value < 100)
      Serial.print(" ");
  }
  Serial.print(value);
}

void serial_RXD() {
  while (Serial.available() > 0) {
    char RXD = Serial.read();
    if (RXD == 'p')
      LogPrint_en = true;
    else if (RXD == 'n')
      LogPrint_en = false;
    else if (RXD == 'd') {
      LogPrint_en = false;
      DiffWriteIn[diff_num] = true;
      Serial.print("Diff_");
      Serial.print(diff_num);
      Serial.println(" Write In(Write In Key 'c'):");
    }
    else if (RXD == 'c') {
      if (DiffWriteIn[diff_num]) {
        if (Negative)
          Temp_diff[diff_num] = diff_temp * (-1);
        else
          Temp_diff[diff_num] = diff_temp;
      }
      Serial.println("");
      Serial.print("-->WriteIn: ");
      Serial.println(Temp_diff[diff_num]);
      diff_temp = 0;
      logdeg = false;
      degnum = 0;
      Negative = false;
      DiffWriteIn[diff_num] = false;
      diff_num++;
      if (diff_num < 4) {
        DiffWriteIn[diff_num] = true;
        Serial.print("Diff_");
        Serial.print(diff_num);
        Serial.println(" Write In(Write In Key 'c'):");
      }
      else
        LogPrint_en = true;
    }
    else if (DiffWriteIn[0] == true || DiffWriteIn[1] == true || DiffWriteIn[2] == true || DiffWriteIn[3] == true) {
      Serial.print(RXD);
      if (RXD == '.')
        logdeg = true;
      else if (RXD == '-')
        Negative = true;
      else if (RXD <= 57 && RXD >= 48) {
        if (!logdeg)
          diff_temp = diff_temp * 10 + (RXD - 48);
        else if (logdeg) {
          double deg = double(RXD - 48) / 10;
          for (int i = 0; i < degnum; i++)
            deg = deg / 10;
          diff_temp = diff_temp + deg;
          degnum++;
        }
      }
    }
  }
}
