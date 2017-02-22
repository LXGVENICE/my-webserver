#pragma once

#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet.h>
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
private:
    pid_t m_pid;
    int m_pipefd[2];
}

class ProcessPool
{
private:
    Processpool(int listenfd,int process_number = 8);
public:
    static ProcessPool* create(int listenfd,int process_number = 8)
    {
        if( m_instance == NULL)
        {
            m_instance = new ProcessPool(listenfd,process_number)
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

ProcessPool* ProcessPool::m_instance = NULL;

static int sig_pipefd[2];

static int setnonblocking(int fd)
{
    int old_option = fcntl(fd,F_CETFL);
    int new_option = old_opion | O_NOBLOCK;
    fcntl(fd,F_SETFL,new_opetion);
    return old_opion;
}

static void addfd(int epollfd,int fd)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epolled,EPOLL_CTL_ADD,fd,&event);
    setnonblocking(fd);
}

static void removefd(int epolled,int fd)
{
    epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,0);
    close(fd);
}

static void sig_handler(int sig)
{
    int save_errno = errno;
    int msg = sig;
    send(sig_pipifd(1),(char*)&msg,1,0);
    error = save_errno;
}

static void addsig(int sig,void(*handler)(int),bool restart = true)
{
    struct sigaction sa;
    bzero(&sa,sizeof(sa));
    sa.sa_handler = handler;
    if(restart)
    {
        sa.sa_flafs |= SA_RESTART;
    }
    sigfillset(&sa.sa_mask);
    assert(sigaction(sig,&sa,NULL) != -1);
}