# PS5: DNA Alignment

## Contact
Name: Jordan Charlot (Laptop)
Section:201

Partner:William Nosike
Partner Section:201

Time to Complete: 5 hours


## Description
Explain what the project does
his project implements optimal DNA sequence alignment using the Needleman-Wunsch dynamic programming algorithm 
to calculate edit distances and alignment paths between genetic sequences.
### Features
- **Data Structures**: 2D integer matrix for dynamic programming table
- **Alignment Logic**:
  - Match penalty: 0
  - Mismatch penalty: 1
  - Gap penalty: 2
  - Backtrace for alignment reconstruction
- **Optimizations**: O(nm) time/space complexity
### Testing
Describe what the unit tests you wrote check for and why you picked them.
Unit tests verify:
- Penalty calculations (matches=0, mismatches=1)
- Empty string handling
- Correct matrix initialization
- Alignment path reconstruction
### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.
- Fixed memory leaks in destructor
- Resolved Valgrind reachable blocks
- Memory limitations with sequences >50,000 bases

## Analysis

### Example
Do one additional test case by hand. It should be constructed in such a way that you know the correct  output before running your program on it, and it should be a "corner case" that helps check if your program handles all special situations correctly. 

Please list:
 - a copy of the test case input
 - the expected test case output
 - whether your program ran correctly on it or not
 - optionally, any other remarks

Input:
ACGT
A-GT
Expected Output:
Edit distance = 2
A A 0
C - 2
G G 0
T T 0
**Result**: Passed
### Specs
Your Computer
Memory: 16GB DDR4
Processors: AMD Ryzen 5 5600U

Partner's Computer
Memory: 16GB DDR4
Processors: AMD Ryzen 5 2600 Six-Core Processor

### Runs
Fill in the table with the results of running your code on both your and your partner's computers.

Using laptop

| data file     | distance | memory (mb) | time (seconds) | Personal PC time |
|---------------|----------|-------------|----------------|--------------|
|ecoli2500.txt  |  118     |     23.89   |   0.022709     |   0.042871   |
|ecoli5000.txt  |  160     |    95.56    |   0.105115     |   0.166738   |
|ecoli10000.txt |  223     |    382.16   |   0.410115     |   0.715933   |
|ecoli20000.txt |  3135    |    1528.64  |   1.69304      |   2.67692    |
|ecoli50000.txt |  19485   |    Killed   |   Killed       |  26.8548     | 
|ecoli100000.txt|          |    Killed   |   Killed       |    Killed    |




Here is an example from another computer for some of the files.

| data file    | distance | time (s) |
|--------------|----------|----------|
|ecoli2500.txt |      118 |    0.171 |
|ecoli5000.txt |      160 |    0.529 |
|ecoli7000.txt |      194 |    0.990 |
|ecoli10000.txt|      223 |    1.972 |
|ecoli20000.txt|     3135 |    7.730 |

### Time
Assume the two strings are the same length (M = N).  By applying the doubling method to the data points that you obtained, estimate the running time of youu program in seconds as a polynomial function of N, in the form a * N^b for some constants a and b.  Determine the largest input your program can handle if it is limited to one day of computation.

Provide a brief justification/explanation of how you applied the doubling method, and if you data seems not to work, describe what went wrong and use the sample data instead.
 - a =  3.63 × 10⁻⁹
 - b = 2
 - largest N = 1,542,000 bases
Doubling method shows consistent ~4x time increase when N doubles → confirms O(N²) complexity

Regression analysis yields:

a = 3.63 × 10⁻⁹ (time coefficient)

b = 2 (quadratic exponent)

Formula: Time (s) = 3.63 × 10⁻⁹ × N²

Max N in 1 day (86,400s):
N = √(86400 / 3.63 × 10⁻⁹) ≈ 1,542,000 bases
### Memory
Assume the two strings are the same length (M = N).  Look at your code and determine how much memory it requires as a polynomial function of N, in the form a * N^b for some constants a and b.  Determine the largest input size your computer can handle if limited to 8GiB of RAM.
 - a = 4.03 × 10⁻³
 - b = 2
 - largest N = 45,000 bases
- **Formula**: Time (s) = 3.63 × 10⁻⁹ × N²
- **Max sequence in 24h**: ~1,542,000 bases
### Valgrind
Run valgrind and list any errors you see.  Identify whether the memory usage reported by valgrind almost matches the calculations in the previous section.

| data file     | Calculated (mb) | Measured (mb) | Difference (%) |
|---------------|-----------------|---------------|----------------|
|ecoli2500.txt  |      23.89      |     23.20     |      -2.89%    |
|ecoli5000.txt  |      95.40      |     95.65     |     +0.26%     |
|ecoli10000.txt |      381.54     |      381.94   |     +0.10%     |
|ecoli20000.txt |      1528.64    |     1491.00   |     -2.46%     |
|ecoli50000.txt |      Killed     |   Killed      |     UNKNOWN    |
|ecoli100000.txt|    Killed       |     Killed    |     UNKNOWN    |

## Pair Programming
If you worked with a partner, do you have any remarks on the pair programming method? E.g., how many times did you switch, what are the tradeoffs of driving vs. navigating, etc.?

## Extra Credit
Anything special you did.  This is required to earn bonus points.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
- Stack Overflow community for debugging help
- Valgrind documentation for memory analysis
