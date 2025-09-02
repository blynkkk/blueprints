#ifndef RGBLed_h
#define RGBLed_h

#include "Arduino.h"

#ifndef RGB_ANIMATION_BUFFER_SIZE
#define RGB_ANIMATION_BUFFER_SIZE 6
#endif

#if RGB_ANIMATION_BUFFER_SIZE < 2
#error "RGBLed: RGB_ANIMATION_BUFFER_SIZE must be at least size 2"
#endif

enum RBGAnimation
{
	RGB_STILL = 0,
	RGB_STROBE,
	RGB_FADE,
	RGB_FADE_IN,
	RGB_FADE_OUT,
	RGB_NO_ANIMATION
};

typedef void (*RGBLedColorCallback)(int red, int green, int blue);

struct RGB_t
{
	uint8_t r;
	uint8_t g;
	uint8_t b;

	bool operator==(const RGB_t &c) const
    {
        return (c.r == r) && (c.g == g) && (c.b == b);
    }
};

struct RGBLed_animation_t
{
	RBGAnimation animation_type;
	int animation_lenght;
	int animation_steps;
	int animation_time_per_color;
	bool loop_animation;
};

class RGBLed
{

public:
	RGBLed();

	bool begin(RGBLedColorCallback hardware_callback);

	void off();
	void on();

	void brightness(RGB_t rgb, int brightness);
	void brightness(int red, int green, int blue, int brightness);
	void brightness(int brightness);

	bool flash(RGB_t rgb, int duration, bool loop = true);
	bool flash(int red, int green, int blue, int duration, bool loop = true);

	void setColor(RGB_t rgb);
	void setColor(int red, int green, int blue);

	bool setDuration( int steps, int duration );
	bool setDuration( int duration );

	bool fadeOut(RGB_t rgb, int steps, int duration);
	bool fadeOut(int red, int green, int blue, int steps, int duration);

	bool fadeIn(RGB_t rgb, int steps, int duration);
	bool fadeIn(int red, int green, int blue, int steps, int duration);

	bool fadeInOut(RGB_t rgb, int steps, int duration);
	bool fadeInOut(int red, int green, int blue, int steps, int duration);

	bool strobe( RGB_t from, RGB_t to, int duration );
	bool strobe( RGB_t *cycle, size_t cycle_steps, int duration );

	bool crossFade(RGB_t from, RGB_t to, int steps, int duration);
	bool crossFade(RGB_t *cycle, size_t cycle_steps, int steps, int duration);
	
	bool crossFade(RGB_t from, RGB_t to, int duration);
	bool crossFade(RGB_t *cycle, size_t cycle_steps, int duration);
	
	void gradient(RGB_t rgbFrom, RGB_t rgbTo, int step);
	void gradient(int fromRed, int fromGreen, int fromBlue, int toRed, int toGreen, int toBlue, int step);
	
	static RGB_t RED;
	static RGB_t YELLOW;
	static RGB_t GREEN;
	static RGB_t CYAN;
	static RGB_t BLUE;
	static RGB_t MAGENTA;
	static RGB_t WHITE;
	static RGB_t BLACK;
	
	private:
	
	RGBLed_animation_t animation_config;
	RGBLedColorCallback hw_cb = nullptr;
	
	SemaphoreHandle_t hw_cb_semaphore = nullptr;
	TaskHandle_t rgb_animation_task_handle = nullptr;
	
	RGB_t p_animation_buffer[RGB_ANIMATION_BUFFER_SIZE + 1];
	
	int _last_red, _last_green, _last_blue;
	int _brightness;
	void color(int red, int green, int blue);
	void intensity(int red, int green, int blue, int brightness);
	void fade(int fromRed, int fromGreen, int fromBlue, int toRed, int toGreen, int toBlue, int steps, int duration);
	void stopTask();
	void crossFadeBlocking(RGB_t from, RGB_t to, int steps, int duration);

	static void xTaskAnimate(void *pvParameters);
};

#endif