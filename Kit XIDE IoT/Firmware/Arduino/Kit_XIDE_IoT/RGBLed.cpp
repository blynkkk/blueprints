#include "Arduino.h"

#include "RGBLed.h"

RGB_t RGBLed::RED = {.r = 255, .g = 0, .b = 0};
RGB_t RGBLed::YELLOW = {.r = 255, .g = 255, .b = 0};
RGB_t RGBLed::GREEN = {.r = 0, .g = 255, .b = 0};
RGB_t RGBLed::CYAN = {.r = 0, .g = 255, .b = 255};
RGB_t RGBLed::BLUE = {.r = 0, .g = 0, .b = 255};
RGB_t RGBLed::MAGENTA = {.r = 255, .g = 0, .b = 255};
RGB_t RGBLed::WHITE = {.r = 255, .g = 255, .b = 255};
RGB_t RGBLed::BLACK = {.r = 0, .g = 0, .b = 0};

RGBLed::RGBLed() : _brightness(100), _last_red(0), _last_green(0), _last_blue(0)
{
	hw_cb_semaphore = xSemaphoreCreateMutex();
	xSemaphoreGive(hw_cb_semaphore);
}

bool RGBLed::begin(RGBLedColorCallback hardware_callback)
{
	if (hardware_callback == nullptr)
		return false;

	if (xSemaphoreTake(hw_cb_semaphore, 200) != pdTRUE)
		return false;

	hw_cb = hardware_callback;
	xSemaphoreGive(hw_cb_semaphore);

	if (rgb_animation_task_handle != nullptr)
	{
		vTaskDelete(rgb_animation_task_handle);
	}

	return true;
}

void RGBLed::off()
{
	stopTask();
	color(0, 0, 0);
}

void RGBLed::on()
{
	stopTask();
	xTaskCreate(xTaskAnimate, "rgb_tsk", 4096, (void *)this, 1, &rgb_animation_task_handle);
}

void RGBLed::brightness(RGB_t rgb, int brightness)
{
	stopTask();
	animation_config.animation_type = RGB_STILL;
	_brightness = brightness;
	p_animation_buffer[0] = rgb;
	intensity(rgb.r, rgb.g, rgb.b, brightness);
}

void RGBLed::brightness(int red, int green, int blue, int brightness)
{
	stopTask();
	animation_config.animation_type = RGB_STILL;
	_brightness = brightness;
	p_animation_buffer[0].r = red;
	p_animation_buffer[0].g = green;
	p_animation_buffer[0].b = blue;
	intensity(red, green, blue, brightness);
}

void RGBLed::brightness(int brightness)
{
	if (rgb_animation_task_handle != nullptr)
	{
		xSemaphoreTake(hw_cb_semaphore, portMAX_DELAY);
	}
	_brightness = brightness;
	if (rgb_animation_task_handle != nullptr)
	{
		xSemaphoreGive(hw_cb_semaphore);
	}
	intensity(_last_red, _last_green, _last_blue, _brightness);
}

void RGBLed::intensity(int red, int green, int blue, int brightness)
{
	if (brightness > 100)
		brightness = 100;
	if (brightness < 0)
		brightness = 0;

	_last_red = red;
	_last_green = green;
	_last_blue = blue;

	red = (red * brightness) / 100;
	green = (green * brightness) / 100;
	blue = (blue * brightness) / 100;
	color(red, green, blue);
}

bool RGBLed::flash(RGB_t rgb, int duration, bool loop)
{
	if ( duration < 1) {
		return false;
	}

	stopTask();

	p_animation_buffer[0].r = rgb.r;
	p_animation_buffer[0].g = rgb.g;
	p_animation_buffer[0].b = rgb.b;

	p_animation_buffer[1].r = 0;
	p_animation_buffer[1].g = 0;
	p_animation_buffer[1].b = 0;

	animation_config.animation_type = RGB_STROBE;
	animation_config.animation_lenght = 2;
	animation_config.animation_steps = 1;
	animation_config.animation_time_per_color = duration;
	animation_config.loop_animation = loop;

	return (xTaskCreate(xTaskAnimate, "rgb_tsk", 4096, (void *)this, 1, &rgb_animation_task_handle) == pdPASS);
}

bool RGBLed::flash(int red, int green, int blue, int duration, bool loop)
{
	RGB_t rgb;
	rgb.r = red;
	rgb.g = green;
	rgb.b = blue;

	return flash(rgb, duration, loop);
}

void RGBLed::setColor(RGB_t rgb)
{
	stopTask();
	animation_config.animation_type = RGB_STILL;
	p_animation_buffer[0] = rgb;
	intensity(rgb.r, rgb.g, rgb.b, _brightness);
}

