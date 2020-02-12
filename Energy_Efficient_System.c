#include<reg51.h>
#define lcd P3
sbit sw1=P0^2;
sbit sens1=P0^0;
sbit sens2=P0^1;
sbit relay1=P2^4;
sbit relay2=P2^3;
sbit fan=P2^7;
sbit fan1=P2^6;
sbit en1=P2^5;
sbit rs=P1^0;
sbit rw=P1^1;
sbit en=P1^2;
int count=0;
int st1=0;
int st2=0;
void checkLeaving();
void checkEntry();
void Msdelay(unsigned int time);

void lcd_cmd(unsigned char cmd);
void lcd_conv(unsigned int value);
void lcd_disp(unsigned int dsize,unsigned char *s);
void lcd_init();
void lcd_data(unsigned char dis_data);

void main()
{
	fan=0;
	fan1=0;
	en1=0;
	relay1=0;
	relay2=0;
	lcd_init();
	lcd_cmd(0x01);
	Msdelay(1);
	lcd_cmd(0x80); 
	lcd_disp(7,"PERSON:");
	lcd_cmd(0xC0);

lcd_disp(3,"ON:");
	Msdelay(100);

	while(1)
	{
		checkEntry();
		checkLeaving();
		
		if(count<0)
		{
			count=0;
		}
		if(count>=0)
		{
			lcd_cmd(0x88);
			Msdelay(1);
			lcd_conv(count);
			Msdelay(1);
		}
		if(count==0)
{
			en1=0;
			fan=0;
			fan1=0;
			relay1=0;
			relay2=0;
			lcd_cmd(0xC4);
			lcd_disp(7,"ALL OFF");
		}
		if(count==1)
		{
			en1=1;
			fan=0;
			fan1=1;
			relay1=1;
			relay2=0;
			lcd_cmd(0xC4);
			lcd_disp(9,"fan bulb1");
}
		if(count==2)
		{
			en1=1;
			fan=0;
			fan1=1;
			relay1=1;
			relay2=0;
			lcd_cmd(0xC4);
			lcd_disp(9,"fan bulb1");
		}
		if(count>=3)
		{
			en1=1;
			fan=0;
			fan1=1;
			relay1=1;
			relay2=1;
			lcd_cmd(0xC4);

			lcd_disp(10,"ALL ARE ON");

	}

}
	}

void Msdelay(unsigned int time)
{
	int i,j;
	for(i=0;i<=time;i++)
	{
		for(j=0;j<1275;j++);
	}
}
void lcd_cmd(unsigned char cmd)
{
	lcd=cmd;
	rs=0;
	rw=0;
	en=1;
Msdelay(1);
	en=0;
	
}
void lcd_data(unsigned char dis_data)
{
	
	lcd=dis_data;
	rs=1;
	rw=0;
	en=1;
	Msdelay(1);
	en=0;
}

void lcd_init()
{
	lcd_cmd(0x38);
	Msdelay(3);
	lcd_cmd(0x0C);
Msdelay(3);
	lcd_cmd(0x01);
	Msdelay(3);
	lcd_cmd(0x06);
	Msdelay(3);
	
}
void lcd_disp(unsigned int dsize,unsigned char *s)
{
	unsigned int i;
	for(i=0;i<dsize;i++)
	{
		lcd_data(s[i]);
		Msdelay(2);
	}
	
}

void lcd_conv(unsigned int value)
{
	unsigned char q,rem;
	q=value/10;
	rem=value%10;
	q=q+0x30;
	rem=rem+0x30;
	lcd_data(q);
	lcd_data(rem);
	Msdelay(1);
}
void checkEntry()
{
	if((sens1==1) || (st1==1) && (st2==0))
	{
		while(sens1==1);
		st1=1;
		if(sens2==1)
		{
			count=count+1;
			st1=0;
			while(sens2==1);
		}
		
	}
	
}
void checkLeaving()
{
	if((sens2==1) || (st2==1) && (st1==0))
	{
		while(sens2==1);
		st2=1;
		if(sens1==1)
		{
			count=count-1;
			st2=0;
			while(sens1==1);
		}
    }
}
