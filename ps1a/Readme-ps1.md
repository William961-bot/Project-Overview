# PS1: LFSR / PhotoMagic

## Contact
Name: William Nosike

Section: 204

Time to Complete: 48hours


## Description
Explain what the project does.
 Fibonacci Liner FeedBack Shift Register
 This Project creates a system that generates random numbers,saves it for later use, and tests it to make sure it works correctly which later can be used for encrypting and decrypting an image. (PhotoMagic Part B)




### Features
Describe the representation you used and why you did things that way as well as any other interesting design decisions you made.

#### Part a
For part A i tried to go simple as i could.  I used the bitset library because it made the process easier and faster it allowed me to perform direct bit manipulation without needing complex bitwise operations .Using bitset helped in shifting and modfiting the register  which at the end made my code more readble and concise. with the addition of bitset helped me create (reg = std::bitset<16>(seed)) which is able to convert string to bitset.
As for the step() i had the idea to use an array to handle the tap postions but i decided again to go the safer and faster route. The approach i used has a faster execution and uses a direct XOR operations.As for the Design for the generate(k), i designed it to multiple bits efficiently.i used this approah because it uses bit shifiting << to maintain correct bit order while keeping the function fast and simple to read. and also chose this approach because of its ablity to call step() k times and ensuring each bit follows the LFSR transformation rules.

#### Part b

### Issues
What doesn't work.  Be honest.  You might be penalized if you claim something works and it doesn't.
Problems
1.Test Failed: ['PhotoMagic'] is not false : Missing compiled files:
	PhotoMagic
2 Your Tests vs: Wrong Insert (0/0)
3. Your Tests vs: Stream (0/0)
4.Your Tests vs: No-throw Constructor (0/0)
5.Your Tests vs: No-throw Generate (0/0)
6.TestThrowGenerate (0/2)

those are the problems as of now 










### Tests
Describe what is being tested in your Boost unit tests.
1.testStepInstr= Produces Correct bit Seguence and computes new bits based on the XOR tap positions.
2.testGenerateInstr(Testing generate(k))= Calls generate(9) to extract 9 bits and checks if the result matches 51.
3.testStepWithDifferentSeed(Verifying step() on a Different Seed)=Ensures that step() produces correct outputs for a different initial seed (1100101010110111).
4.testGenerateSingleBit(Extracting One Bit)=Ensures generate(1) returns exactly one bit, verifying correct bitwise shifting.
5.testGenerateMultipleValues( Extracting Multiple Values)=Extracts two separate 3-bit values (generate(3)) from the same LFSR instance.


### Extra Credit
Anything special you did. This is required to earn bonus points.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
1.https://en.cppreference.com/w/cpp/utility/bitset
2.https://www.geeksforgeeks.org/cpp-bitset-and-its-application/
3.https://youtu.be/2FUz5MAW1QA?si=paSi3IqtFYiyJsLO i just watched the video it help me a little bit 
4.https://www.gnu.org/software/make/manual/html_node/Substitution-Refs.html 



### Credits
List where you got any images or other resources.
1.Used the makefile from ps0 and altered it to make ps1a makefile
