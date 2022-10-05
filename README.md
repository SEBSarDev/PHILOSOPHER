# PHILOSOPHER
A school 42 project to introduce multithreading.

In this problem we have to resolve the Dinning philosophers problem in language C, with the pthread group of function.

To use it :
```
$ make
$ ./philo number_of_philosoper time_before_die time_to_eat time_to_sleep [max_meal]
```
- number_of_philosopher is an integer which represents the philosopher present at dinner
- time_before_die is an integer which represents the time in milliseconds that pass without a philosopher dying if he does not take a meal before
- time_to_eat is an integer which represents the time in milliseconds that a philosopher take to eat
- time_to_sleep is an integer which represents the time in milliseconds that a philosopher take to sleep
- max_meal is an optionnal argument, it is an integer which represents the number of meal that the philosophers will take. If no philosopher died during this time, the program should stop when each philosophizer has finished the number of meals indicated
