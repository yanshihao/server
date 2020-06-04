// 本test主要测试Timestamp
// struct timeval tv;
// struct timezone tz;
// 将得到从linux epoch（1970年1月1日0点0分0秒，UTC格林威治时间）算起的总秒和微秒数。
// 结构体struct timeval中tv_sec存储秒数，tv_usec存储微秒数。 
// 需要做一下减法才行
// gettimeofday (&tv, &tz);

#include "Timestamp.h"
#include <iostream>
#include <sys/time.h>
int main()
{
    Timestamp now(Timestamp::now());
    std::cout <<now.toFormattedString() << std::endl; 
    return 0;
}