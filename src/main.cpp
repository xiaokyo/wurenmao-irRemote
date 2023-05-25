#include <header.h>

const uint16_t kIrLed = 14;
const uint16_t kRecvPin = 5;
const uint16_t recvLedPin = 15;

char auth[] = "c67043f48092";

const uint32_t kBaudRate = 115200;
const uint16_t kCaptureBufferSize = 1024;

const uint8_t kTimeout = 50;

const uint16_t kMinUnknownSize = 12;
const uint8_t kTolerancePercentage = kTolerance; //

IRsend irsend(kIrLed); // Set the GPIO to be used to sending the message.
IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
decode_results results;

// 新建组件对象
BlinkerButton Button1((char *)"btn-abc");
BlinkerButton btn_openkt((char *)"btn-openkt");
BlinkerButton btn_closekt((char *)"btn-closekt");
BlinkerButton btn_openfs((char *)"btn-openfs");
BlinkerButton btn_closefs((char *)"btn-closefs");
BlinkerButton btn_fsyt((char *)"btn-fsyt");

String mode = "send"; // recv, send

/** 闪一下灯 */
void blinblin()
{
  // 闪一下 LED
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
}

void dataRead(const String &data)
{
  BLINKER_LOG("Blinker readString: ", data);

  Blinker.vibrate();

  uint32_t BlinkerTime = millis();

  Blinker.print("millis", BlinkerTime);
}

// 按下按键即会执行该函数
void button1_callback(const String &state)
{
  BLINKER_LOG("get button state: ", state);
  blinblin();
  mode = mode == "send" ? "recv" : "send";
}