void RGBLed::setColor(int red, int green, int blue)
{
	stopTask();
	animation_config.animation_type = RGB_STILL;
	p_animation_buffer[0].r = red;
	p_animation_buffer[0].g = green;
	p_animation_buffer[0].b = blue;
	intensity(red, green, blue, _brightness);
}

void RGBLed::color(int red, int green, int blue)
{
	if (red < 0)
	{
		red = 0;
	}
	if (red > 255)
	{
		red = 255;
	}

	if (green < 0)
	{
		green = 0;
	}
	if (green > 255)
	{
		green = 255;
	}

	if (blue < 0)
	{
		blue = 0;
	}
	if (blue > 255)
	{
		blue = 255;
	}

	if (hw_cb != nullptr)
	{
		xSemaphoreTake(hw_cb_semaphore, portMAX_DELAY);
		hw_cb(red, green, blue);
		xSemaphoreGive(hw_cb_semaphore);
	}
}

bool RGBLed::setDuration(int steps, int duration)
{
	switch (animation_config.animation_type)
	{
	case RGB_STILL:
		break;
	case RGB_STROBE:
		if ( duration < 1)
			return false;
		break;
	case RGB_FADE:
	case RGB_FADE_IN:
	case RGB_FADE_OUT:
		if ( (duration/steps) < 1 )
			return false;
		break;
	default:
		return false;
	}

	stopTask();

	animation_config.animation_time_per_color = duration;
	animation_config.animation_steps = steps;

	return (xTaskCreate(xTaskAnimate, "rgb_tsk", 4096, (void *)this, 1, &rgb_animation_task_handle) == pdPASS);
}

bool RGBLed::setDuration(int duration)
{
	int steps = duration / 100;
	return setDuration(steps, duration);
}

bool RGBLed::fadeOut(RGB_t rgb, int steps, int duration)
{
	if ( duration/steps < 1 )
		return false;

	stopTask();

	p_animation_buffer[0].r = rgb.r;
	p_animation_buffer[0].g = rgb.g;
	p_animation_buffer[0].b = rgb.b;

	p_animation_buffer[1].r = 0;
	p_animation_buffer[1].g = 0;
	p_animation_buffer[1].b = 0;

	animation_config.animation_type = RGB_FADE_OUT;
	animation_config.animation_lenght = 2;
	animation_config.animation_steps = steps;
	animation_config.animation_time_per_color = duration;
	animation_config.loop_animation = false;

	return (xTaskCreate(xTaskAnimate, "rgb_tsk", 4096, (void *)this, 1, &rgb_animation_task_handle) == pdPASS);
}

bool RGBLed::fadeOut(int red, int green, int blue, int steps, int duration)
{
	RGB_t rgb;
	rgb.r = red;
	rgb.g = green;
	rgb.b = blue;

	return fadeOut(rgb, steps, duration);
}

bool RGBLed::fadeIn(RGB_t rgb, int steps, int duration)
{
	if ( duration/steps < 1 )
		return false;

	stopTask();

	p_animation_buffer[0].r = 0;
	p_animation_buffer[0].g = 0;
	p_animation_buffer[0].b = 0;

	p_animation_buffer[1].r = rgb.r;
	p_animation_buffer[1].g = rgb.g;
	p_animation_buffer[1].b = rgb.b;

	animation_config.animation_type = RGB_FADE_IN;
	animation_config.animation_lenght = 2;
	animation_config.animation_steps = steps;
	animation_config.animation_time_per_color = duration;
	animation_config.loop_animation = false;

	return (xTaskCreate(xTaskAnimate, "rgb_tsk", 4096, (void *)this, 1, &rgb_animation_task_handle) == pdPASS);
}

bool RGBLed::fadeIn(int red, int green, int blue, int steps, int duration)
{
	RGB_t rgb;
	rgb.r = red;
	rgb.g = green;
	rgb.b = blue;

	return fadeIn(rgb, steps, duration);
}

bool RGBLed::fadeInOut(RGB_t rgb, int steps, int duration)
{
	if ( duration/steps < 1 )
		return false;

	stopTask();

	p_animation_buffer[0].r = 0;
	p_animation_buffer[0].g = 0;
	p_animation_buffer[0].b = 0;

	p_animation_buffer[1].r = rgb.r;
	p_animation_buffer[1].g = rgb.g;
	p_animation_buffer[1].b = rgb.b;

	animation_config.animation_type = RGB_FADE;
	animation_config.animation_lenght = 2;
	animation_config.animation_steps = steps;
	animation_config.animation_time_per_color = duration;
	animation_config.loop_animation = true;

	return (xTaskCreate(xTaskAnimate, "rgb_tsk", 4096, (void *)this, 1, &rgb_animation_task_handle) == pdPASS);
}

