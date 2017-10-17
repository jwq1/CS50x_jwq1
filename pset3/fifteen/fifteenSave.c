/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // TODO
    
    // highest tile number on board
    int tileNum = d*d-1;
    
    // for each row
    for (int i = 0; i < d; i++) {
        // for each column
        for (int j = 0; j < d; j++) {
        
            // set value for the tile
            board[i][j] = tileNum;
            // eprintf("board[%i][%i] = %i", i, j, board[i][j]);
            
            // reduce tile number by one
            tileNum--;
            // eprintf("tileNum = %i", tileNum);
            
        }
    }
    

// SWAPPER ATTEMPT 2

    // // for each row
    //     for (int i = 0; i < d; i++) {
    //         // for each column
    //         for (int j = 0; j < d; j++) {
            
    //         // if, tile number is 2, and there will be an even number of tiles on the board
    //             if (tileNum == 2 && d%2 == 0) {
                    
    //                 // Set the tile, which would normally be numbered "2", to be "1"
    //                 board[i][j] = 1;
    //             }    
                
    //             // else if, tile number is 1, and there will be an even number of tiles on the board
    //             else if (tileNum == 1 && d%2 == 0) {
                    
    //                 // then set the tile, which would normally be "1", to be "2"
    //                 board[i][j] = 2;
                    
    //             }
                
    //             else {    
                    
    //                 // set value for the tile
    //                 board[i][j] = tileNum;
    //                 // eprintf("board[%i][%i] = %i", i, j, board[i][j]);
                    
    //                 // reduce tile number by one
    //                 tileNum--;
    //                 // eprintf("tileNum = %i", tileNum);
    //             } 
                
                    
                    
    //         }
    //     }



// ATTEMPT AT SWAPPER

    // // if # of tiles, d, is an even then swap 1 and 2.
    // // if d modulo 2, the remainder of d divided by 2, is not 0, then d is not an even number, therefore swap.
    // if (d%2 == 0) {
    //     board[d][d-1] = 2;
    //     board[d][d-2] = 1;
        
        
        
        
    //     // int swapper = board[d][d-2];
        
    //     // // set tile w/ #2, to be tile w/ #1
    //     // board[d][d-2] = board[d][d-1];
        
    //     // // set tile w/ #1, to be tile w/ #2
    //     // board[d][d-1] = swapper;
        
    // }
    
    
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO
    
     // for each row
    for (int i = 0; i < d; i++) {
        // for each column
        for (int j = 0; j < d; j++) {
        
            // print null for final character
            if(board[i][j] == 0){
                printf("   _");
            } 
            
            // else print tile
            else {
                
                // print tile with space in front of single digits
                printf("  %2i", board[i][j]);
                
            }
    
        }
        
        // print new line
        printf("\n\n");    
            
    }
        
        
    
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // TODO
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // TODO
    return false;
}
