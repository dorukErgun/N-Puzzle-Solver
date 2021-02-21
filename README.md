# N-Puzzle-Solver

Program to help user solve the N-Puzzle problem. Sample solved 15-Puzzle (size 4) problem board is below.

| 1 | 2 | 3 | 4 |
| --- | --- | --- | --- |
| 5 | 6 | 7 | 8 |
| 9 | 10 | 11 | 12 |
| 13 | 14 | 15 | |

An initial and a solved 8-Puzzle (size 3) game boards are below.
### Initial Board

| 1 | 8 | 2 |
| --- | --- | --- |
|   | 4 | 3 |
| 7 | 6 | 5 |

### Solved Board

| 1 | 2 | 3 |
| --- | --- | --- |
| 4 | 5 | 6 |
| 7 | 8 |  |

## About the Project
 The program is designed with a Object-Oriented approach and is capable of doing some other stuff like, reading a board from a file, writing to board to a file, making a smart move etc. Full list of functionalities are given below.

| Function Name | Explanation |
| --- | --- |
|print | Prints the current configuration on the screen by sending it to cout|
|printReport | Prints a report about how many moves have been done since reset and if the solution is found|
|readFromFile | Reads the current configuration from the file given as function parameter. The vector of Board objects is resized to 1. See below for details. |
|writeToFile | Writes the current configuration to the file given as function parameter.|
|shuffle | Makes N random moves to shuffle the board. N is given as a function parameter. The vector of Board objects is resized to 1. See below for details.|
|reset | Resets the current configuration to the solution. The vector of Board objects is resized to 0.|
|setsize | Sets the board size to given values. The values are given as parameters and they can be at most 9x9. After setting the size, the boards should be reset.|
|moveRandom |Makes a valid random move. Move is recorded in vector of Board objects. The vector of Board objects is resized to 1. See below for details. |
|move | Makes a move according to the given char parameter. If the parameters is ‘L’ then, the blank tiles moves left, …, etc, as defined below. Move is recorded in vector of Board objects. The vector of Board objects is resized to 1. See below for details.|
|solvePuzzle | Runs the algorithm described below to solve the problem in optimal number of steps.|
|Operator>> | Prints the current configuration on the screen by sending it to ostream object|
|Operator<< | Reads the current configuration from the istream object.|

## Inputs the Use The Program

| Input | Action |
| --- | --- |
| V| Solves the problem from the current configuration using the new algorithm. |
| T| Prints a report about how many moves have been done and if the solution is found|
| E| Asks a file name and saves the current board configuration as a loadable shape file.|
| O| Asks a file name and loads the current board configuration from the shape file.|
| L| moves the empty cell left if there is room|
| R| moves the empty cell right if there is room|
| U| moves the empty cell up if there is room|
| D| moves the empty cell down if there is room|
| S| Shuffle- takes the board to the final solution, and makes size*size random moves to shuffle the board.|

## Algorithm

1. NPuzzle class keeps a vector of Board objects. Initially this vector contains a single object that contains either the board from a file or shuffled board. The number of steps of this board is 0.
2. Take the first element from this vector,
3. Apply all possible moves to this board and push_back each result back to the vector. Before doing the push back, you should check if the same board is already in the vector. If one of the pushed objects is the solution, then your solution is found.
4. Take another element from the vector in order and go to step 3.

Note that the above algorithm can stop in two cases: solution is found or there are no elements to take from the vector. We expect that if there is a solution, we will find it. In order to demonstrate the algorithm better, assume the initial 3x3 board vector in step 1 contains
1 2 3
4 5
7 8 6
Which will be represented as {((1234b5789),S,0)}, where S is the last move, 0 is the number of moves. Step 2 takes this board and pushes back 4 new boards to the vector
{((1234b5786),S,0), ((12345b786),R,1), ((123b45786),L,1),
((1b3425786),U,1), ((1234857b6),D,1)}
Note that bold letters indicate the vector elements that are not chosen from the vector yet. Since, we did not see the solution, we will pick the next element from the vector and go to step 3, which yields
{((1234b5786),S,0), ((12345b786),R,1), ((123b45786),L,1),
((1b3425786),U,1), ((1234857b6),D,1), ((12b453786),U,2), ((12345678b),D,2) }
We see that one of the newly added elements is the solution. We terminate the algorithm. From the solution, we can go back to the original board by applying the inverse moves U and L. We see that the solution needs just two moves.



