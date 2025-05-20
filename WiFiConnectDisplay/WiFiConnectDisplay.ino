#include <ESP8266WiFi.h>
#include <Wire.h>
#include <U8g2lib.h>

#define WIFI_SSID     "YourSSID"
#define WIFI_PASSWORD "YourPassword"

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

int loadingPercent = 0;
bool wifiConnected = false;
bool showFailedOnce = false;
unsigned long lastUpdateTime = 0;

void setup() {
  u8g2.begin();
  u8g2.enableUTF8Print();
  connectToWiFi();
}

// --- حلقه اصلی ---
void loop() {
  handleWiFiConnection();  // بررسی وضعیت اتصال و اتصال مجدد

  if (!wifiConnected) {
    updateLoadingBar();
  }
}

// --- تابع اتصال به وای‌فای ---
void connectToWiFi() {
  WiFi.disconnect();  // برای اطمینان از اتصال جدید
  delay(500);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

// --- بررسی وضعیت وای‌فای و اتصال مجدد در صورت قطع ---
void handleWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    wifiConnected = false;
  } else if (!wifiConnected) {
    wifiConnected = true;
    loadingPercent = 100;
    drawWiFiInfo();  // نمایش اطلاعات اتصال
    delay(5000);
  }

  if (!wifiConnected && loadingPercent >= 100 && !showFailedOnce) {
    showFailedOnce = true;
    for (int i = loadingPercent; i >= 0; i--) {
      loadingPercent = i;
      drawLoadingBar(loadingPercent, "Connection Failed!");
      delay(10);
    }
    drawStatus("Connection Failed!");
    delay(2000);
    connectToWiFi();  // تلاش مجدد برای اتصال
    loadingPercent = 0;
    showFailedOnce = false;
  }
}

// --- آپدیت نوار لودینگ ---
void updateLoadingBar() {
  if (millis() - lastUpdateTime > 100 && loadingPercent < 100) {
    loadingPercent++;
    lastUpdateTime = millis();
  }

  drawLoadingBar(loadingPercent, ("Connecting to " + String(WIFI_SSID)).c_str());
}

// --- رسم نوار لودینگ ---
void drawLoadingBar(int percent, const char* msg) {
  int barX = 14;
  int barY = 28;
  int barW = 100;
  int barH = 10;
  int filledWidth = map(percent, 0, 100, 0, barW);

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_5x8_tr);
    int msgWidth = u8g2.getStrWidth(msg);
    u8g2.drawStr((128 - msgWidth) / 2, 14, msg);

    u8g2.drawFrame(barX - 1, barY - 1, barW + 2, barH + 2);
    u8g2.drawBox(barX, barY, filledWidth, barH);

    char percentStr[10];
    sprintf(percentStr, "%d%%", percent);
    u8g2.setFont(u8g2_font_6x12_tr);
    u8g2.drawStr((128 - u8g2.getStrWidth(percentStr)) / 2, 55, percentStr);

  } while (u8g2.nextPage());
}

// --- نمایش پیغام ساده ---
void drawStatus(const char* msg) {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x10_tr);
    u8g2.drawStr((128 - u8g2.getStrWidth(msg)) / 2, 30, msg);
  } while (u8g2.nextPage());
}

// --- نمایش اطلاعات وای‌فای پس از اتصال ---
void drawWiFiInfo() {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x10_tr);
    String ssid = WiFi.SSID();
    int rssi = WiFi.RSSI();

    u8g2.drawStr(0, 14, "Connected to:");
    u8g2.drawStr(0, 28, ssid.c_str());

    char rssiStr[20];
    sprintf(rssiStr, "Signal: %d dBm", rssi);
    u8g2.drawStr(0, 44, rssiStr);

  } while (u8g2.nextPage());
}
