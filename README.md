8.1. Changes to main
create_comand:

OLD: 

	if (!args) || !tokenize_args(cmd, args))
	{
		free_2d_array(args);
		free(cmd);
		return (NULL);
	}

NEW:

	if (!args)
		return (NULL);
	if (!tokenize_args(cmd, args))
	{
		free_2d_array(args);
		free(cmd);
		return (NULL);
	}

- avoids possible double frees

testerin 6. testi lagaa, jos extract arg palauttaa ft_strdup("") = "\0"
= echo ''

Testing in mnishell terminal: '' and "" also causes infinite loop


exec_path.c

OLD:
- didn't include check for '\0' and produced weird behaviour for '' and "" (path/to/cmd Is a directory)

NEW:
addition:
	if (*cmd == '\0')
		return (NULL);



in main.c we added check after tokenizer so we wont exec unintentionally

in lexer.c add_missing_spaces is fixed, not even sure what did the trick.

9.1.

Add_missing_spaces() has been split up to helper functions to meet Norm standars,
because of that created add_missing_spaces.c -file and appended it to Makefile srcs and to parser.h