# minishell

- $?

- gerer les cas d'erreur NEM
>> Si tu trouves d'autres cas d'erreur pas encore gere dit moi

- gerer les leaks

- Maj SHLVL

- EXPORT
-> ecrit dans env quand "export var" et pas dans export alors que ca devrait etre le contraire
-> rajoute une var quand export VAR_QUI_EXISTE_DEJA alors que devrait rien faire

- double free + Permission denied quand y'a uniquement un dossier (ex : "includes/")

- double free + Exec format error quand on ecrit juste Makefile

- echo -n -n
-> qu'est ce qui va pas là dessus ?

- > bonjour echo hola devrait renvoyer hola

Garde la peche :
- e'c'"h"o hola > test devrait apparemment fonctionner aussi