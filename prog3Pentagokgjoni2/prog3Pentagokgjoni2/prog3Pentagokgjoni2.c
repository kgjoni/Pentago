/* -------------------------------------------------------------------------------------------------------------------------
* prog3Pentagokgjoni2.c
*
* Class: Program #3 for CS 141, Spring 2017.  Tues 11am lab.
* System: Windows 7
* Author: Kristi Gjoni
*
* Pentago is played on a 6 by 6 board, divided into four 3 by 3
* quadrants.  There are two players, X and O, who alternate turns.
* The goal of each player is to get five of their pieces in a row,
* either horizontally, vertically, or diagonally.
* Players take turns placing one of their pieces into an empty
* space anywhere on the board, then choosing one of the four
* board quadrants to rotate 90 degrees left or right.
* If both players get five in a row at the same time, or the
* last move is played with no five in a row, the game is a tie.
* If a player makes five a row by placing a piece, there is no need
* to rotate a quadrant and the player wins immediately.
. . .
* --------------------------------------------------------------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>  // Needed to avoid compiler error for the exit() command
#include <ctype.h>   // For toupper()

// Global variable
const int boardSize = 36;	// constant size of board[]


//--------------------------------------------------------------------------------------------------------------------------
// Display ID info
void displayIdInfo()
{
	printf("\n");
	printf("Author: Kristi Gjoni               \n");
	printf("Program #3: Pentago                \n");
	printf("TA: Moumita Samanta, Tuesday 11 AM \n");
	printf("February 27, 2017                  \n");
	printf("\n");
}//end displayIDInfo()


//--------------------------------------------------------------------------------------------------------------------------
// Display Instructions
void displayInstructions()
{
	printf("\n");
	printf("Play the two-player game of Pentago. Be the first to get 5 in a row.           \n");
	printf("\n");
	printf("Pentago is played on a 6 by 6 board, divided into four 3 by 3 quadrants.       \n");
	printf("There are two players, X and O, who alternate turns. The goal of each player   \n");
	printf("is to get five of their pieces in a row, either horizontally, vertically,      \n");
	printf("or diagonally.                                                                 \n");
	printf("\n");
	printf("Players take turns placing one of their pieces into an empty space anywhere    \n");
	printf("on the board, then choosing one of the four board quadrants to rotate 90       \n");
	printf("degrees left or right.                                                         \n");
	printf("\n");
	printf("If both players get five in a row at the same time, or the last move is played \n");
	printf("with no five in a row, the game is a tie.                                      \n");
	printf("If a player makes five a row by placing a piece, there is no need to rotate a  \n");
	printf("quadrant and the player wins immediately.                                      \n");
	printf("\n");
	printf("Play online at:  https://perfect-pentago.net                                   \n");
	printf("Purchase at:     www.mindtwisterusa.com                                        \n");
	printf("\n");
	printf("For each move provide four inputs:                                             \n");
	printf("row (A-F), column (1-6), quadrant (1-4), rotation direction (L or R)           \n");
	printf("For instance input of B32R places the next piece at B3 and then would rotate   \n");
	printf("quadrant 2 (upper - right) to the right(clockwise).                             \n");
	printf("\n");
	printf("At any point enter 'x' to exit the program.                                    \n");
	printf("\n");
}//end displayInstructions()


//--------------------------------------------------------------------------------------------------------------------------
// Display board
void displayBoard(char board[])
{
	int i;
	printf("1  1 2 3 4 5 6  2\n");
	printf("   -----------   \n");
	printf("A: ");
	for (i = 0; i < boardSize; i++)
	{
		printf("%c ", board[i]);
		if ((i + 1) % 6 == 0) {
			if (i >= 0 && i < 6) { printf(":A"); }
			else if (i >= 6 && i < 12) { printf(":B"); }
			else if (i >= 12 && i < 18) { printf(":C"); }
			else if (i >= 18 && i < 24) { printf(":D"); }
			else if (i >= 24 && i < 30) { printf(":E"); }
			else if (i >= 30 && i < 36) { printf(":F"); } 
			printf("\n");
			if (i >= 0 && i < 6) { printf("B: "); }
			else if (i >= 6 && i < 12) { printf("C: "); }
			else if (i >= 12 && i < 18) { printf("D: "); }
			else if (i >= 18 && i < 24) { printf("E: "); }
			else if (i >= 24 && i < 30) { printf("F: "); }
		}
	}
	printf("   -----------   \n");
	printf("3  1 2 3 4 5 6  4\n");
	printf("\n");
}// end diplayBoard()


//--------------------------------------------------------------------------------------------------------------------------
// Assign 'X' or 'O' to board positions
void assignPlayerPiece(char board[], char inputRow, int inputColumn, char playerPiece)
{
	if (inputRow == 'A') { board[((inputRow / 10) + inputColumn - 7)] = playerPiece; }		//assign 'X' or 'O' if row is 'A'
	if (inputRow == 'B') { board[((inputRow / 10) + inputColumn - 1)] = playerPiece; }		//assign 'X' or 'O' if row is 'B'
	if (inputRow == 'C') { board[((inputRow / 10) + inputColumn + 5)] = playerPiece; }		//assign 'X' or 'O' if row is 'C'
	if (inputRow == 'D') { board[((inputRow / 10) + inputColumn + 11)] = playerPiece; }		//assign 'X' or 'O' if row is 'D'
	if (inputRow == 'E') { board[((inputRow / 10) + inputColumn + 17)] = playerPiece; }		//assign 'X' or 'O' if row is 'E'
	if (inputRow == 'F') { board[((inputRow / 10) + inputColumn + 22)] = playerPiece; }		//assign 'X' or 'O' if row is 'F'
}// end assignPlayerPiece()


//--------------------------------------------------------------------------------------------------------------------------
// Return 1 (for true) if input is not valid.  Input is not valid if any of these are true:
//    1. Row is 'A'< or >'F'.
//    2. Column is 1< or >6.
//    3. Quadrant is 1< or >4.
//    4. Destination is not 'R' or 'L'.
int inputNotValid(char board[], char inputRow, int inputColumn, int inputQuadrant, char inputDirection)
{
	// Validate each possible error condition in turn, returning 1 (true) if any are found.
	// 1. Row input is out of range
	if ((inputRow < 'A') || (inputRow > 'F')) {
		printf("*** Invalid move row.  Please retry.\n");
		return 1;    // Input was invalid, so return 1 (true)
	}

	// 2. Column input is out of range
	if ((inputColumn < 1) || (inputColumn > 6)) {
		printf("*** Invalid move column.  Please retry.\n");
		return 1;    // Input was invalid, so return 1 (true)
	}

	// 3. Quadrant input is out of range
	if ((inputQuadrant < 1) || (inputQuadrant > 4)) {
		printf("*** Selected quadrant is invalid.  Please retry.\n");
		return 1;    // Input was invalid, so return 1 (true)
	}

	// 4. Direction input is out of range
	if ((inputDirection == 'R') || (inputDirection == 'L')) {
		return 0;	// Input was valid, so return 0 (false)
	}
	else {
		printf("*** Quadrant rotation direction is invalid.  Please retry.\n");
		return 1;    // Input was invalid, so return 1 (true)
	}

	return 0;
}//end inputNotValid()


//--------------------------------------------------------------------------------------------------------------------------
// Rotate quadrant 1 through 4, right or left, according to user inputs
void rotateQuadrant(char board[], int inputQuadrant, char inputDirection)
{
	int temp;				// variable to temporary store the board values

	// Input for direction was 'R', so rotate right
	if (inputDirection == 'R')				
	{
		// Input for quadrant was '1', so rotate first quadrant
		if (inputQuadrant == 1) {

			// Rotate corner pieces in quadrant 1
			temp = board[0];
			board[0] = board[2];
			board[2] = temp;
			temp = board[0];
			board[0] = board[14];
			board[14] = temp;
			temp = board[0];
			board[0] = board[12];
			board[12] = temp;

			// Rotate middle pieces in quadrant 1
			temp = board[1];
			board[1] = board[8];
			board[8] = temp;
			temp = board[1];
			board[1] = board[13];
			board[13] = temp;
			temp = board[1];
			board[1] = board[6];
			board[6] = temp;
		}
		// Input for quadrant was '2', so rotate second quadrant
		else if (inputQuadrant == 2) {
			
			// Rotate corner pieces in quadrant 2
			temp = board[3];
			board[3] = board[5];
			board[5] = temp;
			temp = board[3];
			board[3] = board[17];
			board[17] = temp;
			temp = board[3];
			board[3] = board[15];
			board[15] = temp;

			// Rotate middle pieces in quadrant 2
			temp = board[4];
			board[4] = board[11];
			board[11] = temp;
			temp = board[4];
			board[4] = board[16];
			board[16] = temp;
			temp = board[4];
			board[4] = board[9];
			board[9] = temp;
		}
		// Input for quadrant was '3', so rotate third quadrant
		else if (inputQuadrant == 3) {
			
			// Rotate corner pieces in quadrant 3
			temp = board[18];
			board[18] = board[20];
			board[20] = temp;
			temp = board[18];
			board[18] = board[32];
			board[32] = temp;
			temp = board[18];
			board[18] = board[30];
			board[30] = temp;

			// Rotate middle pieces in quadrant 3
			temp = board[19];
			board[19] = board[26];
			board[26] = temp;
			temp = board[19];
			board[19] = board[31];
			board[31] = temp;
			temp = board[19];
			board[19] = board[24];
			board[24] = temp;
		}
		// Input for quadrant was '4', so rotate fourth quadrant
		else if (inputQuadrant == 4) {
			
			// Rotate corner pieces in quadrant 4
			temp = board[21];
			board[21] = board[23];
			board[23] = temp;
			temp = board[21];
			board[21] = board[35];
			board[35] = temp;
			temp = board[21];
			board[21] = board[33];
			board[33] = temp;

			// Rotate middle pieces in quadrant 4
			temp = board[22];
			board[22] = board[29];
			board[29] = temp;
			temp = board[22];
			board[22] = board[34];
			board[34] = temp;
			temp = board[22];
			board[22] = board[27];
			board[27] = temp;
		}

	}
	// Input for direction was 'L', so rotate left
	else if (inputDirection == 'L') 
	{
		// Input for quadrant was '1', so rotate first quadrant
		if (inputQuadrant == 1) {

			// Rotate corner pieces in quadrant 1
			temp = board[0];
			board[0] = board[12];
			board[12] = temp;
			temp = board[0];
			board[0] = board[14];
			board[14] = temp;
			temp = board[0];
			board[0] = board[2];
			board[2] = temp;

			// Rotate middle pieces in quadrant 1
			temp = board[1];
			board[1] = board[6];
			board[6] = temp;
			temp = board[1];
			board[1] = board[13];
			board[13] = temp;
			temp = board[1];
			board[1] = board[8];
			board[8] = temp;
		}
		// Input for quadrant was '2', so rotate second quadrant
		else if (inputQuadrant == 2) {

			// Rotate corner pieces in quadrant 2
			temp = board[3];
			board[3] = board[15];
			board[15] = temp;
			temp = board[3];
			board[3] = board[17];
			board[17] = temp;
			temp = board[3];
			board[3] = board[5];
			board[5] = temp;

			// Rotate middle pieces in quadrant 2
			temp = board[4];
			board[4] = board[9];
			board[9] = temp;
			temp = board[4];
			board[4] = board[16];
			board[16] = temp;
			temp = board[4];
			board[4] = board[11];
			board[11] = temp;
		}
		// Input for quadrant was '3', so rotate third quadrant
		else if (inputQuadrant == 3) {

			// Rotate corner pieces in quadrant 3
			temp = board[18];
			board[18] = board[30];
			board[30] = temp;
			temp = board[18];
			board[18] = board[32];
			board[32] = temp;
			temp = board[18];
			board[18] = board[20];
			board[20] = temp;

			// Rotate middle pieces in quadrant 3
			temp = board[19];
			board[19] = board[24];
			board[24] = temp;
			temp = board[19];
			board[19] = board[31];
			board[31] = temp;
			temp = board[19];
			board[19] = board[26];
			board[26] = temp;
		}
		// Input for quadrant was '4', so rotate fourth quadrant
		else if (inputQuadrant == 4) {

			// Rotate corner pieces in quadrant 4
			temp = board[21];
			board[21] = board[33];
			board[33] = temp;
			temp = board[21];
			board[21] = board[35];
			board[35] = temp;
			temp = board[21];
			board[21] = board[23];
			board[23] = temp;

			// Rotate middle pieces in quadrant 4
			temp = board[22];
			board[22] = board[27];
			board[27] = temp;
			temp = board[22];
			board[22] = board[34];
			board[34] = temp;
			temp = board[22];
			board[22] = board[29];
			board[29] = temp;
		}
	}
}// end rotateQuadrant()


//--------------------------------------------------------------------------------------------------------------------------
// Check if there is a winner
int checkForWinner(char board[]) {
	// Check if player 'O' is the winner

	// Checking all possible horizontal cominations; if five in a row are found, 'O' has won the game
	if (((board[0] == 'O') && (board[1] == 'O') && (board[2] == 'O') && (board[3] == 'O') && (board[4] == 'O')) ||
		((board[1] == 'O') && (board[2] == 'O') && (board[3] == 'O') && (board[4] == 'O') && (board[5] == 'O')) ||
		((board[6] == 'O') && (board[7] == 'O') && (board[8] == 'O') && (board[9] == 'O') && (board[10] == 'O')) ||
		((board[7] == 'O') && (board[8] == 'O') && (board[9] == 'O') && (board[10] == 'O') && (board[11] == 'O')) ||
		((board[12] == 'O') && (board[13] == 'O') && (board[14] == 'O') && (board[15] == 'O') && (board[16] == 'O')) ||
		((board[13] == 'O') && (board[14] == 'O') && (board[15] == 'O') && (board[16] == 'O') && (board[17] == 'O')) ||
		((board[18] == 'O') && (board[19] == 'O') && (board[20] == 'O') && (board[21] == 'O') && (board[22] == 'O')) ||
		((board[19] == 'O') && (board[20] == 'O') && (board[21] == 'O') && (board[22] == 'O') && (board[23] == 'O')) ||
		((board[24] == 'O') && (board[25] == 'O') && (board[26] == 'O') && (board[27] == 'O') && (board[28] == 'O')) ||
		((board[25] == 'O') && (board[26] == 'O') && (board[27] == 'O') && (board[28] == 'O') && (board[29] == 'O')) ||
		((board[30] == 'O') && (board[31] == 'O') && (board[32] == 'O') && (board[33] == 'O') && (board[34] == 'O')) ||
		((board[31] == 'O') && (board[32] == 'O') && (board[33] == 'O') && (board[34] == 'O') && (board[35] == 'O')) ||

		// Checking all possible vertical combinations; if five in a row are found, 'O' has won the game
		((board[0] == 'O') && (board[6] == 'O') && (board[12] == 'O') && (board[18] == 'O') && (board[24] == 'O')) ||
		((board[6] == 'O') && (board[12] == 'O') && (board[18] == 'O') && (board[24] == 'O') && (board[30] == 'O')) ||
		((board[1] == 'O') && (board[7] == 'O') && (board[13] == 'O') && (board[19] == 'O') && (board[25] == 'O')) ||
		((board[7] == 'O') && (board[13] == 'O') && (board[19] == 'O') && (board[25] == 'O') && (board[31] == 'O')) ||
		((board[2] == 'O') && (board[8] == 'O') && (board[14] == 'O') && (board[20] == 'O') && (board[26] == 'O')) ||
		((board[8] == 'O') && (board[14] == 'O') && (board[20] == 'O') && (board[26] == 'O') && (board[32] == 'O')) ||
		((board[3] == 'O') && (board[9] == 'O') && (board[15] == 'O') && (board[21] == 'O') && (board[27] == 'O')) ||
		((board[9] == 'O') && (board[15] == 'O') && (board[21] == 'O') && (board[27] == 'O') && (board[33] == 'O')) ||
		((board[4] == 'O') && (board[10] == 'O') && (board[16] == 'O') && (board[22] == 'O') && (board[28] == 'O')) ||
		((board[10] == 'O') && (board[16] == 'O') && (board[22] == 'O') && (board[28] == 'O') && (board[34] == 'O')) ||
		((board[5] == 'O') && (board[11] == 'O') && (board[17] == 'O') && (board[23] == 'O') && (board[29] == 'O')) ||
		((board[11] == 'O') && (board[17] == 'O') && (board[23] == 'O') && (board[29] == 'O') && (board[35] == 'O')) ||

		// Checking all possible diagonal combinations; if five in a row are found, 'O' has won the game
		((board[4] == 'O') && (board[9] == 'O') && (board[14] == 'O') && (board[19] == 'O') && (board[24] == 'O')) ||
		((board[5] == 'O') && (board[10] == 'O') && (board[15] == 'O') && (board[20] == 'O') && (board[25] == 'O')) ||
		((board[10] == 'O') && (board[15] == 'O') && (board[20] == 'O') && (board[25] == 'O') && (board[30] == 'O')) ||
		((board[11] == 'O') && (board[16] == 'O') && (board[21] == 'O') && (board[26] == 'O') && (board[31] == 'O'))) {

		// Display final statement to the user
		printf("\nO has won the game! \n");
		printf("Thanks for playing.  Exiting...\n");
		exit(0);		// exit the program
	}

	// Check if player 'X' is the winner

	// Checking all possible horizontal cominations; if five in a row are found, 'X' has won the game
	else if (((board[0] == 'X') && (board[1] == 'X') && (board[2] == 'X') && (board[3] == 'X') && (board[4] == 'X')) ||
		((board[1] == 'X') && (board[2] == 'X') && (board[3] == 'X') && (board[4] == 'X') && (board[5] == 'X')) ||
		((board[6] == 'X') && (board[7] == 'X') && (board[8] == 'X') && (board[9] == 'X') && (board[10] == 'X')) ||
		((board[7] == 'X') && (board[8] == 'X') && (board[9] == 'X') && (board[10] == 'X') && (board[11] == 'X')) ||
		((board[12] == 'X') && (board[13] == 'X') && (board[14] == 'X') && (board[15] == 'X') && (board[16] == 'X')) ||
		((board[13] == 'X') && (board[14] == 'X') && (board[15] == 'X') && (board[16] == 'X') && (board[17] == 'X')) ||
		((board[18] == 'X') && (board[19] == 'X') && (board[20] == 'X') && (board[21] == 'X') && (board[22] == 'X')) ||
		((board[19] == 'X') && (board[20] == 'X') && (board[21] == 'X') && (board[22] == 'X') && (board[23] == 'X')) ||
		((board[24] == 'X') && (board[25] == 'X') && (board[26] == 'X') && (board[27] == 'X') && (board[28] == 'X')) ||
		((board[25] == 'X') && (board[26] == 'X') && (board[27] == 'X') && (board[28] == 'X') && (board[29] == 'X')) ||
		((board[30] == 'X') && (board[31] == 'X') && (board[32] == 'X') && (board[33] == 'X') && (board[34] == 'X')) ||
		((board[31] == 'X') && (board[32] == 'X') && (board[33] == 'X') && (board[34] == 'X') && (board[35] == 'X')) ||

		// Checking all possible vertical combinations; if five in a row are found, 'X' has won the game
		((board[0] == 'X') && (board[6] == 'X') && (board[12] == 'X') && (board[18] == 'X') && (board[24] == 'X')) ||
		((board[6] == 'X') && (board[12] == 'X') && (board[18] == 'X') && (board[24] == 'X') && (board[30] == 'X')) ||
		((board[1] == 'X') && (board[7] == 'X') && (board[13] == 'X') && (board[19] == 'X') && (board[25] == 'X')) ||
		((board[7] == 'X') && (board[13] == 'X') && (board[19] == 'X') && (board[25] == 'X') && (board[31] == 'X')) ||
		((board[2] == 'X') && (board[8] == 'X') && (board[14] == 'X') && (board[20] == 'X') && (board[26] == 'X')) ||
		((board[8] == 'X') && (board[14] == 'X') && (board[20] == 'X') && (board[26] == 'X') && (board[32] == 'X')) ||
		((board[3] == 'X') && (board[9] == 'X') && (board[15] == 'X') && (board[21] == 'X') && (board[27] == 'X')) ||
		((board[9] == 'X') && (board[15] == 'X') && (board[21] == 'X') && (board[27] == 'X') && (board[33] == 'X')) ||
		((board[4] == 'X') && (board[10] == 'X') && (board[16] == 'X') && (board[22] == 'X') && (board[28] == 'X')) ||
		((board[10] == 'X') && (board[16] == 'X') && (board[22] == 'X') && (board[28] == 'X') && (board[34] == 'X')) ||
		((board[5] == 'X') && (board[11] == 'X') && (board[17] == 'X') && (board[23] == 'X') && (board[29] == 'X')) ||
		((board[11] == 'X') && (board[17] == 'X') && (board[23] == 'X') && (board[29] == 'X') && (board[35] == 'X')) ||

		// Checking all possible diagonal cominations; if five in a row are found, 'X' has won the game
		((board[4] == 'X') && (board[9] == 'X') && (board[14] == 'X') && (board[19] == 'X') && (board[24] == 'X')) ||
		((board[5] == 'X') && (board[10] == 'X') && (board[15] == 'X') && (board[20] == 'X') && (board[25] == 'X')) ||
		((board[10] == 'X') && (board[15] == 'X') && (board[20] == 'X') && (board[25] == 'X') && (board[30] == 'X')) ||
		((board[11] == 'X') && (board[16] == 'X') && (board[21] == 'X') && (board[26] == 'X') && (board[31] == 'X'))) {

		// Display final statement to the user
		printf("\nX has won the game! \n");
		printf("Thanks for playing.  Exiting...\n");
		exit(0);		// exit the program
	}

}// end checkForWinner()


//--------------------------------------------------------------------------------------------------------------------------
// begin main()
int main()
{
	displayIdInfo();						// Display ID info
	displayInstructions();					// Display game instructions

	char board[36];							// Declare an array of size 36
	int i;									// Used in for loop 
	int count = 1;							// Declare a move number variable that updates each time a move is made
	char inputRow;							// Store user input for row
	int inputColumn;						// Store user input for column
	int inputQuadrant;						// Store user input for quadrant
	char inputDirection;					// Store user input for direction
	char playerPiece;						// Will store 'X' or 'O'

	// Assign '.' to each board piece 
	for (i = 0; i < boardSize; i++)
	{
		board[i] = '.';
	}

	// Dsiplay initial game board
	displayBoard(board);

	// Repeat until all board positions are occupied and game ends in a tie
	while (count < boardSize)
	{
		// Repeat until a winner is found
		while (1) {
			// When count is odd, inputs are taken for player 'X'
			if (count % 2 != 0) {
				printf("%d. Enter row, column, quadrant, direction for X: ", count);
				playerPiece = 'X';
			}
			// When count is even, inputs are taken for player 'O'
			else {
				printf("%d. Enter row, column, quadrant, direction for O: ", count);
				playerPiece = 'O';
			}

			scanf(" %c", &inputRow);	// store user input for 'row'

			// Exit program if user enters 'x' or 'X' at any time
			if (toupper(inputRow) == 'X') {
				printf("Exiting program...\n");
				exit(0);
			}

			scanf("%1d %1d", &inputColumn, &inputQuadrant);		// store user inputs for 'column' and 'quadrant'
			scanf(" %c", &inputDirection);						// store user input for 'direction'

			// Convert user inputs to upper case to simplify error checking
			inputRow = toupper(inputRow);
			inputDirection = toupper(inputDirection);

			// Check for invalid user inputs
			if (inputNotValid(board, inputRow, inputColumn, inputQuadrant, inputDirection))
			{
				continue;   // Input is not valid, so go back up to try again
			}
			else {
				// User input was valid, so break out of user input loop
				printf(" \n");
				printf(" \n");
				break;
			}
			
		}// end of while(1)
		
		assignPlayerPiece(board, inputRow, inputColumn, playerPiece);		// assign 'X' or'O' to the board according to user input

		rotateQuadrant(board, inputQuadrant, inputDirection);		// rotate quadrant according to user inputs

		count++;	// move number variable that updates each time a move is made

		displayBoard(board);	// displaye updated board after players alternate their moves 

		checkForWinner(board);	// check if player 'X' or 'O' has won the game

	}// end of while(count < boardSize)

	// After checking if player 'X' or player 'O' has won the game,
	// display statement for tie. Since there are no more moves left
	// for both players (counter > 36), the game ends in a tie. 
	printf("/nThe game ended with a tie.\n");
	printf("Thanks for playing.  Exiting...\n");

	return 0;
} // end main()