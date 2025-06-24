# PS4: Sokoban

## Contact
Name: William Nosike
Section: COMP 2040 P 1 201
Time to Complete: 7 hours 


## Description
Explain what the project does.
This is a Sokoban puzzle game where the player pushes crates onto specific storage locations within a confined grid-based map. The game works using the SFML library. It reads the level layout from a file and displays the walls, boxes, storage spots, and player on the screen.


### Features
Describe what your major decisions were and why you did things that way.

#### Part a
One of the main decisions I made was using the PIMPL pattern with std::unique_ptr to separate the interface from the implementation, which helped keep Sokoban.hpp clean and easier to manage. I also set up a grid based game board using an enum called CellType to represent different states like  the (Empty, Wall, Box, Storage, BoxStorage, Player).For file I/O, I used operator overloading (>> and <<) to make loading and saving levels more straightforward. I chose a character-based level format to keep level design simple (# for walls, @ for player, A for boxes, a for storage locations).

#### Part b
I made a lot of changes to my code because of my test cases. My code was too robust and confusing, so I simplified it significantly. First, I removed the PIMPL pattern because it became too confusing and was difficult to handle. I also changed the way my textures are loaded. With the removal of the PIMPL pattern, everything in my code is now more direct.i also improved my won logic and reset functionality 




### Memory
Describe how you decided to store the level data including whether you used smart pointers.
For managing the internal stuff, I used std::unique_ptr with the PIMPL pattern. It handles cleanup automatically, so I don’t have to worry about deleting things manually or memory leaks.

i also stored the level in a 1D vector (std::vector<CellType> grid) to represent the game.I use a basic formula (x + y * width) to turn 2D coordinates into a single index in the vector.

The player position is stored separately as an sf::Vector2u, keeping
  movement logic clean and separate from the grid representation itself.
  For reset functionality, the original state is preserved in separate
  member variables (m_originalGrid and m_originalPlayerPosition).


### Lambdas
Describe what <algorithm> functions you used and what lambda expressions you wrote.

i used lambda for my draw method .This lambda encapsulates the sprite positioning and drawing logic,making the code more readable.


### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

right now locally there is no problems but on autograder i 
i have Your Tests vs: Can't move (0/0)
1.7) Your Tests vs: Lots of Boxes (0/0)
1.8) Your Tests vs: Lots of Targets (0/0)
3.1) TestAutowin (0/1)
7.1) TestLevelMoreBoxes (0/1)

### Extra Credit
Anything special you did.  This is required to earn bonus points.


## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.

Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban
https://www.geeksforgeeks.org/pimpl-idiom-in-c-with-examples/
https://www.pngegg.com/en/png-pmuop
