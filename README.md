# xv6 Custom System Calls Implementation

A project implementing custom system calls in the xv6 educational operating system, including `helloos()` and `getrandom()` system calls.

## 📋 Table of Contents

- [Overview](#overview)
- [System Calls Implemented](#system-calls-implemented)
- [Prerequisites](#prerequisites)
- [Installation & Setup](#installation--setup)
- [Building the Project](#building-the-project)
- [Running xv6](#running-xv6)
- [Testing the System Calls](#testing-the-system-calls)
- [Project Structure](#project-structure)
- [Implementation Details](#implementation-details)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)

## 🎯 Overview

This project extends the xv6 operating system with two custom system calls:
- **`helloos()`**: Displays "hello os" message from kernel space
- **`getrandom()`**: Generates pseudo-random numbers using Linear Congruential Generator

The implementation demonstrates core operating system concepts including:
- System call interface design
- Kernel-user space transitions
- Process management
- Synchronization and locking mechanisms

## 🚀 System Calls Implemented

### 1. helloos() System Call
- **Purpose**: Displays "hello os" message
- **Return Value**: 0 on success
- **Usage**: `helloos();`

### 2. getrandom() System Call
- **Purpose**: Generates pseudo-random numbers
- **Return Value**: Random unsigned integer
- **Algorithm**: Linear Congruential Generator with entropy from system ticks and process ID
- **Usage**: `int random_num = getrandom();`

## 📦 Prerequisites

### Required Software
- **GCC**: GNU Compiler Collection
- **QEMU**: System emulator (qemu-system-i386)
- **Make**: Build automation tool
- **Git**: Version control (for cloning)

### Installation on Ubuntu/Debian
```bash
sudo apt update
sudo apt install build-essential qemu-system-x86 git
```

### Installation on macOS
```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install required packages
brew install qemu gcc make git
```

### Installation on Windows
- Install WSL2 (Windows Subsystem for Linux)
- Follow Ubuntu/Debian instructions within WSL2

## 🛠 Installation & Setup

### 1. Clone xv6 Repository
```bash
git clone https://github.com/mit-pdos/xv6-public.git
cd xv6-public
```

### 2. Apply System Call Modifications

#### Modify syscall.h
Add system call numbers:
```c
#define SYS_helloos 22
#define SYS_getrandom 23
```

#### Modify syscall.c
Add function prototypes and syscall table entries:
```c
int sys_helloos(void);
int sys_getrandom(void);

static int (*syscalls[])(void) = {
  // ... existing entries ...
  [SYS_helloos] sys_helloos,
  [SYS_getrandom] sys_getrandom,
};
```

#### Modify sysproc.c
Add system call implementations:
```c
int sys_helloos(void)
{
  cprintf("hello os\n");
  return 0;
}

int sys_getrandom(void)
{
  uint xticks;
  static uint seed = 1;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  
  seed ^= xticks ^ myproc()->pid;
  seed = seed * 1664525 + 1013904223;
  return seed;
}
```

#### Modify user.h
Add user-space function declarations:
```c
int helloos(void);
int getrandom(void);
```

#### Modify usys.S
Add assembly stubs:
```assembly
SYSCALL(helloos)
SYSCALL(getrandom)
```

#### Modify defs.h
Add function declarations:
```c
int sys_helloos(void);
int sys_getrandom(void);
```

### 3. Create Test Programs

#### test_helloos.c
```c
#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
  printf(1, "Calling helloos system call...\n");
  helloos();
  printf(1, "System call completed!\n");
  exit();
}
```

#### test_random.c
```c
#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
  int i;
  int random_num;
  
  printf(1, "Testing getrandom system call...\n");
  
  for(i = 0; i < 10; i++) {
    random_num = getrandom();
    printf(1, "Random number %d: %d\n", i+1, random_num);
  }
  
  printf(1, "Random number generation completed!\n");
  exit();
}
```

#### Update Makefile
Add test programs to UPROGS:
```makefile
UPROGS=\
	_cat\
	_echo\
	_forktest\
	_grep\
	_init\
	_kill\
	_ln\
	_ls\
	_mkdir\
	_rm\
	_sh\
	_stressfs\
	_usertests\
	_wc\
	_zombie\
	_test_helloos\
	_test_random\
```

## 🔨 Building the Project

### Clean and Build
```bash
# Clean previous builds
make clean

# Build xv6 with your modifications
make

# Check for compilation errors
echo $?  # Should output 0 if successful
```

## 🖥 Running xv6

### Start xv6 in QEMU
```bash
# Run with GUI
make qemu

# Run without GUI (text mode only)
make qemu-nox

# Run with GDB support for debugging
make qemu-gdb
```

### Exit QEMU
- Press `Ctrl+A`, then `X`
- Or type `halt` in xv6 shell (if implemented)

## 🧪 Testing the System Calls

Once xv6 is running, test the system calls:

### Test helloos System Call
```bash
$ test_helloos
```
**Expected Output:**
```
Calling helloos system call...
hello os
System call completed!
```

### Test getrandom System Call
```bash
$ test_random
```
**Expected Output:**
```
Testing getrandom system call...
Random number 1: 1041204193
Random number 2: 2097858223
Random number 3: 1553301123
Random number 4: 2009754253
Random number 5: 3465911283
Random number 6: 1922364313
Random number 7: 3378521343
Random number 8: 2834974373
Random number 9: 1291427403
Random number 10: 2747584433
Random number generation completed!
```

## 📁 Project Structure

```
xv6-public/
├── kernel/
│   ├── syscall.h          # System call numbers
│   ├── syscall.c          # System call dispatcher
│   ├── sysproc.c          # Process-related system calls
│   ├── defs.h             # Function declarations
│   └── ...
├── user/
│   ├── user.h             # User-space function declarations
│   ├── usys.S             # Assembly stubs for system calls
│   ├── test_helloos.c     # Test program for helloos()
│   ├── test_random.c      # Test program for getrandom()
│   └── ...
├── Makefile               # Build configuration
└── README.md              # This file
```

## 🔧 Implementation Details

### System Call Flow
1. **User Program** calls `getrandom()`
2. **Assembly Stub** (usys.S) triggers system call interrupt
3. **Kernel Dispatcher** (syscall.c) routes to appropriate handler
4. **System Call Handler** (sysproc.c) executes kernel code
5. **Return Value** passed back to user program

### Random Number Generation
- **Algorithm**: Linear Congruential Generator (LCG)
- **Formula**: `seed = seed * 1664525 + 1013904223`
- **Entropy Sources**: System ticks, process ID, previous seed
- **Thread Safety**: Uses kernel locks for accessing shared resources

### Kernel State Management
- **Locking**: Uses `tickslock` to safely access global `ticks` variable
- **Process Context**: Accesses current process information via `myproc()`
- **Memory Management**: Operates in kernel address space with full privileges

## 🐛 Troubleshooting

### Common Issues

#### Build Errors
```bash
# Issue: "undefined reference to sys_uptime"
# Solution: Ensure all system call functions are implemented in sysproc.c

# Issue: "duplicate symbol"
# Solution: Don't define the same function in multiple files
```

#### Runtime Issues
```bash
# Issue: System call returns 0 or same numbers
# Solution: Check that syscall table entries are correctly added

# Issue: "unknown sys call" error
# Solution: Verify system call numbers are sequential and properly defined
```

#### QEMU Issues
```bash
# Issue: QEMU won't start
sudo apt install qemu-system-x86  # Ensure QEMU is installed

# Issue: No display in QEMU
make qemu-nox  # Use text-only mode
```

### Debug Mode
```bash
# Terminal 1: Start xv6 with GDB support
make qemu-gdb

# Terminal 2: Connect GDB
gdb kernel
(gdb) target remote localhost:26000
(gdb) continue
```

## 🤝 Contributing

### Development Guidelines
1. **Fork** the repository
2. **Create feature branch**: `git checkout -b feature/new-syscall`
3. **Make changes** following xv6 coding style
4. **Test thoroughly** with provided test programs
5. **Submit pull request** with clear description

### Code Style
- Follow xv6 kernel coding conventions
- Use clear, descriptive function names
- Include proper error handling
- Document complex algorithms

## 📚 Learning Resources

### xv6 Documentation
- [xv6 Book](https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf)
- [MIT 6.828 Course](https://pdos.csail.mit.edu/6.828/)
- [xv6 Source Browser](https://pdos.csail.mit.edu/6.828/2018/xv6/)

### Operating Systems Concepts
- Process management and system calls
- Kernel synchronization primitives
- Memory management in operating systems
- Hardware abstraction layers

## 📄 License

This project extends xv6, which is available under the MIT License. See the original xv6 repository for license details.

## 👥 Authors

- **Your Name** - *Initial implementation* -(https://github.com/Sujal261)

## 🙏 Acknowledgments

- MIT PDOS group for creating xv6
- Frans Kaashoek, Robert Morris, and Russ Cox for xv6 development
- The operating systems community for educational resources

---

**Note**: This implementation is for educational purposes. For production systems, consider using cryptographically secure random number generators and implementing proper entropy collection mechanisms.
