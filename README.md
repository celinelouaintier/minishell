# minishell

- Dans le parsing, il faudrait arriver a remettre automatiquement le prompt a la ligne.
Lorsque l'on cat un doc ou qu'on fait echo -n, le prompt apparait apres sur la meme ligne.

- Refaire le parsing

- Le pipe ne fonctionne qu'avec des commandes sans argument et fait un truc chelou avec le readline

- Je crois que j'ai trouve le prblm dans le process_pipes mais trop fatiguee pour le regler :
On boucle sur token donc le premier token est seulement ls dans le cas de ls -la alors qu'apres on verifie si le prochain token est un pipe ce qui n'est pas le cas pour ls (puisque c'est -la) et on fork qund meme.

- Faire le Ctrl + D  && Ctrl + /
