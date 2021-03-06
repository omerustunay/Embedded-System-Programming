/*Para Bozma Makinesi*/




#include "inc/tm4c123gh6pm.h"
#include <stdlib.h>
#include "driverlib/sysctl.h"
#include <stdbool.h>
#include <string.h>

#define LcdDataBits GPIO_PORTD_DATA_R

#define BIT_SET(PORT, PIN) do { \
        PORT |= 1<<PIN; \
} while (0)

#define BIT_RESET(PORT, PIN) do { \
        PORT &= ~(1<<PIN); \
} while (0)

int button_bir, button_iki, button_uc, button_dort, button_bes;
int button_yedi, button_alti;
int sayi = 0, sayi1 = 0, sayi2 = 0, sayi4 = 0, sayi5 = 0;
char onlar[100], birler[100], ondabir[100], yuzdebir[100];
int kalanElde1, kalanElde2, kalanElde3, kalanElde4, kalanElde5, kalanElde6,
		kalanElde7, kalanElde8, kalanElde9;
char yedek1[100], yedek2[100], yedek3[100], yedek4[100], yedek5[100],
		yedek6[100], yedek7[100], yedek8[100], yedek9[100];
char sayac1[100], sayac2[100], sayac3[100], sayac4[100], sayac5[100],
		sayac6[100], sayac7[100], sayac8[100], sayac9[100];
int virgulSolu, virgulSagi;
int ktemp1, ktemp2, ktemp3, ktemp4;
char b1[100], b2[100], b3[100], b4[100], b5[100], b6[100], b7[100], b8[100],
		b9[100];
int kontrol = 0,check=0;

volatile unsigned long gecici;

void port_yukle() {
	SysCtlClockSet(//Hazir kutuphane kullanilarak zaman hesabi yapilir.
	SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); //16 M 1 saniye
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;

	gecici = SYSCTL_RCGC2_R;

	GPIO_PORTD_DIR_R = 0xff;
	GPIO_PORTD_DEN_R = 0xff;

	GPIO_PORTE_DIR_R = 0xff;
	GPIO_PORTE_DEN_R = 0xff;

	GPIO_PORTA_DIR_R = 0xff;
	GPIO_PORTA_DEN_R = 0xff;

	GPIO_PORTF_DIR_R = 0xff;
	GPIO_PORTF_DEN_R = 0xff;

	GPIO_PORTB_DIR_R |= 0x00;
	GPIO_PORTB_AFSEL_R &= ~0x00;
	GPIO_PORTB_DEN_R |= 0xFF;

	GPIO_PORTC_DIR_R |= 0x00;
	GPIO_PORTC_AFSEL_R &= ~0x00;
	GPIO_PORTC_DEN_R |= 0xFF;

}

void lcd_ikili_yazdir(int x) {
	GPIO_PORTE_DATA_R = ((GPIO_PORTE_DATA_R & ~(1 << 1)) | (x << 1));
}

void EN(int x) {
	GPIO_PORTE_DATA_R = ((GPIO_PORTE_DATA_R & ~(1 << 2)) | (x << 2));
}

void resetEN() {
	EN(1);
	SysCtlDelay(500);
	EN(0);
}

void data(unsigned char c) {
	lcd_ikili_yazdir(1);
	SysCtlDelay(400);
	LcdDataBits = c >> 4;
	resetEN();
	LcdDataBits = c;
	resetEN();
}

void cmd(unsigned char c) {
	lcd_ikili_yazdir(0);
	SysCtlDelay(400);
	LcdDataBits = c >> 4;
	resetEN();
	LcdDataBits = c;
	resetEN();
}

void cmd_8bit(unsigned char c) {
	lcd_ikili_yazdir(0);
	SysCtlDelay(15000);
	LcdDataBits = (c);
	resetEN();
}

void temizle(void) {
	cmd(0x01);
	SysCtlDelay(30000);
}

