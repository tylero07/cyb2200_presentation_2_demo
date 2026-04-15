@@
type T;
identifier I;
@@
+ pthread_mutex_lock(&lock);
  T I = progressThroughIntersection();
  ...
+ pthread_mutex_unlock(&lock);
  drawRoad();