# minishell
- dev/stdout
- $? quand tu exit sans rien doit renvoyer le dernier status et pas 0

==1944160== 32 bytes in 1 blocks are still reachable in loss record 15 of 66
==1944160==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1944160==    by 0x401E70: lstnew (set_token.c:21)
==1944160==    by 0x401BDD: set_index (parsing.c:94)
==1944160==    by 0x401D33: parsing (parsing.c:119)
==1944160==    by 0x401564: do_exec (main.c:79)
==1944160==    by 0x4016DE: main (main.c:120)

==1944160== 5 bytes in 1 blocks are still reachable in loss record 2 of 66
==1944160==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1944160==    by 0x403F02: addback (parsing_utils2.c:21)
==1944160==    by 0x401872: strarg (parsing.c:38)
==1944160==    by 0x401B90: set_index (parsing.c:89)
==1944160==    by 0x401D33: parsing (parsing.c:119)
==1944160==    by 0x401564: do_exec (main.c:79)
==1944160==    by 0x4016DE: main (main.c:120)