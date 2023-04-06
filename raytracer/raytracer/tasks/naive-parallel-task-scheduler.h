#pragma once

#include "tasks/task-scheduler.h"


namespace tasks
{
    namespace schedulers
    {
        /// <summary>
        /// Creating Naive parallel task scheduler
        /// </summary>
        TaskScheduler naive_parallel();
    }
}