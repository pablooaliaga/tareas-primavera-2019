#include "nSysimp.h"
#include "fifoqueues.h"
#include "nSystem.h"

void nShare(char* data) {
    START_CRITICAL();
    nTask this_task = current_task;
    this_task->message = data;
    if(this_task->listening==0) {
        END_CRITICAL();
        return;
    }
    this_task->status=NSHARING;
    while(this_task->status==NSHARING) {
        for(int i=0; i<this_task->listening; i++) {
            nTask listener = GetObj(this_task->waiting_msg_queue);
            if (listener->status==WAIT_NSHARE || listener->status==WAIT_NSHARE_TIMEOUT) {
                if(listener->status==WAIT_NSHARE_TIMEOUT) {
                    CancelTask(listener);
                }
                listener->status = READY;
                listener->message = this_task->message;
                PushTask(ready_queue, listener);
            }
        }
        ResumeNextReadyTask();
    }
    END_CRITICAL();
    return;
}

char *nRequest(nTask t, int timeout) {
    START_CRITICAL();
    nTask this_task = current_task;
    t->listening++;
    if(t->status==NSHARING) {
        END_CRITICAL();
        return t->message;
    }
    else {
        if(timeout>0) {
            this_task->status=WAIT_NSHARE_TIMEOUT;
            ProgramTask(timeout);
        }
        else {
            this_task->status=WAIT_NSHARE;
        }
        PushObj(t->waiting_msg_queue, this_task);
        ResumeNextReadyTask();
        END_CRITICAL();
        return this_task->message;
    }
}

void nRelease(nTask t) {
    START_CRITICAL();
    t->listening--;
    current_task->status = READY;
    if(t->listening==0) {
        t->status=READY;
        PushTask(ready_queue, t);
        PushTask(ready_queue, current_task);
        ResumeNextReadyTask();
    }
    END_CRITICAL();
    return;
}