# Question 1: Technical explanation

## How the program is built

This program is built with three jobs that are separate. `temperature_deviation` shows the difference between the given temperature and the the expected temperature and it gives the results as a positive number. `calculate_index` applies the formula in the brief and `classify_water` labels the index into Good, Warning, or Critical. `main` is for reading the inputs, calls the other functions, and printing the formatted results.

## a. Real word applications of the imbedded systems

We could use the example of heat sensors that are used to auto-light the bulbs or even open doors. When heat or movement is sensed around a given parameter, the system is then given signals to light bulbs or open doors as it is a signal that a person is passing by. This is very helpful as it helps to limit the amount of energy lost in electricity or even in the personal efforts and makes the work a lot easier.

C suites these kinds of applications for some reasons. It compiles to small machine code that fits in a microcontroller with a few kilobytes of memory. It lets the programmer talk to the hardware directly through registers and pointers, which is needed to read sensors and drive radios. We do not need the use of garbage collectors nor virtual machines, which makes the timing predictable and quick. Also, almost every microcontroller use C, so this will make it easy as the same skills cross or over the chips used.

## b. Error analysis

1. Sytanx error:
While working on it, forgetting the commas and semi-colons always made it difficult for me to compile and it always require to much attention for it.

2. Semantic error:
This was mainly caused by data types declared. For example, turbidity was declared as an interger before and when we had a temperature of 35, we would always get 17 instead of 17.5. This would make the code run and it was hard to catch the errors until I just remembered it by myself.
Also I forgot to me the deviation positive and this made it more difficult and it pushed the index up instead of down when the deviation was negative.

## c.Compilation lifecycle

The processes that went on while converting out `water_quality.c` program into an executable codes are:

1. Preprocessing: This is where the program reads all the `#` and then pastes in their content. Here it replaces `IDEAL_TEMPERATURE` with `25.0` everywhere, brings the contents of `include <stdio.h>`, and also removes all the comments of the user. The codes are now larger as some other things are imported. We go from the `source code` to the `Preprocessed code`. I used `gcc -E water_quality.c -o water_quality.i`
2. Compilation: here, the processor check for syntax, data types, and reports errors. It also compiles the code into assembly instructions for the target processor. We change the file from `preprocessed code` to `assembly code`by using `gcc -S water_quality.i -o water_quality.s`
3. Assembly: it takes the assembly file and changes it into a machine readable files. This file  still has unresolved references to `printf` and `scanf`, because those live in the C standard library. Here we go from `assembly code` to `object code` by using `gcc -c water_quality.s -o water_quality.o`.
4. Linking: now here the machine readable object codes are linked to the standard libraries. It also adds the standard code and the `main()`. We go from `object code` to `executable binary` and I used `gcc water_quality.o -o water_quality`.

When we run `gcc water_quality.c -o water_quality`, all these are done just in one step.


