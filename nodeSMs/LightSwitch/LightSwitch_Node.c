#include "EncoderSM.h"
#include "ws2812_api.h"

repeating_timer_t timer;
bool TaskA(repeating_timer_t *rt);
uint response;
uint ledPattern;

#define PIXELS 120
#define LIGHT_INTENSITY 100

int main()
{

	stdio_init_all();
	EncoderSM_init();
	ws2812_api_init();

	// negative timeout means exact delay (rather than delay between callbacks)
	if (!add_repeating_timer_ms(-5, TaskA, NULL, &timer)) {
		printf("Failed to add timer\n");
		return 1;
	}

	printf("Hello GPIO IRQ\n");
	while (1)
	{
		if(response > 0)
		{
			ledPattern += ((response == 2) * (-1)) + ((response == 3) * (1u));
			ws2812_api_switchPattern(ledPattern, PIXELS, LIGHT_INTENSITY);
		}
	}
}

bool TaskA(repeating_timer_t *rt) 
{
	EncoderSM_run(&response);
	// printf("RunningTaskA\n");
    return true; // keep repeating
}