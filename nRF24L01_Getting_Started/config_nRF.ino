void init_nrf()
{
  write_reg(en_AA,0x00);            //Disable shock burst in case
  write_reg(en_rx_addr,0x01);       //Enable RX address pipe 0
  write_reg(setup_aw,0x01);         //first two bits of setupt_aw =01 means 3 byte address length
  write_reg(setup_retr,0x00);       //set retries to 0 in case
  write_reg(rf_ch,0x01);            //RF channel 1
  write_reg(rf_setup,0x26);         // 250kbps

  write_reg(feature_reg,0x00);

  write_addr_reg(0x0a,rx_tx_addr);  //write RX pipe address in register
  write_addr_reg(0x10,rx_tx_addr);  //write TX address in register
  Serial.print("\nInitialized");
}

void config_nrf_rx()
{
  write_reg_bit(0x00,6,0);    //RX_DR Enable
  write_reg_bit(0x00,5,1);    //TX_DS disable
  write_reg_bit(0x00,4,1);    //RT disable
  write_reg_bit(0x00,1,1);    //power up
  write_reg_bit(0x00,0,1);    //RX MODE
  send_byte(flush_rx);
  send_byte(flush_tx);
  write_reg(0x11,0x02);       //set rx payload 2 bytes
  digitalWrite(CE_PIN,HIGH);
  delay(10);
  //Serial.print(read_reg(0x11),HEX);
  attachInterrupt(0,ISR_NRF,FALLING);  //attach interrupt..when new data is avaialble nrf pulls down interrupt 0 pin of arduino and get_data() is called 
}

void config_nrf_tx()
{
  write_reg_bit(0x00,6,1);    //RX_DR disable
  write_reg_bit(0x00,5,0);    //TX_DS enable
  write_reg_bit(0x00,4,1);    //RT disable
  write_reg_bit(0x00,1,1);    //power up
  write_reg_bit(0x00,0,0);    //TX Mode
  send_byte(flush_rx);
  send_byte(flush_tx);

  attachInterrupt(0,ISR_NRF,FALLING); //attach interrupt..when data is transmitted nrf pulls down interrupt 0 pin of arduino and update_tx_buffer is called
  delay(20);
}
