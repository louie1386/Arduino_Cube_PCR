void Timer_setup() {
  timer.every(MuxTime, Timer_Mux);
  timer.every(LogTime, Timer_Log);
  timer.every(secTime, Timer_sec);
}

void  Timer_Mux() {
  Mux_func(Mux_Pin_Num);
  Mux_Pin_Num++;
  Mux_Pin_Num = Mux_Pin_Num % 4;
}

void  Timer_Log() {
  /*
    Mux_Pin_Num = 0;
    Mux_func(Mux_Pin_Num);
  */
  Led_OFF();
  serial_RXD();
  if (LogPrint_en)
    serial_log();
  Led_ON();
}

void Timer_sec() {
  if (aTune_fin) {
    Temp_steady[0] = Temp_check(Temp[0], Tar[0], 0);
    Temp_steady[1] = Temp_check(Temp[1], Tar[1], 1);
    Temp_steady[2] = Temp_check(Temp[2], Tar[2], 2);
    Temp_steady[3] = Temp_check(Temp[3], Tar[3], 3);
  }
  if (aTune_Time >= 0)
    aTune_Time++;

  if (HeatingTime_Counter[0] > 0)
    HeatingTime_Counter[0]--;
  if (HeatingTime_Counter[0] == ResponseTime_0)
    Tar[0] = HeatingTemp_0;
  else if (HeatingTime_Counter[0] == 0)
    heater_0_timeout();

  if (HeatingTime_Counter[1] > 0)
    HeatingTime_Counter[1]--;
  if (HeatingTime_Counter[1] == ResponseTime_1)
    Tar[1] = HeatingTemp_1;
  else if (HeatingTime_Counter[1] == 0)
    heater_1_timeout();

  if (HeatingTime_Counter[2] > 0)
    HeatingTime_Counter[2]--;
  if (HeatingTime_Counter[2] == ResponseTime_2)
    Tar[2] = HeatingTemp_2;
  else if (HeatingTime_Counter[2] == 0)
    heater_2_timeout();

  if (HeatingTime_Counter[3] > 0)
    HeatingTime_Counter[3]--;
  if (HeatingTime_Counter[3] == ResponseTime_3)
    Tar[3] = HeatingTemp_3;
  else if (HeatingTime_Counter[3] == 0)
    heater_3_timeout();

  if (Power_Delay)
    Power_Delay--;

  Temp[4] = Temp_avg(TIC4, SampleTimes, 0);
}

