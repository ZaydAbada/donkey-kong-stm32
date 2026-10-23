#include <stm32f031x6.h>
#include "display.h"
void initClock(void);
void initSysTick(void);
void SysTick_Handler(void);
void delay(volatile uint32_t dly);
void setupIO();
int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py);
void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber);
void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode);

void metalSetup();

volatile uint32_t milliseconds;

const uint16_t barrel[] = 
{
	0,0,31243,31243,31243,31243,31243,31243,0,0,0,31243,31243,57100,57100,57100,57100,31243,31243,0,31243,31243,57100,57100,23567,23567,57100,57100,31243,31243,31243,57100,57100,23567,23567,23567,23567,57100,57100,31243,31243,57100,23567,23567,23567,23567,23567,23567,57100,31243,31243,57100,23567,23567,23567,23567,23567,23567,57100,31243,31243,57100,57100,23567,23567,23567,23567,57100,57100,31243,31243,31243,57100,57100,23567,23567,57100,57100,31243,31243,0,31243,31243,57100,57100,57100,57100,31243,31243,0,0,0,31243,31243,31243,31243,31243,31243,0,0
};

const uint16_t metal[] =
{
	24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328,24328
};

const uint16_t metalX[] =
{
	0,20,40,60,80,100
};

const uint16_t metalY[] =
{
	155,150,145,120, 115, 110, 85,80,75,50
};

const uint16_t main_chara[] =
{
	37803,37803,37803,37803,37848,37848,37803,37803,37803,37848,0,37848,37803,37803,37848,37848,37848,37848,37803,37848,0,0,37848,37848,0,0,37848,37848,0,0,37848,33120,37848,37848,33120,37848,37848,0,33120,33120,0,0,0,0,33120,33120,0,0,0,33120,33120,33120,33120,0,37848,33120,0,0,33120,37848
};
const uint16_t main_charaJump[] =
{
	37803,37803,37803,37803,37848,37848,37803,37803,37803,37848,0,37848,37803,37803,37848,37848,37848,37848,37803,37848,0,0,37848,37848,33120,0,37848,37848,0,33120,33120,33120,33120,33120,33120,33120,0,0,33120,33120,0,0,0,0,33120,33120,0,0,0,33120,33120,33120,33120,0,37848,33120,0,0,33120,37848
};

const uint16_t deco1[]=
{
0,0,0,0,4,4,4,4,4,0,0,0,0,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,65415,65415,65415,248,65415,0,0,0,0,0,0,0,65415,65415,65415,65415,65415,8068,0,0,0,0,0,0,65415,65415,65415,4096,4096,0,0,0,0,0,0,0,0,65415,65415,65415,0,0,0,0,0,0,0,0,0,7936,7936,7936,0,0,0,0,0,0,0,0,7936,7936,65535,7936,0,0,0,0,0,0,0,0,7936,7936,65535,7936,7936,7936,7936,0,0,0,0,0,7936,7936,65535,65535,65535,65535,7936,0,0,0,0,0,7936,7936,7936,7936,7936,7936,7936,0,0,0,0,0,7936,7936,7936,7936,0,0,0,0,0,0,0,0,0,7936,65535,7936,0,0,0,0,0,0,0,0,0,7936,65535,7936,0,0,0,0,0,0,0,0,0,7936,65535,7936,0,0,0,0,0,0,0,0,0,7940,7940,7940,7940,0,0,0,
};
const uint16_t deco2[]= 
	{
0,0,0,0,0,4,4,4,4,4,0,0,0,0,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,65415,65415,65415,248,65415,0,0,0,0,0,0,0,65415,65415,65415,65415,65415,8068,0,0,0,0,0,0,65415,65415,65415,4096,4096,0,0,0,0,0,0,0,0,65415,65415,65415,0,0,0,0,0,0,0,0,7936,7936,7936,0,0,0,0,0,0,0,0,7936,7936,65535,7936,0,0,0,0,0,0,0,0,7936,7936,65535,7936,7936,7936,7936,0,0,0,0,0,7936,7936,65535,65535,65535,65535,7936,0,0,0,0,0,7936,7936,7936,7936,7936,7936,7936,0,0,0,0,0,7936,7936,7936,7936,0,0,0,0,0,0,0,0,0,40224,7936,65535,7936,0,0,0,0,0,0,0,40224,40224,7936,65535,7936,0,0,0,0,0,0,65315,40224,40224,7936,65535,40224,0,0,0,0,0,0,0,65315,0,65315,65315,65315,65315,0,0,
	};
