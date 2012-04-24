#ifndef SHUFFLE_H
#define SHUFFLE_H

#include <cstdlib>
#include <ctime>

class Shuffle
{
public:
    Shuffle(bool shuffle);
    void getNumbers(int tab[]);
private:
    bool needShuffle;
    int numbers[10];
    int n;
};

#endif // SHUFFLE_H
