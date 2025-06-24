# PS6: RandWriter

## Contact
Name: William nosike
Section: 201
Time to Complete: 9 hours 

## Description

This project’s all about generating text using a Markov model. It looks at the input and builds a statistical map of character patterns—basically k-grams and what tends to come after them. It keeps track of how often each k-gram shows up, what characters follow them, and uses that info to create new text by randomly picking the next character based on those patterns.

### Features

Describe what your major decisions were and why you did things that way.

I used two separate maps to keep things clear—one to count how often each k-gram shows up, and another to track what characters follow each k-gram. It felt way simpler than trying to squeeze everything into one big structure.

When building the maps, I paid close attention to the loops so I wouldn’t go out of bounds or look for characters that aren’t there—stuff that could crash the program or mess up the results.

I also threw in a lambda function to sort characters by how often they appear. It made the code cleaner

### Testing
What tests did you write?  What exceptions did you use?  Does your code pass the tests?
1. **Comprehensive Test**  
   - Checks k-gram and k-gram-char frequencies for various k (0, 2, 3) using "aaabbc"  
   - Verifies order-0 model with "aabbc"  
   - Includes error handling for invalid inputs  

2. **Generation Test**  
   - Validates `kRand` with "abcabcabc" and text generation output  
   - Tests exception handling in `kRand` and `generate`  

**Exceptions:**  
- `std::invalid_argument` for:  
  - Text shorter than k in constructor  
  - Mismatched k-gram length in `freq`  
  - Missing k-gram in `kRand`  
  - Invalid text length in `generate`



### Lambda
What does your lambda expression do?  What function did you pass it to?
It compares two pairs based on their second elements (the frequency
 values) in descending order.I passed it to std::sort, which sorts the vector of character-frequency pairs.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.


One tricky part was figuring out how to randomly pick characters based on how often they show up. I handled it by first adding up all the frequencies of characters that follow a k-gram, then generating a random number within that total, and finally picking the character that matches that spot in the cumulative distribution.


### Extra Credit
Anything special you did.  This is required to earn bonus points.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

How to loop through a map.pdf






