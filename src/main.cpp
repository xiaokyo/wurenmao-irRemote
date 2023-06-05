#include <header.h>

const uint16_t kIrLed = 14;
const uint16_t tipLedPin = 4;

char auth[] = "c67043f48092";
char ssid[] = "9-1-10";
char pswd[] = "qw123123";

const uint32_t kBaudRate = 115200;

const uint16_t kMinUnknownSize = 12;
const uint8_t kTolerancePercentage = kTolerance; //

IRsend irsend(kIrLed); // Set the GPIO to be used to sending the message.

// 新建组件对象
BlinkerButton btn_openkt((char *)"btn-openkt");
BlinkerButton btn_closekt((char *)"btn-closekt");
BlinkerButton btn_openfs((char *)"btn-openfs");
BlinkerButton btn_closefs((char *)"btn-closefs");
BlinkerButton btn_fsyt((char *)"btn-fsyt");

/** 闪一下灯 */
void blinblin()
{
  // 闪一下 LED
  digitalWrite(tipLedPin, HIGH);
  delay(100);
  digitalWrite(tipLedPin, LOW);
  delay(100);
  digitalWrite(tipLedPin, HIGH);
}

void dataRead(const String &data)
{
  BLINKER_LOG("Blinker readString: ", data);

  Blinker.vibrate();

  uint32_t BlinkerTime = millis();

  Blinker.print("millis", BlinkerTime);
}