const uint16_t deco3[]= 
{
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,4,4,4,4,0,0,0,0,0,0,0,4,4,4,4,4,4,0,0,0,0,7936,7936,4,4,4,4,4,4,7936,7936,0,0,65535,65535,4,4,4,4,4,4,65535,65535,0,0,7936,7936,4,4,4,4,4,4,7936,7936,0,0,0,0,0,4,4,4,4,0,0,0,0,0,0,0,0,0,24327,24327,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};
const uint16_t dg1[]=
{
	0,0,16142,16142,16142,16142,16142,16142,16142,16142,0,0,0,0,0,16142,16142,16142,16142,16142,16142,0,0,0,0,0,16142,16142,16142,16142,16142,16142,16142,16142,0,0,0,0,16142,16142,16142,1994,1994,16142,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,1994,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,1994,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,1994,16142,16142,0,0,0,0,16142,16142,16142,1994,1994,16142,16142,16142,0,0,0,0,16142,16142,16142,16142,16142,16142,16142,16142,0,0,0,0,16142,16142,16142,1994,1994,1994,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,16142,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,16142,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,1994,16142,16142,0,0,0,0,16142,16142,16142,1994,1994,1994,16142,16142,0,0,0,0,0,16142,16142,16142,16142,16142,16142,0,0,0,0,0,0,16142,16142,16142,16142,16142,16142,0,0,0,
};

int main()
{
	int hinverted = 0;
	int vinverted = 0;
	int toggle = 0;
	int hmoved = 0;
	int vmoved = 0;
	int falling = 0;
	uint16_t x = 10;
	uint16_t y = 0;
	uint16_t oldx = x;
	uint16_t oldy = y;
	initClock();
	initSysTick();
	setupIO();
	metalSetup();
	while(1)
	{
		if(y < 50 && y > 38) 
		{

		}
		else
		{
			falling = 1;
			y++;
			//fillRectangle(oldx,oldy,6,10,0);
			//putImage(x,y,6,10,main_chara,hinverted,0);
		}


		hmoved = vmoved = 0;
		hinverted = vinverted = 0;
		if ((GPIOB->IDR & (1 << 4))==0) // right pressed
		{					
			if (x < 110)
			{
				x = x + 1;
				hmoved = 1;
				hinverted=0;
			}						
		}
		if ((GPIOB->IDR & (1 << 5))==0) // left pressed
		{			
			
			if (x > 10)
			{
				x = x - 1;
				hmoved = 1;
				hinverted=1;
			}			
		}
		/*
		if ( (GPIOA->IDR & (1 << 11)) == 0) // down pressed
		{
			if (y < 140)
			{
				y = y + 1;			
				vmoved = 1;
				vinverted = 0;
			}
		}
		*/
		if ( (GPIOA->IDR & (1 << 8)) == 0) // up pressed
		{			
			if (y > 16)
			{
				y = y - 2;
				vmoved = 1;
				vinverted = 0;
			}
		}
		if ((vmoved) || (hmoved) || (falling))
		{
			// only redraw if there has been some movement (reduces flicker)
			fillRectangle(oldx,oldy,6,10,0);
			oldx = x;
			oldy = y;					
			if (hmoved)
			{
				if (toggle)
					putImage(x,y,6,10,main_chara,hinverted,0);
				else
					putImage(x,y,6,10,main_chara,hinverted,0);
				
				toggle = toggle ^ 1;
			}
			else
			{
				putImage(x,y,6,10,main_charaJump,0,vinverted);
			}
			/*
			// Now check for an overlap by checking to see if ANY of the 4 corners of deco are within the target area
			if (isInside(20,80,6,10,x,y) || isInside(20,80,6,10,x+6,y) || isInside(20,80,12,16,x,y+10) || isInside(20,80,6,10,x+6,y+10) )
			{
				printTextX2("GLUG!", 10, 20, RGBToWord(0xff,0xff,0), 0);
			}
			*/
		}		
		delay(50);
	}
	return 0;
}
void initSysTick(void)
{
	SysTick->LOAD = 48000;
	SysTick->CTRL = 7;
	SysTick->VAL = 10;
	__asm(" cpsie i "); // enable interrupts
}
void SysTick_Handler(void)
{
	milliseconds++;
}
void initClock(void)
{
// This is potentially a dangerous function as it could
// result in a system with an invalid clock signal - result: a stuck system
        // Set the PLL up
        // First ensure PLL is disabled
        RCC->CR &= ~(1u<<24);
        while( (RCC->CR & (1 <<25))); // wait for PLL ready to be cleared
        
// Warning here: if system clock is greater than 24MHz then wait-state(s) need to be
// inserted into Flash memory interface
				
        FLASH->ACR |= (1 << 0);
        FLASH->ACR &=~((1u << 2) | (1u<<1));
        // Turn on FLASH prefetch buffer
        FLASH->ACR |= (1 << 4);
        // set PLL multiplier to 12 (yielding 48MHz)
        RCC->CFGR &= ~((1u<<21) | (1u<<20) | (1u<<19) | (1u<<18));
        RCC->CFGR |= ((1<<21) | (1<<19) ); 

        // Need to limit ADC clock to below 14MHz so will change ADC prescaler to 4
        RCC->CFGR |= (1<<14);

        // and turn the PLL back on again
        RCC->CR |= (1<<24);        
        // set PLL as system clock source 
        RCC->CFGR |= (1<<1);
}
void delay(volatile uint32_t dly)
{
	uint32_t end_time = dly + milliseconds;
	while(milliseconds != end_time)
		__asm(" wfi "); // sleep
}

