#include <thread>
#include <atomic>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

class ThreadManager
{
public:
    void Initialize(std::function<void()>PhysicThread , std::function<void()> RenderThread , std::function<void()> GameThread) {
        std::thread RT(RenderThread);
        std::thread PH(PhysicThread);
        std::thread GT(GameThread);
    }

    


private:




};
