#include "tasks/naive-parallel-task-scheduler.h"
#include "easylogging++.h"

using namespace tasks;


namespace
{
    class NaiveParallelTaskScheduler : public tasks::schedulers::_private_::TaskSchedulerImplementation
    {
    public:
		void perform(std::vector<std::shared_ptr<Task>> tasks) const
		{
			static std::mutex mtx;
			std::vector<std::thread> threads;
			unsigned int num_threads = std::thread::hardware_concurrency();

			for (unsigned i = 0; i < num_threads; i++)
			{
				threads.push_back(std::thread(&NaiveParallelTaskScheduler::execute, &tasks, &mtx));
			}

			for (auto& t : threads)
			{
				t.join();
			}

		}

		static void* execute(std::vector<std::shared_ptr<Task>>* tasks, std::mutex* mtx)
		{
			if (tasks->size() > 0)
			{
				mtx->lock();
				auto task = tasks->back();
				tasks->pop_back();
				mtx->unlock();
				task->perform();
				execute(tasks, mtx);
			}
			return 0;
		}
    };
}

TaskScheduler tasks::schedulers::naive_parallel()
{
    LOG(INFO) << "Creating naive parallel scheduler";

    return TaskScheduler(std::make_shared<NaiveParallelTaskScheduler>());
}
