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
	int size();

private:

	SDL_sem* semaphore;
	std::queue<T> _queue;
};

template<typename T>
CThreadQueue<T>::CThreadQueue() {

	semaphore = SDL_CreateSemaphore(1);
}


template<typename T>
CThreadQueue<T>::~CThreadQueue() {

	if (semaphore)
		SDL_DestroySemaphore(semaphore);
}

template<typename T>
void CThreadQueue<T>::push(T element) {	
	
	SDL_SemWait(semaphore);

	_queue.push(element);

	SDL_SemPost(semaphore);
}

template<typename T>
int CThreadQueue<T>::size() {

	int ret;
	SDL_SemWait(semaphore);

	ret = _queue.size();
	
	SDL_SemPost(semaphore);

	return ret;
}

template<typename T>
void CThreadQueue<T>::push(std::vector<T> vec) {

	SDL_SemWait(semaphore);

	while (!vec.empty()) {
		T element = vec[0];
		vec.erase(0);

		_queue.push(element);
	}

	SDL_SemPost(semaphore);
}

template<typename T>
bool CThreadQueue<T>::empty() {

	bool ret;
	SDL_SemWait(semaphore);

	ret = _queue.empty();
	
	SDL_SemPost(semaphore);

	return ret;


}

template<typename T>
T CThreadQueue<T>::pop() {

	SDL_SemWait(semaphore);

	T ret = _queue.front();
	_queue.pop();	

	SDL_SemPost(semaphore);

	return ret;
}
