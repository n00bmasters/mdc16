asect 0x00
main: ext               # Declare labels
default_handler: ext    # as external

# Interrupt vector table (IVT)
# Place a vector to program start and
# map all internal exceptions to default_handler
dc main, 0              # Startup/Reset vector
dc default_handler, 0   # Unaligned SP
dc default_handler, 0   # Unaligned PC
dc default_handler, 0   # Invalid instruction
dc default_handler, 0   # Double fault
align 0x80              # Reserve space for the rest 
                        # of IVT

# Exception handlers section
rsect exc_handlers

# This handler halts processor
default_handler>
    halt

rsect main

main>
    ldi r0, 6
    ldi r1, 7

    if 
    cmp r0, r1
    is eq
    ldi r0, 1
    else 
    ldi r0, 2
    fi

    ldi r3, 0
    st r3, r0



    ldi r0, 8
    ldi r1, 8

    if
    cmp r0, r1
    is eq
    ldi r0, 1
    else 
    ldi r0, 2
    fi

    ldi r3, 1
    st r3, r0
end.