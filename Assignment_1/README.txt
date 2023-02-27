- Each player is represented as a vector element.
  The value of each element represents the role of each player.
  Citizen --> 0, Doctor --> 1, Gangster --> 2. 

- Since for the user players numbering starts from 1, the program
  uses player's id as the main variable and not the player's index
  inside the vector.

- If in night phase there is no available doctor, then the player chosen 
  by the gangster is leaving the game.

Players are allowed to vote themselves.

cin reads up to '.' if needs int and leaves . in buffer.