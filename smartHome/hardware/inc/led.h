#ifndef _led_H_
#define _led_H_





typedef struct
{

	_Bool led_Status;

} led_INFO;

#define led_ON		1

#define led_OFF	0

extern led_INFO led_info;


void led_Init(void);

void led_Set(_Bool status);


#endif
