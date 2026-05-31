#include <WiFi.h>
#include <esp_now.h>

#define DRIVE_X A0
#define DRIVE_Y A1

#define ARM_X A2
#define ARM_Y A3
#define ARM_SW D2

uint8_t aracMAC[] = {0x94, 0x3C, 0xC6, 0xDA, 0xF2, 0xA4};

typedef struct {
  int driveX;
  int driveY;
  int armX;
  int armY;
  int armButton;
} KumandaVerisi;

KumandaVerisi veri;
esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Gonderildi" : "Basarisiz");
}

void setup() {
  Serial.begin(115200);

  pinMode(ARM_SW, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW baslatilamadi");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, aracMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Peer eklenemedi");
    return;
  }

  Serial.println("Kumanda hazir");
}

void loop() {
  veri.driveX = analogRead(DRIVE_X);
  veri.driveY = analogRead(DRIVE_Y);

  veri.armX = analogRead(ARM_X);
  veri.armY = analogRead(ARM_Y);

  veri.armButton = digitalRead(ARM_SW);

  esp_now_send(aracMAC, (uint8_t *)&veri, sizeof(veri));

  Serial.print("DX: ");
  Serial.print(veri.driveX);
  Serial.print(" DY: ");
  Serial.print(veri.driveY);
  Serial.print(" AX: ");
  Serial.print(veri.armX);
  Serial.print(" AY: ");
  Serial.print(veri.armY);
  Serial.print(" SW: ");
  Serial.println(veri.armButton);

  delay(50);
}
