#include <WiFi.h>
#include <esp_now.h>
#include "deneyap.h"
#include <Deneyap_Servo.h>

#define ENA D8
#define ENB D0

#define IN1 D12
#define IN2 D13
#define IN3 D14
#define IN4 D9

#define SERVO_TABAN D1
#define SERVO_ANA_KOL D4
#define SERVO_ON_KOL SDA
#define SERVO_UC A0

Servo servoTaban;
Servo servoAnaKol;
Servo servoOnKol;
Servo servoUc;

int posTaban = 90;
int posAnaKol = 90;
int posOnKol = 90;
int posUc = 90;

int kolModu = 0;
int oncekiButon = 1;
unsigned long sonButonZamani = 0;

typedef struct {
  int driveX;
  int driveY;
  int armX;
  int armY;
  int armButton;
} KumandaVerisi;

KumandaVerisi veri;

const int MAX_HIZ = 255;

void solMotor(int hiz) {
  hiz = constrain(hiz, -255, 255);

  if (hiz > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    ledcWrite(0, hiz);
  } else if (hiz < 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    ledcWrite(0, -hiz);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    ledcWrite(0, 0);
  }
}

void sagMotor(int hiz) {
  hiz = constrain(hiz, -255, 255);

  if (hiz > 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    ledcWrite(1, hiz);
  } else if (hiz < 0) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    ledcWrite(1, -hiz);
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    ledcWrite(1, 0);
  }
}

void dur() {
  solMotor(0);
  sagMotor(0);
}

void ileri() {
  solMotor(MAX_HIZ);
  sagMotor(MAX_HIZ);
}

void geri() {
  solMotor(-MAX_HIZ);
  sagMotor(-MAX_HIZ);
}

void sag() {
  solMotor(MAX_HIZ);
  sagMotor(-MAX_HIZ);
}

void sol() {
  solMotor(-MAX_HIZ);
  sagMotor(MAX_HIZ);
}

void aracKontrol(int x, int y) {
  if (y > 6200) ileri();
  else if (y < 4200) geri();
  else if (x > 6200) sag();
  else if (x < 4200) sol();
  else dur();
}

void butonKontrol() {
  if (veri.armButton == 0 && oncekiButon == 1 && millis() - sonButonZamani > 400) {
    kolModu = !kolModu;
    sonButonZamani = millis();

    Serial.print("MOD DEGISTI: ");
    Serial.println(kolModu);
  }

  oncekiButon = veri.armButton;
}

void kolKontrol() {
  butonKontrol();

  if (kolModu == 0) {
    if (veri.armX > 6200) posTaban += 5;
    else if (veri.armX < 4200) posTaban -= 5;

    if (veri.armY > 6200) posAnaKol += 5;
    else if (veri.armY < 4200) posAnaKol -= 5;
  } 
  else {
    if (veri.armX > 6200) posOnKol += 5;
    else if (veri.armX < 4200) posOnKol -= 5;

    if (veri.armY > 6200) posUc = 150;
    else if (veri.armY < 4200) posUc = 40;
  }

  posTaban = constrain(posTaban, 0, 180);
  posAnaKol = constrain(posAnaKol, 10, 170);
  posOnKol = constrain(posOnKol, 10, 170);
  posUc = constrain(posUc, 30, 170);

  servoTaban.write(posTaban);
  servoAnaKol.write(posAnaKol);
  servoOnKol.write(posOnKol);
  servoUc.write(posUc);
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&veri, incomingData, sizeof(veri));

  aracKontrol(veri.driveX, veri.driveY);
  kolKontrol();

  Serial.print("DX:");
  Serial.print(veri.driveX);
  Serial.print(" DY:");
  Serial.print(veri.driveY);
  Serial.print(" AX:");
  Serial.print(veri.armX);
  Serial.print(" AY:");
  Serial.print(veri.armY);
  Serial.print(" SW:");
  Serial.print(veri.armButton);
  Serial.print(" MOD:");
  Serial.print(kolModu);
  Serial.print(" Servo:");
  Serial.print(posTaban);
  Serial.print(",");
  Serial.print(posAnaKol);
  Serial.print(",");
  Serial.print(posOnKol);
  Serial.print(",");
  Serial.println(posUc);
}

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  ledcSetup(0, 1000, 8);
  ledcSetup(1, 1000, 8);

  ledcAttachPin(ENA, 0);
  ledcAttachPin(ENB, 1);

  servoTaban.attach(SERVO_TABAN, 2, 50, 12);
  servoAnaKol.attach(SERVO_ANA_KOL, 3, 50, 12);
  servoOnKol.attach(SERVO_ON_KOL, 4, 50, 12);
  servoUc.attach(SERVO_UC, 5, 50, 12);

  servoTaban.write(posTaban);
  servoAnaKol.write(posAnaKol);
  servoOnKol.write(posOnKol);
  servoUc.write(posUc);

  dur();

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW baslatilamadi");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("Arac hazir");
}

void loop() {}
