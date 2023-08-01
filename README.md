# Philosophers

🇫🇷

L'objectif du projet "Philosophers" est de se familiariser avec les concepts de __threading__, de __mutexes__ et de __mémoire partagée__ entre processus, en utilisant le langage C.

Le défi est de simuler un scénario où plusieurs philosophes sont assis autour d'une table, en alternant entre manger, dormir et penser.

Chaque philosophe a besoin de deux fourchettes pour manger, mais il y a autant de fourchettes que de philosophes.

L'objectif est de garantir que chaque philosophe puisse manger sans mourir de faim, tout en évitant les problèmes d'interblocage.

Les philosophes ne peuvent pas communiquer entre eux et la simulation prend fin si un philosophe meurt de faim ou si tous les philosophes ont mangé un certain nombre de fois.

Le programme prends plusieurs paramètres :

* `number_of_philosophers` : nombre de philosophes autour de la table.
* `time_to_die` : nombre en millisecondes représentant le temps qu'un philosophe doit vivre après un repas. Si un philosophe n'a pas commencé à manger time_to_die millisecondes après le début de son dernier repas, ou le début de la simulation, il mourra.
* `time_to_eat` : nombre en millisecondes représentant le temps qu'un philosophe met pour finir son repas. Pendant ce temps, le philosophe garde ses deux fourchettes à la main.
* `time_to_sleep` : temps en millisecondes qu'un philosophe passe à dormir.
* `number_of_times_each_philosopher_must_eat` (argument optionnel) : si tous les philosophes ont mangé au moins number_of_times_each_philosopher_must_eat fois, la simulation se termine. Si cet argument n'est pas spécifié, la simulation se termine à la mort d'un philosophe.

__À quoi ressemble l'output__ ?

La sortie du programme doit afficher l'état de chaque philosophe à chaque instant. Chaque message doit être affiché avec un timestamp en millisecondes. Le timestamp indique le temps écoulé depuis le lancement du programme.

[timestamp_in_ms] [X] has taken a fork
[timestamp_in_ms] [X] is eating
[timestamp_in_ms] [X] is sleeping
[timestamp_in_ms] [X] is thinking
[timestamp_in_ms] [X] died

__Comment tester le programme__ ?

* `make` à la racine.
* Les arguments du programme se présent comme ceci : `./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]`.
* Exemple : `./philo 5 800 200 200 5`. Dans cet exemple, il y a 5 philosophes. Un philosophe meurt s'il n'a pas commencé à manger 800 millisecondes après le début de son dernier repas ou depuis le début de la simulation. Il faut 200 millisecondes à un philosophe pour manger, et un philosophe dort pendant 200 millisecondes. Chaque philosophe doit manger 5 fois pour que la simulation se termine.
* Autre exemple : `./philo 5 8000 2000 2000`. Dans ce scénario, aucun philosophe ne meurt et la simulation continue indéfiniment. Pourquoi ? Parce que le temps total que chaque philosophe passe à manger et à dormir (time_to_eat + time_to_sleep) est égal à 4000 millisecondes, ce qui est inférieur au time_to_die de 8000 millisecondes. Cela signifie qu'avant qu'un philosophe ait une chance de mourir, il a déjà eu le temps de commencer un nouveau repas.

![Rating](rating.png)
