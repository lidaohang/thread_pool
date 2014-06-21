#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "file_test.h"
#include "thread/thread_pool.h"
using namespace std;
static std::string IntToString(int i){
        string c;
        ostringstream oss;
        oss<<i;
        c=oss.str();
        return c;
}
int main()
{
        ThreadPool<FileTest>* thread = new ThreadPool<FileTest>(5,1024);
        FileTest* file_test = new FileTest[5];
        for(int i = 0; i < 5; ++i){
                std::string filename("filename");
                filename.append(IntToString(i));
                filename.append(".txt");
                (file_test + i)->setFileName(filename);
                thread->Push(file_test + i);
        }
        while(false)
        {
                for(int i = 0; i < 24; ++i)
                {
                        (file_test + i)->test();
                }
        }
        sleep(5);
        delete []file_test;
        delete thread;
        return 0;
}