void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber)
{
	Port->PUPDR = Port->PUPDR &~(3u << BitNumber*2); // clear pull-up resistor bits
	Port->PUPDR = Port->PUPDR | (1u << BitNumber*2); // set pull-up bit
}
void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode)
{
	/*
	*/
	uint32_t mode_value = Port->MODER;
	Mode = Mode << (2 * BitNumber);
	mode_value = mode_value & ~(3u << (BitNumber * 2));
	mode_value = mode_value | Mode;
	Port->MODER = mode_value;
}
int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py)
{
	// checks to see if point px,py is within the rectange defined by x,y,w,h
	uint16_t x2,y2;
	x2 = x1+w;
	y2 = y1+h;
	int rvalue = 0;
	if ( (px >= x1) && (px <= x2))
	{
		// ok, x constraint met
		if ( (py >= y1) && (py <= y2))
			rvalue = 1;
	}
	return rvalue;
}

void setupIO()
{
	RCC->AHBENR |= (1 << 18) + (1 << 17); // enable Ports A and B
	display_begin();
	pinMode(GPIOB,4,0);
	pinMode(GPIOB,5,0);
	pinMode(GPIOA,8,0);
	pinMode(GPIOA,11,0);
	enablePullUp(GPIOB,4);
	enablePullUp(GPIOB,5);
	enablePullUp(GPIOA,11);
	enablePullUp(GPIOA,8);
}


void metalSetup()
{
	//bottom layer
	putImage(0,155, 20, 3, metal,0,0);
	putImage(20,155, 20, 3, metal,0,0);
	putImage(40,150, 20, 3, metal,0,0);
	putImage(60,150, 20, 3, metal,0,0);
	putImage(80,150, 20, 3, metal,0,0);
	putImage(100,145, 20, 3, metal,0,0);

	//second layer
	putImage(80,120, 20, 3, metal,0,0);
	putImage(60,120, 20, 3, metal,0,0);
	putImage(40,115, 20, 3, metal,0,0);
	putImage(20,115, 20, 3, metal,0,0);
	putImage(0,110, 20, 3, metal,0,0);

	//third layer
	putImage(20,85, 20, 3, metal,0,0);
	putImage(40,85, 20, 3, metal,0,0);
	putImage(60, 80,20, 3, metal,0,0);
	putImage(80,80, 20, 3, metal,0,0);
	putImage(100, 75, 20, 3, metal,0,0);

	//final layer
	putImage(80, 50, 20, 3, metal,0,0);
	putImage(60, 50, 20, 3, metal,0,0);
	putImage(40, 50, 20, 3, metal,0,0);
	putImage(20, 50, 20, 3, metal,0,0);
	putImage(0, 50, 20, 3, metal,0,0);

	//princesses
	putImage(40, 30, 20, 3, metal,0,0);

}