# minishell

- gerer les leaks
==> trouver des leaks

104 alias vmini="make && clear && valgrind \
105 --trace-children=yes \
106 --leak-check=full \
107 --show-leak-kinds=definite \
108 --track-origins=yes \
109 --suppressions=valgrind.supp \
110 ./minishell"