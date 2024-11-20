# minishell
- dev/stdout
- $? quand tu exit sans rien doit renvoyer le dernier status et pas 0

==9626== 54 bytes in 1 blocks are definitely lost in loss record 19 of 67
==9626==    at 0x484DCD3: realloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==9626==    by 0x49CC7BC: getcwd (getcwd.c:86)
==9626==    by 0x10B19C: exec_builtin (builtin.c:30)
==9626==    by 0x109768: do_exec (main.c:86)
==9626==    by 0x10989F: main (main.c:122)