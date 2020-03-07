#include <iostream>
#include <random>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */

/*Task FP.3 : Define a class MessageQueue which has the public methods send and receive. 
Send should take an rvalue reference of type TrafficLightPhase whereas receive should return this type. 
Also, the class should define an std::dequeue called _queue, which stores objects of type TrafficLightPhase. 
Finally, there should be an std::condition_variable as well as an std::mutex as private members.*/

template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
    std::lock_guard<std::mutex> lockGuard(_mutex);
    _queue.emplace_back(std::move(msg));
    _condition.notify_one();
}


/* Implementation of class "TrafficLight" */

 
TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    //DONE: FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class. 
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds. 
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles. 
    
    std::default_random_engine randomEngine;
    std::uniform_real_distribution<double> distribution(4.0, 6.0);
    double cycleDuration = distribution(randomEngine);

    std::chrono::time_point<std::chrono::system_clock> originalTimePoint;

    originalTimePoint = std::chrono::system_clock::now();

    while (true){
        //sleep between cycles
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        //check the elapsed time
        long elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - originalTimePoint).count();

        //if elapsed time is longer or equal to one cycle, traffic light changes state
        if (elapsedTime>=cycleDuration){
            if (_currentPhase == TrafficLightPhase::red){
                _currentPhase = TrafficLightPhase::green;
            }
            else{
                _currentPhase = TrafficLightPhase::red;
            }
        }
    }

}

