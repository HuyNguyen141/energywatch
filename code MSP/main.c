
#include <msp430.h>
#include <math.h>
int x,i=0,j=0,k,d,s=0,t,e,f,h,z=1,set=0;
long so=000000;
int a[6];
int second,minute,hour,secondhold,minutehold,hourhold,secondchange,minutechange,hourchange;
int secondhold1,minutehold1,hourhold1;
float first=0.00;
const float delta=0.00001;
unsigned char *PTxData;                     // Pointer to TX data sdasdwdweqwesdsdasdasd
unsigned char TXByteCtr;
unsigned char timer1sFLG,timer05sFLG;
unsigned char timer5sFLG;
unsigned char timehold,blinkbit;
unsigned char Rxflag;
unsigned char state;
unsigned char RxflagESP;
int r1;
unsigned char TxData[41] =              // Table of data to transmit
	{
	  0xd6,  //set mode
	  0xfc,  //set start bank
	  0xe0,  //device select
	  0xf4,  //ram access
	  0x16 	// x access


	  //0xf2,
	 // 0xff,
	 // 0x01,
	 // 0x02

	};
unsigned char g;
unsigned char RxData[8];
unsigned char TxDataUART[11]={
		0x01,

};

unsigned short CRC;
unsigned char FLG;
unsigned char lenres;
unsigned char lenTx;
unsigned short res;
unsigned char fault1,fault2,fault3;
const unsigned char seg[]={ 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F}; //0-9
const unsigned char seg_kitu[]={
		0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x3D, 0x76, 0x19, 0x1E, 0x7A, 0x38, 0x55, 0x54,
		0x5D, 0x73, 0x67, 0x70, 0x6C, 0x31, 0x3E, 0x7E, 0x1D, 0x6A, 0x6E, 0x49, 0x2D, 0x64,
		0x52,0x00,0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
struct Bit {
  unsigned char B0:1 ;
  unsigned char B1:1 ;
  unsigned char B2:1 ;
  unsigned char B3:1 ;
  unsigned char B4:1 ;
  unsigned char B5:1 ;
  unsigned char B6:1 ;
  unsigned char B7:1 ;
};
union _RAM{
	unsigned char Byte;
	struct Bit bit;
};
union _RAM bientrunggian;
union _RAM dulieu[2][18];
void num(int pos,unsigned char n){
	bientrunggian.Byte = seg[n];
	switch (pos){
	case 1:
	dulieu[0][4].bit.B3 = bientrunggian.bit.B0;
	dulieu[0][3].bit.B3 = bientrunggian.bit.B1;
	dulieu[0][2].bit.B3 = bientrunggian.bit.B2;
	dulieu[0][1].bit.B3 = bientrunggian.bit.B3;
	dulieu[0][2].bit.B4 = bientrunggian.bit.B4;
	dulieu[0][4].bit.B4 = bientrunggian.bit.B5;
	dulieu[0][3].bit.B4 = bientrunggian.bit.B6;
	break;
	case 2:
	dulieu[0][4].bit.B5 = bientrunggian.bit.B0;
	dulieu[0][3].bit.B5 = bientrunggian.bit.B1;
	dulieu[0][2].bit.B5 = bientrunggian.bit.B2;
	dulieu[0][1].bit.B5 = bientrunggian.bit.B3;
	dulieu[0][2].bit.B6 = bientrunggian.bit.B4;
	dulieu[0][4].bit.B6 = bientrunggian.bit.B5;
	dulieu[0][3].bit.B6 = bientrunggian.bit.B6;
	break;
	case 3:
	dulieu[1][4].bit.B7 = bientrunggian.bit.B0;
	dulieu[1][3].bit.B7 = bientrunggian.bit.B1;
	dulieu[1][2].bit.B7 = bientrunggian.bit.B2;
	dulieu[1][1].bit.B7 = bientrunggian.bit.B3;
	dulieu[1][2].bit.B6 = bientrunggian.bit.B4;
	dulieu[1][4].bit.B6 = bientrunggian.bit.B5;
	dulieu[1][3].bit.B6 = bientrunggian.bit.B6;
	break;
	case 4:
	dulieu[1][4].bit.B5 = bientrunggian.bit.B0;
	dulieu[1][3].bit.B5 = bientrunggian.bit.B1;
	dulieu[1][2].bit.B5 = bientrunggian.bit.B2;
	dulieu[1][1].bit.B5 = bientrunggian.bit.B3;
	dulieu[1][2].bit.B4 = bientrunggian.bit.B4;
	dulieu[1][4].bit.B4 = bientrunggian.bit.B5;
	dulieu[1][3].bit.B4 = bientrunggian.bit.B6;
	break;
	case 5:
	dulieu[1][4].bit.B3 = bientrunggian.bit.B0;
	dulieu[1][3].bit.B3 = bientrunggian.bit.B1;
	dulieu[1][2].bit.B3 = bientrunggian.bit.B2;
	dulieu[1][1].bit.B3 = bientrunggian.bit.B3;
	dulieu[1][2].bit.B2 = bientrunggian.bit.B4;
	dulieu[1][4].bit.B2 = bientrunggian.bit.B5;
	dulieu[1][3].bit.B2 = bientrunggian.bit.B6;
	break;
	case 6:
	dulieu[0][4].bit.B7 = bientrunggian.bit.B0;
	dulieu[0][3].bit.B7 = bientrunggian.bit.B1;
	dulieu[0][2].bit.B7 = bientrunggian.bit.B2;
	dulieu[0][1].bit.B7 = bientrunggian.bit.B3;
	dulieu[1][2].bit.B0 = bientrunggian.bit.B4;
	dulieu[1][4].bit.B0 = bientrunggian.bit.B5;
	dulieu[1][3].bit.B0 = bientrunggian.bit.B6;
	break;
	}
	for(i=0;i<2;i++){
				for(j=0;j<18;j++){
					if(i==0)
					k=2*j+5;
					else k=2*j+5+1;
					TxData[k] = dulieu[i][j].Byte;
				}
			}
}
void hienthi(long int number){
	int z=1,n;
	while(number!=0){
		 n=number%10;
		number=number/10;
		num(z,n);
		z++;
	}
}
void kytu(unsigned char pos,unsigned char n){
	switch(n){
	case 'A': t=0;break;
	case 'B': t=1;break;
	case 'C': t=2;break;
	case 'D': t=3;break;
	case 'E': t=4;break;
	case 'F': t=5;break;
	case 'G': t=6;break;
	case 'H': t=7;break;
	case 'I': t=8;break;
	case 'J': t=9;break;
	case 'K': t=10;break;
	case 'L': t=11;break;
	case 'M': t=12;break;
	case 'N': t=13;break;
	case 'O': t=14;break;
	case 'P': t=15;break;
	case 'Q': t=16;break;
	case 'R': t=17;break;
	case 'S': t=18;break;
	case 'T': t=19;break;
	case 'U': t=20;break;
	case 'V': t=21;break;
	case 'W': t=22;break;
	case 'X': t=23;break;
	case 'Y': t=24;break;
	case 'Z': t=25;break;
	case '#': t=26;break;
	case '$': t=27;break;
	case '/': t=28;break;
	case '0': t=30;break;
	case '1': t=31;break;
	case '2': t=32;break;
	case '3': t=33;break;
	case '4': t=34;break;
	case '5': t=35;break;
	case '6': t=36;break;
	case '7': t=37;break;
	case '8': t=38;break;
	case '9': t=39;break;
	default:t=29;break;
	};
	bientrunggian.Byte = seg_kitu[t];
	switch (pos){
	case 1:
	dulieu[0][4].bit.B3 = bientrunggian.bit.B0;
	dulieu[0][3].bit.B3 = bientrunggian.bit.B1;
	dulieu[0][2].bit.B3 = bientrunggian.bit.B2;
	dulieu[0][1].bit.B3 = bientrunggian.bit.B3;
	dulieu[0][2].bit.B4 = bientrunggian.bit.B4;
	dulieu[0][4].bit.B4 = bientrunggian.bit.B5;
	dulieu[0][3].bit.B4 = bientrunggian.bit.B6;
	break;
	case 2:
	dulieu[0][4].bit.B5 = bientrunggian.bit.B0;
	dulieu[0][3].bit.B5 = bientrunggian.bit.B1;
	dulieu[0][2].bit.B5 = bientrunggian.bit.B2;
	dulieu[0][1].bit.B5 = bientrunggian.bit.B3;
	dulieu[0][2].bit.B6 = bientrunggian.bit.B4;
	dulieu[0][4].bit.B6 = bientrunggian.bit.B5;
	dulieu[0][3].bit.B6 = bientrunggian.bit.B6;
	break;
	case 3:
	dulieu[1][4].bit.B7 = bientrunggian.bit.B0;
	dulieu[1][3].bit.B7 = bientrunggian.bit.B1;
	dulieu[1][2].bit.B7 = bientrunggian.bit.B2;
	dulieu[1][1].bit.B7 = bientrunggian.bit.B3;
	dulieu[1][2].bit.B6 = bientrunggian.bit.B4;
	dulieu[1][4].bit.B6 = bientrunggian.bit.B5;
	dulieu[1][3].bit.B6 = bientrunggian.bit.B6;
	break;
	case 4:
	dulieu[1][4].bit.B5 = bientrunggian.bit.B0;
	dulieu[1][3].bit.B5 = bientrunggian.bit.B1;
	dulieu[1][2].bit.B5 = bientrunggian.bit.B2;
	dulieu[1][1].bit.B5 = bientrunggian.bit.B3;
	dulieu[1][2].bit.B4 = bientrunggian.bit.B4;
	dulieu[1][4].bit.B4 = bientrunggian.bit.B5;
	dulieu[1][3].bit.B4 = bientrunggian.bit.B6;
	break;
	case 5:
	dulieu[1][4].bit.B3 = bientrunggian.bit.B0;
	dulieu[1][3].bit.B3 = bientrunggian.bit.B1;
	dulieu[1][2].bit.B3 = bientrunggian.bit.B2;
	dulieu[1][1].bit.B3 = bientrunggian.bit.B3;
	dulieu[1][2].bit.B2 = bientrunggian.bit.B4;
	dulieu[1][4].bit.B2 = bientrunggian.bit.B5;
	dulieu[1][3].bit.B2 = bientrunggian.bit.B6;
	break;
	case 6:
	dulieu[0][4].bit.B7 = bientrunggian.bit.B0;
	dulieu[0][3].bit.B7 = bientrunggian.bit.B1;
	dulieu[0][2].bit.B7 = bientrunggian.bit.B2;
	dulieu[0][1].bit.B7 = bientrunggian.bit.B3;
	dulieu[1][2].bit.B0 = bientrunggian.bit.B4;
	dulieu[1][4].bit.B0 = bientrunggian.bit.B5;
	dulieu[1][3].bit.B0 = bientrunggian.bit.B6;
	break;
	}
	for(i=0;i<2;i++){
		for(j=0;j<18;j++){
			if(i==0)
			k=2*j+5;
			else k=2*j+5+1;
			TxData[k] = dulieu[i][j].Byte;
		}
	}

}
void hienthikytu(char chuoi[]){
	int t,i=1;
	for (t=8; t>=0; t--){
		if(chuoi[t]=='@'){
		t--;
		while (chuoi[t]!='&')
		{kytu(i,chuoi[t]);
		i++;
		t--;};}
	}
}
void hienthifloat(float n){
	int i,j=1,t,k,q,d,p;
	long int tam;
	i = n;
	if ((i>=0)&&(i<=9)) k=1;
	else if ((i>=10)&&(i<=99)) k=2;
	else if ((i>=100)&&(i<=999)) k=3;
	else if ((i>=1000)&&(i<=9999)) k=4;
	else if ((i>=10000)&&(i<=99999)) k=5;
	else k=6;
	switch(k){
	case 1: tam=n*100000;p=5;break;
	case 2: tam=n*10000;p=4;break;
	case 3: tam=n*1000;p=3;break;
	case 4: tam=n*100;p=2;break;
	case 5: tam=n*10;p=1;break;
	default: break;
	}
	//tam=n;
	if ((tam>=0)&&(tam<=9)) q=1;
	else if ((tam>=10)&&(tam<=99)) q=2;
	else if ((tam>=100)&&(tam<=999)) q=3;
	else if ((tam>=1000)&&(tam<=9999)) q=4;
	else if ((tam>=10000)&&(tam<=99999)) q=5;
	else q=6;
	d=p-q;
	t=tam%10;
	while((t==0)&&(p>0)){
		tam=tam/10;
		k=k+1;
		t=tam%10;
		p=p-1;
	};
	switch(k){
		case 1: dulieu[1][1].bit.B2 = 1;dulieu[1][1].bit.B4 = 0;dulieu[1][1].bit.B6 = 0;dulieu[0][1].bit.B6 = 0;dulieu[0][1].bit.B4 = 0;break;
		case 2: dulieu[1][1].bit.B4 = 1;dulieu[1][1].bit.B2 = 0;dulieu[1][1].bit.B6 = 0;dulieu[0][1].bit.B6 = 0;dulieu[0][1].bit.B4 = 0;break;
		case 3: dulieu[1][1].bit.B6 = 1;dulieu[1][1].bit.B2 = 0;dulieu[1][1].bit.B4 = 0;dulieu[0][1].bit.B6 = 0;dulieu[0][1].bit.B4 = 0;break;
		case 4: dulieu[0][1].bit.B6 = 1;dulieu[1][1].bit.B6 = 0;dulieu[1][1].bit.B4 = 0;dulieu[1][1].bit.B2 = 0;dulieu[0][1].bit.B4 = 0;break;
		case 5: dulieu[0][1].bit.B4 = 1;dulieu[0][1].bit.B6 = 0;dulieu[1][1].bit.B6 = 0;dulieu[1][1].bit.B4 = 0;dulieu[1][1].bit.B2 = 0;break;
		default: dulieu[0][1].bit.B4 = 0;dulieu[0][1].bit.B6 = 0;dulieu[1][1].bit.B6 = 0;dulieu[1][1].bit.B4 = 0;dulieu[1][1].bit.B2 = 0;break;
	}
	hienthi(tam);
	if (i==0){
		num(7-k,0);
	};
	while (d>0){
		num(7-k-j,0);
		d--;
		j++;
	}
}
void setupdata(){
	for(j=5;j<41;j++)
	TxData[j]=0x00;

}
void setupdulieu(){
	for(i=0;i<2;i++){
				for(j=0;j<18;j++){
					dulieu[i][j].Byte=0x00;
				}}
}
void setup_timerA0(){
	TA0CTL = TASSEL_2 + MC_1 + ID_0;
	TA0CCR0 = 9216;
	TA0CCTL0 = CCIE;
}
void sendI2C(){

		PTxData = (unsigned char *)TxData;      // TX array start address
	    TXByteCtr = sizeof TxData;              // Load TX byte counter
	    UCB1CTL1 |= UCTR + UCTXSTT;             // I2C TX, start condition
	    __bis_SR_register( GIE);        // Enter LPM0 w/ interrupts
	                                            // Remain in LPM0 until all data
	                                            // is TX'd
	    while (UCB1CTL1 & UCTXSTP);             // Loop until STP is TX'd
}
void hienthisecond(int number){
	int z=1,n;
	for(z=1;z<3;z++){
		n=number%10;
		number=number/10;
		num(z,n);
		a[6-z]=n;
			}
}
void hienthiminute(int number){
	int z=3,n;
	for(z=3;z<5;z++){
		n=number%10;
		number=number/10;
		num(z,n);
		a[6-z]=n;
			}
}
void hienthihour(int number){
	int z=5,n;
	for(z=5;z<7;z++){
		n=number%10;
		number=number/10;
		num(z,n);
		a[6-z]=n;
			}
}
void holdtime(){
	if (timer1sFLG==1) {
		second += 1;
		if (second==60) {second=0;minute+=1;}
		if(minute==60) {hour+=1;minute=0;}
		if(hour==24) {hour=0;}

		timer1sFLG=0;
}
}

void CRC_RX(unsigned char Data[],unsigned char length)
      {
      	unsigned char *Pointer;
		int i;
        unsigned int crc = 0xFFFF;
        unsigned char ByteCtr;
        Pointer=(unsigned char *)Data;
        ByteCtr =length-2;
        while (ByteCtr) {

          crc ^= *Pointer++;          // XOR byte into least sig. byte of crc

          for (i = 8; i != 0; i--) {    // Loop over each bit
            if ((crc & 0x0001) != 0) {      // If the LSB is set
              crc >>= 1;                    // Shift right and XOR 0xA001
              crc ^= 0xA001;
            }
            else                            // Else LSB is not set
              crc >>= 1;                    // Just shift right
          }
          ByteCtr--;
        }


        int crcl = (crc & 0xFF00)/256; //Swaping  the bytes
        int crch = (crc & 0x00FF)*256;
        CRC = crch + crcl;
        if (CRC==Data[length-2]*256+Data[length-1]) FLG=1; else FLG=0;

      }

void CRC_TX(unsigned char Data[],unsigned char length){
	unsigned char *Pointer;
	int i;
	unsigned int crc = 0xFFFF;
	unsigned char ByteCtr;
	Pointer=(unsigned char *)Data;
	ByteCtr =length-2;
	while (ByteCtr) {

	          crc ^= *Pointer++;          // XOR byte into least sig. byte of crc

	          for (i = 8; i != 0; i--) {    // Loop over each bit
	            if ((crc & 0x0001) != 0) {      // If the LSB is set
	              crc >>= 1;                    // Shift right and XOR 0xA001
	              crc ^= 0xA001;
	            }
	            else                            // Else LSB is not set
	              crc >>= 1;                    // Just shift right
	          }
	          ByteCtr--;
	        }


			int crcl = (crc & 0xFF00)/256; //Swaping  the bytes
	        int crch = (crc & 0x00FF)*256;
	        CRC = crch+crcl;
	        Data[length-2]=(CRC&0xFF00)/256;
	        Data[length-1]=(CRC&0x00FF);
}
void UartSend_String(unsigned char Data[], unsigned char Length) {
	P2OUT &= ~BIT3;
	unsigned char *pData;
	pData=(unsigned char *)Data;
//	while(!(IFG2 & UCA0TXIFG));
//	UCA0TXBUF = 0x40;
	while (Length){
	while(!(IFG2 & UCA0TXIFG));
	UCA0TXBUF = *pData++;
	Length--;}
//	while(!(IFG2 & UCA0TXIFG));
//	UCA0TXBUF = 0x26;
	e=0;
	while(e!=6);
	P2OUT |= BIT3;

}
void UART(){
/*	if(RxflagESP==1){
		P5OUT ^= BIT0;
		TxDataUART[1]=0x04;
		TxDataUART[2]=0x06;
		TxDataUART[3]=0x00;
		TxDataUART[4]=hour;
		TxDataUART[5]=0x00;
		TxDataUART[6]=minute;
		TxDataUART[7]=0x00;
		TxDataUART[8]=second;
		lenTx=11;
		CRC_TX(TxDataUART,lenTx);
		UartSend_String(TxDataUART,lenTx);
		RxflagESP=0;
	}*/
	if(s==8){

		P5OUT ^= BIT0;
		//UartSend_String(RxData,8);



		//setupdulieu();
		//hienthi(RxData[7]);
		//sendI2C();
		CRC_RX(RxData,8);
		if (FLG==1){//P5OUT ^= BIT0;
		res=RxData[2]*256+RxData[3];
		lenres=RxData[4]*256+RxData[5];
		if (RxData[1]!=0x04){fault1=1;}
		if ((res<4001)||(res>4003)) {fault2=1;}
		if ((lenres>3)||((res==4002)&&(lenres>2))||((res==4003)&&(lenres>1))){fault3=1;}
		if(fault1==1){TxDataUART[1]=0x84;TxDataUART[2]=0x01;lenTx=5;fault1=0;}
		else{
			if(fault2==1) {TxDataUART[1]=0x84;
			TxDataUART[2]=0x02;lenTx=5;fault2=0;}
			else
			{if(fault3==1) {TxDataUART[1]=0x84; TxDataUART[2]=0x03;lenTx=5;fault3=0;}
			else{
		TxDataUART[1]=0x04;
		switch (res){
		case 4001:{
			switch(lenres){
			case 1:
				TxDataUART[2]=0x02;
				TxDataUART[3]=0x00;
				TxDataUART[4]=hour;
				lenTx=7;
				break;
			case 2:
				TxDataUART[2]=0x04;
				TxDataUART[3]=0x00;
				TxDataUART[4]=hour;
				TxDataUART[5]=0x00;
				TxDataUART[6]=minute;
				lenTx=9;break;
			case 3:
				TxDataUART[2]=0x06;
				TxDataUART[3]=0x00;
				TxDataUART[4]=hour;
				TxDataUART[5]=0x00;
				TxDataUART[6]=minute;
				TxDataUART[7]=0x00;
				TxDataUART[8]=second;
				lenTx=11;break;
			}break;}
		case 4002:{
			switch(lenres){
			case 1:
			TxDataUART[2]=0x02;
			TxDataUART[3]=0x00;
			TxDataUART[4]=minute;
			lenTx=7;
			break;
			case 2:
			TxDataUART[2]=0x04;
			TxDataUART[3]=0x00;
			TxDataUART[4]=minute;
			TxDataUART[5]=0x00;
			TxDataUART[6]=second;
			lenTx=9;break;
		}break;}
		case 4003:{
			switch(lenres){
			case 1:
			TxDataUART[2]=0x02;
			TxDataUART[3]=0x00;
			TxDataUART[4]=second;
			lenTx=7;
			break;
		}break;}}}}}

		CRC_TX(TxDataUART,lenTx);
		UartSend_String(TxDataUART,lenTx);}
		s=0;

}
}
void UART2(){
	TxDataUART[1]=0x04;
	TxDataUART[2]=0x06;
	TxDataUART[3]=0x00;
	TxDataUART[4]=hour;
	TxDataUART[5]=0x00;
	TxDataUART[6]=minute;
	TxDataUART[7]=0x00;
	TxDataUART[8]=second;
	lenTx=11;
	CRC_TX(TxDataUART,lenTx);
	UartSend_String(TxDataUART,lenTx);
}
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  P5DIR |= BIT0;
  P5OUT |= BIT0;
  P2DIR &= ~BIT7;
  P3DIR &= ~BIT4;
  P3DIR &= ~BIT3;
  P2DIR |= BIT3;
  P2OUT |= BIT3;
  FLL_CTL1 &= ~XT2OFF;
  FLL_CTL1 |= SELS;
  FLL_CTL2 |= XT2S_2;


  P2SEL |= BIT4+BIT5;                       // P2.4,5 UART option select
  UCA0CTL1 |= UCSSEL_2 + UCSWRST;                     // CLK = SMCLK
  UCA0BR0 = 96;                           // 14745600/9600/16 - 96
  UCA0BR1 = 0;                           //
  UCA0CTL0 |= UCPAR+UCPEN;
  UCA0MCTL |= UCOS16;                          // Modulation
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0RXIE;                 // Enable USCI_A0 TX/RX interrupt


  __bis_SR_register( GIE);


  setup_timerA0();
  P2SEL |= BIT1+BIT2;                       // Assign I2C pins to USCI_B0
  UCB1CTL1 |= UCSWRST;                      // Enable SW reset
  UCB1CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
  UCB1CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
  UCB1BR0 = 148;                             // fSCL = SMCLK/148 = 96.7kHz
  UCB1BR1 = 0;
  UCB1I2CSA = 0x3c;                         // Slave Address is 03Ch
  UCB1CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  UC1IE |= UCB1TXIE;                          // Enable TX interrupt
  setupdata();
  setupdulieu();
  //hienthi(999);
//hienthikytu("&ABDEFGH@");
  //	  hienthifloat(15.234);
  	//  sendI2C();
	timer1sFLG=0;
	timer5sFLG=0;
	state=1;
	s=0;
	while (1)
  {
		//check receive data and send data
		  UART();

		//check button
		//nhan lan 1
		if((P2IN & BIT7)!=BIT7){
		while ((P2IN & BIT7)!=BIT7){UART();holdtime();};
		set=set+1;
		secondhold1=second;minutehold1=minute;hourhold1=hour;
		}
		switch(set){
		case (1):
		secondhold=secondhold1;minutehold=minutehold1;hourhold=hourhold1;
		secondchange=secondhold;minutechange=minutehold;hourchange=hourhold;
		setupdulieu();
		hienthisecond(secondhold);
		hienthiminute(minutehold);
		hienthihour(hourhold);
		sendI2C();
		break;
		//nhan lan 2
		case (2):
		setupdulieu();
		hienthiminute(minutechange);
		hienthihour(hourchange);
		if(blinkbit==1){
		hienthisecond(secondchange);
		};
		sendI2C();
		if((P3IN & BIT4)!=BIT4){
		timehold=0;
		while ((P3IN & BIT4)!=BIT4){UART();holdtime();setupdulieu();hienthiminute(minutechange);hienthihour(hourchange);hienthisecond(secondchange);sendI2C();if(timehold==2){if(timer05sFLG==1){secondchange=secondchange+1;if(secondchange==60) secondchange=0;timer05sFLG=0;}}};
		secondchange=secondchange+1;if(secondchange==60) secondchange=0;
		}
		if((P3IN & BIT3)!=BIT3){
		timehold=0;
		while ((P3IN & BIT3)!=BIT3){UART();holdtime();setupdulieu();hienthiminute(minutechange);hienthihour(hourchange);hienthisecond(secondchange);sendI2C();if(timehold==2){if(timer05sFLG==1){secondchange=secondchange-1;if(secondchange==-1) secondchange=59;timer05sFLG=0;}}};
		secondchange=secondchange-1;if(secondchange==-1) secondchange=59;
		}
		break;
		//nhan lan 3
		case (3):
		setupdulieu();
		hienthisecond(secondchange);
		hienthihour(hourchange);
		if(blinkbit==1){
		hienthiminute(minutechange);}
		sendI2C();
		if((P3IN & BIT4)!=BIT4){
		timehold=0;
		while ((P3IN & BIT4)!=BIT4){UART();holdtime();setupdulieu();hienthisecond(secondchange);hienthihour(hourchange);hienthiminute(minutechange);sendI2C();if(timehold==2){if(timer05sFLG==1){minutechange=minutechange+1; if(minutechange==60) minutechange=0;timer05sFLG=0;}}};
		minutechange=minutechange+1; if(minutechange==60) minutechange=0;
		}
		if((P3IN & BIT3)!=BIT3){
		timehold=0;
		while ((P3IN & BIT3)!=BIT3){UART();holdtime();setupdulieu();hienthisecond(secondchange);hienthihour(hourchange);hienthiminute(minutechange);sendI2C();if(timehold==2){if(timer05sFLG==1){minutechange=minutechange-1; if(minutechange==-1) minutechange=59;timer05sFLG=0;}}};;
		minutechange=minutechange-1; if(minutechange==-1) minutechange=59;
		}
		//nhan lan 4
		break;
		case (4):
		setupdulieu();
		hienthisecond(secondchange);
		hienthiminute(minutechange);
		if(blinkbit==1){
		hienthihour(hourchange);}
		sendI2C();
		if((P3IN & BIT4)!=BIT4){
		timehold=0;
		while ((P3IN & BIT4)!=BIT4){UART();holdtime();setupdulieu();hienthisecond(secondchange);hienthiminute(minutechange);hienthihour(hourchange);sendI2C();if(timehold==2){if(timer05sFLG==1){hourchange=hourchange+1; if(hourchange==24) hourchange=0;timer05sFLG=0;}}};
		hourchange=hourchange+1; if(hourchange==24) hourchange=0;
		}
		if((P3IN & BIT3)!=BIT3){
		timehold=0;
		while ((P3IN & BIT3)!=BIT3){UART();holdtime();setupdulieu();hienthisecond(secondchange);hienthiminute(minutechange);hienthihour(hourchange);sendI2C();if(timehold==2){if(timer05sFLG==1){hourchange=hourchange-1; if(hourchange==-1) hourchange=23;timer05sFLG=0;}}};
		hourchange=hourchange-1; if(hourchange==-1) hourchange=23;
		}
		break;
		//nhan lan 5
		case 5:
		if (secondhold!=secondchange) {second=secondchange;if (minutehold!=minutechange) minute=minutechange;else minute=minutehold;if (hourhold!=hourchange) hour=hourchange;else hour=hourhold;};
		if (minutehold!=minutechange) {minute=minutechange;if (secondhold!=secondchange) second=secondchange;else second=secondhold;if (hourhold!=hourchange) hour=hourchange;else hour=hourhold;};
		if (hourhold!=hourchange) {hour=hourchange;if (minutehold!=minutechange) minute=minutechange;else minute=minutehold;if (secondhold!=secondchange) second=secondchange;else second=secondhold;};
		set=0;
		break;

		}
//time clock
if (timer1sFLG==1) {

	second += 1;
	if (second==60) {second=0;minute+=1;}
	if(minute==60) {hour+=1;minute=0;}
	if(hour==24) {hour=0;}
	if(set==0){
	setupdulieu();
	dulieu[0][1].bit.B6 = 1;dulieu[1][1].bit.B4 = 1;
	hienthisecond(second);
	hienthiminute(minute);
	hienthihour(hour);
	sendI2C();}
	UART();
	timer1sFLG=0;

}

		}

}

