# minishell

- $?

- gerer les leaks

- Regler la petite erreur d'export

- !!!!!!!!!!! > bonjour echo hola devrait renvoyer hola !!!!!!!!!!!
==> pareil pour ca je pense : - revoir INPUT  : < includes/minishell.h cat 

Garde la peche :
- e'c'"h"o hola > test devrait apparemment fonctionner aussi

Comportements chelous :
- "echo -nnnnn" ET "echo -n -nnn -nnnn" doivent rien renvoyer MAIS "echo -n-nnn -nnnn" doit renvoyer -n-nnn -nnnn
- bash-5.1$ echo -nnn -------------n
-------------nbash-5.1$
- echo $:$= | cat -e ==> $:$=$