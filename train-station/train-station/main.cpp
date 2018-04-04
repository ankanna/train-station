
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <ncurses.h>

std::mutex mx;

void run_train(int length, int train_ID )
{
        mx.lock();
    std::string s(1, (char) train_ID);
    //printw( "/ntrain %s : ", &s );
    std::cout << std::endl << "train " + s + " : ";
    for (int i = 0; i < length; i++)
    {
      //   printw( "==" );
        std::cout << "==";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    mx.unlock();
}

int main()
{
    int train_number = 15;
    
    std::vector<std::thread> threads;
    std::vector<int> trains;
    
    for (int i = 0; i < train_number; i++){
        trains.push_back(i+65);
    }
    for (int i = 0; i < train_number; i++)
        threads.push_back(std::thread(run_train, i+1, trains[i])); // startuje nowy watek i wrzca do wektora
    
    for (auto& thread : threads){ // for (int i = 0; i < 10; i++)
        thread.join();           // threads[i].join()
    }
    
    return 0;
}
