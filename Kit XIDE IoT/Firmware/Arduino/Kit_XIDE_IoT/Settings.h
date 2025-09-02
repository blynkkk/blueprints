
/*
 * Board configuration (see examples below).
 */

#if defined(USE_XC01_R5)

  #ifndef MIKROBUS_PWM
    #define MIKROBUS_PWM 5
  #endif
  #ifndef MIKROBUS_INT
    #define MIKROBUS_INT 7
  #endif
  #ifndef MIKROBUS_RX
    #define MIKROBUS_RX 9
  #endif
  #ifndef MIKROBUS_TX
    #define MIKROBUS_TX 10
  #endif
  #ifndef MIKROBUS_SDA
    #define MIKROBUS_SDA 12
  #endif
  #ifndef MIKROBUS_SCL
    #define MIKROBUS_SCL 13
  #endif
  #ifndef MIKROBUS_AN
    #define MIKROBUS_AN 4
  #endif
  #ifndef MIKROBUS_RST
    #define MIKROBUS_RST 15
  #endif
  #ifndef MIKROBUS_CS
    #define MIKROBUS_CS 6
  #endif
  #ifndef MIKROBUS_SCK
    #define MIKROBUS_SCK 8
  #endif
  #ifndef MIKROBUS_MISO
    #define MIKROBUS_MISO 18
  #endif
  #ifndef MIKROBUS_MOSI
    #define MIKROBUS_MOSI 17
  #endif
  #ifndef uSD_CS
    #define uSD_CS -1
  #endif
  #ifndef BOARD_LED
    #define BOARD_LED 16
  #endif
  #ifndef BOARD_BUTTON
    #define BOARD_BUTTON 0
  #endif

  #ifndef BOARD_BUTTON
    #define BOARD_BUTTON_PIN            0
  #else
    #define BOARD_BUTTON_PIN            BOARD_BUTTON
  #endif
  
  #define BOARD_BUTTON_ACTIVE_LOW     true

  #define BOARD_LED_PIN               BOARD_LED
  #define BOARD_LED_INVERSE           false
  #define BOARD_LED_BRIGHTNESS        64

#else

  #warning "Custom board configuration is used"

  #define BOARD_BUTTON_PIN            0                     // Pin where user button is attached
  #define BOARD_BUTTON_ACTIVE_LOW     true                  // true if button is "active-low"

  //#define BOARD_LED_PIN             4                     // Set LED pin - if you have a single-color LED attached
  //#define BOARD_LED_PIN_R           15                    // Set R,G,B pins - if your LED is PWM RGB
  //#define BOARD_LED_PIN_G           12
  //#define BOARD_LED_PIN_B           13
  //#define BOARD_LED_PIN_WS2812      4                     // Set if your LED is WS2812 RGB
  #define BOARD_LED_INVERSE           false                 // true if LED is common anode, false if common cathode
  #define BOARD_LED_BRIGHTNESS        64                    // 0..255 brightness control

#endif


/*
 * Advanced options
 */

#define BUTTON_HOLD_TIME_INDICATION   3000
#define BUTTON_HOLD_TIME_ACTION       10000
#define BUTTON_PRESS_TIME_ACTION      50

#define BOARD_PWM_MAX                 1023

#define BOARD_LEDC_CHANNEL_1          1
#define BOARD_LEDC_CHANNEL_2          2
#define BOARD_LEDC_CHANNEL_3          3
#define BOARD_LEDC_TIMER_BITS         10
#define BOARD_LEDC_BASE_FREQ          12000

#if !defined(CONFIG_DEVICE_PREFIX)
#define CONFIG_DEVICE_PREFIX          "Blynk"
#endif
#if !defined(CONFIG_AP_URL)
#define CONFIG_AP_URL                 "blynk.setup"
#endif
#if !defined(CONFIG_DEFAULT_SERVER)
#define CONFIG_DEFAULT_SERVER         "blynk.cloud"
#endif
#if !defined(CONFIG_DEFAULT_PORT)
#define CONFIG_DEFAULT_PORT           443
#endif

#define WIFI_CLOUD_MAX_RETRIES        500
#define WIFI_NET_CONNECT_TIMEOUT      50000
#define WIFI_CLOUD_CONNECT_TIMEOUT    50000
#define WIFI_AP_IP                    IPAddress(192, 168, 4, 1)
#define WIFI_AP_Subnet                IPAddress(255, 255, 255, 0)
//#define WIFI_CAPTIVE_PORTAL_ENABLE

//#define USE_TICKER
//#define USE_TIMER_ONE
//#define USE_TIMER_THREE
//#define USE_TIMER_FIVE
#define USE_PTHREAD

#define BLYNK_NO_DEFAULT_BANNER

#if defined(APP_DEBUG)
  #define DEBUG_PRINT(...)  BLYNK_LOG1(__VA_ARGS__)
  #define DEBUG_PRINTF(...) BLYNK_LOG(__VA_ARGS__)
#else
  #define DEBUG_PRINT(...)
  #define DEBUG_PRINTF(...)
#endif
