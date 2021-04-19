uint8_t temp[2];

uint8_t  SPI_T(uint8_t msg)    //Repetive SPI transmit sequence
{
   uint8_t msg_temp = 0;  //vairable to hold received data
   digitalWrite(CS, LOW);     //select spi device
   msg_temp = SPI.transfer(msg);    //send and receive
   digitalWrite(CS,HIGH);    //deselect spi device
   return(msg_temp);      //return received byte
}

uint16_t LeerEncoder()
{
   uint8_t received = 0xA5;    //just a temp variable
   ABSposition = 0;    //reset position variable
   
   SPI.begin();    //Start transmission.
   digitalWrite(CS,LOW); //Habilitar disp SPI.
   
   SPI_T(0x10);   //issue read command
   received = SPI_T(0x00);    //issue NOP to check if encoder is ready to send
   
   while (received != 0x10)    //loop while encoder is not ready to send
   {
     received = SPI_T(0x00);    //check again if encoder is still working 
     delay(2);    //wait a bit  --Cambiado de 2 a 1, probando.
   }
   
   temp[0] = SPI_T(0x00);    //Receive MSB
   temp[1] = SPI_T(0x00);    //Receive LSB

   digitalWrite(CS, HIGH);  //just to make sure   
   SPI.end();    //end transmition
   
   temp[0] &=~ 0xF0;    //mask out the first 4 bits, 00001111
    
   ABSposition = temp[0] << 8;    //shift MSB to correct ABSposition in ABSposition message
   ABSposition += temp[1];    // add LSB to ABSposition message to complete message

  return ABSposition;
}


