# TriOS

TriOS is a small C++ balanced-ternary CPU/emulator project. It models a simple ternary computing platform with a six-trit word type, memory, registers, an assembler, a fetch/decode/execute CPU loop, and a minimal terminal monitor.

The project is intentionally low-level and educational: it explores how a custom CPU architecture can be represented in software without depending on a binary machine model.

## Motivation

Most introductory CPU emulators model binary machines. TriOS uses **balanced ternary**, where each trit can represent `-1`, `0`, or `1`, to experiment with a different numeric foundation and instruction architecture.

The current goal is not to provide a full operating system. Instead, TriOS is a small computing platform that can:

- represent ternary machine values,
- store data and encoded instructions in memory,
- assemble a small instruction set into memory,
- execute instructions through a CPU emulator,
- expose a simple interactive monitor for loading, running, and inspecting programs.

## Current Features

- **Balanced ternary primitives**
  - `Trit` values: `NEG = -1`, `ZERO = 0`, `POS = 1`.
  - `Tryte` values made from six trits.
  - Integer conversion for values in the range `-364` to `364`.
  - `Tryte` addition, subtraction, multiplication, equality, inequality, and prefix increment.

- **Memory model**
  - Fixed-size memory initialized to 200 `Tryte` cells.
  - Bounds-checked data reads and writes.
  - Fixed-width instruction reads and writes.
  - Each encoded instruction occupies four consecutive `Tryte` cells.

- **CPU emulator**
  - Register file containing `R0` through `R6`, `PC`, and `SP`.
  - Flags register containing `zero`, `carry`, `negative`, and `overflow` flags.
  - Fetch/decode/execute loop.
  - Host-side call stack for `CALL` and `RET`.

- **Instruction set**
  - Data movement: `LOAD`, `STORE`, `MOV`
  - Arithmetic: `ADD`, `SUB`, `MUL`
  - Comparison: `CMP`
  - Control flow: `JMP`, `JZ`, `CALL`, `RET`
  - Termination: `HALT`
  - Placeholder: `SYSCALL`

- **Assembler**
  - Assembles individual lines or files into memory.
  - Supports labels in source files.
  - Strips semicolon comments.
  - Treats opcodes case-insensitively.

- **Interactive monitor**
  - Assemble interactively.
  - Assemble from a file.
  - Run the CPU.
  - Read/write memory.
  - Dump general-purpose registers.
  - Reset CPU state.

- **Tests and build tooling**
  - `Makefile` build targets.
  - Assertion-based C++ tests for core behavior.

## Architecture

TriOS is organized as a small emulator stack:

```text
Terminal monitor (main.cpp)
        |
        v
Assembler  ------------------+
        |                    |
        v                    |
Memory <---------------------+
        |
        v
CPU fetch/decode/execute loop
        |
        v
Registers, flags, call stack
        |
        v
Tryte arithmetic
        |
        v
Trit values
```

### Major Components

| Component | Path | Responsibility |
| --- | --- | --- |
| Monitor | `main.cpp` | Provides the command-line interface for assembling, running, memory access, register dump, reset, and exit. |
| Ternary values | `trit/` | Defines `Trit` and `Tryte`, including balanced-ternary conversion and arithmetic. |
| Logic gates | `logic/` | Defines simple ternary `NOT`, `AND`, and `OR` gates. These are currently separate from CPU execution. |
| Memory | `memory/` | Stores data and encoded instructions as `Tryte` values. |
| CPU | `cpu/` | Owns registers/flags/call stack, fetches instructions, decodes opcodes, and executes instructions. |
| Assembler | `assembler/` | Parses assembly text and writes encoded instructions into memory. |
| ALU | `alu/` | Placeholder for a future dedicated arithmetic/logic unit. Current arithmetic is performed through `Tryte` operations. |
| Tests | `tests/` | Contains assertion-based tests for core emulator behavior. |

## How It Works Internally

### Balanced ternary data model

A `Trit` is a single balanced-ternary digit:

```cpp
NEG  = -1
ZERO = 0
POS  = 1
```

A `Tryte` stores six trits. Because it uses balanced ternary, a six-trit `Tryte` represents integer values from `-364` through `364`.

### Instruction encoding

Instructions are encoded as four `Tryte` values in memory:

```text
[ opcode ][ arg1 ][ arg2 ][ arg3 ]
```

For example, this assembly instruction:

```asm
ADD R3 R1 R2
```

is stored as something equivalent to:

```text
[ ADD ][ R3 ][ R1 ][ R2 ]
```

Since every instruction is four `Tryte` cells wide, normal sequential execution advances the program counter by `4` after most instructions.

