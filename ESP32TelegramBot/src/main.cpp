// Простий Telegram BOT яак альтернатива MQTT на ESP32
// https://www.youtube.com/watch?v=Gnf5DOrhnN4
// https://github.com/MoonFox2006/TeleBot

/*
Створити групу
(до групи можна додати інших зацікавлених у отриманні даних користувачів)

"Taxi Lviv"
https://web.telegram.org/z/#-820758516

Групи можуть мати:
- До 200 000 учасників
- Постійна історія чату
- Публічні посилання, такі як t.me/title
- Адміни з різними правами

Щоб дізнатися API ключ для свого бота необхідно:
1. Перейти до системного бота @BotFather
2. Надіслати в діалог з @BotFather команду /mybots
3. Вибрати з клавіатури під повідомленням юзернейм потрібного робота
4. Вибрати з клавіатури під повідомленням пункт API Token
*/

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char WIFI_SSID[] = "***";
const char WIFI_PSWD[] = "***";

// "***_bot" (https://web.telegram.org/z/#***) (Bot)
const char BOT_KEY[] = "***";

// "***" (https://web.telegram.org/z/#-***) (Group)
constexpr int32_t CHAT_ID = -0;                     // "-0" Replace with -ID !

constexpr uint8_t LED_PIN = 0;
constexpr bool LED_LEVEL = LOW;
RTC_DATA_ATTR uint32_t boots = 0;

static bool telegramSendMessage(const char *message) {
  WiFiClientSecure client;
  HTTPClient https;
  bool result = false;
  client.setInsecure();
  if (https.begin(client, String("https://api.telegram.org/bot") + BOT_KEY + "/")) {
    String post;
    https.addHeader("Content-Type", "application/json");
    https.addHeader("Connection", "close");
    post = "{\"method\":\"sendMessage\",\"chat_id\":" + String(CHAT_ID) + ",\"text\":\"" + message + "\"}";
    Serial.println(">> " + post);
    result = https.POST(post) == 200;
    Serial.println("<< " + https.getString());
    https.end();
  }
  return result;
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, !LED_LEVEL);
  
  Serial.begin(115200);
  while (!Serial);

  ++boots;
  Serial.printf("\nBoard boots %u\r\n", boots);

  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PSWD);
  Serial.printf("Connecting to \"%s\"", WIFI_SSID);

  while (!WiFi.isConnected()) {
    digitalWrite(LED_PIN, LED_LEVEL);
    delay(10);
    digitalWrite(LED_PIN, !LED_LEVEL);
    delay(100);
    Serial.print('.');
  }

  Serial.print(" OK, IP: ");
  Serial.println(WiFi.localIP());

  char msg[48];
  snprintf(msg, sizeof(msg), "Board \\\"ESP32\\\" boots %u", boots);
  if (telegramSendMessage(msg)) {Serial.println("BOT OK");}
  else {Serial.println("BOT fail!");}
  Serial.flush();

  esp_sleep_enable_timer_wakeup(60000000);    // Sleep 60 s
  esp_deep_sleep_disable_rom_logging();
  esp_deep_sleep_start();
}

void loop() {}
