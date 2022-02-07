#pragma once

<<<<<<< HEAD
=======
#include <climits>
>>>>>>> Producer-Consumer
#include <mutex>
#include <condition_variable>

class CProcess {
 protected:
  std::mutex& access;
  std::condition_variable& condition;
  bool& ready;

 public:
  CProcess() = delete;
  CProcess(CProcess const&) = delete;
  CProcess(std::mutex& access_, std::condition_variable& condition_, bool& ready_)
    : access(access_),
      condition(condition_),
      ready(ready_) {
  }
};

class CProducer final : public CProcess {
 private:
  std::array<char, frame_size> & frame;

 public:
  CProducer() = delete;
  CProducer(CProducer const&) = delete;
  CProducer(std::mutex& access_, std::condition_variable& condition_, bool& ready_, std::array<char, frame_size> & frame_)
    : CProcess(access_, condition_, ready_),
      frame(frame_) {
  }

  void produce(std::chrono::seconds const duration) const {
    std::chrono::time_point<std::chrono::steady_clock> const finish{std::chrono::steady_clock::now() + duration};
    while (std::chrono::steady_clock::now() < finish) {
      /*while (ready)
        std::this_thread::sleep_for(std::chrono::seconds(1));*/
      std::unique_lock<std::mutex> locker(access);
      condition.wait_until(locker, finish, [&ready = ready] () -> bool { return !ready; });
      send_data();
      ready = !ready;
      locker.unlock();
      condition.notify_one();
    }
  }

 private:
  void send_data() const {
    std::chrono::time_point<std::chrono::steady_clock> const start{std::chrono::steady_clock::now()};
    char control_variable{0};
    for (auto& item : frame) {
      item = static_cast<char>(CHAR_MIN+rand()%UCHAR_MAX);
      control_variable^=item;
    }
    std::cout << "Written buffer signature:\t" << std::to_string(control_variable) << "\tDuration: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() << "\tms" << std::endl;
  }
};

class CConsumer final : public CProcess {
 private:
  std::array<char, frame_size> const& frame;

 public:
  CConsumer() = delete;
  CConsumer(CConsumer const&) = delete;
  CConsumer(std::mutex& access_, std::condition_variable& condition_, bool& ready_, std::array<char, frame_size> const& frame_)
    : CProcess(access_, condition_, ready_),
      frame(frame_) {
  }

  void consume(std::chrono::seconds const duration) const {
    std::chrono::time_point<std::chrono::steady_clock> const finish{std::chrono::steady_clock::now() + duration};
    while (std::chrono::steady_clock::now() < finish) {
      /*while (!ready)
        std::this_thread::sleep_for(std::chrono::seconds(1));*/
      std::unique_lock<std::mutex> locker(access);
      condition.wait_until(locker, finish, [&ready = ready] () -> bool { return ready; });
      get_data();
      ready = !ready;
      locker.unlock();
      condition.notify_one();
    }
  }

 private:
  void get_data() const {
    std::chrono::time_point<std::chrono::steady_clock> const start{std::chrono::steady_clock::now()};
    char control_variable{0};
    for (auto const& item : frame) {
      control_variable^=item;
    }
    std::cout << "Read buffer signature:\t\t" << std::to_string(control_variable) << "\tDuration: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() << "\tms" << std::endl;
  }
};