### CPU execution loop

The CPU starts at an address, stores that address in `PC`, and then repeats:

1. Read four `Tryte` cells from memory at `PC`.
2. Decode the opcode `Tryte` into an `Opcodes` enum value.
3. Execute the instruction.
4. Update registers, flags, memory, or `PC`.
5. Stop when `HALT` is executed.

### Registers

The CPU register file contains nine indexed registers:

| Register | Index | Purpose |
| --- | ---: | --- |
| `R0` | 0 | General-purpose register |
| `R1` | 1 | General-purpose register |
| `R2` | 2 | General-purpose register |
| `R3` | 3 | General-purpose register |
| `R4` | 4 | General-purpose register |
| `R5` | 5 | General-purpose register |
| `R6` | 6 | General-purpose register |
| `PC` | 7 | Program counter |
| `SP` | 8 | Stack pointer |

`CALL` and `RET` currently use a host C++ `std::stack<Tryte>` for return addresses rather than a memory-backed emulated stack.

### Assembly source files

The assembler supports simple whitespace-separated assembly syntax:

```asm
LOAD R0 100
LOAD R1 101
ADD R2 R0 R1
HALT
```

File assembly also supports labels:

```asm
loop:
ADD R3 R0 R1
JMP loop
```

Semicolon comments are ignored:

```asm
LOAD R0 100 ; load memory[100] into R0
```

## Instruction Set

| Instruction | Form | Description |
| --- | --- | --- |
| `LOAD` | `LOAD <reg> <addr>` | Load memory at `<addr>` into `<reg>`. |
| `STORE` | `STORE <reg> <addr>` | Store `<reg>` into memory at `<addr>`. |
| `MOV` | `MOV <dst> <src>` | Copy `<src>` register into `<dst>`. |
| `ADD` | `ADD <dst> <lhs> <rhs>` | Add two registers and store the result in `<dst>`. |
| `SUB` | `SUB <dst> <lhs> <rhs>` | Subtract `<rhs>` from `<lhs>` and store the result in `<dst>`. |
| `MUL` | `MUL <dst> <lhs> <rhs>` | Multiply two registers and store the result in `<dst>`. |
| `CMP` | `CMP <lhs> <rhs>` | Compare two registers and update flags. |
| `JMP` | `JMP <addr>` | Set `PC` to `<addr>`. |
| `JZ` | `JZ <addr>` | Jump to `<addr>` if the zero flag is set. |
| `CALL` | `CALL <addr>` | Push return address and jump to `<addr>`. |
| `RET` | `RET` | Return to the most recent call address. |
| `HALT` | `HALT` | Stop CPU execution. |

`SYSCALL` is declared in the opcode enum but is not currently assembled or implemented beyond a placeholder execution branch.

## Tech Stack

- C++17
- Standard C++ library only
- `make`
- `g++` or another C++17-compatible compiler

No third-party libraries are required.

## Project Structure

```text
TriOS/
├── main.cpp                    # Interactive monitor entry point
├── Makefile                    # Build and test targets
├── program.tri                 # Example assembly source file
├── Notes                       # Early design notes and project direction
├── arch.md                     # Early architecture notes
├── todo.md                     # Future work backlog
├── trit/
│   ├── trit.hpp                # Trit enum
│   ├── tryte.hpp               # Tryte interface
│   └── tryte.cpp               # Tryte implementation
├── logic/
│   ├── gates.hpp               # Ternary gate interfaces
│   └── gates.cpp               # Ternary gate implementations
├── memory/
│   ├── memory.hpp              # Memory interface
│   └── memory.cpp              # Memory implementation
├── cpu/
│   ├── cpu.hpp                 # CPU interface
│   ├── cpu.cpp                 # CPU register access and run loop
│   ├── instruction.hpp         # Opcode and instruction definitions
│   ├── instructionHandler.cpp  # Decode and execute logic
│   ├── register.hpp            # Register and flag definitions
│   └── register.cpp            # Register parser
├── assembler/
│   ├── assembler.hpp           # Assembler interface
│   ├── assembler.cpp           # Assembly parsing and file processing
│   └── assembleLoader.cpp      # Instruction encoding helpers
├── alu/
│   ├── alu.hpp                 # Placeholder
│   └── alu.cpp                 # Placeholder
└── tests/
    └── test_trios.cpp          # Assertion-based test executable
```

## Installation and Setup

### Prerequisites

Install:

- `make`
- a C++17 compiler such as `g++`

On many Linux systems:

```bash
sudo apt install build-essential
```

### Build

```bash
make
```

This builds the `trios` executable in the repository root.