bool RGBLed::fadeInOut(int red, int green, int blue, int steps, int duration)
{
	RGB_t rgb;
	rgb.r = red;
	rgb.g = green;
	rgb.b = blue;

	return fadeInOut(rgb, steps, duration);
}

bool RGBLed::strobe(RGB_t from, RGB_t to, int duration)
{
	RGB_t cycle[2];

	cycle[0] = from;
	cycle[1] = to;

	return strobe(cycle, 2, duration);
}

bool RGBLed::strobe(RGB_t *cycle, size_t cycle_steps, int duration)
{
	if ( duration < 1)
		return false;

	if (cycle_steps > RGB_ANIMATION_BUFFER_SIZE)
		return false;

	stopTask();

	p_animation_buffer[0].r = cycle[cycle_steps - 1].r;
	p_animation_buffer[0].g = cycle[cycle_steps - 1].g;
	p_animation_buffer[0].b = cycle[cycle_steps - 1].b;

	for (size_t i = 0; i < cycle_steps; i++)
	{
		p_animation_buffer[i + 1].r = cycle[i].r;
		p_animation_buffer[i + 1].g = cycle[i].g;
		p_animation_buffer[i + 1].b = cycle[i].b;
	}

	animation_config.animation_type = RGB_STROBE;
	animation_config.animation_lenght = cycle_steps;
	animation_config.animation_steps = 1;
	animation_config.animation_time_per_color = duration;
	animation_config.loop_animation = true;

	return (xTaskCreate(xTaskAnimate, "rgb_tsk", 4096, (void *)this, 1, &rgb_animation_task_handle) == pdPASS);
}

void RGBLed::crossFadeBlocking(RGB_t from, RGB_t to, int steps, int duration)
{
	fade(from.r, from.g, from.b, to.r, to.g, to.b, steps, duration);
}

void RGBLed::fade(int fromRed, int fromGreen, int fromBlue, int toRed, int toGreen, int toBlue, int steps, int duration)
{
	// Determine per color change
	//   toValue - fromValue = deltaValue
	int deltaRed = toRed - fromRed;
	int deltaGreen = toGreen - fromGreen;
	int deltaBlue = toBlue - fromBlue;

	// Determine change per step per color
	//   deltaValue / steps
	//   Note: Forcing casting to floats to ensure smooth fades
	//         with large number of steps
	float changeRed = (float)deltaRed / (float)steps;
	float changeGreen = (float)deltaGreen / (float)steps;
	float changeBlue = (float)deltaBlue / (float)steps;

	// run through steps
	for (int i = 0; i <= steps; i++)
	{
		// Determine the new value for each color based on the step
		//  stepValue = fromValue + (changeValue * stepNumber)
		int stepRed = fromRed + (changeRed * i);
		int stepGreen = fromGreen + (changeGreen * i);
		int stepBlue = fromBlue + (changeBlue * i);

		// Make step change in color
		intensity(stepRed, stepGreen, stepBlue, _brightness);

		// delay based on total duration requested and number of steps
		if (i < steps)
		{
			delay((unsigned long)(duration / steps));
		}
	}
}

void RGBLed::xTaskAnimate(void *pvParameters)
{
	RGBLed *pvIncomingObj = (RGBLed *)pvParameters;

	RBGAnimation animation_type = pvIncomingObj->animation_config.animation_type;
	int animation_lenght = pvIncomingObj->animation_config.animation_lenght;
	int animation_timer_per_color = pvIncomingObj->animation_config.animation_time_per_color;
	int animation_steps = pvIncomingObj->animation_config.animation_steps;
	bool loop_animation = pvIncomingObj->animation_config.loop_animation;

	do
	{
		switch (animation_type)
		{
		case RGB_STILL:
			pvIncomingObj->intensity(pvIncomingObj->p_animation_buffer[0].r, pvIncomingObj->p_animation_buffer[0].g, pvIncomingObj->p_animation_buffer[0].b, pvIncomingObj->_brightness);
			loop_animation = false;
			break;
		case RGB_STROBE:
			for (int i = 1; i < animation_lenght; i++)
			{
				pvIncomingObj->crossFadeBlocking(pvIncomingObj->p_animation_buffer[i - 1], pvIncomingObj->p_animation_buffer[i], 1, animation_timer_per_color);
			}
			pvIncomingObj->crossFadeBlocking(pvIncomingObj->p_animation_buffer[animation_lenght - 1], pvIncomingObj->p_animation_buffer[0], 1, animation_timer_per_color);
			break;
		case RGB_FADE:
			for (int i = 1; i < animation_lenght; i++)
			{
				pvIncomingObj->crossFadeBlocking(pvIncomingObj->p_animation_buffer[i - 1], pvIncomingObj->p_animation_buffer[i], animation_steps, animation_timer_per_color);
			}
			pvIncomingObj->crossFadeBlocking(pvIncomingObj->p_animation_buffer[animation_lenght - 1], pvIncomingObj->p_animation_buffer[0], animation_steps, animation_timer_per_color);
			break;
		case RGB_FADE_IN:
			pvIncomingObj->crossFadeBlocking(pvIncomingObj->p_animation_buffer[0], pvIncomingObj->p_animation_buffer[1], animation_steps, animation_timer_per_color);
			break;
		case RGB_FADE_OUT:
			pvIncomingObj->crossFadeBlocking(pvIncomingObj->p_animation_buffer[0], pvIncomingObj->p_animation_buffer[1], animation_steps, animation_timer_per_color);
			break;
		default:
			loop_animation = false;
			break;
		}
		// Prevent watchdog activation due to too small animation steps
		delay( 10 );
	} while (loop_animation);

	pvIncomingObj->rgb_animation_task_handle = nullptr;
	vTaskDelete(NULL);
}

