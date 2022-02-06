#include <iostream>
#include <thread>
#include <climits>

constexpr size_t frame_size = 16 * 1024 * 1024;
std::array<char, frame_size> frame;

#include <ProducerConsumer.hpp>

int main(int argc, char* argv[]) {
  std::mutex frame_access;
  std::condition_variable wait_condition;
  bool frame_ready{false};
  CProducer const Producer(frame_access, wait_condition, frame_ready, frame);
  CConsumer const Consumer(frame_access, wait_condition, frame_ready, frame);

  using namespace std::literals;
  std::thread ProducerThread(&CProducer::produce, &Producer, 10s),
              ConsumerThread(&CConsumer::consume, &Consumer, 10s);

  ProducerThread.join();
  ConsumerThread.join();

  return EXIT_SUCCESS;
}
