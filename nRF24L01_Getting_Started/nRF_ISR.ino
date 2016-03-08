void ISR_NRF()
{
  byte status_nrf;
  status_nrf=read_reg(nrf_status);

  if((status_nrf>>6 & 0x01))
    get_data();                                         //If data recieved
  if((status_nrf>>5 & 0x01))
    update_tx_buffer();                                 //Data successfully transmitted
  if((status_nrf>>4 & 0x01))
    max_rt();                                           //Maximum Retransmissions
}

void get_data()                              //ISR for reciever
{
  Serial.print("\nRX Interrupt");
  ss_low();
  data_in[0]=send_byte_ns(rd_rx_payload);   //Instruction to read payload
  data_in[1]=send_byte_ns(0);               // Read data byte 1
  data_in[2]=send_byte_ns(0);               //Read data byte 2
  ss_high();
  delay(2);
  write_reg_bit(0x07,6,1);                  //Clear Interrupt flag in STATUS reg of nRF very essential..because flag isn't automatically cleared when ISR is called
  
  Serial.print("\nRecieved Bytes\t");
  Serial.print(data_in[0],HEX);
  Serial.print('\t');
  Serial.print(data_in[1],DEC);
  Serial.print('\t');
  Serial.print(data_in[2],DEC);
  
}

void update_tx_buffer()
{
  Serial.print("\n\nTX Interrupt");
  tx_buffer[0]=tx_buffer[0] + 2;
  tx_buffer[1]=tx_buffer[1] + 2;
  write_reg_bit(0x07,5,1);                  //Clear Interrupt flag in STATUS reg of nRF very essential..because flag isn't automatically cleared when ISR is called
  
  Serial.print("\nUpdated TX buffer\t");
  Serial.print(tx_buffer[0]);
  Serial.print('\t');
  Serial.print(tx_buffer[1]);
}

void max_rt()
{
  Serial.print("\nMaximum Number of Retransmit reached");
  write_reg_bit(0x07,4,1);
}
