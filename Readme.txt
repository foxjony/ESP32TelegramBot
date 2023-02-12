Простий Telegram BOT яак альтернатива MQTT на ESP32
https://www.youtube.com/watch?v=Gnf5DOrhnN4
https://github.com/MoonFox2006/TeleBot

Створити групу
(до групи можна додати інших зацікавлених у отриманні даних користувачів)

// "***_bot" (https://web.telegram.org/z/#***) (Bot)
const char BOT_KEY[] = "***";

// "***" (https://web.telegram.org/z/#-***) (Group)
constexpr int32_t CHAT_ID = -0;                     // "-0" Replace with -ID !

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