// 发送红外信号
void send_ir(String name = "open_kongtiao")
{
  blinblin();
  // 打开空调
  uint16_t open_kongtiao[371] = {8940, 4476, 526, 574, 526, 576, 524, 600, 500, 576, 524, 576, 524, 1700, 526, 1704, 524, 600, 500, 600, 500, 600, 500, 600, 500, 1702, 524, 1700, 528, 1700, 526, 600, 500, 576, 524, 1702, 526, 1702, 526, 576, 524, 576, 524, 1700, 528, 574, 524, 576, 524, 576, 524, 1702, 526, 576, 524, 1700, 528, 576, 524, 600, 500, 600, 500, 574, 548, 578, 500, 576, 524, 1700, 526, 574, 526, 1700, 526, 600, 500, 576, 524, 576, 522, 1702, 526, 600, 500, 576, 546, 576, 500, 576, 524, 576, 524, 574, 526, 600, 500, 600, 500, 576, 524, 576, 546, 1678, 526, 600, 500, 576, 524, 1700, 526, 1700, 526, 574, 526, 576, 524, 600, 500, 600, 500, 576, 524, 576, 524, 1700, 548, 1678, 526, 600, 500, 1700, 526, 1702, 526, 600, 500, 576, 524, 1700, 526, 576, 524, 576, 524, 576, 524, 1700, 526, 600, 500, 600, 500, 600, 500, 600, 500, 576, 524, 576, 524, 600, 500, 576, 524, 574, 524, 576, 524, 576, 524, 576, 524, 576, 524, 600, 500, 576, 524, 576, 522, 600, 500, 600, 500, 598, 500, 576, 524, 576, 524, 574, 526, 576, 524, 600, 500, 600, 500, 574, 524, 576, 524, 576, 524, 574, 524, 574, 526, 576, 524, 600, 500, 576, 524, 574, 524, 576, 524, 576, 524, 576, 524, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 576, 522, 576, 524, 600, 500, 600, 500, 600, 500, 600, 500, 576, 524, 576, 524, 574, 526, 576, 524, 576, 524, 1700, 526, 1700, 528, 600, 500, 600, 500, 600, 500, 1700, 526, 576, 524, 600, 500, 1702, 526, 1702, 526, 1700, 526, 574, 524, 574, 526, 600, 500, 1700, 526, 1700, 526, 574, 526, 600, 500, 600, 500, 574, 526, 576, 524, 576, 524, 576, 524, 600, 500, 576, 524, 574, 548, 1678, 526, 1700, 526, 576, 524, 576, 524, 600, 500, 600, 500, 598, 500, 600, 500, 576, 532, 568, 524, 600, 500, 600, 500, 600, 500, 576, 528, 570, 524, 576, 524, 576, 524, 600, 500, 576, 524, 600, 500, 576, 524, 576, 524, 576, 546, 1678, 526, 600, 500, 1700, 526, 1700, 526, 600, 500, 1700, 528, 1700, 526, 1702, 526};

  // 关闭空调
  uint16_t close_kongtiao[371] = {8976, 4436, 562, 540, 560, 540, 560, 540, 560, 540, 560, 540, 560, 1666, 560, 1666, 560, 540, 560, 540, 558, 542, 558, 542, 556, 1668, 560, 1668, 558, 1668, 558, 542, 556, 542, 556, 1668, 558, 1668, 558, 542, 556, 544, 556, 1670, 556, 544, 556, 544, 554, 544, 556, 544, 556, 544, 556, 1670, 556, 544, 556, 544, 556, 544, 554, 544, 556, 544, 556, 544, 556, 1670, 556, 546, 554, 1670, 556, 546, 554, 544, 556, 544, 554, 1670, 556, 544, 554, 544, 556, 544, 554, 546, 554, 546, 554, 544, 556, 544, 554, 544, 554, 544, 556, 544, 556, 1670, 556, 544, 554, 544, 556, 1670, 556, 1670, 556, 544, 556, 544, 556, 546, 554, 544, 554, 544, 554, 544, 556, 1670, 556, 1670, 556, 544, 556, 1670, 556, 1670, 556, 544, 556, 544, 554, 1672, 556, 544, 554, 544, 556, 544, 554, 1670, 556, 544, 554, 546, 554, 544, 556, 544, 556, 544, 556, 544, 556, 544, 556, 544, 554, 544, 554, 544, 556, 544, 554, 544, 556, 544, 556, 544, 556, 544, 556, 544, 556, 544, 556, 544, 556, 544, 556, 544, 556, 544, 556, 544, 556, 544, 556, 544, 556, 542, 556, 544, 556, 544, 556, 544, 556, 542, 556, 544, 556, 542, 556, 544, 556, 542, 556, 544, 556, 544, 556, 542, 558, 542, 556, 544, 556, 542, 556, 544, 556, 542, 558, 542, 558, 542, 556, 542, 558, 544, 556, 542, 558, 542, 558, 540, 558, 542, 558, 540, 558, 542, 558, 540, 558, 540, 560, 540, 560, 1666, 560, 1666, 560, 540, 560, 540, 586, 514, 560, 1666, 562, 540, 560, 540, 560, 1666, 560, 1666, 560, 1666, 562, 540, 560, 540, 560, 540, 560, 1664, 562, 1666, 562, 538, 560, 538, 560, 540, 560, 540, 560, 538, 586, 512, 560, 540, 560, 538, 560, 540, 586, 1640, 562, 540, 560, 1664, 588, 514, 560, 538, 560, 1664, 562, 538, 562, 540, 586, 514, 560, 540, 586, 516, 558, 540, 560, 538, 560, 540, 560, 540, 560, 540, 560, 538, 560, 538, 560, 540, 562, 538, 560, 540, 584, 514, 588, 512, 586, 514, 560, 1666, 562, 1664, 588, 1640, 562, 1664, 562, 540, 560, 538, 588, 1638, 562, 1666, 562};

  // 打开风扇
  uint16_t open_fengshan[75] = {4512, 4486, 480, 1518, 478, 1518, 478, 1518, 504, 1494, 480, 1518, 478, 1518, 478, 2468, 480, 1518, 478, 1518, 478, 2466, 480, 1516, 480, 2466, 478, 1518, 478, 1518, 478, 2468, 478, 1520, 478, 1516, 4510, 4484, 480, 1516, 478, 1520, 480, 1516, 480, 1518, 478, 1518, 478, 1518, 478, 2412, 534, 1518, 480, 1518, 478, 2468, 504, 1494, 476, 2468, 480, 1516, 480, 1518, 478, 2468, 480, 1516, 478, 13992, 9040, 2296, 478};

  // 关闭风扇
  uint16_t close_fengshan[75] = {4520, 4476, 514, 1482, 514, 1484, 510, 1486, 512, 1484, 512, 1484, 514, 1484, 514, 2432, 512, 1486, 512, 1484, 512, 2434, 484, 1512, 510, 2436, 484, 1514, 484, 1512, 510, 2436, 484, 1514, 484, 1512, 4514, 4480, 482, 1514, 508, 1488, 484, 1512, 482, 1514, 506, 1490, 482, 1516, 482, 2464, 484, 1514, 482, 1514, 482, 2464, 480, 1516, 482, 2464, 482, 1516, 480, 1512, 484, 2396, 550, 1516, 478, 13992, 9040, 2298, 478};

  // 摇头
  uint16_t yaotou_fengshan[75] = {4548, 4448, 516, 1482, 512, 1484, 514, 1482, 516, 1482, 516, 1482, 514, 1482, 514, 2432, 514, 1484, 514, 1484, 514, 1482, 516, 1482, 512, 2434, 514, 2432, 490, 2458, 514, 1484, 514, 1482, 512, 1482, 4546, 4448, 516, 1480, 514, 1484, 514, 1482, 516, 1482, 486, 1510, 684, 1312, 518, 2366, 578, 1484, 512, 1486, 512, 1482, 514, 1484, 512, 2436, 516, 2432, 514, 2432, 514, 1486, 510, 1486, 514, 13956, 9048, 2292, 484};

  if (name == "open_kongtiao")
  {
    irsend.sendRaw(open_kongtiao, 371, 38); // Send a raw data capture at 38kHz.
  }
  else if (name == "close_kongtiao")
  {
    irsend.sendRaw(close_kongtiao, 371, 38); // Send a raw data capture at 38kHz.
  }
  else if (name == "open_fengshan")
  {
    irsend.sendRaw(open_fengshan, sizeof(open_fengshan) / sizeof(int), 38); // Send a raw data capture at 38kHz.
  }
  else if (name == "close_fengshan")
  {
    irsend.sendRaw(close_fengshan, sizeof(close_fengshan) / sizeof(int), 38); // Send a raw data capture at 38kHz.
  }
  else if (name == "yaotou_fengshan")
  {
    irsend.sendRaw(yaotou_fengshan, sizeof(yaotou_fengshan) / sizeof(int), 38); // Send a raw data capture at 38kHz.
  }
}

