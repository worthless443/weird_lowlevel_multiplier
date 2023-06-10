# Multiply integers as you would do with vector multipication 
Aiming to use vector multipication instead of standard method of multipication between two natural whole integers and instead use vector of different dimentionss. 
# Core ideology
 * without needing any multipication instructions from the CPU
 * working only with bits to interpret base-10 integers as "components"(0)
# Try using
```bash
$ ./compile
$ ./mlt 142 669
normal -> 94998
explicit -> 94998
exiting with 1
```
## Work in progress
Only multipication with specific numbers (those which are possibly aligned) work and doesn't work for anything <100 and >1023 (1)

- **(0)** __Dissection into smaller whole 10 aligned numbers__
- **(1)** __not explained yet__
