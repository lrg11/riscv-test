# DHRY-CFLAGS := -O3 -DTIME -DNOENUM -Wno-implicit -save-temps
# DHRY-CFLAGS += -fno-builtin-printf -fno-common -falign-functions=4

riscv64-unknown-elf-gcc -march=rv64g -mabi=lp64d -mcmodel=medany \
    -I. -nostdlib -nostartfiles -Tlink.ld \
 -O3 -DTIME -DNOENUM -Wno-implicit -save-temps -fno-builtin-printf -fno-common -falign-functions=4 -Xlinker --defsym=__stack_size=0x800 -Xlinker --defsym=__heap_size=0x1000 \
 -o readcsr_bm readcsr_bm.c bench/*.c benchmark-dhrystone/*.c benchmark-dhrystone/*.S lib/crt.S lib/*.c