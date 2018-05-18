#include <reg515.sfr>
#include <lcd.h>

void wait();

void main()
{
	unsigned char znak;
	unsigned int liczba=0;
	lcd_init();
	while(1)
	{
		znak=get_kb();
		wait();
		if(znak>='0' && znak<='9')
		{
			if(liczba==0)
			{
				out_instr(0x01);
			}
			liczba=(10*liczba) + (znak - 48);
			out_char(znak);
		}

		if(znak=='e')
		{
			out_char(liczba);
			liczba=0;
		}
	}
}

void wait()
{
	int i=0;
	for(i=0;i<20000;i++)
	{
	}
}