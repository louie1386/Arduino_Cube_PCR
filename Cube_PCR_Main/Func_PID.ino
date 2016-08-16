void PID_setup() {
  Temp[0] = Temp_avg(TIC0, SampleTimes, Temp_diff[0]);
  PID0.SetOutputLimits(0, 255);
  PID0.SetSampleTime(PIDSampleTime);
  PID0.SetMode(AUTOMATIC);
  PID1.SetOutputLimits(0, 255);
  PID1.SetSampleTime(PIDSampleTime);
  PID1.SetMode(AUTOMATIC);
  PID2.SetOutputLimits(0, 255);
  PID2.SetSampleTime(PIDSampleTime);
  PID2.SetMode(AUTOMATIC);
  PID3.SetOutputLimits(0, 255);
  PID3.SetSampleTime(PIDSampleTime);
  PID3.SetMode(AUTOMATIC);

  aTune.SetOutputStep(aTuneStep);
  aTune.SetControlType(aTuneMode);
  aTune.SetNoiseBand(aTuneNoise);
  aTune.SetLookbackSec((int)aTuneLookBack);
}

bool  PID_autotune() {
  if (Power_Delay == 0 && aTune_en == false) {
    aTune_en = true;
    if (Temp[0] > aTune_en_Temp) {
      for (int i = 0; i < 4; i++) {
        Kp[i] = Kp_0;
        Ki[i] = Ki_0;
        Kd[i] = Kd_0;
      }
      PID0.SetTunings(Kp[0], Ki[0], Kd[0]);
      PID1.SetTunings(Kp[1], Ki[1], Kd[1]);
      PID2.SetTunings(Kp[2], Ki[2], Kd[2]);
      PID3.SetTunings(Kp[3], Ki[3], Kd[3]);
      aTune_fin = true;
      Serial.println("Default PID!");
      aTune_Time = 0;
      return true;
    }
  }

  byte val = (aTune.Runtime());
  if (val == 1 && aTune_fin == false && aTune_en == true) {
    for (int i = 0; i < 4; i++) {
      Kp[i] = aTune.GetKp();
      Ki[i] = aTune.GetKi();
      Kd[i] = aTune.GetKd();
    }
    PID0.SetTunings(Kp[0], Ki[0], Kd[0]);
    PID1.SetTunings(Kp[1], Ki[1], Kd[1]);
    PID2.SetTunings(Kp[2], Ki[2], Kd[2]);
    PID3.SetTunings(Kp[3], Ki[3], Kd[3]);
    aTune_fin = true;
    Serial.print("Autotune completed! (");
    Serial.print(aTune_Time);
    Serial.println("sec)");
    aTune_Time = (-1);
    return true;
  }
  else
    return false;
}

void  PID0_Control() {
  Temp[0] = Temp_avg(TIC0, SampleTimes, Temp_diff[0]);
  if (!(PID_autotune()))
    PID0.Compute();

  if (Volt[0] < 0 || Volt[0] > 255)
    Volt[0] = 0;

  if (LedRG[0])
    Tar[0] = 0;

  if (Temp[0] >= MaxTemp || Temp[0] <= 0)
    Volt[0] = 0;
  analogWrite(Heater_0, Volt[0]);
}

void  PID1_Control() {
  Temp[1] = Temp_avg(TIC1, SampleTimes, Temp_diff[1]);
  PID1.Compute();

  if (Volt[1] < 0 || Volt[1] > 255)
    Volt[1] = 0;

  if (LedRG[1])
    Tar[1] = 0;

  if (Temp[1] >= MaxTemp || Temp[1] <= 0)
    Volt[1] = 0;
  analogWrite(Heater_1, Volt[1]);
}

void  PID2_Control() {
  Temp[2] = Temp_avg(TIC2, SampleTimes, Temp_diff[2]);
  PID2.Compute();

  if (Volt[2] < 0 || Volt[2] > 255)
    Volt[2] = 0;

  if (LedRG[2])
    Tar[2] = 0;

  if (Temp[2] >= MaxTemp || Temp[2] <= 0)
    Volt[2] = 0;
  analogWrite(Heater_2, Volt[2]);
}

void  PID3_Control() {
  Temp[3] = Temp_avg(TIC3, SampleTimes, Temp_diff[3]);
  PID3.Compute();

  if (Volt[3] < 0 || Volt[3] > 255)
    Volt[3] = 0;

  if (LedRG[3])
    Tar[3] = 0;

  if (Temp[3] >= MaxTemp || Temp[3] <= 0)
    Volt[3] = 0;
  analogWrite(Heater_3, Volt[3]);
}
