#include <stdio.h>
#include <raylib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BOARD_SIZE 8
#define TILE_SIZE 42
#define TILE_TYPES 5

int score=0;
const char tile_chars[TILE_TYPES]={'$', '%', '&', '@', '#'};


char board[BOARD_SIZE][BOARD_SIZE]={0};
Vector2 grid_origin;
Texture2D background;
char random_tile(){
    return tile_chars[rand() % TILE_TYPES];
}
bool tilesMacthes[BOARD_SIZE][BOARD_SIZE]={false};

bool findTilesMacthes(){
    bool found= false;
    for(int x=0; x<BOARD_SIZE; x++){
        for(int y=0; y<BOARD_SIZE - 2; y++){
                char wy1= board[x][y];
                char wy2= board[x][y + 1];
                char wy3= board[x][y + 2];
                if(wy1 == wy2 && wy2 == wy3){
                      //fprintf(stdout, "won index y starting %d end %d is %c, %c, %c \n", y, y+2, wy1, wy2, wy3);
                     tilesMacthes[x][y] = true;
                     tilesMacthes[x][y + 1] = true;
                     tilesMacthes[x][y + 2] = true;
                     score++;
                     found = true;
                }
                    //
        };
    };
    for (int x=0; x<BOARD_SIZE - 2; x++){
        for(int y=0; y<BOARD_SIZE; y++){
             char yw1= board[x][y];
             char yw2= board[x  + 1][y];
             char yw3= board[x  + 2][y];
             if(yw1 == yw2 && yw2 == yw3){
             //fprintf(stdout, "won index x starting %d end %d is %c, %c, %c and y is %d \n", x, x+2, yw1, yw2, yw3, y);
             tilesMacthes[x][y] = true;
             tilesMacthes[x + 1][y] = true;
             tilesMacthes[x + 1][y] = true;
              score++;
              found = true;
            }
        }
    }
    return found;
};
void removeMacthes(){
        for(int xAxios=0; xAxios < BOARD_SIZE; xAxios){
            for(int yAxios=0; yAxios <BOARD_SIZE; yAxios++){
                if(tilesMacthes[xAxios][yAxios]){
                    board[xAxios][yAxios]= random_tile();
                    tilesMacthes[xAxios][yAxios]= false;
                }else{
                    board[xAxios][yAxios]= board[xAxios][yAxios];
                }
            }
        }
    
}
void init_board(){
    for(int i=0; i<BOARD_SIZE; i++){// for outer section of array
        for(int j=0; j<BOARD_SIZE; j++){// for iner section of array
            board[i][j]= random_tile();// what this does is for every element of our inner array way change the value to a random selected data
        }
    }
    int grid_width = BOARD_SIZE * TILE_SIZE;
    int grid_height = BOARD_SIZE * TILE_SIZE;

    grid_origin =(Vector2){
        (GetScreenWidth() - grid_width) / 2,
        (GetScreenHeight() - grid_height) / 2
    };
};

