# 查看Podman环境
因为交叉编译环境在镜像中，先查看有哪些images
`podman images`
# 生成自动销毁的临时容器
需要注意将要编译的程序所在目录作为容器可见的共享文件夹，一般是当前目录，并在容器的/app中找到编译的源程序
`podman run --rm -it -v $(pwd):/app localhost/chipyard-slim:latest bash`
`cd /app`
049a4828c20b 30b51b633805 镜像ID也行（经验证）
# 容器中交叉编译命令
riscv64-unknown-elf-gcc -march=rv64g -mabi=lp64d -mcmodel=medany \
    -I. -O3 -nostdlib -nostartfiles -Tlink.ld \
    -o readcsr_bm readcsr_bm.c bench/*.c benchmark-dhrystone/*.c benchmark-dhrystone/*.S lib/crt.S lib/*.c
