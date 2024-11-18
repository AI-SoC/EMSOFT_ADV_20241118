#!/bin/bash

gdb-multiarch \
        -ex "target remote :3333" \
        -s "out.elf" \
    	-ex "load" \
    	-ex "b main.c:56" \
    	-ex "set arc arm" \
        -ex "monitor system_reset" \
        -ex "continue" 