void lcd_init() {
	cmd_8bit(0x30);
	cmd_8bit(0x30);
	cmd_8bit(0x30);
	cmd_8bit(0x20);
	cmd(0x28);               // 2 Satir olarak ayarla
	cmd(0x0c);              // Culcd_ikili_yazdiror 'Ä± gÃ¶rÃ¼nÃ¼r yap
	temizle();               // EkranÄ± temizle
	cmd(0x6);                 // Yazi modunu aÃ§(culcd_ikili_yazdiror otomatik taÅŸÄ±)
}

void koordinat(char x, char y) {
	if (x == 1)
		cmd(0x80 + ((y - 1) % 16));
	else
		cmd(0xC0 + ((y - 1) % 16));
}

void yazdir(char *p) {
	while (*p)
		data(*p++);
}

void hesapla(int para) {

	int para1 = 0, para2 = 0, para3 = 0, para4 = 0, para5 = 0, para6 = 0,
			para7 = 0, para8 = 0, para9 = 0;
	int yirmilik = 0, onluk = 0, beslik = 0, birlik = 0, yarimlik = 0,
			ceyreklik = 0, metelik = 0, delik = 0, kurusluk = 0;

	para1 = para;
	while (para >= 2000) {
		yirmilik++;
		para = para - 2000;
	}
	para2 = para;
	while (para >= 1000) {
		onluk++;
		para = para - 1000;
	}
	para3 = para;
	while (para >= 500) {
		beslik++;
		para = para - 500;
	}
	para4 = para;
	while (para >= 100) {
		birlik++;
		para = para - 100;
	}
	para5 = para;
	while (para >= 50) {
		yarimlik++;
		para = para - 50;
	}
	para6 = para;
	while (para >= 25) {
		ceyreklik++;
		para = para - 25;
	}
	para7 = para;
	while (para >= 10) {
		metelik++;
		para = para - 10;
	}
	para8 = para;
	while (para >= 5) {
		delik++;
		para = para - 5;
	}
	para9 = para;
	while (para >= 1) {
		kurusluk++;
		para = para - 1;
	}
	if (yirmilik != 0) {
		temizle();
		SysCtlDelay(8000000);
		kalanElde1 = para1 - (yirmilik * 2000);

		if (kalanElde1 >= 1000) // sayi = 1259
				{
			virgulSolu = kalanElde1 / 100; // 1259/100; 12 virgÃ¼lÃ¼n solu;
			virgulSagi = kalanElde1 - (virgulSolu * 100);

			koordinat(1, 1);
			yazdir("------------");

			itoa(virgulSolu, yedek1, 10);
			koordinat(1, 12);
			yazdir(yedek1);

			koordinat(1, 14);
			yazdir(".");

			itoa(virgulSagi, b1, 10);
			koordinat(1, 15);
			yazdir(b1);
		} else if (kalanElde1 >= 100) // sayi = 733
				{
			virgulSolu = kalanElde1 / 100; // 733 / 100 = 7 virgÃ¼lÃ¼n solu;
			virgulSagi = kalanElde1 - (virgulSolu * 100); //virgÃ¼lsagi = 33;

			koordinat(1, 1);
			yazdir("-------------");

			itoa(virgulSolu, yedek1, 10);
			koordinat(1, 13);
			yazdir(yedek1);

			koordinat(1, 14);
			yazdir(".");

			itoa(virgulSagi, b1, 10);
			koordinat(1, 15);
			yazdir(b1);
		} else if (kalanElde1 >= 10) //sayi=34;
				{
			virgulSagi = kalanElde1;

			koordinat(1, 1);
			yazdir("-------------");

			koordinat(1, 13);
			yazdir("0");

			koordinat(1, 14);
			yazdir(".");

			itoa(virgulSagi, b1, 10);
			koordinat(1, 15);
			yazdir(b1);
		} else if (kalanElde1 >= 1) //sayi = 6;
				{
			virgulSagi = kalanElde1;

			koordinat(1, 1);
			yazdir("-------------");

			koordinat(1, 13);
			yazdir("0");

			koordinat(1, 14);
			yazdir(".");

			koordinat(1, 15);
			yazdir("0");

			itoa(virgulSagi, b1, 10);
			koordinat(1, 16);
			yazdir(b1);
		}
		else {
					virgulSagi = kalanElde7;

					koordinat(1, 1);
					yazdir("-------------");

					koordinat(1, 13);
					yazdir("0");

					koordinat(1, 14);
					yazdir(".");

					koordinat(1, 15);
					yazdir("0");

					itoa(virgulSagi, b7, 10);
					koordinat(1, 16);
					yazdir(b7);
				}

		itoa(yirmilik, sayac1, 10);
		koordinat(2, 1);
		yazdir(sayac1);
		koordinat(2, 2);
		yazdir("- yirmilik");
		SysCtlDelay(48000000);
		lcd_ikili_yazdir(0);
	}

	if (onluk != 0) {
		temizle();
		SysCtlDelay(8000000);
		kalanElde2 = para2 - (onluk * 1000);

		if (kalanElde2 >= 1000) // sayi = 1259
				{
			virgulSolu = kalanElde2 / 100; // 1259/100; 12 virgulun solu;
			virgulSagi = kalanElde2 - (virgulSolu * 100);

			koordinat(1, 1);
			yazdir("------------");

			itoa(virgulSolu, yedek2, 10);
			koordinat(1, 12);
			yazdir(yedek2);

			koordinat(1, 14);
			yazdir(".");

			itoa(virgulSagi, b2, 10);
			koordinat(1, 15);
			yazdir(b2);
		}

		else if (kalanElde2 >= 100) // sayi = 733
				{
			virgulSolu = kalanElde2 / 100; // 733 / 100 = 7 virgulun solu;
			virgulSagi = kalanElde2 - (virgulSolu * 100); //virgulsagi = 33;

			koordinat(1, 1);
			yazdir("-------------");

			itoa(virgulSolu, yedek2, 10);
			koordinat(1, 13);
			yazdir(yedek2);

			koordinat(1, 14);
			yazdir(".");

			itoa(virgulSagi, b2, 10);
			koordinat(1, 15);
			yazdir(b2);
		} else if (kalanElde2 >= 10) //sayi=34;
				{
			virgulSagi = kalanElde2;

			koordinat(1, 1);
			yazdir("-------------");

			koordinat(1, 13);
			yazdir("0");

			koordinat(1, 14);
			yazdir(".");

			itoa(virgulSagi, b2, 10);
			koordinat(1, 15);
			yazdir(b2);
		} else if (kalanElde2 >= 1) //sayi = 6;
				{
			virgulSagi = kalanElde2;

			koordinat(1, 1);
			yazdir("-------------");

			koordinat(1, 13);
			yazdir("0");

			koordinat(1, 14);
			yazdir(".");

			koordinat(1, 15);
			yazdir("0");

			itoa(virgulSagi, b2, 10);
			koordinat(1, 16);
			yazdir(b2);
		} else {
			koordinat(1, 1);
			yazdir("-------------");

			koordinat(1, 13);
			yazdir("0");

			koordinat(1, 14);
			yazdir(".");

			koordinat(1, 15);
			yazdir("0");

			koordinat(1, 16);
			yazdir("0");
		}

		itoa(onluk, sayac2, 10);
		koordinat(2, 1);
		yazdir(sayac2);
		koordinat(2, 2);
		yazdir("- onluk");
		SysCtlDelay(48000000);
		lcd_ikili_yazdir(0);

	}

	if (beslik != 0) {
		temizle();
		SysCtlDelay(8000000);
		kalanElde3 = para3 - (beslik * 500);

		if (kalanElde3 >= 100) // sayi = 733
				{
			virgulSolu = kalanElde3 / 100; // 733 / 100 = 7 virgÃ¼lÃ¼n solu;
			virgulSagi = kalanElde3 - (virgulSolu * 100); //virgÃ¼lsagi = 33;

			koordinat(1, 1);
			yazdir("-------------");

			itoa(virgulSolu, yedek3, 10);
			koordinat(1, 13);
			yazdir(yedek3);

			koordinat(1, 14);
			yazdir(".");

			itoa(virgulSagi, b3, 10);
			koordinat(1, 15);
			yazdir(b3);
		} else if (kalanElde3 >= 10) //sayi=34;
				{
			virgulSagi = kalanElde3;

			koordinat(1, 1);
			yazdir("-------------");

			koordinat(1, 13);
			yazdir("0");

			koordinat(1, 14);
			yazdir(".");

			itoa(virgulSagi, b3, 10);
			koordinat(1, 15);
			yazdir(b3);
		} else if (kalanElde3 >= 1) //sayi = 6;
				{
			virgulSagi = kalanElde3;

			koordinat(1, 1);
			yazdir("-------------");

			koordinat(1, 13);
			yazdir("0");

			koordinat(1, 14);
			yazdir(".");

			koordinat(1, 15);
			yazdir("0");

			itoa(virgulSagi, b3, 10);
			koordinat(1, 16);
			yazdir(b3);
		}
		else {
					virgulSagi = kalanElde7;

					koordinat(1, 1);
					yazdir("-------------");

					koordinat(1, 13);
					yazdir("0");

					koordinat(1, 14);
					yazdir(".");

					koordinat(1, 15);
					yazdir("0");

					itoa(virgulSagi, b7, 10);
					koordinat(1, 16);
					yazdir(b7);
				}

		itoa(beslik, sayac3, 10);
		koordinat(2, 1);
		yazdir(sayac3);
		koordinat(2, 2);
		yazdir("- beslik");
		SysCtlDelay(48000000);
		lcd_ikili_yazdir(0);
	}

	if (birlik != 0) {
		temizle();
		SysCtlDelay(8000000);
		kalanElde4 = para4 - (birlik * 100);

		if (kalanElde4 >= 100) // sayi = 733
				{
			virgulSolu = kalanElde4 / 100; // 733 / 100 = 7 virgÃ¼lÃ¼n solu;
			virgulSagi = kalanElde4 - (virgulSolu * 100); //virgÃ¼lsagi = 33;

			koordinat(1, 1);
			yazdir("-------------");

			itoa(virgulSolu, yedek4, 10);
			koordinat(1, 13);
			yazdir(yedek4);

			koordinat(1, 14);
			yazdir(".");

			itoa(virgulSagi, b4, 10);
			koordinat(1, 15);
			yazdir(b4);
		} else if (kalanElde4 >= 10) //sayi=34;
				{
			virgulSagi = kalanElde4;

			koordinat(1, 1);
			yazdir("-------------");

			koordinat(1, 13);
			yazdir("0");

			koordinat(1, 14);
			yazdir(".");

			itoa(virgulSagi, b4, 10);
			koordinat(1, 15);
			yazdir(b4);
		} else if (kalanElde4 >= 1) //sayi = 6;
				{
			virgulSagi = kalanElde4;

			koordinat(1, 1);
			yazdir("-------------");

			koordinat(1, 13);
			yazdir("0");

			koordinat(1, 14);
			yazdir(".");

			koordinat(1, 15);
			yazdir("0");

			itoa(virgulSagi, b4, 10);
			koordinat(1, 16);
			yazdir(b4);
		}
		else {
				virgulSagi = kalanElde4;

				koordinat(1, 1);
				yazdir("------------");

				koordinat(1, 13);
				yazdir("0");

				koordinat(1, 14);
				yazdir(".");

				koordinat(1, 15);
				yazdir("0");

				itoa(virgulSagi, b4, 10);
				koordinat(1, 16);
				yazdir(b4);
		}

		itoa(birlik, sayac4, 10);
		koordinat(2, 1);
		yazdir(sayac4);
		koordinat(2, 2);
		yazdir("- birlik");
		SysCtlDelay(48000000);
		lcd_ikili_yazdir(0);
	}

	if (yarimlik != 0) {
		temizle();
		SysCtlDelay(8000000);
		kalanElde5 = para5 - (yarimlik * 50);

		if (kalanElde5 >= 10) //sayi=34;
				{
			virgulSagi = kalanElde5;

			koordinat(1, 1);
			yazdir("-------------");

			koordinat(1, 13);
			yazdir("0");

			koordinat(1, 14);
			yazdir(".");

			itoa(virgulSagi, b5, 10);
			koordinat(1, 15);
			yazdir(b5);
		} else if (kalanElde5 >= 1) //sayi = 6;
				{
			virgulSagi = kalanElde5;

			koordinat(1, 1);
			yazdir("-------------");

			koordinat(1, 13);
			yazdir("0");

			koordinat(1, 14);
			yazdir(".");

			koordinat(1, 15);
			yazdir("0");

			itoa(virgulSagi, b5, 10);
			koordinat(1, 16);
			yazdir(b5);
		}
		else {
					virgulSagi = kalanElde7;

					koordinat(1, 1);
					yazdir("-------------");

					koordinat(1, 13);
					yazdir("0");

					koordinat(1, 14);
					yazdir(".");

					koordinat(1, 15);
					yazdir("0");

					itoa(virgulSagi, b7, 10);
					koordinat(1, 16);
					yazdir(b7);
				}

		itoa(yarimlik, sayac5, 10);
		koordinat(2, 1);
		yazdir(sayac5);
		koordinat(2, 2);
		yazdir("- yarimlik");
		SysCtlDelay(48000000);
		lcd_ikili_yazdir(0);

	}

	if (ceyreklik != 0) {
		temizle();
		SysCtlDelay(8000000);
		kalanElde6 = para6 - (ceyreklik * 25);

		if (kalanElde6 >= 10) //sayi=34;
				{
			virgulSagi = kalanElde6;

			koordinat(1, 1);
			yazdir("-------------");

			koordinat(1, 13);
			yazdir("0");

			koordinat(1, 14);
			yazdir(".");

			itoa(virgulSagi, b6, 10);
			koordinat(1, 15);
			yazdir(b6);
		} else if (kalanElde6 >= 1) //sayi = 6;
				{
			virgulSagi = kalanElde6;

			koordinat(1, 1);
			yazdir("------------");

			koordinat(1, 13);
			yazdir("0");

			koordinat(1, 14);
			yazdir(".");

			koordinat(1, 15);
			yazdir("0");

			itoa(virgulSagi, b6, 10);
			koordinat(1, 16);
			yazdir(b6);
		}
		else {
					virgulSagi = kalanElde7;

					koordinat(1, 1);
					yazdir("-------------");

					koordinat(1, 13);
					yazdir("0");

					koordinat(1, 14);
					yazdir(".");

					koordinat(1, 15);
					yazdir("0");

					itoa(virgulSagi, b7, 10);
					koordinat(1, 16);
					yazdir(b7);
				}

		itoa(ceyreklik, sayac6, 10);
		koordinat(2, 1);
		yazdir(sayac6);
		koordinat(2, 2);
		yazdir("- ceyreklik");
		SysCtlDelay(48000000);
		lcd_ikili_yazdir(0);
	}

	if (metelik != 0) {
		temizle();
		SysCtlDelay(8000000);
		kalanElde7 = para7 - (metelik * 10);

		if (kalanElde7 >= 10) //sayi=34;
				{
			virgulSagi = kalanElde7;

			koordinat(1, 1);
			yazdir("-------------");

			koordinat(1, 13);
			yazdir("0");

			koordinat(1, 14);
			yazdir(".");

			itoa(virgulSagi, b7, 10);
			koordinat(1, 15);
			yazdir(b7);
		} else {
			virgulSagi = kalanElde7;

			koordinat(1, 1);
			yazdir("-------------");

			koordinat(1, 13);
			yazdir("0");

			koordinat(1, 14);
			yazdir(".");

			koordinat(1, 15);
			yazdir("0");

			itoa(virgulSagi, b7, 10);
			koordinat(1, 16);
			yazdir(b7);
		}

		itoa(metelik, sayac7, 10);
		koordinat(2, 1);
		yazdir(sayac7);
		koordinat(2, 2);
		yazdir("- metelik");

		SysCtlDelay(48000000);
		lcd_ikili_yazdir(0);
	}

	if (delik != 0) {
		temizle();
		SysCtlDelay(8000000);
		kalanElde8 = para8 - (delik * 5);

		virgulSagi = kalanElde8;

		koordinat(1, 1);
		yazdir("------------");

		koordinat(1, 13);
		yazdir("0");

		koordinat(1, 14);
		yazdir(".");

		koordinat(1, 15);
		yazdir("0");

		itoa(virgulSagi, b8, 10);
		koordinat(1, 16);
		yazdir(b8);

		itoa(delik, sayac8, 10);
		koordinat(2, 1);
		yazdir(sayac8);
		koordinat(2, 2);
		yazdir("- delik");
		SysCtlDelay(48000000);
		lcd_ikili_yazdir(0);
	}

	if (kurusluk != 0) {
		temizle();
		SysCtlDelay(8000000);
		kalanElde9 = para9 - (kurusluk * 1);

		virgulSagi = kalanElde9;

		koordinat(1, 1);
		yazdir("-----------");

		koordinat(1, 13);
		yazdir("0");

		koordinat(1, 14);
		yazdir(".");

		koordinat(1, 15);
		yazdir("0");

		itoa(virgulSagi, b9, 10);
		koordinat(1, 16);
		yazdir(b9);

		itoa(kurusluk, sayac9, 10);
		koordinat(2, 1);
		yazdir(sayac9);
		koordinat(2, 2);
		yazdir("- kurusluk");
		SysCtlDelay(4000000);
		lcd_ikili_yazdir(0);
	}

}

