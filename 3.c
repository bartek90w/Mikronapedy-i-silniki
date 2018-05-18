#include <reg515.sfr>
#include <lcd.h>

_interrupt 0 void int_0(void);
void wait(int a);

int komutacja[4]={8,2,4,1};
int ruch=0, hamowanie=100; 
int l_imp=0;


void main()
{
	unsigned char znak;
	int liczba=0;
	lcd_init();
	IT0=1;
	EX0=1;
	EAL=1;
	while(1)
	{
		znak=get_kb();
		wait(20000);
		if(znak>='0' && znak<='9')
		{
			liczba=(10*liczba) + (znak - 48);
			out_char(znak);
			wait(20000);
		}

		if(znak=='e')
		{
			out_instr(0x01);
			l_imp=liczba;
			EAL=1;
			P1=4;
			wait(2500);
			P1=1;
			ruch=0;
			liczba=0;
		}
	}
}

void wait(int a)
{
	int i=0;
	for(i=0;i<a;i++)
	{
	}
}

_interrupt 0 void int_0(void)
{
	P1=komutacja[ruch];
	ruch++;
	wait(hamowanie);
	if(ruch>3)
	{
		ruch=0;
	}
	if(l_imp>0)
	{
		l_imp--;
	}
	if(l_imp<=100)
	{
		hamowanie+=2;
	}
	if(l_imp<=0)
	{
		EAL=0;
		hamowanie=100;
		ruch=0;
	}
}

