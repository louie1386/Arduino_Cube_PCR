#include <PID_v1.h>
#include <PID_AutoTune_v0.h>
#include <Event.h>
#include <Timer.h>

/*  Version   修改內容
    1.00      初版
    1.01      修改試管插入音效條件
    1.02      修改AutoTune參數
    1.03      關閉AutoTune,固定PID值
    1.04      修改buzzer頻率，修改baudrate
    1.05      輸出溫度補正值
*/
#define Version         1.05

//Pin define-----------------
//Analog Pin
#define AREF            A0
#define TIC0            A1
#define TIC1            A2
#define TIC2            A3
#define TIC3            A4
#define TIC4            A5
#define TIC5            A6
#define AutoResetPin    A7

//Digital Pin(PWM)
#define Heater_0        3
#define Heater_1        5
#define Heater_2        6
#define Heater_3        9
#define Buzzer          10
#define Fan             11
#define ReadyLED        13

//Digital Pin
#define Mux_S0          2
#define Mux_S1          4
#define Mux_S2          7
#define Mux_S3          8
#define Mux_SIG         12

//Timer----------------------
#define MuxTime         2
#define LogTime         1000
#define secTime         1000

Timer timer;
int Timer_buzzer = (-1);

//Button---------------------
#define button_disable_delay  2

bool  button[4] = {false, false, false, false};
int   button_disable_counter[4] = {0, 0, 0, 0};

//Temp-----------------------
#define TempIC_Diff_0   6
#define TempIC_Diff_1   5
#define TempIC_Diff_2   7
#define TempIC_Diff_3   5

#define TempIC_Type     1
#define TempIC_base_0   500
#define TempIC_reso_0   10
#define TempIC_base_1   400
#define TempIC_reso_1   19.5

#define TempTarRange    5
#define SampleTimes     5
#define chkTime         5

int     ADC3V3 =          666;
int     Power_Delay =     2;
double  Temp[6] =         {0, 0, 0, 0, 0, 0};
double  Tar[4] =          {0, 0, 0, 0};
double  Temp_diff[4] =    {TempIC_Diff_0, TempIC_Diff_1, TempIC_Diff_2, TempIC_Diff_3};
bool    Temp_steady[4] =  {false, false, false, false};

//PID-----------------------
#define PIDSampleTime   100
#define PIDOutputLimit  255
#define aTune_well      0
#define aTune_mode      false

#define aKp   1000
#define aKi   0
#define aKd   0

#define dKp   200
#define dKi   20
#define dKd   0

//Well_0
#define Kp_0   dKp
#define Ki_0   dKi
#define Kd_0   dKd

//Well_1
#define Kp_1   dKp
#define Ki_1   dKi
#define Kd_1   dKd

//Well_2
#define Kp_2   dKp
#define Ki_2   dKi
#define Kd_2   dKd

//Well_3
#define Kp_3   dKp
#define Ki_3   dKi
#define Kd_3   dKd

#define aTuneStep       250
#define aTuneNoise      0.5
#define aTuneLookBack   3
#define aTuneMode       0

double        Volt[4] = {0, 0, 0, 0};
double        Kp[4] =   {aKp, aKp, aKp, aKp};
double        Ki[4] =   {aKi, aKi, aKi, aKi};
double        Kd[4] =   {aKd, aKd, aKd, aKd};

bool          aTune_en = false;
bool          aTune_fin = false;
int           aTune_Time = 0;

PID PID0(&Temp[0], &Volt[0], &Tar[0], Kp[0], Ki[0], Kd[0], DIRECT);
PID PID1(&Temp[1], &Volt[1], &Tar[1], Kp[1], Ki[1], Kd[1], DIRECT);
PID PID2(&Temp[2], &Volt[2], &Tar[2], Kp[2], Ki[2], Kd[2], DIRECT);
PID PID3(&Temp[3], &Volt[3], &Tar[3], Kp[3], Ki[3], Kd[3], DIRECT);
PID_ATune aTune(&Temp[aTune_well], &Volt[aTune_well]);

