#!/bin/sh
# patch realtek prebuilt so files for musl libc, using patchelf
# generated so runtime depends on gcompat
# Author: jjm2473

patchelf --version || exit 1

rm -rf musl/lib 2>/dev/null

mkdir -p musl/lib || exit 1

echo "copy *.so to musl/lib/"

find lib -type f -name '*.so' -exec cp -a '{}' musl/lib/ ';' || exit 1

echo "patchelf musl/lib/*.so"

patchelf --remove-needed libdl.so.2 --remove-needed libpthread.so.0 --remove-needed libm.so.6 \
    --replace-needed ld-linux-aarch64.so.1 libgcompat.so.0 \
    --replace-needed libc.so.6 libc.so \
    --clear-symbol-version __assert_fail \
    --clear-symbol-version calloc \
    --clear-symbol-version clock_gettime \
    --clear-symbol-version dlclose \
    --clear-symbol-version dlopen \
    --clear-symbol-version dlsym \
    --clear-symbol-version free \
    --clear-symbol-version malloc \
    --clear-symbol-version __memcpy_chk \
    --clear-symbol-version memcpy \
    --clear-symbol-version printf \
    --clear-symbol-version pthread_attr_destroy \
    --clear-symbol-version pthread_attr_init \
    --clear-symbol-version pthread_attr_setdetachstate \
    --clear-symbol-version pthread_cond_broadcast \
    --clear-symbol-version pthread_cond_destroy \
    --clear-symbol-version pthread_cond_init \
    --clear-symbol-version pthread_cond_timedwait \
    --clear-symbol-version pthread_cond_wait \
    --clear-symbol-version pthread_create \
    --clear-symbol-version pthread_mutex_destroy \
    --clear-symbol-version pthread_mutex_init \
    --clear-symbol-version pthread_mutex_lock \
    --clear-symbol-version pthread_mutex_unlock \
    --clear-symbol-version putchar \
    --clear-symbol-version puts \
    --clear-symbol-version __stack_chk_fail \
    --clear-symbol-version __stack_chk_guard \
    --clear-symbol-version strcmp \
    --clear-symbol-version __strcpy_chk \
    --clear-symbol-version strcpy \
    --clear-symbol-version usleep \
    --clear-symbol-version close \
    --clear-symbol-version __errno_location \
    --clear-symbol-version fchmod \
    --clear-symbol-version fclose \
    --clear-symbol-version fdopen \
    --clear-symbol-version fgetpos64 \
    --clear-symbol-version fileno \
    --clear-symbol-version flock \
    --clear-symbol-version fopen64 \
    --clear-symbol-version fprintf \
    --clear-symbol-version fread \
    --clear-symbol-version fsetpos64 \
    --clear-symbol-version fstat64 \
    --clear-symbol-version fwrite \
    --clear-symbol-version __getdelim \
    --clear-symbol-version getenv \
    --clear-symbol-version getpid \
    --clear-symbol-version ioctl \
    --clear-symbol-version __isoc99_sscanf \
    --clear-symbol-version lockf64 \
    --clear-symbol-version memset \
    --clear-symbol-version mkdir \
    --clear-symbol-version open64 \
    --clear-symbol-version snprintf \
    --clear-symbol-version __sprintf_chk \
    --clear-symbol-version sprintf \
    --clear-symbol-version stat64 \
    --clear-symbol-version stderr \
    --clear-symbol-version strerror \
    --clear-symbol-version strlen \
    --clear-symbol-version strtol \
    --clear-symbol-version syscall \
    --clear-symbol-version vsnprintf \
    musl/lib/* || exit 1

echo "copy softlink to musl/lib/"

find lib -type l -name '*.so' -exec cp -a '{}' musl/lib/ ';' || exit 1

