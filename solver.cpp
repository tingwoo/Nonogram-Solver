#include <iostream>
#include <string.h>
#include <vector>

void tryArrangement(int rowLength, 
                    int start,
                    int indexOfActiveSegment,
                    std::vector<int>& segments, 
                    int* knownList,  // {0 1 - - - 1 1 - - 0 0}
                    int* paramList1, // {1 0 3 2 1 0 0 4 3 2 1} consider known black blocks
                    int* paramList2, // {0 8 7 6 5 4 3 2 1 0 0} consider known white blocks
                    int* currentRow,
                    bool* alwaysBlack, 
                    bool* alwaysWhite) {

    if(indexOfActiveSegment >= segments.size()) {
        bool completeRow[80] = {0};

        // check there's no block that must be black in the rest section.
        for(int i = start; i < rowLength; i++) {
            if(knownList[i] == 1) return;
        }
        
        // turn currentRow (0 2 0 0 1) into completeRow (0 1 1 0 1) and then modify alwaysWhite and alwaysBlack.
        for(int i = 0; i < rowLength; i++){
            for(int j = 0; j < currentRow[i]; j++) {
                completeRow[i+j] = true;
            }
            if(completeRow[i]) alwaysWhite[i] = false;
            else alwaysBlack[i] = false;
        }
        return;
    }

    int segmentLength = segments[indexOfActiveSegment];
    for(int i = start; i <= std::min(rowLength - segmentLength, start + paramList1[start]); i++) {
        if(paramList2[i] >= segmentLength && (i+segmentLength == rowLength || knownList[i+segmentLength] != 1)) {
            currentRow[i] = segmentLength;
            tryArrangement(rowLength, i+segmentLength+1, indexOfActiveSegment+1, segments, knownList, paramList1, paramList2, currentRow, alwaysBlack, alwaysWhite);
            currentRow[i] = 0;
        }
    }
    return;
}

int main() {
    int col, row;
    std::string hintText;
    std::vector<int> hint[80]; // assume at most 80 hint cols + rows 
    bool rowsSolved[80] = {0};
    int grid[80][80];

    // input
    std::cin >> col >> row;
    std::cin >> hintText;

    // transform input hint string
    int hintIndex = 0;
    printf("Columns:\n");
    for(int i = 0; i < hintText.length(); i++) {
        if(hintText[i] == ',') {
            hintIndex++;
            printf("\n");
            if(hintIndex == col) printf("Rows:\n");
        } else if(hintText[i] <= '9' && hintText[i] >= '0') {
            hint[hintIndex].push_back(hintText[i] - '0');
            printf("%d ", hint[hintIndex].back());
        } else {
            hint[hintIndex].push_back(hintText[i] - 'A' + 10);
            printf("%d ", hint[hintIndex].back());
        }
    }
    printf("\n");

    for(int i = 0; i < col; i++)
        for(int j = 0; j < row; j++)
            grid[i][j] = -1;

    int tmp1, tmp2;
    int knownList[80];
    int paramList1[80];
    int paramList2[80];
    int currentRow[80];
    bool alwaysBlack[80];
    bool alwaysWhite[80];

    while(true) {
        bool gridChanged = false;
        for(int i = 0; i < col; i++) {
            if(rowsSolved[i]) continue;
            for(int j = 0; j < row; j++) {
                knownList[j] = grid[i][j];
                currentRow[j] = 0;
                alwaysBlack[j] = true;
                alwaysWhite[j] = true;
            }
            tmp1 = 0;
            tmp2 = 0;
            for(int j = row-1; j >= 0; j--) {
                if(knownList[j] == 1) tmp1 = 0; else tmp1++;
                if(knownList[j] == 0) tmp2 = 0; else tmp2++;
                paramList1[j] = tmp1;
                paramList2[j] = tmp2;
            }

            tryArrangement(row, 0, 0, hint[i], knownList, paramList1, paramList2, currentRow, alwaysBlack, alwaysWhite);

            bool rowSolved = true;
            for(int j = 0; j < row; j++) {
                if(alwaysBlack[j]) {
                    switch(grid[i][j]) {
                    case 1:
                        break;
                    case 0:
                        printf("\nUnsolvable.\n");
                        return 0;
                    default:
                        grid[i][j] = 1;
                        gridChanged = true;
                        break;
                    }
                }
                if(alwaysWhite[j]) {
                    switch(grid[i][j]) {
                    case 1:
                        printf("\nUnsolvable.\n");
                        return 0;
                    case 0:
                        break;
                    default:
                        grid[i][j] = 0;
                        gridChanged = true;
                        break;
                    }
                }
                if(grid[i][j] == -1) rowSolved = false;
            }
            rowsSolved[i] = rowSolved;
        }

        for(int i = 0; i < row; i++) {
            if(rowsSolved[col+i]) continue;
            for(int j = 0; j < col; j++) {
                knownList[j] = grid[j][i];
                currentRow[j] = 0;
                alwaysBlack[j] = true;
                alwaysWhite[j] = true;
            }
            tmp1 = 0;
            tmp2 = 0;
            for(int j = col-1; j >= 0; j--) {
                if(knownList[j] == 1) tmp1 = 0; else tmp1++;
                if(knownList[j] == 0) tmp2 = 0; else tmp2++;
                paramList1[j] = tmp1;
                paramList2[j] = tmp2;
            }

            tryArrangement(col, 0, 0, hint[col+i], knownList, paramList1, paramList2, currentRow, alwaysBlack, alwaysWhite);

            bool rowSolved = true;
            for(int j = 0; j < col; j++) {
                if(alwaysBlack[j]) {
                    switch(grid[j][i]) {
                    case 1:
                        break;
                    case 0:
                        printf("\nUnsolvable.\n");
                        return 0;
                    default:
                        grid[j][i] = 1;
                        gridChanged = true;
                        break;
                    }
                }
                if(alwaysWhite[j]) {
                    switch(grid[j][i]) {
                    case 1:
                        printf("\nUnsolvable.\n");
                        return 0;
                    case 0:
                        break;
                    default:
                        grid[j][i] = 0;
                        gridChanged = true;
                        break;
                    }
                }
                if(grid[j][i] == -1) rowSolved = false;
            }
            rowsSolved[col+i] = rowSolved;
        }

        if(!gridChanged) {
            printf("\nUnsolvable.\n");
            return 0;
        }

        printf("\n");
        bool solved = true;
        int count = 0;
        for(int j = 0; j < row; j++) {
            for(int i = 0; i < col; i++) {
                switch(grid[i][j]) {
                case 1:
                    printf("* ");
                    count++;
                    break;
                case 0:
                    printf("  ");
                    count++;
                    break;
                default:
                    printf(". ");
                    solved = false;
                    break;
                }
            }
            printf("\n");
        }
        printf("%.2f%% solved\n", count * 100.0 / (col * row));
        if(solved) break;
    }
    printf("\nNonogram Solved.\n");
    return 0;
}