# cia-software
Software function to generate commands for the CIA PCB, and to provide health checks to OBC.

The chip chosen to supply PWM outputs is the PCA9685. Here is the link to the data sheet: https://cdn-shop.adafruit.com/datasheets/PCA9685.pdf. Table of contents is located on the last page of the document.

For communication with the PCA9685, following a START condition (see section 8.1.1 on page 30), the bus master (OBC) must output the address byte of the PCA9685, with the last bit being 1 for a read operation or 0 for a write operation. After the chip acknowledges the access of the OBC, the OBC then sends the address of the register it would like to read from or write to. After the register is accessed, the OBC can either write the corresponding register command (see the "CIADataStruct", which is in ciaAllocation.h), or it can read from the register. 

Both the address bytes of the chip (one for reading and one for writing), along with the address bytes of each device register are stored in ciaAllocation.h. 

Example: 
OBC:  START
      *sends* "devAddrWrite"     (address constant for writing stored in ciaAllocation.h)
chip: *sends acknowledge to OBC*
OBC:  *reads acknowledge from chip*
      *sends* "posXlead1Addr[0]" (address for the first register of the first lead of the positive x face magnetorquer)
      *sends* "posXlead1[0]"     (command for the first register of the first lead of the positive x face magnetorquer)
      *sends* "posXlead1Addr[1]" (second register address)
      *sends* "posXlead1[1]"     (second register command)
      *sends* "posXlead1Addr[2]" (third register address)
      *sends* "posXlead1[2]"     (third register command)
      *sends* "posXlead1Addr[3]" (fourth register address)
      *sends* "posXlead1[3]"     (fourth register command)
      
      (repeat for every magnetorquer lead)
