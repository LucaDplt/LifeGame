#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int FPS;

int SIZE = 0;
char **ACTUAL_TAB;
char **NEXT_TAB;
pthread_t **THREADS;
pthread_barrier_t BARRIER;

char DEAD = '.';
char ALIVE = 'O';

void show(char** tab)   
{
    string tabToString;
    for(int line = 0; line < SIZE; line++)
    {
        for(int column = 0; column < SIZE; column++)
        {
            tabToString += string(1, tab[line][column]) + " ";
        }
        tabToString += "\n";
    }
    cout<<tabToString;
}

char** initTab()
{
    char **tab = new char*[SIZE];
    for(int line = 0; line < SIZE; line++)
    {
        tab[line] = new char[SIZE];
        for(int column = 0; column < SIZE; column++)
        {
            int rd = rand() % 3;
            if(rd == 0)
            {
                tab[line][column] = ALIVE;
            }
            else
            {
                tab[line][column] = DEAD;
            }
        }
    }
    return tab;
}

bool check()
{
    for(int x = 0; x < SIZE; x++)
    {
        for(int y = 0; y < SIZE; y++)
        {
            if(ACTUAL_TAB[x][y] != NEXT_TAB[x][y])
            {
                return false;
            }
        }
    }
    return true;
}

void* cellFunction(void* arg)
{
    int* pos = (int*)arg;
    int x = pos[0];
    int y = pos[1];
    delete pos;

    int limit = FPS * 30;
    for(int i = 0; i < limit; i++)
    {
        int countAlive = 0;

        //Left
        if(x > 0)
        {
            if(ACTUAL_TAB[x - 1][y] == ALIVE)
            {
                countAlive ++;
            }
        }
        //Right
        if(x < SIZE-1)
        {
            if(ACTUAL_TAB[x + 1][y] == ALIVE)
            {
                countAlive ++;
            }
        }
        //Up
        if(y > 0)
        {
            if(ACTUAL_TAB[x][y-1] == ALIVE)
            {
                countAlive ++;
            }
        }
        //Down
        if(y < SIZE-1)
        {
            if(ACTUAL_TAB[x][y+1] == ALIVE)
            {
                countAlive ++;
            }
        }
        //UpLeft
        if(x > 0 and y > 0)
        {
            if(ACTUAL_TAB[x-1][y-1] == ALIVE)
            {
                countAlive ++;
            }
        }
        //UpRight
        if(x < SIZE-1 and y > 0)
        {
            if(ACTUAL_TAB[x+1][y-1] == ALIVE)
            {
                countAlive ++;
            }
        }
        //DownLeft
        if(x > 0 and y < SIZE-1)
        {
            if(ACTUAL_TAB[x-1][y+1] == ALIVE)
            {
                countAlive ++;
            }
        }
        //DownRight
        if(y < SIZE-1 and x < SIZE-1)
        {
            if(ACTUAL_TAB[x+1][y+1] == ALIVE)
            {
                countAlive ++;
            }
        }

        if(ACTUAL_TAB[x][y] == ALIVE)
        {
            if(countAlive < 2 or countAlive > 3)
            {
                NEXT_TAB[x][y] = DEAD;
            }
            else
            {
                NEXT_TAB[x][y] = ALIVE;
            }
        }
        if(ACTUAL_TAB[x][y] == DEAD)
        {
            if(countAlive == 3)
            {
                NEXT_TAB[x][y] = ALIVE;
            }
            else
            {
                NEXT_TAB[x][y] = DEAD;
            }
        }

        pthread_barrier_wait(&BARRIER);

        if(x == 0 && y == 0)
        {
            char** tmp;
            tmp = ACTUAL_TAB;
            ACTUAL_TAB = NEXT_TAB;
            NEXT_TAB = tmp;
            if(check())
            {
                exit(0);
            }

            usleep(1000000/FPS);
            system("cls");
            show(ACTUAL_TAB);
        }
        
        pthread_barrier_wait(&BARRIER);
    }
    return nullptr;
}

void init()
{
    string str;
    bool isNumber = true;
    do
    {
        isNumber = true;
        cout<<"Enter the size of grid Int -> [Int x Int] : ";
        cin>>str;
        for(int i = 0; i < str.size(); i++)
        {
            if(!isdigit(str[i]))
            {
                isNumber = false;
                break;
            }
        }
    } while (!isNumber);
    SIZE = stoi(str);

    do
    {
       str = "";
        do
        {
            isNumber = true;
            cout<<"Enter the speed (FPS) : ";
            cin>>str;
            for(int i = 0; i < str.size(); i++)
            {
                if(!isdigit(str[i]))
                {
                    isNumber = false;
                    break;
                }
            }
        } while (!isNumber);
        FPS = stoi(str); 
    } while(FPS >= 1000000);
    
    

    ACTUAL_TAB = initTab();
    NEXT_TAB = initTab();

    THREADS = new pthread_t*[SIZE];
    for(int i = 0; i < SIZE; i++)
    {
        THREADS[i] = new pthread_t[SIZE];
    }

    pthread_barrier_init(&BARRIER, nullptr, SIZE * SIZE);

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int* pos = new int[2]{i, j};
            pthread_create(&THREADS[i][j], nullptr, cellFunction, pos);
        }
    }
}

int main()
{
    srand(time(nullptr));
    init(); 
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            pthread_join(THREADS[i][j], nullptr);
        }
    }
    return 0;
}