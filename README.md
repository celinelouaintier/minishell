# minishell

- gerer les leaks
==> trouver des leaks

- Regler la petite erreur d'export

- Faire une redirection dans un DOSSIER ferme le shell au lieu de juste print une erreur (ex : echo tg > includes)
=> semi réglé, faire la même chose que TRUNC pour les autres + s'occuper du handle_redirection dans les enfants.


104 alias vmini="make && clear && valgrind \
105 --trace-children=yes \
106 --leak-check=full \
107 --show-leak-kinds=definite \
108 --track-origins=yes \
109 --suppressions=valgrind.supp \
110 ./minishell"