void RGBLed::stopTask()
{
	if (rgb_animation_task_handle != nullptr)
	{
		xSemaphoreTake(hw_cb_semaphore, pdTRUE);
		// Double check before deletion, if the task handler was deleted by something else
		if ( rgb_animation_task_handle != nullptr ) {
			vTaskDelete(rgb_animation_task_handle);
			rgb_animation_task_handle = nullptr;
		}
		xSemaphoreGive(hw_cb_semaphore);
	}
}

bool RGBLed::crossFade(RGB_t from, RGB_t to, int steps, int duration)
{
	RGB_t cycle[2];

	cycle[0] = from;
	cycle[1] = to;

	return crossFade(cycle, 2, steps, duration);
}

bool RGBLed::crossFade(RGB_t *cycle, size_t cycle_steps, int steps, int duration)
{
	if ( (duration/steps) < 1 )
		return false;

	if (cycle_steps > RGB_ANIMATION_BUFFER_SIZE)
		return false;

	stopTask();

	p_animation_buffer[0].r = cycle[cycle_steps - 1].r;
	p_animation_buffer[0].g = cycle[cycle_steps - 1].g;
	p_animation_buffer[0].b = cycle[cycle_steps - 1].b;

	for (size_t i = 0; i < cycle_steps; i++)
	{
		p_animation_buffer[i + 1].r = cycle[i].r;
		p_animation_buffer[i + 1].g = cycle[i].g;
		p_animation_buffer[i + 1].b = cycle[i].b;
	}

	animation_config.animation_type = RGB_FADE;
	animation_config.animation_lenght = cycle_steps;
	animation_config.animation_steps = steps;
	animation_config.animation_time_per_color = duration;
	animation_config.loop_animation = true;

	return (xTaskCreate(xTaskAnimate, "rgb_tsk", 4096, (void *)this, 1, &rgb_animation_task_handle) == pdPASS);
}

bool RGBLed::crossFade(RGB_t from, RGB_t to, int duration)
{
	int steps = 0;
	RGB_t cycle[2];

	cycle[0] = from;
	cycle[1] = to;

	steps = duration / 100;

	return crossFade(cycle, 2, steps, duration);
}

bool RGBLed::crossFade(RGB_t *cycle, size_t cycle_steps, int duration)
{
	int steps = 0;

	steps = duration / 100;

	return crossFade(cycle, cycle_steps, steps, duration);
}

void RGBLed::gradient(RGB_t rgbFrom, RGB_t rgbTo, int step)
{
	gradient(rgbFrom.r, rgbFrom.g, rgbFrom.b, rgbTo.r, rgbTo.g, rgbTo.b, step);
}

void RGBLed::gradient(int fromRed, int fromGreen, int fromBlue, int toRed, int toGreen, int toBlue, int step)
{
	stopTask();
	// Determine per color change
	//   toValue - fromValue = deltaValue
	int deltaRed = toRed - fromRed;
	int deltaGreen = toGreen - fromGreen;
	int deltaBlue = toBlue - fromBlue;

	// Determine change per step per color
	//   deltaValue / steps
	//   Note: Forcing casting to floats to ensure smooth fades
	//         with large number of steps
	float changeRed = (float)deltaRed / (float)255;
	float changeGreen = (float)deltaGreen / (float)255;
	float changeBlue = (float)deltaBlue / (float)255;

	// Determine the new value for each color based on the step
	//  stepValue = fromValue + (changeValue * stepNumber)
	int stepRed = fromRed + (changeRed * step);
	int stepGreen = fromGreen + (changeGreen * step);
	int stepBlue = fromBlue + (changeBlue * step);

	// Make step change in color
	intensity(stepRed, stepGreen, stepBlue, _brightness);
}