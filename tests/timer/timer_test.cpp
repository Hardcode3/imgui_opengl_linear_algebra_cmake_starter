#include <timer.h>

int main()
{
    Timer timer;
    timer.begin();

    int i = 0;
    while (i < 1e8)
        i += 1;

    timer.stop();
    timer.printExecutionTime();

    timer.begin();
    int j = 0;
    while (j < 1e8)
        j += 1;
    timer.stop();
    timer.printExecutionTime();

    timer.begin();
    timer.stop();
    timer.printExecutionTime();
    return 0;
}