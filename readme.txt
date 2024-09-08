assumptions:
if in case of "slli", "srli", "srai", we get imm value out of allowed bounds, we throw an error

supports identification of missing register or immediate value

not taking hex values in lui

checking opening and closing paranthesis condition in S format and I format

producing output file unless a error is encountered, terminates only after error

stress testing of load type instructions

check error for extra argument in the instruction

confirm the case of jalr(offset inside or outside the brackets)
