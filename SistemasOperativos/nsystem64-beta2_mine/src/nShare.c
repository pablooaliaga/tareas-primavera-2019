#include "fifoqueues.h"
#include "nSysimp.h"
//Possible change this to nsystem
#include "nSystem.h"

/*
 * Function: nShare 
 * 
 * 
 */
void nShare(char *data){
    START_CRITICAL();
    nTask this_task = current_task;
    if(this_task->n_request == 0){
        //Esto es importante, soltar el critical en este return.
        END_CRITICAL();
        return;
    }
    this_task->share_msg = data;
    this_task->status = WAIT_RELEASE;
    while(!EmptyFifoQueue(this_task->share_queue)){
        nTask new_task = (nTask) GetObj(this_task->share_queue);
        
        if(new_task->status == WAIT_SHARE || new_task->status == WAIT_SHARE_TIMEOUT){
            if(new_task->status == WAIT_SHARE_TIMEOUT){
                CancelTask(new_task);
            }
            new_task->share_msg = data;
            new_task->status = READY;
            
            PushTask(ready_queue, new_task);
        }
    }
    ResumeNextReadyTask();  
    END_CRITICAL();
    return;
}

/*
 * Function: nRequest
 * 
 * 
 */
char* nRequest(nTask t, int timeout){
    char* msg;
    START_CRITICAL();
    //Caso en que el mensaje esta listo para llevarselo
    t->n_request = t->n_request + 1;
    if(t->status == WAIT_RELEASE){
        msg = t->share_msg;
    }
    else{
        nTask this_task = current_task;
        //set share msg to NULL
        this_task->share_msg = 0;
        if(timeout > 0){
            this_task->status = WAIT_SHARE_TIMEOUT;
            ProgramTask(timeout);
        }
        else{
            this_task->status = WAIT_SHARE;
        }
        PutObj(t->share_queue, (void *)this_task);
        ResumeNextReadyTask();
        //Si me despertaron y fue timeout sera NULL sino sera el message real
        msg = this_task->share_msg;
    }
    END_CRITICAL();
    return msg;
}

/*
 * Function: nRelease
 * 
 * 
 */
void nRelease(nTask t){
    START_CRITICAL();   
    t->n_request = t->n_request - 1;
    if(t->n_request == 0){
        //Despertar al que comparte
        t->status = READY;
        PushTask(ready_queue, t);
    }
    END_CRITICAL();
    return;
}