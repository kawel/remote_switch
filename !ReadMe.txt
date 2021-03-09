ComPort settings: 
	BaudRate: 9600
	Parity Bit: None
	Data Bit: 8
	Stop Bit: 1


Note: 
  The virtual COM port in the mEDBG requires the terminal software to set the Data Terminal Ready(DTR) signal to enable the UART pins connected to the ATtiny416. If the DTR signal is not enabled theUART pins on the mEDBG are kept in high-z (tri-state), rendering the COM port unusable. The DTR signal is automatically set by some terminal software, but it may have to be manually enabled in the target terminal

Functionality: 
	* Unit sends keep alive information "!\r\n" every few seconds
	* The LED build in the Button1 can be turn ON by sending single char 'o' 
	* The LED build in the Button1 can be turn OFF by sending single char 'f'
	* When Button1 is activated the "a\r\n" is sent.
	* When Button2 is activated the "b\r\n" is sent.

