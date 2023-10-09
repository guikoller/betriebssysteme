// Praktikum p5  Semaphor-Bibliothek mittels pthreads
// Datei semtest.cpp

#include <pthread.h>
#include <iostream>
#include "semaphor.h"
#include <unistd.h>

using namespace std;

void* kritisch(void* sem) {
  Semaphor* s = (Semaphor*)sem;
  cout << "Thread " << (unsigned)pthread_self() << " versucht kritischen Programmteil zu betreten." << endl;
  s->P();
  cout << "Thread " << (unsigned)pthread_self() << ": Im kritischen Programmteil" << endl;
  sleep(4);
  s->V();
  cout << "Thread " << (unsigned)pthread_self() << " hat kritischen Programmteil verlassen." << endl;
  return NULL;
}

int main() {
    Semaphor sem(2);
    pthread_t tid1, tid2, tid3, tid4;
    
    pthread_create(&tid1, NULL, kritisch, (void*) &sem);
    pthread_create(&tid2, NULL, kritisch, (void*) &sem);
    pthread_create(&tid3, NULL, kritisch, (void*) &sem);
    pthread_create(&tid4, NULL, kritisch, (void*) &sem);
    
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);
    pthread_join(tid4,NULL);
 
    return 0;
}

