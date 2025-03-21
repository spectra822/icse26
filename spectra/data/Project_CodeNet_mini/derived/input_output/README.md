# Input and Output Files



This is a collection of txt files that contain sample input and corresponding sample output for problems. They were extracted from the problem description html files using a Python program. Only the first sample input and sample output that were found in any given problem description are included.  Within the "data" folder, there is one directory for every problem number for which both input and output were found. For 132 problem descriptions, sample input and/or sample output was not found.

An input file for any given problem can be fed into a solution program and the program output will ideally match the output file. Sometimes, however, solution program output and the output file will not be exact matches due to formatting differences. For example, some problems allow solutions to have several different variations (e.g. different numbers of decimal places).

### Missing Accepted Solutions

There are 21 problems that did not have any accepted solutions in the four programming languages that we focused on (i.e. C, C++, Python, Java) . These can be found in **"no_solutions.txt"**.

### Verifying Input and Output Files

For every problem, input was fed into accepted solution programs in order to check if the output from the solution program matched the output file. We checked accepted solution programs in C, C++, Python, and Java. We considered problem input and output to be "verified" if program output matched the output file for at least one tested program in any of the four programming languages used. As mentioned, there may be differences in formatting of solutions. Thus, "verified" problem input will not always produce output that is identical to the output file in accepted programs. There are 3,574 problems with verifed input and output files.

There are 272 problems for which none of the accepted solution programs that we tested produced output that matched the output files. These problems with "unverifed" input and output files can be found in **"unverified_accepted_solutions.txt"**. This file does not contain problems that had no accepted solutions in C, C++, Python, or Java.

### Input Files

Every problem number directory contains a file named "input.txt", which contains sample input.

e.g. data/p00003/input.txt:

```
3
4 3 5
4 3 6
8 8 8
```

### Output Files

Every problem number directory also contains a file named "output.txt". This file contains the correct output for a solution program when using the sample input for that problem. 

e.g. data/p00003/output.txt:

```
YES
NO
NO
```



