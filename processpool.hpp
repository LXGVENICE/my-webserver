#pragma once

#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <strings.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <assert.h>
#include "cgi_conn.hpp"

class Process
{
public:
    Process():m_pid(-1){}
public:
    pid_t m_pid;
    int m_pipefd[2];
};

class ProcessPool
{
private:
    ProcessPool(int listenfd,int process_number = 8);
public:
    static ProcessPool* create(int listenfd,int process_number = 8)
    {
        if( m_instance == NULL)
        {
            m_instance = new ProcessPool(listenfd,process_number);
        }
        return m_instance;
    }
    ~ProcessPool();
    void run();
private:
    void setup_sig_pipe();
    void run_parent();
    void run_child();
private:
    static const int MAX_PROCESS_NUMBER = 16;
    static const int USER_PER_PROCESS = 65536;
    static const int MAX_EVENT_NUMBER = 10000;//epoll
    int m_process_number;//sum num of process
    int m_idx;//from 0
    int m_epollfd;
    int m_listenfd;
    bool m_stop;
    Process* m_sub_process;
    static ProcessPool* m_instance;
};
