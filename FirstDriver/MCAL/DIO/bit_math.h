#ifndef LIB_BIT_MATH_H_
#define LIB_BIT_MATH_H_

#define SET_BIT(PORT_ID, PIN_ID)  PORT_ID |= (1 << PIN_ID) //0b00001000
#define CLR_BIT(PORT_ID, PIN_ID)  PORT_ID &= ( ~(1 << PIN_ID))
#define TGL_BIT(PORT_ID, PIN_ID)  PORT_ID ^= (1 << PIN_ID)
#define GET_BIT(PORT_ID, PIN_ID)  (((PORT_ID) >> (PIN_ID)) & 0x01) //0b00001000 == 0

/*#define  IS_BIT_SET(PORT_ID, PIN_ID)  (PORT_ID&(1<<PIN_ID))>>PIN_ID
#define  IS_BIT_CLR(PORT_ID, PIN_ID)  !((PORT_ID&(1<<PIN_ID))>>PIN_ID)
#define  ROR(PORT_ID, PIN_ID)         PORT_ID=(PORT_ID<<(REGISTER_SIZE-num))|(reg>>(num))
#define  ROL(PORT_ID, PIN_ID)         reg=(reg>>(REGISTER_SIZE-num))|(reg<<(num))*/




#endif /* LIB_BIT_MATH_H_ */
