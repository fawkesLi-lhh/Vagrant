#include "Epoller.h"

#include <fcntl.h>

Epoller::Epoller(int maxEvent):epollFd(epoll_create(5)), events(new epoll_event[maxEvent]),events_size(maxEvent){
    assert(epollFd >= 0);
}

Epoller::~Epoller() {
    close(epollFd);
    delete[] events;
}

bool Epoller::addFd(int fd, uint32_t events) {
    if(fd < 0) return false;
    epoll_event ev = {0};
    ev.data.fd = fd;
    ev.events = events;
    epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &ev);
    int old_option = fcntl( fd, F_GETFL );
    int new_option = old_option | O_NONBLOCK;
    fcntl( fd, F_SETFL, new_option );
    return true;
}

bool Epoller::modFd(int fd, uint32_t events) {
    if(fd < 0) return false;
    epoll_event ev = {0};
    ev.data.fd = fd;
    ev.events = events;
    return 0 == epoll_ctl(epollFd, EPOLL_CTL_MOD, fd, &ev);
}

bool Epoller::delFd(int fd) {
    if(fd < 0) return false;
    epoll_event ev = {0};
    return 0 == epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, &ev);
}

int Epoller::wait(int timeoutMs) {
    return epoll_wait(epollFd, &events[0], events_size, timeoutMs);
}

int Epoller::getEventFd(size_t i) const {
    assert(i < events_size&& i >= 0);
    return events[i].data.fd;
}

uint32_t Epoller::getEvents(size_t i) const {
    assert(i < events_size && i >= 0);
    return events[i].events;
}

int Epoller::getEpollFd(){
    return epollFd;
}