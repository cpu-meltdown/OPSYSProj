#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Read the sudoku board from text file
void readInitialBoard (int board[][9]){
   FILE * fp;
   char * line = NULL;
   size_t len = 0;
   ssize_t read;
   int i;
   int j = 0;
   
   fp = fopen("./boards.txt", "r");
   
   while ((read = getline(&line, &len, fp)) != -1){
     for (i = 0; i < strlen(line)-1; i++){
       board [j][i] = line[i] - '0';
     }
     j++;
   }
   fclose(fp);
}

//Fill possibleValues matrix with possible values of every cell
void getPossibleValues (int board[][9], int possibleValues[][8]){
  int tempi, tempj, row, col,  k, l, sqr, i;
  int tempRowValues[9] = {0};
  int tempColValues[9] = {0};
  int tempSqrValues[9] = {0};
  sqr = 0;
  row = 0;
  col = 0;
  i = 0;
  
  while (sqr < 9){
    tempi = row;
    while (tempi < (row + 3)){
      tempj = col;
      while (tempj < (col + 3)){
	if (board[tempi][tempj] == 0){
	  for (k = row; k < row + 3; k ++){
	    for (l = col; l < col + 3; l++){
	      if (board[k][l] != 0)
		tempSqrValues[board[k][l]-1]++;
	    }
	  }
	  for (k = 0; k < 9; k++){
	    if (board[tempi][k] != 0)
	      tempRowValues[board[tempi][k]-1]++;
	  }
	  for (k = 0; k < 9; k++){
	    if (board[k][tempj] != 0)
	      tempColValues[board[k][tempj]-1]++;
	  }
	  for (k = 0; k < 9; k++){
	    if (tempRowValues[k] == 0 && tempColValues[k] == 0 && tempSqrValues[k] == 0){
	      possibleValues[(tempi*9)+tempj][i] = k+1;
	      i++;
	    }
	  }
	  if (i == 1)
	    board[tempi][tempj] = possibleValues[(tempi*9)+tempj][i-1];
	  memset(tempColValues, 0, sizeof(tempColValues));
	  memset(tempRowValues, 0, sizeof(tempRowValues));
	  memset(tempSqrValues, 0, sizeof(tempSqrValues));
	  i = 0;
	}
        tempj++;
      }
      tempi++;
    }
    sqr++;
    if ((sqr % 3) == 0){
      row += 3;
      col = 0;
    } 
    else
      col += 3;
  }

}

int main(){
  int board[9][9] = {0};
  int possibleValues[81][8] = {0};
  
  readInitialBoard(board);
  getPossibleValues(board, possibleValues);
  int i=0,j=0;
  for (i = 0; i < 81; i++){
    for (j = 0; j < 8; j++)
      printf ("%d ",possibleValues[i][j]);
    printf("\n");
  }
  return 0;
}
