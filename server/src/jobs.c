//
// Created by Frityet on 2022-01-13.
//

#include "jobs.h"

#include <common.h>

#include <assert.h>

//local pthread_mutex_t jobcount_lock = PTHREAD_MUTEX_INITIALIZER;

local struct job *latest_job(struct worker *worker)
{
    struct job *job = NULL, *tmp = NULL;
    while ((tmp = enumerate_jobs(worker)))
        job = tmp;
    return job;
}

local struct job *create_job(struct worker      *worker,
                             job_f              *func,
                             struct job_args    args,
                             job_complete_f     *on_complete)
{
    struct job *job = NEW(struct job);
    {
        job->function       = func;
        job->args.argc      = args.argc;
        job->args.argv      = args.argv;
        job->on_complete    = on_complete;
        job->id             = worker->job_count + 1;
        job->worker         = worker;
        job->next_job       = NULL;
    }
    return job;
}

local void remove_job(struct worker *worker)
{
    struct job *job = worker->jobs;
    worker->jobs = job->next_job;
    worker->job_count--;
}

struct job *add_job(struct worker   *worker,
                    job_f           *func,
                    struct job_args args,
                    job_complete_f  *on_complete)
{
    struct job *latest  = latest_job(worker);

    latest->next_job    = create_job(worker, func, args, on_complete);
    worker->job_count++;
    return latest->next_job;
}

struct job *enumerate_jobs(struct worker *worker)
{
    static size_t index = 0;

    struct job *current_job = worker->jobs;
    for (size_t i = 0; i < index; ++i) {
        current_job = current_job->next_job;
    }
    index++;

    if (index == worker->job_count) {
        index = 0;
        return NULL;
    }

    return current_job;
}

struct worker *employ_worker(job_f              *func,
                             struct job_args    args,
                             job_complete_f     *job_complete,
                             work_complete_f    *work_complete)
{
    struct worker *worker = NEW(struct worker);

    worker->job_count           = 1;
    worker->jobs                = create_job(worker, func, args, job_complete);
    worker->on_work_complete    = work_complete;
    worker->running             = FALSE;

    return worker;
}

void worker_thread(struct worker *worker)
{
    struct job *job = NULL;
    while((job = enumerate_jobs(worker))) {
        job->function(&job->args);
        if (job->on_complete != NULL)
            job->on_complete(worker, job);
        remove_job(worker);
        free(job);
    }

    if (worker->on_work_complete != NULL)
        worker->on_work_complete(worker);

    worker->running = FALSE;
}

void run_worker(struct worker *worker)
{
    if (pthread_create(&worker->thread, NULL, (void *(*)(void *)) worker_thread, worker) != 0) {
        fprintf(stderr, "Could not create thread!\n"
                        "Reason: %s", strerror(errno));
        pthread_exit(NULL);
    }
    worker->running = TRUE;
}


