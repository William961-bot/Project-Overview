# PS3: N-Body Simulation



## Contact

Name:William Nosike 

Section: 201

Time to Complete: 24Hours





## Description

Explain what the project does.

n body sim is basically a graphical sim of the solar system while using an sfml to show it . the system is divded into three major parts ....

1. CelestialBody (individual planets/stars):This represents a single celestial body (e.g., the sun, Earth, Mars

2. Universe (a container for all celestial bodies):This represents the solar system, containing all celestial bodies.

3. Main Program (orchestrates the simulation)

4 Physics : It has physics that Computes gravitational forces usng Newton's law of universal gravitation between bodies.







### Features

Describe what your major decisions were and why you did things that way.

In designing this N-Body simulation, I made some deciscions to make my code easy to read and efficent. i changed up the celestialbdody.hpp or in the case used as guide to construst the cpp. i removed the getter for the object mass,object velocity, object postion because for reason my whole code became chunky and confusting so i decided to remove it....some other features are the  std::shared_ptr<sf::Texture> pointer this really helped me because when i run the program i had the white squares. this helped so much in keeping  or preventing memory leaks another feature i would say is the adding of friend function .I made the stream operators (operator>> and operator<<) as friend functions of the Universe class.i did this so that the operators can access the private members of Universe (like radius_ and bodies_).another feauture is the addbody method .i made this method so that bodies can be addedd after the universe creation.this feature was added to make the univerese class more flexbile.......i was also able to perform two tests there are CelestialBody_IO Test Case,Universe_IO Test Case
CelestialBody_IO:Verifies that CelestialBody correctly reads and writes its properties using streams.Universe_IO:Checks if Universe correctly reads and writes multiple celestial bodies, making sure of  proper formatting of n (number of bodies) and radius.

PARTb:
Part B: My Implementation of the N-Body Simulation(CelestialBody class has been extended with methods to update position and
  velocity)
In Part B, I built the physics engine to simulate gravitational interactions between celestial bodies. I improved code readability, added new getter methods for physics calculations, and updated header files for better organization.
 i also made a little adjument  to std::unique_ptr in main.cpp for managing the Universe object. Built a loop that runs until T is reached, outputting the final state. as for the unit test  i added one test for for the physics simulation it is a simple test that  Checks if gravity correctly moves Earth toward the Sun and also Checks if orbital motion correctly increases VY
 some new funtions were also added to the mix (calculateForces,step ) which handle most of the code.



### Memory

Describe how you managed the lifetimes of your objects, including if you used smart pointers.

In my implementation, I managed object lifetimes efficiently using smart pointers (std::shared_ptr) to handle texture management within CelestialBody. . Each instance of CelestialBody owns a std::shared_ptr .....<sf::Texture>, ensuring that textures are automatically deallocated when no longer needed, preventing memory leaks.



### Issues

What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

I had more trouble with test cases. My code had to changed aot of times but at the end i was able to figure it out. as now the Your Tests vs: Leapfrog (0/1),Your Tests vs: Fixed deltas. i could not figure out the leapfrog so i used the Euler method for step


### Extra Credit

Anything special you did.  This is required to earn bonus points.

If you created your own universe file.  Describe it here and explain why it is interesting.







## Acknowledgements

List all sources of help including the instructor or TAs, classmates, and web pages.

If you used images or other resources than the ones provided, list them here.


1.https://www.sfml-dev.org/development/style/#use-of-pointers-and-references checked out more on the use of pointers it helped a little bit 

2.https://www.geeksforgeeks.org/fill-and-fill_n-functions-in-c-stl/

3.https://www.geeksforgeeks.org/hypot-hypotf-hypotl-c/

5.

6.



























