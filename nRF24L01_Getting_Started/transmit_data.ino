void transmit_data()
{
  send_byte(flush_tx);
  ss_low();
  data_in[0]=send_byte_ns(wt_tx_payload);     //instruction to load tx buffer
  data_in[1]=send_byte_ns(tx_buffer[0]);      //data byte 1
  data_in[2]=send_byte_ns(tx_buffer[1]);      //data byte 2
  ss_high();
  delay(10);
  
  digitalWrite(CE_PIN,LOW);                 //actual transmission starts now
  delay(20);                                //delay is essential
  digitalWrite(CE_PIN,HIGH);                //end transmisssion
  delay(10);
  Serial.print("\nData Transmitted");
}
