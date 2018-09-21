/***********************************************************************
  * Copyright (c) 2012, Baidu Inc. All rights reserved.
  * 
  * Licensed under the BSD License
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  * 
  *      license.txt
  *********************************************************************/

#ifndef _WIN32

#include "event_poll.h"
#include "socket_util.h"
#include "log.h"
#include "bgcc_error.h"

#include <assert.h>

namespace bgcc {

    EventLoop::EventLoop() :
        _state(S_UNINIT), _stopped(true), _epfd(-1) {
        }

    int32_t EventLoop::create() {
        if (S_UNINIT != _state) {
            return -1;
        }

        _epfd = epoll_create(EventLoop::GREATER_THAN_ZERO);

        if (-1 == _epfd) {
            return -1;
        }
        else {
            _state = S_INIT;
            return 0;
        }
    }

    int32_t EventLoop::destroy() {
        SocketTool::close(_epfd);
        _state = S_DESTROYED;
        return 0;
    }

    int32_t EventLoop::add_event(Event* event) {
        if (S_INIT != _state && S_LOOP != _state) {
            return -1;
        }

        if (NULL == event) {
            return 0;
        }

        int32_t fd = event->fd;
        uint32_t mask = event->mask;
        int32_t op = EPOLL_CTL_ADD;

        if (fd < 0 || fd >= MAXNFD) { 
            BGCC_WARN("bgcc", "Before Add fd=%d to Epoll failed, fd is invalid", fd);
            return -1;
        }

        _events[fd].mask = mask;

        struct epoll_event ee;

        // To fix valgrind error: Syscall param epoll_ctl(event) points to uninitialised byte(s)
        memset(&ee.data, 0, sizeof(ee.data));

        ee.data.fd = fd;
        ee.events = 0;

        if (mask & EVENT_READ) {
            ee.events |= EPOLLIN;
            _events[fd].read_cb = event->read_cb;
            _events[fd].read_cb_arg = event->read_cb_arg;
        }

        if (mask & EVENT_WRITE) {
            ee.events |= EPOLLOUT;
            _events[fd].write_cb = event->write_cb;
            _events[fd].write_cb_arg = event->write_cb_arg;
        }

        if (mask & EVENT_ERROR) {
            ee.events |= EPOLLERR;
            _events[fd].error_cb = event->error_cb;
            _events[fd].error_cb_arg = event->error_cb_arg;
        }

        if(SocketTool::set_nonblock(fd, 1)!=0){
            BGCC_WARN("bgcc", "Before Add fd=%d to Epoll Set To Nonblock Failed(%d)",
                    fd, BgccGetLastError());
            return -1;
        }

        int32_t ret=epoll_ctl(_epfd, op, fd, &ee);
        if (ret == -1) {
            BGCC_WARN("bgcc", "epoll_ctl failed, fd=%d, op=%d(%d)", fd, op, BgccGetLastError());
        } else {
            BGCC_TRACE("bgcc", "epoll_ctl sucess, fd=%d, op=%d", fd, op);
        }

        if(0!=ret&&EPOLL_CTL_ADD==op){
            if(SocketTool::set_nonblock(fd, 0)!=0){
                BGCC_WARN("bgcc", "Add fd=%d to Epoll Failed Set To Block Failed(%d)",
                    fd, BgccGetLastError());
            }
        }

        return ret;
    }

    int32_t EventLoop::del_event(Event* event) {
        if (S_INIT != _state && S_LOOP != _state) {
            return -1;
        }

        if (NULL == event) {
            return 0;
        }

        int32_t fd = event->fd;
        
        if (fd < 0 || fd >= MAXNFD) { 
            BGCC_WARN("bgcc", "Before del fd=%d from Epoll failed, fd is invalid", fd);
            return -1;
        }
        
        uint32_t mask = _events[fd].mask & (~event->mask);
        _events[fd].mask = mask;

        struct epoll_event ee;
        ee.data.fd = fd;
        ee.events = 0;
        if (mask & EVENT_READ) ee.events |= EPOLLIN;
        if (mask & EVENT_WRITE) ee.events |= EPOLLOUT;

        int32_t op;
        if (mask != EVENT_NONE) {
            op = EPOLL_CTL_MOD;
        } else {
            op = EPOLL_CTL_DEL;
//			_events[fd].Reset();
        }

        int32_t ret=epoll_ctl(_epfd, op, fd, &ee);
        if (ret == -1) {
            BGCC_WARN("bgcc", "epoll_ctl failed, fd=%d, op=%d(%d)", fd, op, BgccGetLastError());
        } else {
            BGCC_TRACE("bgcc", "epoll_ctl sucess, fd=%d, op=%d", fd, op);
        }

        if(EPOLL_CTL_DEL==op&&0==ret){
            if(SocketTool::set_nonblock(fd, 0)!=0){
                BGCC_WARN("bgcc", "Del fd=%d From Epoll Set To Block Failed(%d)",
                        fd, BgccGetLastError());
            }
        }
        return ret;
    }

    int32_t EventLoop::loop() {
        if (_state != S_INIT) {
            return -1;
        }
        _state = S_LOOP;
        _stopped = false;

        struct epoll_event ep_events[EventLoop::MAXNEVENT_EACH_ROUND];
        int32_t numevents;

        while (!_stopped) {
            do {
                numevents = epoll_wait(_epfd, ep_events, EventLoop::MAXNEVENT_EACH_ROUND, 200);
            } while (numevents == SOCKET_ERROR && errno == EINTR);

            if (numevents > 0) {
                int j;

                for (j = 0; j < numevents; j++) {
                    struct epoll_event* e = ep_events + j;
                    int32_t fd = e->data.fd;

                    if (e->events & EPOLLIN) {
                        if (_events[fd].read_cb)
                            (_events[fd].read_cb)(this, fd, _events[fd].read_cb_arg);
                    }
                    if (e->events & EPOLLOUT) {
                        if (_events[fd].write_cb)
                            (_events[fd].write_cb)(this, fd, _events[fd].write_cb_arg);
                    }
                    if (e->events & EPOLLERR) {
                        if (_events[fd].error_cb)
                            (_events[fd].error_cb)(this, fd, _events[fd].error_cb_arg);
                    }
                }
            }
        }

        _state = S_STOP;
        return 0;
    }

    int32_t EventLoop::unloop() {
        _stopped = true;
        return 0;
    }

    bool EventLoop::is_stopped() const {
        return _stopped;
    }

    void EventLoop::reset_event(int event_idx) {
        assert(event_idx < MAXNFD && event_idx >= 0);

        _events[event_idx].Reset();
    }

    const int EventLoop::GREATER_THAN_ZERO = 10;
    const int EventLoop::MAXNEVENT_EACH_ROUND = 10;
}

#endif

