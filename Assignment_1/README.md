Notes on Assignment 1 for "Town of Salem".

- Players are stored in a vector with integers. The **value** of each element represents the **role** of the player. 0 --> Citizen. 1 --> Doctor, 2 --> Gangster, -1 --> Loser.  

- In every function, wherever we refer to a player, we use their **id** and not their vector index.

  For example, for player #1 we use the value 1 instead of 0. This helps since whenever we ask a user for input they give the players id.

- In night phase, when the doctor is out of the game, the player chosen by the gangster is sent directly out.

- Players are allowed to vote themselves, except the doctor in night phase.

- There are three functions that take input from the user; `get_option()`, `get_id()`, and `get_vote()`. At first, we used `cin >> integer_id` to read an integer from the user. It seemed to work fine, but that was not the case. The program was vulnerable to the following inputs:

  - When the user gives a **floating point number** (e.g. `4.7`)  `cin >> integer_id` does **not** fail. The integer part of the number (`4`) is stored to `integer_id` and the rest (`.7`) remains in the stream. This leads to two kinds of errors :
    - The program reads a value that should not have been read at first place.
    -  It fills the input stream with garbage.
  - When the user gives a line containing **whitespaces**, e.g. `7 4 `, the program reads the first part before the first whitespace and leaves the rest on the stream. As a result when the user is asked again to enter a value the stream is already full and assumes that the garbage left is the given value. In our example, the first time we read from user the value `7` will be accepted without error but when we ask again, the user cannot enter a value since the remaining  `4` will be assumed to be the input.

  The solution we came up to deal with all these errors is to **read the whole line** with `getline()` (https://cplusplus.com/reference/string/string/getline/) and store it as a `string`. Then we can check the string if it represents an integer with our `is_int()`. If this is true then we can use `stoi()` (https://cplusplus.com/reference/string/stoi/) to transform it to integer. `stoi()` is pretty resilient to leading and following whitespaces, signs, leading zeroes etc. Following this approach makes the use of `cin.ignore(...)` unnecessary.

- User can give `EOF` from input. This cause a lot of trouble since neither `cin.ignore()` nor `cin.clean()`  can bring the stream back to its original state. Using `cin.eof()` we identify the EOF input and throw an exception that will be caught by `main()` . The functions `info_menu()`, `get_valid_id()`, `get_valid_vote()` re-throw the exception when the catch it.