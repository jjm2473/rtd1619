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
    --clear-symbol-version abort \
    --clear-symbol-version access \
    --clear-symbol-version connect \
    --clear-symbol-version __cxa_atexit \
    --clear-symbol-version dlerror \
    --clear-symbol-version dprintf \
    --clear-symbol-version dup \
    --clear-symbol-version execlp \
    --clear-symbol-version exit \
    --clear-symbol-version fcntl64 \
    --clear-symbol-version __fdelt_chk \
    --clear-symbol-version feof \
    --clear-symbol-version fflush \
    --clear-symbol-version fgets \
    --clear-symbol-version fputs \
    --clear-symbol-version fseek \
    --clear-symbol-version ftell \
    --clear-symbol-version __getauxval \
    --clear-symbol-version getpagesize \
    --clear-symbol-version getpriority \
    --clear-symbol-version gettid \
    --clear-symbol-version gettimeofday \
    --clear-symbol-version __isoc99_fscanf \
    --clear-symbol-version __isoc99_vfscanf \
    --clear-symbol-version kill \
    --clear-symbol-version localtime \
    --clear-symbol-version lrint \
    --clear-symbol-version lseek64 \
    --clear-symbol-version memcmp \
    --clear-symbol-version memmove \
    --clear-symbol-version mlock \
    --clear-symbol-version mmap64 \
    --clear-symbol-version msync \
    --clear-symbol-version munlock \
    --clear-symbol-version munmap \
    --clear-symbol-version nanosleep \
    --clear-symbol-version perror \
    --clear-symbol-version pipe \
    --clear-symbol-version poll \
    --clear-symbol-version pthread_attr_getschedparam \
    --clear-symbol-version pthread_attr_setschedparam \
    --clear-symbol-version pthread_attr_setstacksize \
    --clear-symbol-version pthread_cancel \
    --clear-symbol-version pthread_cond_clockwait \
    --clear-symbol-version pthread_cond_signal \
    --clear-symbol-version pthread_detach \
    --clear-symbol-version pthread_exit \
    --clear-symbol-version pthread_getspecific \
    --clear-symbol-version pthread_join \
    --clear-symbol-version pthread_key_create \
    --clear-symbol-version pthread_mutexattr_destroy \
    --clear-symbol-version pthread_mutexattr_init \
    --clear-symbol-version pthread_mutexattr_setpshared \
    --clear-symbol-version pthread_mutexattr_settype \
    --clear-symbol-version pthread_mutex_trylock \
    --clear-symbol-version pthread_once \
    --clear-symbol-version pthread_self \
    --clear-symbol-version pthread_setname_np \
    --clear-symbol-version pthread_setspecific \
    --clear-symbol-version pthread_sigmask \
    --clear-symbol-version pthread_yield \
    --clear-symbol-version qsort \
    --clear-symbol-version raise \
    --clear-symbol-version rand \
    --clear-symbol-version read \
    --clear-symbol-version realloc \
    --clear-symbol-version recvmsg \
    --clear-symbol-version remove \
    --clear-symbol-version sched_getparam \
    --clear-symbol-version sched_setscheduler \
    --clear-symbol-version select \
    --clear-symbol-version sendmsg \
    --clear-symbol-version setenv \
    --clear-symbol-version setpgid \
    --clear-symbol-version setpriority \
    --clear-symbol-version setrlimit64 \
    --clear-symbol-version sigaddset \
    --clear-symbol-version sigemptyset \
    --clear-symbol-version signal \
    --clear-symbol-version socket \
    --clear-symbol-version sqrt \
    --clear-symbol-version srand \
    --clear-symbol-version stdout \
    --clear-symbol-version __stpcpy_chk \
    --clear-symbol-version strcasecmp \
    --clear-symbol-version __strcat_chk \
    --clear-symbol-version strchr \
    --clear-symbol-version strftime \
    --clear-symbol-version strncmp \
    --clear-symbol-version strncpy \
    --clear-symbol-version strnlen \
    --clear-symbol-version strrchr \
    --clear-symbol-version strstr \
    --clear-symbol-version strtok \
    --clear-symbol-version system \
    --clear-symbol-version tcgetattr \
    --clear-symbol-version tcsetattr \
    --clear-symbol-version time \
    --clear-symbol-version tolower \
    --clear-symbol-version toupper \
    --clear-symbol-version unlink \
    --clear-symbol-version unsetenv \
    --clear-symbol-version vfork \
    --clear-symbol-version vfprintf \
    --clear-symbol-version waitpid \
    --clear-symbol-version write \
    musl/lib/* || exit 1

echo "copy softlink to musl/lib/"

find lib -type l -name '*.so' -exec cp -a '{}' musl/lib/ ';' || exit 1

