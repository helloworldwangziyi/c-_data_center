# procctl

这个模块实现了调度程序的功能，比如我们模仿的气象数据采集，就可以通过该程序按照规定的时间重复，（就是多长时间采集一次）

  

需要注意一下几点：

1. execl 和 execv的使用 execl 需要对不同参数进行处理，但是execv就可以避免这样，更加优雅

2. 子进程执行完后，我们需要手动的退出，否则再子进程调用失败时，我们将会得到过多的僵尸进程，会使系统崩溃

其他的没啥了，看看代码吧

```
char *pargv[argc];

for (int ii=2;ii<argc;ii++)

	pargv[ii-2]=argv[ii];

pargv[argc-2]=NULL;
 // 这一部分对应1 我们将要用到的参数放到pargv的列表中 这样就不必忧心参数个数的问题了

 // 这一部分对应2 
   while (true)
  {
    if (fork()==0)
    {
      execv(argv[2],pargv);
      exit(0); // 这里加上退出防止execv调用失败 无限生成子进程
    }
    else
    {
      int status;
      wait(&status);
      sleep(atoi(argv[1]));
    }
  }
 
```

  


