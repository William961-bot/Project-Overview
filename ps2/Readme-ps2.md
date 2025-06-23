# PS2: Triangle Fractal

## Contact
Name: William Nosike
Section:201

Partner Name: Jordan Charlot
Partner Section: 201

Time to Complete: 4 hours


## Description
This program creates a recursive Triangle Fractal and also offers a unique take on the Sierpiński Triangle, using SFML. The program deals with two command line arguments: L, which represents the length of the base equilateral triangle, and N, which determines the recursion depth. The fractal is drawn recursively by splitting each triangle continuing until the set recursion depth is reached. The SFML window takes care of the rendering making sure that the fractal remains properly scaled and centered.

### Features
Recursive Generation: Each parent triangle spawns three smaller child triangles, ensuring geometric consistency.
Efficient Rendering: The SFML's VertexArray is used for optimized drawing, while ConvexShape defines individual triangles.
Color Gradient: The fractal incorporates a gradient effect that varies with recursion depth, enhancing visual appeal.
Dynamic Rotation: This is an optional rotation parameter lets users rotate the entire fractal, set via command-line arguments.
Interactive Animation: The fractal's rotation can be animated during runtime for a more engaging visual experience.

Modified Sierpinski Triangle: Unlike traditional Sierpinski triangles that leave the central area empty, our implementation fills the central triangle, creating a different visual effect where child triangles form a complete ring.

Precise Triangle Positioning: We carefully calculated the positions of triangle vertices using mathematical formulas to ensure proper equilateral triangle proportions (using length * √3/2 for height) and centered the entire fractal in the 800x800 window.

### Changes Made
1. **Triangle Positioning (Lines 9-23)**: Improved the triangle positioning to center it properly on screen and make it point downward.
   - Added mathematical calculations to create a proper equilateral triangle
   - made sure the triangle is centered in the 800x800 window
   - Used height calculation with √3/2 formula for proper proportions

2. **Recursion Depth Fix (Line 23)**: Added +1 to fix recursion depth issue.
   - This ensures the correct number of recursion levels are generated

3. **Central Triangle Fill (Lines 41-48)**: cahnged  the traditional Sierpinski algorithm to fill the central triangle.
   - Traditional Sierpinski triangles leave this area empty
   - central triangle with a different color
   - Creates a unique visual effect where child triangles form a complete ring

### Issues
The problems are as follows:
Performance Bottlenecks: When the recursion depth exceeded seven, the exponential growth in the number of triangles significantly slowed rendering. Ensuring that the fractal was fully contained within the SFML window required careful adjustments to the base triangle's position and scaling.
Precision Errors: Floating-point arithmetic introduced slight misalignments at deeper recursion levels.
Recursion Depth Adjustment: We needed to adjust the recursion depth calculation (adding +1) to fix an issue with the intended depth not being correctly achieved.

### Extra Credit
The optional rotation parameter allows the user to specify an initial orientation, with smooth animation incorporated to modify the angle dynamically. These additions make the fractal more visually appealing and interactive. Note: if you press the spacebar, you can pause and resume the rotation of the triangle.

## Pair Programming
How did working with a partner affect your work?
Working with a partner significantly improved the development process by allowing us to debug and brainstorm more efficiently. I worked on the rotation logic, color interpolation and performance while my partner Jordan focused on fractal geometry, and SFML integration, implementing recursion. We did a switch roles system where we switched roles every thirty to forty minutes. We did this to ensure that we could equally contribute to coding and reviewing each other's work.

List all sources of help including the instructor or TAs, classmates, and web pages.
https://www.sfml-dev.org/tutorials/2.6/
https://www.sfml-dev.org/documentation/2.6.1/