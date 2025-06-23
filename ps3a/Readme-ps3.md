# PS3: N-Body Simulation 

## Contact
Name:William Nosike 
Section: 201
Time to Complete: 8Hours(redo)


## Description
Explain what the project does.
n body sim is basically a graphical sim of the solar system while using an sfml to show it . the system is divded into three major parts ....
1. CelestialBody (individual planets/stars):This represents a single celestial body (e.g., the sun, Earth, Mars
2. Universe (a container for all celestial bodies):This represents the solar system, containing all celestial bodies.
3. Main Program (orchestrates the simulation)






### Features
Describe what your major decisions were and why you did things that way.

In designing this N-Body simulation, I made some decisions to make my
  code easy to read and efficient. I changed up the celestialbody.hpp or
  in the case used as guide to construct the cpp. I added getters and
  setters for the object mass, object velocity, object position to make
  my code better encapsulated... some other features are the
  std::unique_ptrsf::Texture pointer this really helped me because when I
   run the program I had the white squares. This helped so much in
  keeping or preventing memory leaks another feature I would say is the
  adding of public methods for stream operations instead of friend
  functions. I made methods like loadFromStream and writeToStream that
  the operators use. I also added parameterized constructors and proper copy/move operations another feauture is the addbody method .i made this method so that bodies can be addedd after the universe creation.this feature was added to make the univerese class more flexbile.......i was also able to perform two tests there are CelestialBody_IO Test Case,Universe_IO TestCase
CelestialBody_IO:Verifies that CelestialBody correctly reads and writes its properties using streams.Universe_IO:Checks if Universe correctly reads and writes multiple celestial bodies, making sure of  proper formatting of n (number of bodies) and radius.


### Memory
Describe how you managed the lifetimes of your objects, including if you used smart pointers.

In my implementation, I managed object lifetimes efficiently using
  smart pointers (std::unique_ptr) to handle texture management within
  CelestialBody. Each instance of CelestialBody owns a
  std::unique_ptrsf::Texture, ensuring that textures are automatically
  deallocated when no longer needed, preventing memory leaks

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.
as of now i have no issues 

### Extra Credit
Anything special you did.  This is required to earn bonus points.
If you created your own universe file.  Describe it here and explain why it is interesting.

i was able to add stars to the project. i added it to give the solar system more life. the background was made by randomly placing white pixels that can be used to represent stars.



## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.
1.https://www.youtube.com/watch?v=L9N7ZbGSckk this is a video i watched 
2.https://www.sfml-dev.org/development/style/#use-of-pointers-and-references checked out more on the use of pointers it helped a little bit 
3.
4.
5.
6.













