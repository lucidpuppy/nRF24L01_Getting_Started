/* Basic code to get started with nRF24L01+. Arduino Mega is configured as transmitter and UNO as receiver.
 * This is the code for the TX node so its for tranmsitter node..replace the function config_nrf_tx with config_nrf_rx
 * and uncomment pins definition for UNO are you're good to go
 * comment or queries
 * <bian.boozebacon@outlook.com>
 * for more info: https://tachymoron.wordpress.com/
 */



/*                                          
//Uno Recieves                              
#define MOSI_PIN 11
#define MISO_PIN 12
#define SCK_PIN 13
#define SS_ARD_PIN 10
#define SS_PIN 7
#define CE_PIN 8  //CE HIGH for RX
#define IRQ 2
*/

//Mega Transmits
#define MOSI_PIN 51
#define MISO_PIN 50
#define SCK_PIN 52
#define SS_ARD_PIN 53
#define SS_PIN 48
#define CE_PIN 49  //CE HIGH for RX
#define IRQ 2

// nrf instructions

#define flush_tx 0b11100001
#define flush_rx 0b11100010

#define rd_rx_payload 0b01100001
#define wt_tx_payload 0b10100000

#define set_mode() SPCR&=0xf3
#define set_data_order() SPCR&=0xdf
#define begin_spi() SPCR|=0x40

//register addresses

#define nrf_config     0x00
#define en_AA 0x01
#define en_rx_addr     0x02
#define setup_aw       0x03
#define setup_retr     0x04
#define rf_ch          0x05
#define rf_setup       0x06
#define nrf_status     0x07
#define observe_tx     0x08
#define rpd            0x09
#define rx_addr_p0     0x0a
#define rx_addr_p1     0x0b
#define rx_addr_p2     0x0c
#define rx_addr_p3     0x0d
#define rx_addr_p4     0x0e
#define rx_addr_p5     0x0f
#define tx_addr        0x10
#define rx_pw_p0       0x11
#define rx_pw_p1       0x12
#define rx_pw_p2       0x13
#define rx_pw_p3       0x14
#define rx_pw_p4       0x15
#define rx_pw_p5       0x16
#define fifo_status    0x17
#define dyn_payload    0x1c
#define feature_reg    0x1d

byte data_in[4],tx_buffer[2]={0,1},rx_tx_addr[3]={0x1a,0x2b,0x3c};

void setup()
{
  Serial.begin(115200);
  init_spi();                     //intialize SPI on arduino
  set_sck_mode_order();           //set clock rate mode and data order
  begin_spi();                    //set SPI enable bit in SPCR
  config_nrf_tx();                //configure as transmitter
  init_nrf();
  clear_interrupts();
  Serial.print("\nAll set..!!");
}

void loop()
{
  //test_spi();                   //Tests SPI connection
  transmit_data();                //Transmits data via RF channel
  Serial.print('\n');
  delay(1000);
}


ISR(SPI_STC_vect)
{
  Serial.print("\nArduino ISR CALLED");
}

void display_register()
{
  Serial.print("\nnrf_config ");
  Serial.print(read_reg(nrf_config),HEX);

  Serial.print("\nen_shock_burst ");
  Serial.print(read_reg(en_AA),HEX);

  Serial.print("\nen_rx_addr ");
  Serial.print(read_reg(en_rx_addr),HEX);

  Serial.print("\nsetup_aw ");
  Serial.print(read_reg(setup_aw),HEX);

  Serial.print("\nsetup_retr ");
  Serial.print(read_reg(setup_retr),HEX);

  Serial.print("\nrf_ch ");
  Serial.print(read_reg(rf_ch),HEX);

  Serial.print("\nrf_setup ");
  Serial.print(read_reg(rf_setup),HEX);

  Serial.print("\nnrf_status ");
  Serial.print(read_reg(nrf_status),HEX);

  Serial.print("\nobserve_tx ");
  Serial.print(read_reg(observe_tx),HEX);

  Serial.print("\nrpd ");
  Serial.print(read_reg(rpd),HEX);

  Serial.print("\nrx_addr_p0 ");
  Serial.print(read_reg(rx_addr_p0),HEX);

  Serial.print("\nrx_addr_p1 ");
  Serial.print(read_reg(rx_addr_p1),HEX);

  Serial.print("\nrx_addr_p2 ");
  Serial.print(read_reg(rx_addr_p2),HEX);

  Serial.print("\nrx_addr_p3 ");
  Serial.print(read_reg(rx_addr_p3),HEX);

  Serial.print("\nrx_addr_p4 ");
  Serial.print(read_reg(rx_addr_p4),HEX);

  Serial.print("\nrx_addr_p5 ");
  Serial.print(read_reg(rx_addr_p5),HEX);

  Serial.print("\ntx_addr ");
  Serial.print(read_reg(tx_addr),HEX);

  Serial.print("\nrx_pw_p0 ");
  Serial.print(read_reg(rx_pw_p0),HEX);
  
  Serial.print("\nrx_pw_p1 ");
  Serial.print(read_reg(rx_pw_p1),HEX);
  
  Serial.print("\nrx_pw_p2 ");
  Serial.print(read_reg(rx_pw_p2),HEX);
  
  Serial.print("\nrx_pw_p3 ");
  Serial.print(read_reg(rx_pw_p3),HEX);

  Serial.print("\nrx_pw_p4 ");
  Serial.print(read_reg(rx_pw_p4),HEX);
  
  Serial.print("\nrx_pw_p5 ");
  Serial.print(read_reg(rx_pw_p5),HEX);

  Serial.print("\nfifo_status ");
  Serial.print(read_reg(fifo_status),HEX);

  Serial.print("\ndyn_payload ");
  Serial.print(read_reg(dyn_payload),HEX);

  Serial.print("\nfeature_reg ");
  Serial.print(read_reg(feature_reg),HEX);
}
