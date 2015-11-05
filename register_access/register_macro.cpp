    #include <iostream>
    #include "enum_binary_operators.hpp"

	// Code that should go in the library:
    
    /**
     * \brief An object ancapsulating a memory-mapped peripheral control register.
     *
     * \param reg_bits      An enum defining the bitfields for that register.
     * \param ret_address   The memory-mapped address where the register lies in
     *                      memory
     */
    template < typename reg_bits, uintptr_t reg_address >
    class Register
    {
    	private:
    		// On the intended pare metal target, this wouldn't be neccesary, as
    		// the value would be stored in the memory-mapped address of the register.
    		uint16_t value = 0;
    	public:
    		// Write a new value to the register
    		inline Register& operator= (reg_bits const& val)
    		{
    			// This is what is intended, but of course segfaults when not on bare metal.
    			//*reinterpret_cast<uint16_t*>(reg_address) = static_cast < uint16_t > (val);
    
    			// dummy replacement of the above line.
    			value = static_cast < uint16_t > (val);
    			// possibly do some more things like send the value to a remote register.
    			return *this;
    		}
    		operator uint16_t()							// Read register
    		{
    			// This is what is intended, but of course segfaults when not on bare metal.
    			//return *reinterpret_cast<uint16_t*>(reg_address);
    
    			// dummy replacement of the above line.
    			return value;
    		}
    		[[deprecated("Please only use the appropriate register bit enum values to manipulate the register!")]] Register& operator= (int val) {}
    };
    
    
    /**
     * \brief An Object encapsulating a memory-mapped peripheral
     *
     * \param base_address	The base address of the registers belonging to that peripheral.
     */
    template < uintptr_t base_address>
    class Some_peripheral
    {
    	public:
    		// This enum should not be in global namespace to avoid name conflicts.
    		// For example many peripherals might have a register named
    		// "control_register".
    		enum reg1_bits : uint16_t
    		{
    			AM  = (1 << 3),
    			FOO = (1 << 4),
    			BAR = (1 << 5),
    		};
    		// more register bit definitions
    
    		Register < reg1_bits, base_address + 0x8e > reg1;
    		// more registers
    
    	// ...
    	// possibly more high-level functions for the peripheral like
    	// initialisation routines, transmission routines, etc.
    };
    
    // More peripherals
    
    
    // The base address should be provided by some file defining the peripheral addresses for a given chip.gg
    //extern constexpr some_peripheral_base;
    constexpr uintptr_t some_peripheral_base = 0x8fce0000;
    
    Some_peripheral<some_peripheral_base> some_peripheral1;
    // And some more peripherals
    
    



	// User code:

    int main()
    {
    	// Get the current value of the register.
    	std::cout<<"reg1 = "<<static_cast < uint16_t > (some_peripheral1.reg1)<<std::endl;
    
    
    
    	// Each register can only be written with the bits that belong to it.
    	some_peripheral1.reg1 = Some_peripheral<some_peripheral_base>::reg1_bits::AM
    	                      | Some_peripheral<some_peripheral_base>::reg1_bits::BAR;
    
    	// This is the intended usage:
    	// Somehow, operator= should be able to deduce the scope resolution automatically at runtime.
    	//some_peripheral1.reg1 = AM | BAR;
    
    	std::cout<<"reg1 = "<<static_cast < uint16_t > (some_peripheral1.reg1)<<std::endl;
    
    	return 0;
    }
