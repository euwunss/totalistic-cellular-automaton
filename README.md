# totalistic-cellular-automaton  

### Overview
This project implements a __totalistic cellular automaton__ that simulates the evolution of a one-dimensional world where each cell can exist in one of three possible states: 0, 1, or 2. The behavior of each cell is governed by rules based on the local sum of its own status and the status of its immediate neighbors. By specifying a rule number in the range 0 - 2186, different complex patterns and behaviors emerge over time as the automaton evolves.

The project provides a visualization of the evolution, where cells change state across multiple generations according to user-defined rules. Users can interactively set the initial conditions and rules, and observe how the automaton behaves over time.

### Input and Interaction
The program prompts users to enter:

- _Rule number:_ Determines how cells evolve, with a valid range of 0 - 2186.  
- _Number of generations:_ Specifies how many times the world should evolve.  
- _Initial active cell value:_ Sets the initial state (1 or 2) for the center cell in the world.
The program displays each generation step-by-step, providing a visual evolution of the automaton.

### How to Run
Clone the Repository:

```
git clone <repository-url>
```

Compile the Program:

```
gcc totalistic_cellular_automaton.c -o totalistic_automaton
```

Run the Executable:

```
./totalistic_automaton
```

Follow the on-screen prompts to input the rule number, initial active cell value, and the number of generations you wish to observe.

### Example Output

```
Welcome to the Totalistic Cellular Automaton!
Enter the rule # (0-2186): 777


The value array for rule #777 is 1001210

The evolution of all possible states are as follows:
Local Sum:   6       5       4       3       2       1       0      
States:    |+++|   |++-|   |++ |   |+- |   |-- |   |-  |   |   |    
                   |+-+|   |+ +|   |+ -|   |- -|   | - |            
                   |-++|   | ++|   |-+ |   | --|   |  -|            
                           |+--|   | +-|   |+  |                    
                           |-+-|   |- +|   | + |                    
                           |--+|   | -+|   |  +|                    
                                   |---|                            
New Status: |-|     | |     | |     |-|     |+|     |-|     | |     

Enter the number of generations (1-49): 32

Enter the value (1 or 2) for the initial active cell: 1


Initializing world & evolving...
                                -                                 1 
                               ---                                3 
                              -+-+-                               7 
                             --   --                              4 
                            -++- -++-                             12 
                           --  -+-  --                            8 
                          -++--- ---++-                           16 
                         --   -+++-   --                          12 
                        -++- -- - -- -++-                         17 
                       --  -++++-++++-  --                        23 
                      -++--- --   -- ---++-                       20 
                     --   -++++- -++++-   --                      24 
                    -++- -- -- -+- -- -- -++-                     24 
                   --  -+++++++- -+++++++-  --                    36 
                  -++--- ----- -+- ----- ---++-                   30 
                 --   -+++---++- -++---+++-   --                  34 
                -++- -- -  -   -+-   -  - -- -++-                 24 
               --  -++++----- -- -- -----++++-  --                36 
              -++--- --  ---+++++++++---  -- ---++-               44 
             --   -++++--+-  -------  -+--++++-   --              39 
            -++- -- --    ---+-----+---    -- -- -++-             35 
           --  -++++++-  -+-   ---   -+-  -++++++-  --            43 
          -++--- ---- ---- -- -+-+- -- ---- ---- ---++-           43 
         --   -+++--+++--+++++-   -+++++--+++--+++-   --          60 
        -++- -- -    -    --- -- -- ---    -    - -- -++-         30 
       --  -++++--  ---  -+-+++++++++-+-  ---  --++++-  --        58 
      -++--- --  +--+-+---   -------   ---+-+--+  -- ---++-       51 
     --   -++++-+-      -+- -+-----+- -+-      -+-++++-   --      49 
    -++- -- --   --    -- -+-  ---  -+- --    --   -- -- -++-     39 
   --  -++++++- -++-  -+++- ---+-+--- -+++-  -++- -++++++-  --    71 
  -++--- ---- -+-  ---- - -++-     -++- - ----  -+- ---- ---++-   54 
 --   -+++--++- ---+--++-+-  --   --  -+-++--+--- -++--+++-   --  66 
_________________________________________________________________
         11111111111122122222333233322222122111111111111         
 123446880124553586790390676810272018676093097685355421088644321 
```

___
### Acknowledgment
This project was completed as part of the CS 211 course at University of Illinois Chicago, under the guidance of Professors Scott Reckinger and David Hayes. The initial project idea and requirements were provided as part of the course assignment.
