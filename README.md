# minishell

- gerer les leaks
==> elucider les still reachable ?
- tester valgrind avec export
- getcwd leak ? (env | grep PWD)
- "Conditional jump or move depends on uninitialised value(s)" sur tous les while (tmp)

- Regler la petite erreur d'export

- Faire une redirection dans un DOSSIER ferme le shell au lieu de juste print une erreur (ex : echo tg > includes)