#include <reg515.sfr>
#include <lcd.h>

_interrupt 5 void int_T2(void);
void wait(void);

int tab_ruch[6]={0xDE,0xDB,0xF9,0xED,0xE7,0xF6};
int tab_spraw[6]={3,1,5,4,6,2};
int ruch=0, kierunek=0, hallotron, j; 
unsigned int l_imp=0;


void main()
{
	unsigned char znak;
	unsigned int liczba=0;
	lcd_init();
	EAL=1;
	ET2=1;
	T2I0=1;
	T2R1=1;
	while(1)
	{
		znak=get_kb();
		wait();
		if(znak=='l')
		{
			kierunek=0;
			//out_char('l');
			//out_char(' ');

		}
		if(znak=='p')
		{
			kierunek=1;
			//out_char('p');
			//out_char(' ');

		}
		if(znak>='0' && znak<='9')
		{
			if(liczba==0)
			{
				//out_instr(0x01);
			}
			liczba=(10*liczba) + (znak - 48);
			out_char(znak);
			wait();
		}

		if(znak=='e')
		{
			//out_char(liczba);
			if(liczba>=100 && liczba <=500)
			{
				l_imp=1000000/liczba;
				CRCL=0xFFFF-l_imp;
				CRCH=(0xFFFF-l_imp) >> 8;
			}
			liczba=0;
			out_instr(0x01);
		}
	}
}

void wait(void)
{
	int i=0;
	for(i=0;i<20000;i++)
	{
	}
}

_interrupt 5 void int_T2(void)
{
	TF2=0;
	hallotron = P4 & 0x07;
	for(j=0;j<6;j++)
	{
		if(hallotron==tab_spraw[j])
		{
			ruch=j;
		}
	}

	if(kierunek==1)
	{
		if(ruch==5)
		{
			ruch=0;
			P1=tab_ruch[ruch];
		}
		else
		{
			P1=tab_ruch[ruch+1];
		}	
	}
	else
	{
		if(ruch==0)
		{
			ruch=5;
			P1=tab_ruch[ruch];
		}

		else
		{
			P1=tab_ruch[ruch-1];
		}	
	}
}

