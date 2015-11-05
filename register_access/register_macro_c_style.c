    #include <stdio.h>
    #include <stdint.h>
    
    /* Might be in some library like this: */
    #define SOME_PERIPHERAL_BASE_ADDRESS 0x8fce0000
    #define SOME_PERIPHERAL_REG1 (*((uint16_t*)(SOME_PERIPHERAL_BASE_ADDRESS + 0x8e)))
    
    #define SOME_PERIPHERAL_REG1_AM  (1 << 3)
    #define SOME_PERIPHERAL_REG1_FOO (1 << 4)
    #define SOME_PERIPHERAL_REG1_BAR (1 << 5)
    
    
    /* User code: */
    int main()
    {
		/* How to use these definitions on a bare metal system: */
    	/* SOME_PERIPHERAL_REG1 is initialies to the reset value by hardware, so
    	 * there is no need to initialise it. */
    	/* printf("reg1 = %i\n", SOME_PERIPHERAL_REG1); */
    	/* This will of course segfault when not on a bare metal system. */
    	/* SOME_PERIPHERAL_REG1 = SOME_PERIPHERAL_REG1_AM | SOME_PERIPHERAL_REG1_BAR; */
    	/* printf("reg1 = %i\n", SOME_PERIPHERAL_REG1); */
    
    	/* Ersatz dummy code for testing on a pc: */
    	uint16_t value=0;
    	printf("reg1 = %i\n", value);

    	value = SOME_PERIPHERAL_REG1_AM | SOME_PERIPHERAL_REG1_BAR; /* <- No type-safty! */

    	printf("reg1 = %i\n", value);
    
    	return 0;
    }