### Run tests

```bash
make test
```

### Clean generated binaries

```bash
make clean
```

## Usage

Start the monitor:

```bash
./trios
```

You should see:

```text
Booting TriOS v1...
Enter a command (assem, fassem, run, mem, fetmem, regdump, reset, exit):
```

### Monitor commands

| Command | Description |
| --- | --- |
| `assem <address>` | Assemble instructions interactively starting at `<address>`. End input with `END`. |
| `fassem <filename>` | Assemble a source file into memory starting at address `0`. |
| `run` | Run the CPU from address `0`. |
| `mem <address> <value>` | Write a raw `Tryte` value into memory. |
| `fetmem <address>` | Read and print memory at an address. |
| `regdump` | Print registers `R0` through `R6`. |
| `reset` | Reset CPU registers and call stack. |
| `exit` | Exit the monitor. |

### Example: interactively add two values

```text
mem 100 5
mem 101 7
assem 0
LOAD R0 100
LOAD R1 101
ADD R2 R0 R1
STORE R2 102
HALT
END
run
fetmem 102
```

Expected final memory query:

```text
Value at address 102: 12
```

During execution, the CPU currently prints debug traces for each executed instruction.

### Example: assemble from `program.tri`

`program.tri` contains a small loop using labels. It expects data to already exist in memory addresses `100`, `101`, `102`, and `103`.

A typical run is:

```text
mem 100 0
mem 101 1
mem 102 10
mem 103 1
fassem program.tri
run
regdump
```

The sample program currently computes values internally and can be inspected with `regdump`; the emulator does not yet have a print syscall or console-output instruction for assembly programs.

## Configuration

TriOS currently has no runtime configuration files and does not read environment variables.

The main build-time configuration is in `Makefile`:

- `CXX` defaults to `g++`
- `CXXFLAGS` defaults to `-std=c++17 -Wall -Wextra -pedantic -I.`

You can override them when invoking `make`:

```bash
make CXX=clang++ CXXFLAGS="-std=c++17 -Wall -Wextra -pedantic -I."
```

## Testing

The test suite is a single assertion-based C++ executable built by `make test`.

Current coverage includes:

- `Tryte` default initialization and arithmetic,
- memory reset behavior,
- CPU register mapping consistency,
- CPU execution of a basic `LOAD`/`HALT` program,
- assembler comment handling and label resolution.

Run it with:

```bash
make test
```

## Benchmarking

No benchmarking suite or performance measurements are currently present.

## Current Limitations

TriOS is an early emulator prototype. Important current limitations include:

- No standalone OS kernel, process model, scheduler, filesystem, or virtual memory.
- No implemented system-call interface; `SYSCALL` is only a placeholder.
- No assembly-level output instruction yet, so programs cannot print directly.
- No division, modulo, push/pop, conditional jumps beyond `JZ`, interrupts, or traps.
- No real emulated stack memory; `CALL`/`RET` use a host C++ stack.
- `SP` exists but is not actively used by instruction execution.
- The ALU module is a placeholder; arithmetic is currently implemented through `Tryte` operations.
- The ternary logic gates are implemented separately but are not integrated into the CPU execution pipeline.
- Memory is fixed at 200 `Tryte` cells.
- Instructions are fixed-width and occupy four `Tryte` cells each.
- The assembler has basic label/comment support but not a complete source language, symbol table diagnostics, constants, variables, or data sections.
- `.MEM` and `.MEMO` directives are currently ignored/reserved rather than implemented.
- CPU execution prints debug output directly to standard output.

## Future Improvements

Planned or natural next steps include:

- Implement a dedicated ALU module and route arithmetic/logic instructions through it.
- Add `DIV`, `MOD`, `PUSH`, `POP`, `JNZ`, relational jumps, `NOP`, and interrupt-related instructions.
- Implement `SYSCALL` and basic monitor/OS services such as printing.
- Add memory-backed stack behavior using `SP`.
- Expand the assembler with diagnostics, constants, data directives, variables, and a clearer source format.
- Add a disassembler and debugger commands such as step, breakpoints, traces, memory dump, and register dump.
- Add tests for every instruction and edge cases around arithmetic overflow/range behavior.
- Document the instruction set architecture, memory map, calling convention, and executable format as they stabilize.

## Technical Summary

TriOS is a C++17 balanced-ternary CPU emulator that demonstrates the core pieces of a custom machine architecture: ternary numeric representation, memory, registers, instruction encoding, assembly parsing, and a fetch/decode/execute runtime. It is intentionally compact, testable, and low-level, making it a useful platform for experimenting with ternary computing concepts and emulator design.
