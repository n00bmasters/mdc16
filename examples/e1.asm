asect 0
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
    ld r0, r2
    inc r0
    ld r0, r3

    not r2
    not r3

    push r1

    ldi r0, 0
    ldi r1, 1

    add r1, r2
    add r0, r3

    pop r1

    st r1, r2
    inc r1
    st r1, r3

end.