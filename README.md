# Challenge

## Basic Structure

Build a simple producer consumer scenario in C++. For the sake of simplicity the 
scenario shall run on linux, and standard C++ can be used. Your solution should
consist out of two independent modules each running in their own thread.

(1) A producer module which gathers data 

(2) A consumer module which receives data to send it away

The two modules need to communicate and the data transformed is expected 
to be big ~16MB per step. Depending on the configuration of the system 
data shall be processed between 10 and 1000 times per second.

Consider your code to be part of a larger system and one you are tasked to 
implement two stages of the system - a producer that talks to a piece of 
hardware to grab video images audio buffers, hardware I/O or network packets
and a consumer that could apply some sort of data transformation / aggregation
or filtering prior to passing the data on. To keep the challenge short
the domain specific aspects are left out.

## Requirements 

1. **Independent.** The two modues run in seperate threads and should be
able to run in parallel. I.e while the producer is already preparing 
the data for step N+2 or N+1 the consumer is operating on step N.

2. **Decoupled.** The two modules should be capable of running in different 
speeds at least temporarily. If the consumer occasionally take more time
to process and send off data the producer shall be able to continue.

3. **C++.** Use standard C++ and Linux facilities.

4. **Reasonable performance.** Avoid unncessary inefficiencies in data
transfer processing or inter thread communication, to leave CPU resources 

5. **Constant frame size.** You can assume the frame size is a compile 
time constant.

6. **I/O**
Assume the following interface exists:
```
constexpr size_t frame_size = 16 * 1024 * 1024;
void             get_data(std::span<char, frame_size> const& output);
void             send_data(std::span<const char, frame_size> const& output);
```

The producer shall call `get_data` to get the next data set and the consumer
shall call `send_data` to finish.

## Deliverables:

1. Working code for the communication components

2. Code that sets up the two modules and runs them for at least 10 seconds and then
shuts down. You can provide stub implementations of `get_data` and `send_data` to make
your tests easier or leave them empty. 

3. A description of your choices. What did you use and why? How did performance
considerations affect your design decisions? What alternatives did you consider?

