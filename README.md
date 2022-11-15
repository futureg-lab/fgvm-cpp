# fgvm-cpp
FutureG-lab Virtual Machine : LLVM wannabe programming language parser/compiler generator (IR code generation, JIT compilation, specific target compilation)
* Main goal is to build a easy to use compiler builder with a better developer experience.

# Creating a programming language with fgvm 
```
Source code ---> Lexer/Tokenizer ---> Parser ---> Intermediate code compilation (fgvm IR) ---> Linking ---> Interpret / JIT or Compilation to a specific target assembly : x86, ARM, WASM
```

# fgvm IR v1

## Description
1. fgvm IR is designed so that each line of code represents a single atomic assignement (literal assignement or function call) that holds a strongly typed value, a bloc definition or a function definition.
2. Any generated fgvm IR code is designed for parsers and compilers, not for humans !
3. The current spec supports external symbols for linking purposes and prebuilt functions, the syntax is also very minimalistic, `%var_name`, `func_name`, `@some_keyword`.

## IR Code example
Example fgvm IR code generated from the Brainf_ck program `+++[>+++++[>+++++<-]<-]>>----------.+++++.+++++++.----.++.----------.` :
```c
%mem_size = u32 255
%main_ptr = u32 alloc %mem_size
%curr_val = u8 get_val_addr %main_ptr
%curr_val = u8 incr %curr_val
%set_curr_val = u32 set_val_addr %main_ptr %curr_val
%curr_val2 = u8 get_val_addr %main_ptr
%curr_val2 = u8 incr %curr_val2
%set_curr_val2 = u32 set_val_addr %main_ptr %curr_val2
%curr_val3 = u8 get_val_addr %main_ptr
%curr_val3 = u8 incr %curr_val3
%set_curr_val3 = u32 set_val_addr %main_ptr %curr_val3
%curr_val4 = u8 get_val_addr %main_ptr
%zero = u8 0
%comp = bool eq %curr_val4 %zero
@loop %comp loop_bloc
@bloc loop_bloc: {
    %main_ptr = u32 incr %main_ptr
    %curr_val5 = u8 get_val_addr %main_ptr
    %curr_val5 = u8 incr %curr_val5
    %set_curr_val4 = u32 set_val_addr %main_ptr %curr_val5
    %curr_val6 = u8 get_val_addr %main_ptr
    %curr_val6 = u8 incr %curr_val6
    %set_curr_val5 = u32 set_val_addr %main_ptr %curr_val6
    %curr_val7 = u8 get_val_addr %main_ptr
    %curr_val7 = u8 incr %curr_val7
    %set_curr_val6 = u32 set_val_addr %main_ptr %curr_val7
    %curr_val8 = u8 get_val_addr %main_ptr
    %curr_val8 = u8 incr %curr_val8
    %set_curr_val7 = u32 set_val_addr %main_ptr %curr_val8
    %curr_val9 = u8 get_val_addr %main_ptr
    %curr_val9 = u8 incr %curr_val9
    %set_curr_val8 = u32 set_val_addr %main_ptr %curr_val9
    %curr_val10 = u8 get_val_addr %main_ptr
    %zero2 = u8 0
    %comp2 = bool eq %curr_val10 %zero2
    @loop %comp2 loop_bloc2
    @bloc loop_bloc2: {
        %main_ptr = u32 incr %main_ptr
        %curr_val11 = u8 get_val_addr %main_ptr
        %curr_val11 = u8 incr %curr_val11
        %set_curr_val9 = u32 set_val_addr %main_ptr %curr_val11
        %curr_val12 = u8 get_val_addr %main_ptr
        %curr_val12 = u8 incr %curr_val12
        %set_curr_val10 = u32 set_val_addr %main_ptr %curr_val12
        %curr_val13 = u8 get_val_addr %main_ptr
        %curr_val13 = u8 incr %curr_val13
        %set_curr_val11 = u32 set_val_addr %main_ptr %curr_val13
        %curr_val14 = u8 get_val_addr %main_ptr
        %curr_val14 = u8 incr %curr_val14
        %set_curr_val12 = u32 set_val_addr %main_ptr %curr_val14
        %curr_val15 = u8 get_val_addr %main_ptr
        %curr_val15 = u8 incr %curr_val15
        %set_curr_val13 = u32 set_val_addr %main_ptr %curr_val15
        %main_ptr = u32 decr %main_ptr
        %curr_val16 = u8 get_val_addr %main_ptr
        %curr_val16 = u8 decr %curr_val16
        %set_curr_val14 = u32 set_val_addr %main_ptr %curr_val16
    }
    %main_ptr = u32 decr %main_ptr
    %curr_val17 = u8 get_val_addr %main_ptr

/* ... truncated ... */

%curr_val60 = u8 get_val_addr %main_ptr
%curr_val60 = u8 decr %curr_val60
%set_curr_val53 = u32 set_val_addr %main_ptr %curr_val60
%curr_val61 = u8 get_val_addr %main_ptr
%print6 = bool stdout_print %curr_val61
```
