# minishell

- $?

- gerer les leaks

- Regler la petite erreur d'export
==> doit pouvoir exporter plusieurs variables sur la meme ligne et unset aussi : "Minishell> export test=test coucou=coucou" = export test="test" ET export coucou="coucou"

- LES COMMANDES FONCTIONNENT QUAND ON UNSET PATH ????

- !!!!!!!!!!! > bonjour echo hola devrait renvoyer hola !!!!!!!!!!!
==> pareil pour ca je pense : - revoir INPUT  : < includes/minishell.h cat 

Comportements chelous :
- "echo -nnnnn" ET "echo -n -nnn -nnnn" doivent rien renvoyer MAIS "echo -n-nnn -nnnn" doit renvoyer -n-nnn -nnnn
- bash-5.1$ echo -nnn -------------n
-------------nbash-5.1$
- echo $:$= | cat -e ==> $:$=$