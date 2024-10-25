# minishell

--> Il reste l'env ou les expands (qui est un peu du parsing en vrai)

- Minishell> ls -la > test
ls: cannot access '>': No such file or directory => prblm parsing je pense

- retirer espace apres quand un seul ARG a echo

- ft_exit() doit renvoyer le nombre correspondant a la facon d'exit (checker comportement)

- changer PWD et OLDPWD dans l'env quand on cd

- Probleme pour enchainer les > et les |

- exit() ne sort plus du shell

- Redirections fonctionnent qu'avec builtins ? (cree le fichier mais n'arrive pas a ecrire dedans)

- cd fcontionne plus => fonctionne mais toujours rien ne s'ecrit sur l'env

- executer les commandes avec chemin relatif