int main(void){
    //fprintf(stdout, "well the file is loaded \n");
    InitWindow(800, 450, "puzzle game");// screan width
    SetTargetFPS(60);// this tells the updates the cpu every 16miliseconds leave this out and your cpu works the loop
    srand(time(NULL));
    background = LoadTexture("assets/d.png");
    Vector2 mouse ={0, 0};
    Vector2 selectedTile={0, 0};
    Vector2 compiredTile={0, 0};
    init_board();
    findTilesMacthes();
    //removeMacthes();
    //fprintf(stdout, "random %d \n", rand());
    //lets bring out our raylib window
    int count =0;
    while(!WindowShouldClose()){
          //findTilesMacthes(); 
        // lestin on mouse events
        mouse = GetMousePosition();
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            //fprintf(stdout, "mouse is pressed %d times mouse position horizontaly is %f  mouse position vaticaly is %f \n", ++count, mouse.x, mouse.y);
            int xClikedPosition= (mouse.x - grid_origin.x) / TILE_SIZE;
            int yClikedPosition= (mouse.y - grid_origin.y) / TILE_SIZE;
            if(xClikedPosition >= 0 && xClikedPosition < 8 && yClikedPosition >= 0 && yClikedPosition < 8){
               // fprintf(stdout, "user cliked carecter %c  index  cliked are x - %d y- %d\n", board[yClikedPosition][xClikedPosition], xClikedPosition, yClikedPosition);
                compiredTile =(Vector2){selectedTile.x, selectedTile.y};
                selectedTile=(Vector2){xClikedPosition + 1, yClikedPosition + 1};
                //removeMacthes();
                findTilesMacthes();
            }else{
            selectedTile=(Vector2){0, 0};
             compiredTile=(Vector2){0, 0};
            }
            /*
            am going to be addressing view port values in pixes
            so basicaly to get the position cliked we suptract the position cliked on the screan 
            from the known position our grid box stats so 
            window width = 800 px;
            window hiegth = 450 px;
            since we are drawing to the screan 8 rows and 8 columes for each row the structure is like this
            array[0 - 7][0 -7]=  0 1 2 3 4 5 6 7
                                1 - - - - - - - -
                                2 - - - - - - - -
                                3 - - - - - - - -
                                4 - - - - - - - - 
                                5 - - - - - - - - 
                                6 - - - - - - - - 
                                7 - - - - - - - - 
            and we have out Tile to be 42px and we used it for the x and y axis
            so a single element in our array is 
                42px              
            42px  -
            and our window is horitontal/x = 800px, vatical/y = 450px,
            so our window is somthing like this
                              800px 
            - - - - - - - - - - - - - - - - - - - - - - 
            |                                         |
            |                                         |  
            |                                         | 
    450px   |                                         |  
            |                                         |  
            |                                         |  
            |                                         |  
            |                                         |      
            - - - - - - - - - - - - - - - - - - - - - - 
             now drowing/rending each reactangle would give use a view like this
             
                              800px 
            - - - - - - - - - - - - - - - - - - - - - - 
            | -                                       |
            | ^                                       |  
            | |                                       | 
    450px   | only one cube                           |  
            |                                         |  
            |                                         |  
            |                                         |  
            |                                         |      
            - - - - - - - - - - - - - - - - - - - - - -
                                                    46px 
             not that were geting only one tile 46px  -  and not rows or columed well we are not getting rows or colums because its stacked upon each other in a for loop we did

             for(let x=0; x<arrayLenth; x++){ this for each row //array[row][colums];
                for(let y=0; y<arrayLenth; y++){ this for colums each element in a row //array[row][colums];
                  ->  //DrawRectangleLinesEx(firstAgumentDataStructure, thickness of rectengules borders, color of rectengules borders); so we pass there aguments here
                  Rectangle rect={
                    0, //this the position of the cube not reactengle a single cube x axis position horizontaly (to move left and write)
                    0, //this for the vatical axios y axiox  (to move up and down)
                    46, //the actule cube size x aixos (point a to b);
                    46  //the actule cube size y aixos (point c to d);
                    //
                    DrawRectangleLinesEx(rect, 2, BLACK);
                };
                not point a starts at the position x is defined at x is at 10px we start point a at 10px and move the size of tile horizontaly
                same goes for y but y dosent start at the point its geavin rithe it ends so y pushes x (down or up)and x pushes (y left and right)
                 now why we got all our cubes in a single position is becasue wehn rendering/drawaing reactangle we starts all at x 0 and y ends at 0
                 to fixe this we could start the next cube at the end of the last like so
                 Rectangle rect={
                    x * 46, 
                    y * 46, 
                    46, //the actule cube size x aixos (point a to b);
                    46  //the actule cube size y aixos (point c to d);
                };
                //
                since i is for each row and i starts at 0 so (1) cube starts at x -0px and moves to x- 46px               __   
                and for (1) cube y axios its starts at y- 0px colume and ends at at y- 46px so first cube makes angle 90 | 1 cube
                next itaration is cube 2 x is now 1  and 1 * 46 = 46 so cube 2 x axios (starts) at x- 46px and moves x- 46px so it (ends) at 46px whick in them 2 cube starts at end of first cube then adds 46 more to its lentgh,               __  
                same logic for y axios y is at second colume of row so it starts at 46 and moves 46 down you notice that both first and second cube x and y axios starts at same point and end at same point so  2 cube makes up angle 90 as well | 2 cube

                and when you view it with two cube its 

                --
                | 1 cube
                __
                |  2 cube
                and so one now if all moves somthly we end up with this view  
                
                              800px 
            - - - - - - - - - - - - - - - - - - - - - - 
            |   0 1 2 3 4 5 6 7                       |                  
            | 1 - - - - - - - -                       |   
            | 2 - - - - - - - -                       |  
            | 3 - - - - - - - -                       |  
            | 4 - - - - - - - -                       |  
            | 5 - - - - - - - -                       |      
            | 6 - - - - - - - -                       |  
            | 7 - - - - - - - -                       |
            |                                         | 
    450px   |                                         |  
            |                                         |  
            |                                         |  
            |                                         |  
            |                                         |      
            - - - - - - - - - - - - - - - - - - - - - -                         

            now we got our grid but its not the the middle can you guess why 
            well we start our row and colume at index 0 so 0px to the left how do we center it
            well taking that diaram we know our grid is 8 rows 8 columes each columes is 46 by 46 so 8 rows multiply by 46 columes is  8 * 46 = 336 
            so we know our grid table is 336px both width and hight so 
                grid
            
                ___ 336x_______
               |     
         336px |
               | 
               
          now since 336px is in 800px width and 336px is in 450px height we are left with
          464px of width in our window and 114px of hight in our window like so           
                
                              800px 
            - - - - - - - - - - - - - - - - - - - - - - 
            |   0 1 2 3 4 5 6 7                       |                  
            | 1 - - - - - - - -                       |   
            | 2 - - - - - - - -                       |  
            | 3 - - - - - - - -     left(464px)w      |  
            | 4 - - - - - - - -                       |  
            | 5 - - - - - - - -                       |      
            | 6 - - - - - - - -                       |  
            | 7 - - - - - - - -                       |
            |                                         | 
    450px   |                                         |  
            |               left(114px)h              |  
            |                                         |  
            |                                         |  
            |                                         |      
            - - - - - - - - - - - - - - - - - - - - - -            
          
            but how do we center the grid well if since we know we got space and our left over is 464 and even number that could be divided by two we just spit it in half to get the middle 
            so 464 / 2 = 232px and 114 / 2 is 57px
            if we view it we should have somthing like this
                               800px 
            - - - - - - - - - - - - - - - - - - - - - - 
            |              left(57)h                  |                  
            |                                         |   
            |              0 1 2 3 4 5 6 7            |  
            |            1 - - - - - - - -            |  
            |            2 - - - - - - - -            |  
            |            3 - - - - - - - -            |      
            |(232px)w    4 - - - - - - - -  (232px)w  |  
            |            5 - - - - - - - -            |
            |            5 - - - - - - - -            | 
    450px   |            5 - - - - - - - -            |  
            |                                         |  
            |                                         |  
            |              left(57)h                  |  
            |                                         |      
            - - - - - - - - - - - - - - - - - - - - - -  
            well we got the viture of how to get it in the middle by spliting the left over space by two 
            to start at the middle we have to start first row at 232px and first colume at 57px
            which we can apply as follow
            Rectangle rect={
                    ((window width - grid width) / 2)  + row index  * 46 ,
                    ((window heigth - grid higth) / 2) + row index  * 46 ,
                    TILE_SIZE,
                    TILE_SIZE
                };
            DrawRectangleLinesEx(rect, 2, BLACK);
          }
             }
            
             */
         };
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(
            background,
            (Rectangle){
             0, 0, background.width, background.height
            },
            (Rectangle){
            0, 0, GetScreenWidth(), GetScreenHeight()
            },
            (Vector2){ 0, 0 },
            0.0f,
            WHITE
        );
        DrawText(TextFormat("Score: %d", score), 15, 16, 20, ORANGE);
        //fprintf(stdout, "gird origin %lf \r", grid_origin.x);
        for(int x=0; x<BOARD_SIZE; x++){
            //
            for (int y=0; y<BOARD_SIZE; y++){
                Rectangle rect={
                    grid_origin.x + (x * TILE_SIZE),
                    grid_origin.y + (y * TILE_SIZE),
                    TILE_SIZE,
                    TILE_SIZE
                };
                DrawRectangleLinesEx(rect, 2, BLACK);
                DrawTextEx(
                    GetFontDefault(),
                    TextFormat("%c", board[x][y]),
                    (Vector2) {rect.x + 13, rect.y + 9},
                    20, 1, tilesMacthes[x][y] ? GREEN : WHITE
                );
                //   
            };
            
        }
        //
        if(selectedTile.x > 0){
            DrawRectangleLinesEx((Rectangle){
            grid_origin.x + ((selectedTile.x -1) * TILE_SIZE),
            grid_origin.y + ((selectedTile.y -1)* TILE_SIZE),
            TILE_SIZE,
            TILE_SIZE
        },
        2,
        YELLOW
        );
        
        if(compiredTile.x > 0){
            int x= selectedTile.x -1;
            int y= selectedTile.y -1; 
            int cx= compiredTile.x - 1;
            int cy= compiredTile.y - 1;
            char selectedCharecter= board[x][y];
            char compiredCharecter= board[cx][cy];
            //fprintf(stdout, "selected tile %c and compired tile is %c \r", selectedCharecter, compiredCharecter);
            // swap tiles
            if(((cx + 1) == x) && cy == y || ((cx - 1) == x) && cy == y){
            board[x][y]= compiredCharecter;
            board[cx][cy]= selectedCharecter;
            //fprintf(stdout, "move tile \n");
            }else if(((cy + 1) == y) && cx == x || ((cy - 1) == y) && cx == x){
            board[x][y]= compiredCharecter;
            board[cx][cy]= selectedCharecter;
            //fprintf(stdout, "move tile \n");
            }
            compiredTile=(Vector2){0, 0};
            //fprintf(stdout, "user is at cx %d and want to move x %d cy %d and want to move y %d \n", cx, x, cy, y);
                    
                    
        }
        
        }
        EndDrawing();
    };
    
    //clear resuses
    UnloadTexture(background);
    // close window
    CloseWindow();
    return 0;
}