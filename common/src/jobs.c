//
// Created by Frityet on 2022-01-13.
//

#include "jobs.h"

#include "common.h"

//local pthread_mutex_t jobcount_lock = PTHREAD_MUTEX_INITIALIZER;

#define ENUMERATE_JOBS(_name, _worker) for (struct job *(_name) = (_worker)->jobs; (_name)/*->next_job*/ != NULL; (_name) = (_name)->next_job)

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
    if (worker->jobs == NULL) {
        worker->jobs = create_job(worker, func, args, on_complete);
        return worker->jobs;
    }

    struct job *latest = NULL;


    ENUMERATE_JOBS(tmp, worker) {
        latest = tmp;
    }

    if (latest == NULL) {
    }
    latest->next_job = create_job(worker, func, args, on_complete);
    worker->job_count++;
    return latest->next_job;
}

struct worker *employ_worker(job_f              *func,
                             struct job_args    args,
                             job_complete_f     *job_complete,
                             work_complete_f    *work_complete)
{
    struct worker *worker = NEW(struct worker);

    worker->job_count           = 0;
    worker->jobs                = create_job(worker, func, args, job_complete);
    worker->job_count++;
    worker->on_work_complete    = work_complete;
    worker->running             = FALSE;
    worker->done                = FALSE;

    return worker;
}

void *worker_thread(struct worker *worker)
{
    while (!worker->done) {
        ENUMERATE_JOBS(job, worker) {
            job_f *func = job->function;
            func(&job->args);
            if (job->on_complete != NULL)
                job->on_complete(worker, job);
            remove_job(worker);
            free(job);
        }

        if (worker->on_work_complete != NULL)
            worker->on_work_complete(worker);
    }

    worker->running = FALSE;

    return NULL;
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


