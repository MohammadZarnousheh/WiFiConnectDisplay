این پروژه با استفاده از ماژول ESP8266 و نمایشگر OLED مدل SH1106 طراحی شده تا وضعیت اتصال به شبکه وای‌فای را به‌صورت گرافیکی و جذاب نمایش دهد. در هنگام راه‌اندازی، یک نوار پیشرفت (Progress Bar) روند اتصال را نمایش می‌دهد. پس از اتصال موفق، قدرت سیگنال وای‌فای (RSSI) روی نمایشگر نمایش داده می‌شود.
در صورتی که ارتباط وای‌فای به هر دلیلی قطع شود (مثلاً خاموش شدن مودم)، سیستم به‌صورت خودکار تلاش می‌کند مجدداً متصل شود و رابط لودینگ مجدداً نمایش داده می‌شود.

 اتصالات سخت‌افزاری:

نمایشگر OLED مدل SH1106 با ارتباط I2C:

SCL ➝ GPIO5 (D1 روی NodeMCU)

SDA ➝ GPIO4 (D2 روی NodeMCU)

VCC ➝ 3.3V

GND ➝ GND

در صورت استفاده از بردهای دیگر مانند Wemos D1 Mini یا بردهای غیر NodeMCU، شماره پایه‌ها را متناسب با پین‌آوت آن‌ها تنظیم کنید.



This project uses the ESP8266 module and an OLED display (SH1106) to graphically visualize the WiFi connection status. On boot, a progress bar shows the connection attempt. Once connected, the device displays the current WiFi signal strength (RSSI).
If WiFi is disconnected (e.g. router turned off), the system automatically attempts to reconnect, and the loading interface reappears.

🔌 Hardware Connections:

OLED SH1106 via I2C:

SCL ➝ GPIO5 (D1 on NodeMCU)

SDA ➝ GPIO4 (D2 on NodeMCU)

VCC ➝ 3.3V

GND ➝ GND

If you're using other boards like Wemos D1 Mini or bare ESP8266 modules, make sure to adapt the pins accordingly.
