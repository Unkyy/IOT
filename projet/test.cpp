#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

#define NUM_THREADS 5

#define BLACK   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"

std::mutex colour_mutex;

void PrintAsciiText(int id)
{
    string colour;

    colour_mutex.lock();
    switch(id)
    {
    case 0:
        colour = RED;
        break;
    case 1:
        colour = GREEN;
        break;
    case 2:
        colour = YELLOW;
        break;
    case 3:
        colour = BLUE;
        break;
    case 4:
        colour = CYAN;
        break;
    default:
        colour = BLACK;
        break;
    }

    cout << colour << "I'm a new thread, I'm number " << id << BLACK << endl;
    colour_mutex.unlock();
}

int main()
{
    vector<thread> threads;

    for(int i = 0; i < NUM_THREADS; ++i)
    {
        threads.push_back(std::thread(PrintAsciiText, i));
    }

    for (vector<thread>::iterator it = threads.begin() ; it != threads.end() ; ++it)
    {
        it->join();
    }

    return 0;
}
