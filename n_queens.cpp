// C++ program to solve N Queen Problem using backtracking

#include <iostream>
#define N 4
using namespace std;

// A utility function to print solution
void printSolution(int board[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            if (board[i][j])
                cout << "Q ";
            else
                cout << ". ";
        cout << "\n";
    }
}

// A utility function to check if a queen can
// be placed on board[row][col]. Note that this
// function is called when "col" queens are
// already placed in columns from 0 to col -1.
// So we need to check only left side for
// attacking queens
bool isSafe(int board[N][N], int row, int col)
{
    int i, j;

    // Check this row on left side
    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;

    // Check upper diagonal on left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check lower diagonal on left side
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

// A recursive utility function to solve N
// Queen problem
bool solveNQUtil(int board[N][N], int col)
{
    // base case: If all queens are placed
    // then return true
    if (col >= N)
        return true;

    // Consider this column and try placing
    // this queen in all rows one by one
    for (int i = 0; i < N; i++)
    {

        // Check if the queen can be placed on
        // board[i][col]
        if (isSafe(board, i, col))
        {

            // Place this queen in board[i][col]
            board[i][col] = 1;

            // recur to place rest of the queens
            if (solveNQUtil(board, col + 1))
                return true;

            // If placing queen in board[i][col]
            // doesn't lead to a solution, then
            // remove queen from board[i][col]
            board[i][col] = 0; // BACKTRACK
        }
    }

    // If the queen cannot be placed in any row in
    // this column col then return false
    return false;
}

// This function solves the N Queen problem using
// Backtracking. It mainly uses solveNQUtil() to
// solve the problem. It returns false if queens
// cannot be placed, otherwise, return true and
// prints placement of queens in the form of 1s.
// Please note that there may be more than one
// solutions, this function prints one of the
// feasible solutions.
bool solveNQ()
{
    int board[N][N] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

    if (solveNQUtil(board, 0) == false)
    {
        cout << "Solution does not exist";
        return false;
    }

    printSolution(board);
    return true;
}

// Driver program to test above function
int main()
{
    solveNQ();
    return 0;
}



// ----------------------------------------------------------
// Branch and Bound

// #include<iostream> 
// using namespace std; 
// int N; 


// // function for printing the solution 
// void printSol(vector<vector<int>>board) 
// { 
// for(int i = 0;i<N;i++){ 
// 	for(int j = 0;j<N;j++){ 
// 		cout<<board[i][j]<<" "; 
// 	} 
// 	cout<<"\n"; 
// } 
// } 

// /* Optimized isSafe function 
// isSafe function to check if current row contains or current left diagonal or current right diagonal contains any queen or not if 
// yes return false 
// else return true 
// */

// bool isSafe(int row ,int col ,vector<bool>rows , vector<bool>left_digonals ,vector<bool>Right_digonals) 
// { 
	
// if(rows[row] == true || left_digonals[row+col] == true || Right_digonals[col-row+N-1] == true){ 
// 	return false; 
// } 
	
// return true; 
// } 

// // Recursive function to solve N-queen Problem 
// bool solve(vector<vector<int>>& board ,int col ,vector<bool>rows , vector<bool>left_digonals ,vector<bool>Right_digonals) 
// {	 
// 	// base Case : If all Queens are placed 
// 	if(col>=N){ 
// 		return true; 
// 	} 

// 	/* Consider this Column and move in all rows one by one */
// 	for(int i = 0;i<N;i++) 
// 	{ 
// 		if(isSafe(i,col,rows,left_digonals,Right_digonals) == true) 
// 		{ 
// 			rows[i] = true; 
// 			left_digonals[i+col] = true; 
// 			Right_digonals[col-i+N-1] = true; 
// 			board[i][col] = 1; // placing the Queen in board[i][col] 
				
// 				/* recur to place rest of the queens */

// 			if(solve(board,col+1,rows,left_digonals,Right_digonals) == true){ 
// 				return true; 
// 			} 
				
// 			// Backtracking 
// 			rows[i] = false; 
// 			left_digonals[i+col] = false; 
// 			Right_digonals[col-i+N-1] = false; 
// 			board[i][col] = 0; // removing the Queen from board[i][col] 

// 		} 
// 	} 

// 		return false; 
// } 


// int main() 
// { 
// // Taking input from the user 

// cout<<"Enter the no of rows for the square Board : "; 
// cin>>N; 


// // board of size N*N 
// vector<vector<int>>board(N,vector<int>(N,0)); 


// 	// array to tell which rows are occupied 
// vector<bool>rows(N,false);		 

// // arrays to tell which diagonals are occupied					 
// vector<bool>left_digonals(2*N-1,false); 
// vector<bool>Right_digonals(2*N-1,false); 


// bool ans = solve(board , 0, rows,left_digonals,Right_digonals); 

// if(ans == true){ 

// 	// printing the solution Board 
// 	printSol(board); 
// } 
// else{ 
// 	cout<<"Solution Does not Exist\n"; 
// } 
// } 
// // This Code is Contributed by Parshant Rajput 