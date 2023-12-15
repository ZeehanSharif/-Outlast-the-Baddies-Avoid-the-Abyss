# -Outlast-the-Baddies-Avoid-the-Abyss
It's a fun adventure-based game where we have a hero (our protagonist) trying to maneuver through different enemies and obstacles to reach "a ladder" and win the game.

Our game is played on an arbitrarily sized rectangular grid, where each cell can contain a variety of different occupants:

The user plays as the Hero (H), who is trying to exit the board by navigating to
the Escape Ladder (*), but there are many obstacles in the way: 
Wall (+) cells are barriers that can not be landed on, 
Abyss (#) cells are holes in the floor that lead to the demise of any object that lands on it, 
Regular Monsters (m) continually seek to capture the hero, one step at a time either/both vertically or/and horizontally,
Super Monsters (M) continually seek to capture the hero, but must take two steps at a time either/both vertically or/and horizontally, and
Bats (~) continually seek to occupy the hero's column, but cannot change rows.

Once the initial board is set up, the cells occupied by Walls, Abysses, and the exit EscapeLadder will never change (i.e. they are static). However, the Hero and Baddies (regular Monsters, super Monsters, and Bats) will move throughout the board. 

Whereas the Hero (i.e. the user) can see the entire board to build a strategy for navigating an escape path while avoiding Abyss cells and Baddies, a misstep by the Hero, where they move into an Abyss cell or a cell occupied by a Baddie, results in their demise with the Hero being removed from the board and the end of the game; this is a losing result. However, if the Hero reaches the EscapeLadder successfully, then they have escaped, which also results in the Hero being removed from the board and the end of the game; in this case, we have a winning result! 

The Baddies, on the other hand, have a single focus of capturing the Hero. Each type of Baddie makes moves following their specific movement rules that only depend on the Hero's position, with no regard for avoiding Abyss cells:

Regular Monsters compare their current position (row and column) on the board to the Hero's position (row and column) and take 1-step toward the Hero horiztonally and/or 1-step toward the Hero vertically. 
Super Monsters do the same comparison of their position to the Hero's position, but are much bigger than regular Monsters and, therefore, MUST take 2-steps toward the Hero either/both horiztonally or/and vertically. Super Monsters are unable to only take 1-step movements in either direction. 
Finally, Bats immediately fly to the Hero's column, but can never leave their initial row. 
The Hero and all Baddies are not allowed to end their move on a Wall cell OR go beyond the edge of the board. Attempted out-of-bounds moves are dealt with by separately checking the horizontal and vertical components of the movement, and ignoring either OR both components that put the Hero or Baddie out-of-bounds. Attempted movements onto a Wall need a little bit more care since Wall cells can be anywhere: attempts to move onto a Wall are dealt with by completely ignoring the horizontal portion of the attempted move and only moving vertically, unless that is still a Wall, in which case the attempted move is completely ignored and they stay put for that round. Here is what that means for the various types of attempted movements:

if the Hero or a Baddie attempts to move perfectly horiztonally to end on a Wall, then their attempted move is ignored and they stay put for that round;
if the Hero or a Baddie attempts to move perfectly vertically to end on a Wall, then their attempted move is ignored and they stay put for that round.
if the Hero or a Baddie attempts to move diagonally to end on a Wall, then the horizontal portion of their movement is ignored and their attempted move is updated with the vertical portion only; then, their attempted move is checked again for a Wall.
One special case is that the exit EscapeLadder acts a Wall cell for the Baddies, but it is the (ONLY) exit cell for the Hero.

Since the movement of the Baddies is predictable, a successful Hero's strategy is to move in such a way that will cause each Baddie to fall into an Abyss cell. This can be challenging and/or impossible depending on the random arrangement of the initial board (quantity and location of Abyss cells, quantity and location of Baddies, etc.).
