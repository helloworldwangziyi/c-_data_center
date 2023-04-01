// 写一个数据入库程序
#include"_public.h"
#include"_mysql.h"

CLogFile logfile;

connection conn;

CPActive PActive;

void EXIT(int sig);

// 业务处理函数
bool _obmindtodb(char *pathname,char *connstr, char *charset);

int main(int argc, char *argv[])
{
  // 帮助文档。
  if (argc!=5)
  {
    printf("\n");
    printf("Using:./obtmindtodb pathname connstr charset logfile\n");

    printf("Example:/project/tools1/bin/procctl 10 /project/idc1/bin/obtmindtodb /idcdata/surfdata \"127.0.0.1,root,123456,mysql,3306\" \"utf8\" /log/idc/obtmindtodb.log\n\n");

    printf("本程序用于把全国站点分钟观测数据保存到数据库的T_ZHOBTMIND表中，数据只插入，不更新。\n");
    printf("pathname 全国站点分钟观测数据文件存放的目录。\n");
    printf("connstr  数据库连接参数：ip,username,password,dbname,port\n");
    printf("charset  数据库的字符集。\n");
    printf("logfile  本程序运行的日志文件名。\n");
    printf("程序每10秒运行一次，由procctl调度。\n\n\n");

    return -1;
  }

  // 关闭全部的信号和输出
  // 设置信号 在shell状态下可以用 kill + 进程号 正常种植进程
  // 但是请不要使用 "kill -9 进程号" 杀死进程，因为这样会导致数据库连接没有正常关闭。
  CloseIOAndSignal();
  signal(SIGINT,EXIT); signal(SIGTERM, EXIT);

  // 打开日志文件
  if(logfile.Open(argv[4],"a+") == false)
  {
    printf("Open logfile %s error!\n", argv[4]);
    return  -1;
  }

  // 进程的心跳 这里时间留5000 表示方便调试
    PActive.AddPInfo(5000,"obtmindtodb");

  /*
  // 连接数据库。
  if (conn.connecttodb(argv[2],argv[3])!=0)
  {
    logfile.Write("connect database(%s) failed.\n%s\n",argv[2],conn.m_cda.message); return -1;
  }

  logfile.Write("connect database(%s) ok.\n",argv[2]);

  // 提交事务。
  conn.commit();
  */
  return 0;
}

void EXIT(int  sig)
{
    logfile.Write("程序退出，sig  = %d\n\n",sig);
    conn.disconnect();
    exit(0);
}

// 业务处理函数
bool _obmindtodb(char *pathname,char *connstr, char *charset)
{
    CDir Dir;
    
    // 打开目录
    if(Dir.OpenDir(pathname, "*.xml") == false)
    {
        logfile.Write("Di.OpenDir(%s) failed \n",pathname);
        return false;
    }

    while(true)
    {
        // 读取目录 得到一个数据文件名
        if(Dir.ReadDir() == false) break;

        logfile.Write("filename=%s\n", Dir.m_FullFileName);

        // 打开文件

        // while(1)
        // {
        //     // 处理文件的每一行
        // }

        // 删除文件 提交事务

    }

    return true;
}
