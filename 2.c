#include <reg515.sfr>
#include <lcd.h>

_interrupt 5 void int_T2(void);
void wait(void);

int komutacja[3][8]={{8,2,4,1,8,2,4,1},{9,10,6,5,9,10,6,5},{8,10,2,6,4,5,1,9}};
int komut=0, ruch=0, kierunek=0; 
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
		if(znak=='g')
		{
			komut++;
			if(komut>2)
			{
				komut=0;
			}
			if(komut==0)
			{
				out_char('1');
				out_char('/');
				out_char('2');
				out_char(' ');
			}
			if(komut==1)
			{
				out_char('1');
				out_char('/');
				out_char('4');
				out_char(' ');
			}

			if(komut==2)
			{
				out_char('3');
				out_char('/');
				out_char('8');
				out_char(' ');
			}

		}
		if(znak=='l')
		{
			kierunek=0;
			out_char('l');
			out_char(' ');

		}
		if(znak=='p')
		{
			kierunek=1;
			out_char('p');
			out_char(' ');

		}
		if(znak=='d')
		{
			out_instr(0x01);
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
			if(liczba>=17 && liczba <=500)
			{
				l_imp=1000000/liczba;
				CRCL=0xFFFF-l_imp;
				CRCH=(0xFFFF-l_imp) >> 8;
			}
			liczba=0;
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
	P1=komutacja[komut][ruch];
	if(kierunek==0)
	{
		ruch++;
		if(ruch>7)
		{
			ruch=0;
		}
		TF2=0;	
	}
	else
	{
		ruch--;
		if(ruch<0)
		{
			ruch=7;
		}
		TF2=0;
	}
}

