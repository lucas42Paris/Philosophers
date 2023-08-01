# Philosophers

🇫🇷

L'objectif du projet "Philosophers" est de se familiariser avec les concepts de __threading__, de __mutexes__ et de __mémoire partagée__ entre processus, en utilisant le langage C.

Le défi est de simuler un scénario où plusieurs philosophes sont assis autour d'une table, en alternant entre manger, dormir et penser.

Chaque philosophe a besoin de deux fourchettes pour manger, mais il y a autant de fourchettes que de philosophes.

L'objectif est de garantir que chaque philosophe puisse manger sans mourir de faim, tout en évitant les problèmes d'interblocage.

Les philosophes ne peuvent pas communiquer entre eux et la simulation prend fin si un philosophe meurt de faim ou si tous les philosophes ont mangé un certain nombre de fois.

Le programme prends plusieurs paramètres :

* `number_of_philosophers` : le nombre de philosophes autour de la table.
* `time_to_die` : nombre en millisecondes représentant le temps qu'un philosophe doit vivre après un repas. Si un philosophe n'a pas commencé à manger time_to_die millisecondes après le début de son dernier repas, ou le début de la simulation, il mourra.
* `time_to_eat` : nombre en millisecondes représentant le temps qu'un philosophe met pour finir son repas. Pendant ce temps, le philosophe garde ses deux fourchettes à la main.
* `time_to_sleep` : temps en millisecondes qu'un philosophe passe à dormir.
* `number_of_times_each_philosopher_must_eat` (argument optionnel) : si tous les philosophes ont mangé au moins number_of_times_each_philosopher_must_eat fois, la simulation se termine. Si cet argument n'est pas spécifié, la simulation se termine à la mort d'un philosophe.

![Rating](rating.png)