int main() {

	port_yukle();
	lcd_init();
	temizle();
	SysCtlDelay(8000000);
	int sayac = 0;

	git:

	if (kontrol == 1) {
		kontrol = 0;
		sayi = 0, sayi1 = 0, sayi2 = 0, sayi4 = 0, sayi5 = 0;

	}
	koordinat(1, 1);
	yazdir("para");
	koordinat(2, 1);
	yazdir("giriniz");

	while (1) {
		button_bir = GPIO_PORTB_DATA_R & 0x01;             //PB0 bagli 1. buton.
		button_iki = GPIO_PORTB_DATA_R & 0x02;             //PB1 bagli 2. buton.
		button_uc = GPIO_PORTB_DATA_R & 0x04;              //PB2 bagli 3. buton.
		button_dort = GPIO_PORTB_DATA_R & 0x08;            //PB3 bagli 4. buton.
		button_bes = GPIO_PORTB_DATA_R & 0x10;             //PB4 bagli 5. buton.
		button_alti = GPIO_PORTB_DATA_R & 0x20;            //PB5 bagli 6. buton.
		button_yedi = GPIO_PORTC_DATA_R & 0x10;            //PC4 bagli 7. buton.

		if (button_bir == 0) {
			GPIO_PORTE_DATA_R |= 0x08;                // kirmizi led yanar PE3 .
			temizle();
			SysCtlDelay(3200000);
			GPIO_PORTE_DATA_R &= ~(0x08);             // kirmizi led soner PE3 .

			koordinat(1, 1);
			yazdir("girilen:");
			sayi1 = sayi1 + 1;
			if (sayi1 == 10)
				sayi1 = 0;

			itoa(sayi1, onlar, 10);

			koordinat(1, 12);
			yazdir(onlar);
			check=0;

		}

		else if (button_iki == 0) {
			GPIO_PORTE_DATA_R |= 0x10;                 // kirmizi led yanar PE4.
			temizle();
			SysCtlDelay(3200000);
			GPIO_PORTE_DATA_R &= ~(0x10);              // kirmizi led soner PE4.

			koordinat(1, 1);
			yazdir("girilen:");
			sayi2 = sayi2 + 1;
			if (sayi2 == 10)
				sayi2 = 0;
			itoa(sayi2, birler, 10);
			if (sayi1 != 0) {
				koordinat(1, 12);
				yazdir(onlar);
			}
			koordinat(1, 13);
			yazdir(birler);
			check=0;

		} else if (button_uc == 0) {

			GPIO_PORTE_DATA_R |= 0x20;                 // kirmizi led yanar PE5.
			temizle();
			SysCtlDelay(3200000);
			if (check>5){
				kontrol = 1;
				GPIO_PORTE_DATA_R &= ~(0x20);
				goto git;
							check=0;

			}
			GPIO_PORTE_DATA_R &= ~(0x20);              // kirmizi led soner PE5.
			check++;


			koordinat(1, 1);
			yazdir("girilen:");

			if (sayi1 != 0) {
				koordinat(1, 12);
				yazdir(onlar);
			}
			koordinat(1, 13);
			yazdir(birler);
			koordinat(1, 14);
			yazdir(".");


		} else if (button_dort == 0) {
			GPIO_PORTA_DATA_R |= 0x80;                 // kirmizi led yanar PA7.
			temizle();
			SysCtlDelay(3200000);
			GPIO_PORTA_DATA_R &= ~(0x80);      // kirmizi led soner PA7 .

			koordinat(1, 1);
			yazdir("girilen:");

			sayi4 = sayi4 + 1;
			if (sayi4 == 10)
				sayi4 = 0;
			itoa(sayi4, ondabir, 10);
			if (sayi1 != 0) {
				koordinat(1, 12);
				yazdir(onlar);
			}

			koordinat(1, 13);
			yazdir(birler);
			koordinat(1, 14);
			yazdir(".");

			koordinat(1, 15);
			yazdir(ondabir);
			check=0;

		} else if (button_bes == 0) {
			GPIO_PORTA_DATA_R |= 0x40;        // kirmizi led yanar PA6.
			temizle();
			SysCtlDelay(3200000);
			GPIO_PORTA_DATA_R &= ~(0x40);             // kirmizi led soner PA6 .

			koordinat(1, 1);
			yazdir("girilen:");

			sayi5 = sayi5 + 1;
			if (sayi5 == 10)
				sayi5 = 0;
			itoa(sayi5, yuzdebir, 10);
			if (sayi1 != 0) {
				koordinat(1, 12);
				yazdir(onlar);
			}

			koordinat(1, 13);
			yazdir(birler);
			koordinat(1, 14);
			yazdir(".");

			koordinat(1, 15);
			yazdir(ondabir);

			koordinat(1, 16);
			yazdir(yuzdebir);
			check=0;
		}

		else if (button_alti == 0) {
			GPIO_PORTA_DATA_R |= 0x10;        // kirmizi led yanar PA4.
			temizle();
			SysCtlDelay(3200000);
			GPIO_PORTA_DATA_R &= ~(0x10);             // kirmizi led soner PA4 .

			sayi = sayi1 * 1000 + sayi2 * 100 + sayi4 * 10 + sayi5 * 1;

			hesapla(sayi);
			check=0;

		} else if (button_yedi == 0) {
			GPIO_PORTF_DATA_R |= 0x10;        // kirmizi led yanar PF4.
			temizle();
			SysCtlDelay(3200000);
			GPIO_PORTF_DATA_R &= ~(0x10);             // kirmizi led soner PF4 .

			kontrol = 1;
			goto git;
			check=0;
		}

	}
}



/*
 *16x02 Bagantilar
/-------------------------------------------------/
 LCD          Tiva C
-----           ------
VSS              GROUND
VDD              +5V
V0               GROUND
RS               PE1
E                PE2
D4               PD0
D5               PD1
D6               PD2
D7               PD3
BUTTON
----------
ONLAR           PB0
BIRLER          PB1
NOKTA           PB2
ONDABIRLER       PB3
YUZDEBIRLER     PB4
ENTER           PB5
RESET           PC4


LED
----
ONLAR           PE3
BIRLER          PE4
NOKTA           PE5
ONDABIRLER      PA7
YUZDEBIRLER     PA6
ENTER           PA4
RESET           PF4


 /--------------------------------------------------------/
*/
