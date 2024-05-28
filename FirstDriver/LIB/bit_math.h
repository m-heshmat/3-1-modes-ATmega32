#ifndef LIB_BIT_MATH_H_
#define LIB_BIT_MATH_H_

#define SET_BIT(PORT_ID, PIN_ID)  PORT_ID |= (1 << PIN_ID)
#define CLR_BIT(PORT_ID, PIN_ID)  PORT_ID &= (~(1 << PIN_ID))
#define TGL_BIT(PORT_ID, PIN_ID)  PORT_ID ^= (1 << PIN_ID)
#define GET_BIT(PORT_ID, PIN_ID)  (((PORT_ID) >> (PIN_ID)) & 0x01)

#define IS_BIT_SET(reg, bit)  (reg & (1 << bit)) >> bit
#define IS_BIT_CLR(reg, bit)  !((reg & (1 << bit)) >> bit)
#define ROR(reg, num)         reg = (reg << (REGISTER_SIZE - num)) | (reg >> (num))
#define ROL(reg, num)         reg = (reg >> (REGISTER_SIZE - num)) | (reg << (num))



#endif /* LIB_BIT_MATH_H_ */
