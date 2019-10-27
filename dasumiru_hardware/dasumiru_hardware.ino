// GPIO12にジャンパワイヤがつながったままだとESP32にプログラムを書き込みできない。
// 書き込むときは外してからやろう。

#include <Bounce2.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "config.h"
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

// ボタン関連
#define NUM_BUTTONS 3
const int BUTTON_PINS[NUM_BUTTONS] = {12, 14, 15};
Bounce *buttons = new Bounce[NUM_BUTTONS];
bool isDataSending = false;

// DFPlayerMini関連
HardwareSerial myHardwareSerial(2); // RX:16, TX:17
DFRobotDFPlayerMini myDFPlayer;
bool isSoundPlaying = false;
int maxVolume = 10;
int minVolume = 0;

// SoftPot関連
// 押さえてる状態の最小値
const int minimum = 50;

// 押さえてる状態の最大値
// ESP32でのanalogReadの最大値は4096になる
const int maximum = 4000;

// 離しているかどうかの閾値
const int threshold = 30;

// 状態管理用のフラグ
bool wasPressed = false;

// analogReadはADCピンのみ対応
const int sensorPin = 34;

// 関数群
void ConnectWiFi();
void printDetail(uint8_t type, int value);
void DFPlayerSetUp();
void ButtonsSetUp();
void OnButtonPressed(int pin);
void SoftPotRead();
void ChangeVolume(int softPotValue);
void ConnectAwsiot();

void setup()
{
  Serial.begin(115200);
  delay(100);
  ButtonsSetUp();
  DFPlayerSetUp();

  configTime(9 * 3600L, 0, "ntp.nict.jp", "time.google.com", "ntp.jst.mfeed.ad.jp");//NTPの設定
}

void loop()
{
  // MP3ファイルの再生が終わったら呼ばれる
  if (myDFPlayer.available())
  {
    printDetail(myDFPlayer.readType(), myDFPlayer.readType()); //Print the detail message from DFPlayer to handle different errors and states.
  }

  // ボタン監視
  for (int i = 0; i < NUM_BUTTONS; i++)
  {
    // Update the Bounce instance :
    buttons[i].update();

    if (buttons[i].fell())
    {
      OnButtonPressed(BUTTON_PINS[i]);
    }
  }

  // SoftPot監視
  SoftPotRead();
}

void SendData(char* s)
{
  char pubMessage[128];
  WiFiClientSecure httpsClient;
  PubSubClient mqttClient(httpsClient);

  struct tm timeInfo;//時刻を格納するオブジェクト
  char stime[20];//文字格納用

  httpsClient.setCACert(rootCA);
  httpsClient.setCertificate(certificate);
  httpsClient.setPrivateKey(privateKey);
  mqttClient.setServer(awsEndpoint, awsPort);

  // WiFi接続
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.println(WiFi.localIP());
  delay(1000);

  // 時刻取得
  getLocalTime(&timeInfo);//tmオブジェクトのtimeInfoに現在時刻を入れ込む
  sprintf(stime, "%04d/%02d/%02d %02d:%02d:%02d",
          timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday,
          timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);//人間が読める形式に変換

  Serial.println(stime);//時間をシリアルモニタへ出力

  // MQTT接続
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32";
    //clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (mqttClient.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying＿
      delay(5000);
    }
  }
  
  sprintf(pubMessage, "{\"time\": \"%s\", \"message\": \"%s\"}", stime, s);
  //sprintf(pubMessage, "{\"message\": \"%c\"}", s);

  Serial.println(pubMessage);
  
  mqttClient.publish(pubTopic, pubMessage);
  Serial.println("Published.");
  delay(100);
  mqttClient.disconnect();
  httpsClient.stop();
  WiFi.mode(WIFI_OFF);
  Serial.println("disconnect WiFi");
  Serial.flush();
  isDataSending = false;
}

void printDetail(uint8_t type, int value)
{
  switch (type)
  {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      isSoundPlaying = false;  // 追加。再生が終わったらフラグを下ろす。
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value)
      {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

void DFPlayerSetUp()
{
  myHardwareSerial.begin(9600);

  Serial.println();
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(myHardwareSerial)) {  //Use hardwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  // 25がMaxくらいでいい感じかも
  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
}

void ButtonsSetUp()
{
  for (int i = 0; i < NUM_BUTTONS; i++)
  {
    buttons[i].attach( BUTTON_PINS[i] , INPUT_PULLUP  );
    buttons[i].interval(10);
  }
}

void OnButtonPressed(int pin)
{
  if (pin == 12)  // 小
  {
    Serial.println("button12 pressed!");
    // データ送信中でなければ送信。
    if (!isDataSending)
    {
      isDataSending = true;
      SendData("small");
    } 
  }
  else if (pin == 14) // 大
  {
    Serial.println("button14 pressed!");
    if (!isDataSending)
    {
      isDataSending = true;
      SendData("big");
    } 
  }
  else // 擬音再生
  {
    Serial.println("button15 pressed!");
    // 擬音再生中でないなら擬音再生。
    if (!isSoundPlaying)
    {
      myDFPlayer.play(1);
      isSoundPlaying = true;
    }
  }
}

void SoftPotRead()
{
  int softPotValue = analogRead(sensorPin);
  
  bool isPressed;
  if (softPotValue < threshold)
  {
    isPressed = false;
  }
  else if (softPotValue >= minimum)
  {
    isPressed = true;
  }

  // ドラッグされている間音量調整
  if (wasPressed && isPressed)
    ChangeVolume(softPotValue);
  
  wasPressed = isPressed;
  delay(50);
}

void ChangeVolume(int softPotValue)
{
  int volume = map(softPotValue, minimum, maximum, minVolume, maxVolume);  
  volume = constrain(volume, minVolume, maxVolume);
  myDFPlayer.volume(volume);
}
