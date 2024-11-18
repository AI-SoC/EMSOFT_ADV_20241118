arm-none-eabi-gdb  -s "out.elf" -ex "target remote :3333" -ex "load"  -ex "b main.c:56" -ex "continue" 
