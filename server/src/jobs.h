//
// Created by Frityet on 2022-01-13.
//

#ifndef UNIGS_JOBS_
#define UNIGS_JOBS_

#include <common.h>

#include <pthread.h>

#include <unigs_types.h>

struct worker;
struct job;

#define JOB_ARGS(...) (struct job_args) { .argc = VA_ARGS_COUNT(__VA_ARGS__), .argv = (void *[]){ __VA_ARGS__ } }
struct job_args {
    size_t  argc;
    void    **argv;
};

typedef void    job_f(struct job_args *args);
typedef void    job_complete_f(struct worker *worker, struct job *job);
typedef void    work_complete_f(struct worker *);

struct job {
    job_f           *function;
    struct worker   *worker;
    struct job_args args;
    size_t          id;
    job_complete_f  *on_complete;
    struct job      *next_job;
};


struct worker {
    pthread_t       thread;
    struct job      *jobs;
    atomic size_t   job_count;
    bool            running;
    work_complete_f *on_work_complete;
};


struct job *enumerate_jobs(struct worker *worker);
struct worker *employ_worker(job_f              *func,
                             struct job_args    args,
                             job_complete_f     *job_complete,
                             work_complete_f    *work_complete);
struct job *add_job(struct worker   *worker,
                    job_f           *func,
                    struct job_args args,
                    job_complete_f  *on_complete);
void run_worker(struct worker *worker);
static inline void wait_for_worker(struct worker *worker)
{
    if (!worker->running)
        return;
    pthread_join(worker->thread, NULL);
}
static inline void layoff_worker(struct worker *worker)
{
    wait_for_worker(worker);
    free(worker);
}

#endif //UNIGS_JOBS_
