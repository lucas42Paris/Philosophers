# Philosophers

🇫🇷

L'objectif du projet "Philosophers" est de se familiariser avec les concepts de __threading__, de __mutexes__ et de __mémoire partagée__ entre processus, en utilisant le langage C.

Le défi est de simuler un scénario où plusieurs philosophes sont assis autour d'une table, en alternant entre manger, dormir et penser.

Chaque philosophe a besoin de deux fourchettes pour manger, mais il y a autant de fourchettes que de philosophes.

L'objectif est de garantir que chaque philosophe puisse manger sans mourir de faim, tout en évitant les problèmes d'interblocage.

Les philosophes ne peuvent pas communiquer entre eux et la simulation prend fin si un philosophe meurt de faim ou si tous les philosophes ont mangé un certain nombre de fois.

<img src="/dining_philosophers_problem.png" width="500">

__Le programme prends plusieurs paramètres__ :

* `number_of_philosophers` : nombre de philosophes autour de la table.
* `time_to_die` : nombre en millisecondes représentant le temps qu'un philosophe doit vivre après un repas. Si un philosophe n'a pas commencé à manger time_to_die millisecondes après le début de son dernier repas, ou le début de la simulation, il mourra.
* `time_to_eat` : nombre en millisecondes représentant le temps qu'un philosophe met pour finir son repas. Pendant ce temps, le philosophe garde ses deux fourchettes à la main.
* `time_to_sleep` : temps en millisecondes qu'un philosophe passe à dormir.
* `number_of_times_each_philosopher_must_eat` (argument optionnel) : si tous les philosophes ont mangé au moins number_of_times_each_philosopher_must_eat fois, la simulation se termine. Si cet argument n'est pas spécifié, la simulation se termine à la mort d'un philosophe.

__À quoi ressemble l'output__ ?

La sortie du programme doit afficher l'état de chaque philosophe à chaque instant. Chaque message doit être affiché avec un timestamp en millisecondes. Le timestamp indique le temps écoulé depuis le lancement du programme.

`[timestamp_in_ms] [X] has taken a fork`  
`[timestamp_in_ms] [X] is eating`  
`[timestamp_in_ms] [X] is sleeping`  
`[timestamp_in_ms] [X] is thinking`  
`[timestamp_in_ms] [X] died`

__Comment tester le programme__ ?

* `make` à la racine.
* Les arguments du programme se présent comme ceci : `./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]`.
* Exemple : `./philo 5 800 200 200 5`. Dans cet exemple, il y a 5 philosophes. Un philosophe meurt s'il n'a pas commencé à manger 800 millisecondes après le début de son dernier repas ou depuis le début de la simulation. Il faut 200 millisecondes à un philosophe pour manger, et un philosophe dort pendant 200 millisecondes. Chaque philosophe doit manger 5 fois pour que la simulation se termine.
* Autre exemple : `./philo 5 8000 2000 2000`. Dans ce scénario, aucun philosophe ne meurt et la simulation continue indéfiniment. Pourquoi ? Parce que le temps total que chaque philosophe passe à manger et à dormir (time_to_eat + time_to_sleep) est égal à 4000 millisecondes, ce qui est inférieur au time_to_die de 8000 millisecondes. Cela signifie qu'avant qu'un philosophe ait une chance de mourir, il a déjà eu le temps de commencer un nouveau repas.

🇺🇸

The goal of the "Philosophers" project is to work with the concepts of __threading__, __mutexes__ and __shared memory__ between processes, using the C language.

The challenge is to simulate a scenario where several philosophers are seated around a table, alternating between eating, sleeping and thinking.

Each philosopher needs two forks to eat, but there are as many forks as there are philosophers.

The goal is to ensure that every philosopher can eat without starving, while avoiding deadlock issues.

The philosophers cannot communicate with each other and the simulation ends if a philosopher dies of hunger or if all the philosophers have eaten a certain number of times.

<img src="/dining_philosophers_problem.png" width="500">

__Parameters of the program__ :

* `number_of_philosophers`: number of philosophers around the table.
* `time_to_die`: number in milliseconds representing the time a philosopher must live after a meal. If a philosopher has not started eating time_to_die milliseconds after their last meal begins, or the simulation begins, they will die.
* `time_to_eat`: number in milliseconds representing the time a philosopher takes to finish his meal. During this time, the philosopher keeps his two forks in his hand.
* `time_to_sleep`: time in milliseconds a philosopher spends sleeping.
* `number_of_times_each_philosopher_must_eat` (optional argument): if all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation ends. If this argument is not specified, the simulation ends when a philosopher dies.

__What does the output look like__?

The output of the program should display the state of each philosopher at each instant. Each message should be displayed with a timestamp in milliseconds. The timestamp indicates the time elapsed since the launch of the program.

[timestamp_in_ms] [X] took a fork
[timestamp_in_ms] [X] eats
[timestamp_in_ms] [X] is sleeping
[timestamp_in_ms] [X] reflects
[timestamp_in_ms] [X] died

__How to test the program__?

* `make` in the philo repository.
* Program arguments look like this: `./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]`.
* Example: `./philo 5 800 200 200 5`. In this example, there are 5 philosophers. A philosopher dies if he has not started eating 800 milliseconds after the start of his last meal or since the start of the simulation. It takes 200 milliseconds for a philosopher to eat, and a philosopher sleeps for 200 milliseconds. Each philosopher must eat 5 times for the simulation to end.
* Another example: `./philo 5 8000 2000 2000`. In this scenario, no philosopher dies and the simulation continues indefinitely. For what ? Because the total time each philosopher spends eating and sleeping (time_to_eat + time_to_sleep) equals 4000 milliseconds, which is less than the time_to_die of 8000 milliseconds. This means that before a philosopher has a chance to die, he has already had time to start a new meal.

![Rating](rating.png)
