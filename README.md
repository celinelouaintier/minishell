# minishell

- Le $? est dans le env donc tu peux l'afficher faut juste le modifier la valeur (il ne s'affiche pas quand on fait env ou export tkt)
PS : J'ai peut etre casse la norm du parsing du env et du export au passage ^^
==> valeur modifiee ! Faut juste que ca renvoie les bonnes valeurs maintenant <3

- gerer les leaks

- Regler la petite erreur d'export

- !!!!!!!!!!! > bonjour echo hola devrait renvoyer hola !!!!!!!!!!!
==> pareil pour ca je pense : - revoir INPUT  : < includes/minishell.h cat 

Comportements chelous :
- "echo -nnnnn" ET "echo -n -nnn -nnnn" doivent rien renvoyer MAIS "echo -n-nnn -nnnn" doit renvoyer -n-nnn -nnnn
- bash-5.1$ echo -nnn -------------n
-------------nbash-5.1$
- echo $:$= | cat -e ==> $:$=$