// 发送红外信号
void send_ir(String name = "open_kongtiao")
{
  blinblin();
  // 打开空调
  uint16_t open_kongtiao[371] = {8962, 4442, 554, 546, 552, 546, 552, 546, 552, 550, 550, 546, 554, 1670, 554, 1670, 552, 548, 554, 546, 552, 546, 552, 546, 554, 1672, 554, 1672, 554, 1672, 554, 546, 552, 546, 552, 1672, 554, 1670, 554, 546, 554, 546, 552, 1670, 554, 546, 552, 546, 552, 546, 552, 1670, 554, 546, 554, 1672, 554, 546, 554, 546, 554, 546, 552, 548, 552, 546, 552, 1672, 554, 1672, 554, 1670, 554, 1670, 554, 1672, 554, 1670, 554, 1670, 554, 1672, 554, 546, 552, 546, 554, 546, 552, 548, 552, 546, 554, 546, 554, 546, 552, 546, 552, 546, 554, 546, 552, 1672, 554, 1670, 554, 1672, 554, 1670, 554, 546, 552, 546, 552, 546, 552, 546, 552, 546, 552, 546, 552, 546, 554, 1672, 554, 1670, 554, 546, 552, 546, 554, 546, 552, 546, 552, 546, 554, 1672, 554, 1670, 558, 1668, 552, 1672, 554, 548, 552, 546, 552, 546, 554, 546, 552, 546, 554, 546, 552, 546, 552, 546, 552, 546, 552, 546, 554, 546, 552, 546, 552, 546, 552, 546, 552, 546, 552, 546, 552, 546, 552, 546, 552, 546, 552, 546, 552, 546, 554, 544, 554, 546, 552, 546, 552, 548, 552, 546, 552, 546, 554, 546, 554, 546, 552, 546, 552, 546, 554, 546, 552, 546, 552, 546, 552, 546, 552, 546, 554, 546, 552, 546, 552, 546, 552, 546, 552, 546, 552, 546, 552, 546, 552, 546, 554, 546, 552, 546, 552, 546, 552, 546, 554, 546, 552, 546, 552, 546, 552, 548, 552, 548, 552, 546, 552, 546, 552, 1670, 554, 1672, 554, 546, 552, 546, 554, 546, 554, 1672, 554, 546, 554, 546, 552, 1672, 554, 1672, 554, 546, 552, 1672, 554, 546, 552, 546, 552, 1672, 554, 1670, 554, 546, 554, 546, 554, 546, 552, 546, 552, 546, 554, 546, 552, 546, 552, 546, 552, 546, 554, 546, 552, 1672, 554, 1672, 554, 546, 552, 546, 552, 546, 552, 546, 552, 546, 552, 548, 552, 546, 552, 546, 554, 544, 554, 546, 552, 546, 552, 546, 552, 546, 554, 546, 552, 546, 554, 546, 552, 546, 554, 546, 552, 546, 552, 546, 552, 546, 554, 546, 552, 546, 554, 1670, 554, 546, 554, 546, 552, 1672, 554, 546, 552, 546, 552};

  // 关闭空调
  uint16_t close_kongtiao[371] = {8994, 4416, 576, 522, 576, 520, 576, 520, 576, 522, 576, 522, 574, 1646, 576, 1646, 576, 522, 576, 522, 576, 522, 576, 522, 576, 1646, 576, 1646, 576, 1646, 576, 522, 576, 522, 574, 1648, 574, 1646, 576, 522, 576, 522, 576, 1646, 574, 522, 574, 522, 576, 522, 576, 522, 574, 522, 576, 522, 576, 522, 576, 1646, 574, 522, 576, 522, 576, 520, 576, 522, 576, 1646, 574, 522, 576, 1646, 574, 522, 576, 522, 576, 522, 576, 1646, 576, 522, 574, 522, 576, 522, 574, 524, 574, 522, 576, 522, 576, 522, 574, 522, 576, 522, 576, 522, 576, 1646, 576, 522, 576, 522, 574, 1648, 574, 1648, 574, 522, 574, 524, 574, 522, 574, 522, 574, 524, 574, 524, 574, 522, 574, 1648, 574, 522, 574, 1648, 574, 1648, 574, 522, 574, 1648, 574, 1648, 574, 524, 574, 522, 574, 1648, 574, 522, 574, 522, 574, 522, 574, 522, 574, 524, 574, 524, 574, 524, 574, 524, 574, 524, 574, 524, 574, 522, 574, 522, 574, 524, 574, 524, 574, 524, 574, 522, 574, 524, 572, 548, 550, 548, 548, 548, 548, 548, 548, 550, 548, 524, 574, 548, 550, 548, 550, 548, 550, 548, 550, 548, 548, 550, 548, 548, 548, 548, 550, 548, 550, 548, 548, 548, 548, 550, 548, 548, 548, 548, 548, 550, 548, 550, 548, 548, 548, 548, 548, 548, 548, 548, 548, 550, 548, 548, 548, 548, 548, 548, 548, 548, 548, 548, 548, 550, 548, 550, 548, 548, 548, 548, 548, 550, 548, 550, 548, 1676, 546, 548, 548, 1674, 548, 548, 548, 550, 546, 1674, 548, 550, 548, 550, 548, 1674, 548, 1674, 524, 1698, 524, 572, 548, 550, 524, 572, 524, 1698, 524, 1698, 548, 550, 524, 574, 524, 572, 524, 574, 522, 574, 524, 574, 522, 574, 524, 574, 524, 574, 524, 1698, 524, 574, 524, 1698, 522, 574, 524, 572, 524, 1698, 524, 574, 524, 574, 524, 572, 524, 574, 524, 574, 524, 574, 524, 574, 524, 574, 524, 574, 522, 574, 522, 574, 524, 574, 524, 574, 524, 574, 524, 574, 524, 574, 524, 574, 522, 574, 522, 1700, 522, 574, 522, 574, 522, 574, 522, 1700, 522, 1700, 522, 1700, 522, 576, 522}; // UNKNOWN 4227CEF8

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
    irsend.sendRaw(open_fengshan, 76, 38); // Send a raw data capture at 38kHz.
  }
  else if (name == "close_fengshan")
  {
    irsend.sendRaw(close_fengshan, 76, 38); // Send a raw data capture at 38kHz.
  }
  else if (name == "yaotou_fengshan")
  {
    irsend.sendRaw(yaotou_fengshan, 76, 38); // Send a raw data capture at 38kHz.
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
  irrecv.enableIRIn(); // Start the receiver

#if defined(BLINKER_PRINT)
  BLINKER_DEBUG.stream(BLINKER_PRINT);
  BLINKER_DEBUG.debugAll();
#endif

  // 初始化有LED的IO
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(recvLedPin, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(recvLedPin, LOW);
  // 初始化blinker
  Blinker.begin(auth);
  Blinker.attachData(dataRead);
  Button1.attach(button1_callback);

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
  if (mode == "recv")
  {
    if (irrecv.decode(&results))
    {
      blinblin();
      // Display a crude timestamp.
      uint32_t now = millis();
      Serial.printf(D_STR_TIMESTAMP " : %06u.%03u\n", now / 1000, now % 1000);
      // Check if we got an IR message that was to big for our capture buffer.
      if (results.overflow)
        Serial.printf(D_WARN_BUFFERFULL "\n", kCaptureBufferSize);
      // Display the library version the message was captured with.
      Serial.println(D_STR_LIBRARY "   : v" _IRREMOTEESP8266_VERSION_STR "\n");
      // Display the tolerance percentage if it has been change from the default.
      if (kTolerancePercentage != kTolerance)
        Serial.printf(D_STR_TOLERANCE " : %d%%\n", kTolerancePercentage);
      // Display the basic output of what we found.
      Serial.print(resultToHumanReadableBasic(&results));
      // Display any extra A/C info if we have it.
      String description = IRAcUtils::resultAcToString(&results);
      if (description.length())
        Serial.println(D_STR_MESGDESC ": " + description);
      yield(); // Feed the WDT as the text output can take a while to print.
#if LEGACY_TIMING_INFO
      // Output legacy RAW timing info of the result.
      Serial.println(resultToTimingInfo(&results));
      yield(); // Feed the WDT (again)
#endif         // LEGACY_TIMING_INFO
      // Output the results as source code
      Serial.println(resultToSourceCode(&results));
      Serial.println(); // Blank line between entries
      yield();
    }
  }
}
