// ftp 测试代码测试ftp是否可以使用
#include "_ftp.h"

Cftp ftp;

int main()
{
    if(ftp.login("127.0.0.1:21", "wangziyi", "123456") == false)
    {
        printf("ftp.login(127.0.0.1:21) failed \n"); return -1;
    }
    printf("ftp.login(127.0.0.1:21) ok\n");
    ftp.logout();
    return 0;
}