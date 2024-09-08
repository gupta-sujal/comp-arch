Assumptions:

if in case of "slli", "srli", "srai", we check if the imm value is out of allowed bounds or in Hex format.

For lui format, the given immediate values should be in decimal.

Checking opening and closing paranthesis condition in S format and I format

Producing output file unless a error is encountered, terminates only after error


Error Handling: 

For a given instruction, we check for any missing register or immediate value for e.g and t2, t5, .

We check for the immediate values that each of their character must be a digit. This restricts the user from giving inputs like “12a” as an immediate value.

We are checking the availability of the input file and prevent running into error in case the user has input file missing or named something else.

We check if there are missing register or immediate values in the instruction line such as “add x2, x3,”.  The limits of the immediate values is also checked. 

For B and J type instructions, we check that the label being used is a valid label, that is actually present in the input file.

we have used some inbuilt functions such as stoi (for string to integer conversion), compare(t check the equality of strings), find(to find the index of a char in string).