//Heater--------------------
//Default Setting
#define HeatingTime_Def       900   //PCR反應時間(含預熱時間)
#define PreHeatingTime_Def    60    //預熱時間
#define PreHeatingTemp_Def    120   //預熱溫度
#define HeatingTemp_Def       102   //PCR反應溫度

//Channel 1 Setting
#define HeatingTime_0       HeatingTime_Def   //PCR反應時間(含預熱時間)
#define PreHeatingTime_0    PreHeatingTime_Def    //預熱時間
#define PreHeatingTemp_0    PreHeatingTemp_Def   //預熱溫度
#define HeatingTemp_0       HeatingTemp_Def   //PCR反應溫度
#define ResponseTime_0      HeatingTime_0 - PreHeatingTime_0
#define AtuneTemp_0         HeatingTemp_0

//Channel 2 Setting
#define HeatingTime_1       HeatingTime_Def   //PCR反應時間(含預熱時間)
#define PreHeatingTime_1    PreHeatingTime_Def    //預熱時間
#define PreHeatingTemp_1    PreHeatingTemp_Def   //預熱溫度
#define HeatingTemp_1       HeatingTemp_Def   //PCR反應溫度
#define ResponseTime_1      HeatingTime_1 - PreHeatingTime_1
#define AtuneTemp_1         HeatingTemp_1

//Channel 3 Setting
#define HeatingTime_2       HeatingTime_Def   //PCR反應時間(含預熱時間)
#define PreHeatingTime_2    PreHeatingTime_Def    //預熱時間
#define PreHeatingTemp_2    PreHeatingTemp_Def   //預熱溫度
#define HeatingTemp_2       HeatingTemp_Def   //PCR反應溫度
#define ResponseTime_2      HeatingTime_2 - PreHeatingTime_2
#define AtuneTemp_2         HeatingTemp_2

//Channel 4 Setting
#define HeatingTime_3       HeatingTime_Def   //PCR反應時間(含預熱時間)
#define PreHeatingTime_3    PreHeatingTime_Def    //預熱時間
#define PreHeatingTemp_3    PreHeatingTemp_Def   //預熱溫度
#define HeatingTemp_3       HeatingTemp_Def   //PCR反應溫度
#define ResponseTime_3      HeatingTime_3 - PreHeatingTime_3
#define AtuneTemp_3         HeatingTemp_3

#define aTune_en_Temp       0    //可以啟動AutoTune的最高溫度
#define MaxTemp             135   //過熱關閉加熱器溫度

bool  Heating_Begin[4] = {false, false, false, false};
int   HeatingTime_Counter[4] = {(-1), (-1), (-1), (-1)};

//Buzzer--------------------
#define buzzer_Hz 4978
#define buzzer_ms 500

//Mux-----------------------
#define MuxButtonPin0 0
#define MuxButtonPin1 1
#define MuxButtonPin2 2
#define MuxButtonPin3 3

#define MuxGreLedPin0 12
#define MuxGreLedPin1 13
#define MuxGreLedPin2 14
#define MuxGreLedPin3 15

#define MuxFloatPin   4

int Mux_Pin_Num = 0;

//Led-----------------------
bool GreLED_en[4] = {false, false, false, false};

//Log-----------------------
bool    LogPrint_en = false;
bool    DiffWriteIn[4] = {0, 0, 0, 0};
bool    logdeg = false;
bool    Negative = false;
double  diff_temp = 0;
int     degnum = 0;
int     diff_num = 0;

//Main----------------------
void setup() {
  // put your setup code here, to run once:
  Fan_setup();
  Serial_setup();
  TempIC_setup();
  Buzzer_setup();
  Mux_setup();
  PID_setup();
  Timer_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  timer.update();
}
