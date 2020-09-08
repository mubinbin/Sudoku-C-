#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<bits/stdc++.h>

using namespace std;
const int MAX = 9;
//manually input sudoku board
// void input_board()
// {
//     int mat[MAX][MAX]; // matrix can have max 3 rows and 3 cols
//         int i, j;
//         cout << "Enter the matrix elements row-wise :- " << endl;
//         for ( i = 0; i < MAX; i++ ) { // outer loop iterates over each row
//             for ( j = 0; j < MAX; j++ ) { // inter loop iterates over each column
//                 cout << "mat[" << i << "][" << j << "] : ";
//                 // i -> row no. and j -> col no.
//                 cin >> mat[i][j];
//             }
//         }
// }

// print matrix
void print_board (int board[9][9])
{
    for (int i = 0; i < 9; i++ ) {
      for (int j = 0; j < 9; j++ ) {
         cout << board[i][j] << " ";
      }
      cout << endl;
   }
}

//return row and col for empty
bool empty (int board[9][9], int &row, int &col)
{   

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] != 0)
            {
                continue;
            }
            row = i;
            col = j;
            return true;
        }   
    }       
    return false;
}

// create a visited hash table
// void visited (unordered_map<int, list<int>> visited, list<int> List, int input, int index)
// {
//     List.push_back(input);
//     visited[index] = List;
//     return visited;
// }



// check input is valid or not
bool valid (int board[9][9], int &input, int &x, int &y)
{
    // x, y are the index we want to check
    int i, j; // row and col for board;
    // valid in rows
    for (j = 0; j < 9; j++)
    {
        if (board[x][j] == input && j != y)
            return false;
    }
    // valid in cols
    for (i = 0; i < 9; i++) 
    {
        if (board[i][y] == input && i != x)
            return false;
    }
    // valid in subsets
    int sub_x, sub_y;
    for (int n = 0; n < 3; n++)
    {
        //subset row index
        sub_x = (x - x % 3) + n;
        for (int m = 0; m < 3; m++)
        {
            //subset col index
            sub_y = (y - y % 3) + m;
            if (board[sub_x][sub_y] == input && sub_x !=x && sub_y != y)
                return false;  
        }
    }
    return true;
}

// solution
bool solve_new (int board[9][9])
{
    // these -1 dont matter, just randomly give a number
    int row = -1, col = -1;
    // if there is no empty anymore, suduko solved
    if (!empty(board, row, col))
        return true;

    for (int input = 1; input <=9; input++)
    {
        board[row][col] = input;
        // check if input valid
        if (valid(board, input, row, col))
        {
            if (solve_new(board)) // this will go and try to solve the next empty, ex. if line 111 is checking [0][2]
                return true;      // this will go to solve [0][3]
            
            board[row][col] = 0; // if not line 113 (when [0][3] return false), this will zero [0][2]
            //cout<<row <<' '<<col <<", ";
        }
    }

    board[row][col] = 0; // this will zero [0][3], if there is no valid number
    return false;
}





// void solve_sudoku(int board[9][9],\
//                   unordered_map<int, vector<int>> visited,\
//                   vector<int> valid_ci,\
//                   vector<int> v,\
//                   int n,\
//                   int input,\
//                   int index)
// {
//     int ppr, ppc; // empty row and col before preivous
//     int pr, pc; // previous empty row and col
//     int cr, cc; // current empty row and col
//     int ci, pi; // current input and previous input
//     // int temp, temp2;
//     // unordered_map<int, vector<int>> visited;
//     // vector<int> valid_ci;
//     vector<int>::iterator iter;
//     // valid_ci.clear();
//     if (pi == 10)
//     {
//         pi = 1;
//     }
//     if (index + 1 <= n)
//     {    
//         cr = v[index];
//         cc = v[index + 1];
//         if (index >= 2)
//         {
//             pr = v[index - 2];
//             pc = v[index - 1];
//             // temp = board[pr][pc];
//         }
//         // if (i >= 4)
//         // {
//         //     ppr = v[i - 4];
//         //     ppc = v[i - 3];
//         // }
//         for (ci = input; ci <= 9; ci++)
//         {
//             if (valid(board, ci, cr, cc))
//             {
//                 iter = find(visited[index].begin(), visited[index].end(), ci);
//                 if (iter == visited[index].end()) //if ci not in valid_ci vector, put it in
//                 { 
//                     // if not, update vector and hash table
//                     valid_ci.push_back(ci);
//                     visited[index] = valid_ci;                 
//                     board[cr][cc] = ci; 
//                     index = index + 2;
//                     valid_ci.clear();
//                 }                       
//                 else if (iter != visited[index].end())
//                 {    // if in the vector, meaning board[pr][pc] need to reset
//                     pi = board[pr][pc] + 1; 
//                     board[pr][pc] = 0;
//                     index = index-2;
//                     valid_ci = visited[index];
//                     solve_sudoku(board, visited, valid_ci, v, n, pi, index);
//                 }
//                 solve_sudoku(board, visited, valid_ci, v, n, 1, index);
//             }else{
//                 //need to change preivous empty, backtrack
//                 if (ci == 9)
//                 {
//                     pi = board[pr][pc] + 1; // board[pr][pc] could be 9
//                     board[pr][pc] = 0;
//                     index = index-2;
//                     valid_ci = visited[index];
//                     solve_sudoku(board, visited, valid_ci, v, n, pi, index);
//                 }
//             }
//         }
//     }
// } 





int main()
{
    // initialize a metrix
    int board [9][9] =  {{0,0,0,1,0,6,0,2,5},  
                            {0,0,0,0,0,0,0,4,0}, 
                            {8,0,7,0,3,0,0,0,0},
                            {9,0,0,0,0,2,0,0,0},
                            {0,7,6,0,9,0,4,8,0},
                            {0,0,0,4,0,0,0,0,6},
                            {0,0,0,0,4,0,5,0,3},
                            {0,4,0,0,0,0,0,0,0},
                            {3,1,0,5,0,7,0,0,0}};
    
    solve_new(board);

    // int input = 7;
    // int x = 8;
    // int y = 4;
    // vector<int> v = empty(board);
    print_board (board);
    // for (int i = 0; i <v.size(); i++)
    // {
    //     cout << v[i] <<endl;
    // }
    //cout << valid(board, input, x, y) << endl;

    return 0;
}