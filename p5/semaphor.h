// Praktikum p5  Semaphor-Bibliothek mittels pthreads
// Datei semaphore.pp

class Semaphor {
  unsigned sem_val;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
public:
  Semaphor(unsigned init);
  ~Semaphor();
  void P(void);
  void V(void);
};


