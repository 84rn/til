#pragma once
#include <queue>
#include <vector>
#include "SDL/SDL.h"

template<typename T>
class CThreadQueue {
public:
	CThreadQueue();
	~CThreadQueue();

	void push(T);
	T pop();
	void push(std::vector<T>);
	bool empty();

private:
	void start();
	void stop();

	SDL_mutex* mutex;
	std::queue<T> _queue;
};

template<typename T>
CThreadQueue<T>::CThreadQueue() {

	mutex = SDL_CreateMutex();
}


template<typename T>
CThreadQueue<T>::~CThreadQueue() {

	if (mutex)
		SDL_DestroyMutex(mutex);
}

template<typename T>
void CThreadQueue<T>::push(T element) {

	start();

	_queue.push(element);

	stop();
}

template<typename T>
void CThreadQueue<T>::push(std::vector<T> vec) {

	start();

	while (!vec.empty()) {
		T element = vec[0];
		vec.erase(0);

		_queue.push(element);
	}

	stop();
}

template<typename T>
T CThreadQueue<T>::pop() {

	start();

	T ret = _queue.front();
	_queue.pop();

	stop();

	return T;
}

template<typename T>
void CThreadQueue<T>::start() {

	while (SDL_LockMutex(mutex) != 0) {
		SDL_Delay(10);
	}
}

template<typename T>
void CThreadQueue<T>::stop() {

	SDL_UnlockMutex(mutex);
}