/** 空调控制 */
void open_kongtiao_callback(const String &state)
{
  send_ir("open_kongtiao");
}

void close_kongtiao_callback(const String &state)
{
  send_ir("close_kongtiao");
}

void open_fengshan_callback(const String &state)
{
  send_ir("open_fengshan");
}

void close_fengshan_callback(const String &state)
{
  send_ir("close_fengshan");
}

void yaotou_fengshan_callback(const String &state)
{
  send_ir("yaotou_fengshan");
}

// 小爱风扇控制
void miotPowerState(const String &state)
{
  BLINKER_LOG("need set power state: ", state);

  if (state == BLINKER_CMD_ON)
  {
    send_ir("open_fengshan");

    BlinkerMIOT.powerState("on");
    BlinkerMIOT.print();
  }
  else if (state == BLINKER_CMD_OFF)
  {
    send_ir("close_fengshan");

    BlinkerMIOT.powerState("off");
    BlinkerMIOT.print();
  }
}

// 水平摇头
void miotHSwingState(const String &state)
{
  BLINKER_LOG("need set HSwing state: ", state);
  // horizontal-swing

  if (state == BLINKER_CMD_ON)
  {
    send_ir("yaotou_fengshan");

    BlinkerMIOT.hswing("on");
    BlinkerMIOT.print();
  }
  else if (state == BLINKER_CMD_OFF)
  {
    send_ir("yaotou_fengshan");

    BlinkerMIOT.hswing("off");
    BlinkerMIOT.print();
  }
}

// 控制空调
void miotLevel(uint8_t level)
{
  BLINKER_LOG("need set level: ", level);
  // 0:AUTO MODE, 1-3 LEVEL
  if (level == 1)
  {
    send_ir("open_kongtiao");
  }
  else if (level == 2)
  {
    send_ir("close_kongtiao");
  }

  BlinkerMIOT.level(level);
  BlinkerMIOT.print();
}

void setup()
{
  // 初始化串口
  Serial.begin(115200);
  irsend.begin();

  // 初始化有LED的IO
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(tipLedPin, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(tipLedPin, LOW);
  // 初始化blinker
  Blinker.begin(auth, ssid, pswd);
  Blinker.attachData(dataRead);

  btn_openkt.attach(open_kongtiao_callback);
  btn_closekt.attach(close_kongtiao_callback);
  btn_openfs.attach(open_fengshan_callback);
  btn_closefs.attach(close_fengshan_callback);
  btn_fsyt.attach(yaotou_fengshan_callback);

  BlinkerMIOT.attachPowerState(miotPowerState);
  BlinkerMIOT.attachHSwing(miotHSwingState);
  BlinkerMIOT.attachLevel(miotLevel);
}

void loop()
{
  Blinker.run();
}
