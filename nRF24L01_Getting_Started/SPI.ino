void init_spi()
{
  pinMode(MOSI_PIN,OUTPUT);
  pinMode(MISO_PIN,INPUT);
  pinMode(SCK_PIN,OUTPUT);
  pinMode(SS_ARD_PIN,OUTPUT);
  pinMode(SS_PIN,OUTPUT);
  pinMode(IRQ,INPUT);
  SPCR=0x00;
  SPCR|=0x10; //Interrupt disabled,Arduino as Master.
  delay(2);
}

void ss_low()
{
  digitalWrite(SS_PIN,LOW);
}

void ss_high()
{
  digitalWrite(SS_PIN,HIGH);
}

void set_sck_mode_order()
{
  set_sck();
  set_mode();
  set_data_order();
}

void set_sck()
{
  SPCR&=0xFC;
  SPSR|=0x01;
}
