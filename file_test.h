/*
 * file_test.h
 *
 * Created on: May 2, 2014
 * Author: root
 */
#ifndef FILE_TEST_H_
#define FILE_TEST_H_
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
class FileTest {
public:
        FileTest();
        virtual ~FileTest();
        void process();
        void setFileName(std::string filename);
        static void test();
private:
         std::string m_filename;
         //bool status;
};
#endif /* FILE_TEST_H_ */

/*
 * file_test.cpp
 *
 * Created on: May 2, 2014
 * Author: root
 */
#include "file_test.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include "log/log.h"
#include<fstream>
using namespace std;
static int num = 0;
FileTest::FileTest():m_filename("") {
        // TODO Auto-generated constructor stub
}
FileTest::~FileTest() {
        // TODO Auto-generated destructor stub
}
void FileTest::setFileName(std::string filename)
{
        m_filename = filename;
}
std::string IntToString(int i){
        string c;
        ostringstream oss;
        oss<<i;
        c=oss.str();
        return c;
}
static Logs logger=Logs::instance();
void FileTest::process()
{
        num++;
        logger.write_error("num:");
        logger.write_error(IntToString(num).c_str());
        logger.write_error(m_filename.c_str());
}
void FileTest::test()
{
num++;
cout << num << endl;
}
