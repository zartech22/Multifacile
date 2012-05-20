#include "Shuffle.h"

Shuffle::Shuffle(bool shuffle)
{
    needShuffle = shuffle;
}
void Shuffle::getNumbers(int tab[])
{
    if(needShuffle)
    {
        srand(time(0));

        for (int i=0; i<10; i++)
            numbers[i] = i;

        for (int i=0; i<(10-1); i++)
        {
            int r = i + (rand() % (10-i));
            int temp = numbers[i]; numbers[i] = numbers[r]; numbers[r] = temp;
        }
        for(int i = 0; i<10; i++)
        {
            numbers[i]++;
            tab[i] = numbers[i];
        }

    }
    else if(!needShuffle)
    {
        for(int i = 0; i < 10; i++)
        {
            numbers[i] = i+1;
            tab[i] = numbers[i];
        }
    }
}
void Shuffle::getNumbers(int tab[], int array[])
{
    srand(time(0));

    for (int i=0; i<10; i++)
        numbers[i] = i;

    for (int i=0; i<(10-1); i++)
    {
        int r = i + (rand() % (10-i));
        int temp = numbers[i]; numbers[i] = numbers[r]; numbers[r] = temp;
    }
    for(int i = 0; i<10; i++)
    {
        numbers[i]++;
        tab[i] = numbers[i];
    }
    for(int i = 0; i < (10-1); i++)
    {
        int r = i + (rand() % (10-i));
        int temp = numbers[i]; numbers[i] = numbers[r]; numbers[r] = temp;
    }
    for(int i = 0; i < 10; i++)
        array[i] = numbers[i];
}