//------------------------------------------------------------------------------
// The USCIAB0TX_ISR is structured such that it can be used to transmit any
// number of bytes by pre-loading TXByteCtr with the byte count. Also, TXData
// points to the next byte to transmit.
//------------------------------------------------------------------------------
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TimerInterruptCCR0(void){

	if((x==400)||(x==800)||(x==1200)) timer05sFLG=1;
	if (x==800){blinkbit^=1;};
	if (x==1600){
		blinkbit^=1;
		timehold +=1; if(timehold==3) timehold=2;
		timer05sFLG=1;
		timer1sFLG=1;

	x = 0;}
	else
		x += 1;
	e+=1;if(e>=6) e=6;

	if (timer5sFLG==1) {f=0;timer5sFLG=0;}
	f +=1;
}
#pragma vector = USCIAB1TX_VECTOR
__interrupt void USCIAB1TX_ISR(void)
{
  if (TXByteCtr)                            // Check TX byte counter
  {
    UCB1TXBUF = *PTxData++;                 // Load TX buffer
    TXByteCtr--;                            // Decrement TX byte counter
  }
  else
  {
    UCB1CTL1 |= UCTXSTP;                    // I2C stop condition
    UC1IFG &= ~UCB1TXIFG;                     // Clear USCI_B1 TX int flag
   // __bic_SR_register_on_exit(CPUOFF);      // Exit LPM0
  }
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
	//timer5sFLG=1;
	if ((f>900)||(s==8)) {s=0;};
	RxData[s]=UCA0RXBUF;
	s++;
	//f=s;
	//if(s>=8) {Rxflag=1;g=8;};
	timer5sFLG=1;
	//f=0;
	/*if (UCA0RXBUF=='@') {RxflagESP=1;state=0;}
	if (UCA0RXBUF!='@') {state=1;}
	if(state==1){
				RxData[s]=UCA0RXBUF;
						s+=1;
						if(s>=8){Rxflag=1;s=0;g=8;};
			}

*/













	/*r1=UCA0RXBUF-48;
	if((state==1)&&(r1!=18)){RxData[0]=RxData[0]*10+r1;};
	if((state==2)&&(r1!=19)){RxData[1]=RxData[1]*10+r1;};
	if((state==3)&&(r1!=20)){RxData[2]=RxData[2]*10+r1;};
	if((state==4)&&(r1!=21)){RxData[3]=RxData[3]*10+r1;};
	if((state==5)&&(r1!=22)){RxData[4]=RxData[4]*10+r1;};
	if((state==6)&&(r1!=23)){RxData[5]=RxData[5]*10+r1;};
	if((state==7)&&(r1!=24)){RxData[6]=RxData[6]*10+r1;};
	if((state==8)&&(r1!=25)){RxData[7]=RxData[7]*10+r1;};
	if (r1==17) { state=1;
	int w;
	for(w=0;w<8;w++) RxData[w]=0;
	}
	if (r1==18) state=2;
	if (r1==19) state=3;
	if (r1==20) state=4;
	if (r1==21) state=5;
	if (r1==22) state=6;
	if (r1==23) state=7;
	if (r1==24) state=8;
	if (r1==25) {state=0;Rxflag=1;g=8;};


*/






	//timer5sFLG=1;
	//if(f>1000) s=0;
	//while(!(IFG2 & UCA0RXIFG));
	//r1=UCA0RXBUF;
	//		Rxflag=1;
   // if(s>=8) {Rxflag=1;s=0;g=8;timer5sFLG=0;}
//	if((UCA0RXBUF=='&')&&(s>=8)){Rxflag=1;s=0;g=8;state=0;}
//	if((state==1))
//		{RxData[s]=UCA0RXBUF;
//		s+=1;}
//	if(UCA0RXBUF=='@') {state=1;s=0;};

	//while(!(IFG2 & UCA0RXIFG));

	//if((state==2)) {Rxflag=1;s=0;g=8;}


}

