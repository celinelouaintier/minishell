# minishell

--> Il reste l'env ou les expands (qui est un peu du parsing en vrai)

- Minishell> ls -la > test
ls: cannot access '>': No such file or directory => prblm parsing je pense

- retirer espace apres quand un seul ARG a echo
>> Résolue (I guess ?)

- pipes fonctionnent pas avec les builtins

- ft_exit() doit renvoyer le nombre correspondant a la facon d'exit (checker comportement)

- changer PWD et OLDPWD dans l'env quand on cd

- CTRL C trop de prompts / CTRL \ doit arreter la cmd
>> SIG_DFL dans les child pour Ctrl + \ et Ctrl + C
