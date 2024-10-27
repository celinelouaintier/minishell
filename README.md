# minishell

--> Il reste l'env

- ft_exit() doit renvoyer le nombre correspondant a la facon d'exit (checker comportement)

- changer PWD et OLDPWD dans l'env quand on cd

- Probleme pour enchainer les > et les |

- exit() ne sort plus du shell
>> Si ?

- Redirections fonctionnent qu'avec builtins ? (cree le fichier mais n'arrive pas a ecrire dedans)
>> Normalement c'est réglé, je laisse prcq j'ai pas fait bcp de tests

- cd fcontionne plus => fonctionne mais toujours rien ne s'ecrit sur l'env

- cd fonctionne pas avec des chemins absolu

- executer les commandes avec chemin relatif

- $?
