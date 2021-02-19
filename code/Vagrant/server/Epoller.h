#ifndef EPOLLER_H
#define EPOLLER_H

#include <sys/epoll.h> 
#include <fcntl.h>  
#include <unistd.h> 
#include <assert.h> 
#include <vector>
#include <errno.h>

class Epoller {
public:
    explicit Epoller(int maxEvent = 1024);
    virtual ~Epoller();
    bool addFd(int fd, uint32_t events);
    bool modFd(int fd, uint32_t events);
    bool delFd(int fd);
    int wait(int timeoutMs = -1);
    int getEventFd(size_t i) const;
    uint32_t getEvents(size_t i) const;
    int getEpollFd();
private:
    int epollFd;
    struct epoll_event *events;  
    int events_size;
};

#endif //EPOLLER_H