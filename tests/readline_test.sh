#!/bin/bash

# Change to the directory containing the script
cd "$(dirname "$0")"

# Define the path to the minishell executable
MINISHELL_PATH="../minishell"

# Test Case 1: Empty input
echo "" | $MINISHELL_PATH
if [ $? -eq 0 ]; then
    echo "Test Case 1: Passed"
else
    echo "Test Case 1: Failed"
fi

# Test Case 2: Normal string input
echo "hello world" | $MINISHELL_PATH
if [ $? -eq 0 ]; then
    echo "Test Case 2: Passed"
else
    echo "Test Case 2: Failed"
fi

# Test Case 3: Special characters input
echo "echo \$HOME" | $MINISHELL_PATH
if [ $? -eq 0 ]; then
    echo "Test Case 3: Passed"
else
    echo "Test Case 3: Failed"
fi

# Test Case 4: Multiple commands
{
    echo "first command"
    echo "second command"
} | $MINISHELL_PATH
if [ $? -eq 0 ]; then
    echo "Test Case 4: Passed"
else
    echo "Test Case 4: Failed"
fi

# Test Case 5: Exit command
echo "exit" | $MINISHELL_PATH
if [ $? -eq 0 ]; then
    echo "Test Case 5: Passed"
else
    echo "Test Case 5: Failed"
fi

# Test Case 6: Input with only spaces
echo "     " | $MINISHELL_PATH
if [ $? -eq 0 ]; then
    echo "Test Case 6: Passed"
else
    echo "Test Case 6: Failed"
fi

# Test Case 7: Invalid command
echo "invalidcommand" | $MINISHELL_PATH
if [ $? -eq 127 ]; then
    echo "Test Case 7: Passed"
else
    echo "Test Case 7: Failed"
fi

# Test Case 8: Command with arguments
echo "ls -l /" | $MINISHELL_PATH
if [ $? -eq 0 ]; then
    echo "Test Case 8: Passed"
else
    echo "Test Case 8: Failed"
fi

# Test Case 9: Multiple lines input
{
    echo "echo first line"
    echo "echo second line"
} | $MINISHELL_PATH
if [ $? -eq 0 ]; then
    echo "Test Case 9: Passed"
else
    echo "Test Case 9: Failed"
fi

# Test Case 10: Special characters and spaces
echo "echo 'This is a test with special characters !@#$%^&*() and spaces'" | $MINISHELL_PATH
if [ $? -eq 0 ]; then
    echo "Test Case 10: Passed"
else
    echo "Test Case 10: Failed"
fi

# Test Case 11: Check for memory leaks (using valgrind if available)
if command -v valgrind &> /dev/null; then
    echo "hello world" | valgrind --leak-check=full $MINISHELL_PATH &> valgrind_output.txt
    if grep -q "no leaks are possible" valgrind_output.txt; then
        echo "Test Case 11: Passed"
    else
        echo "Test Case 11: Failed"
    fi
    rm valgrind_output.txt
else
    echo "Valgrind not installed. Skipping Test Case 11."
fi



# その時利用した コード
# void	recursive_readline(void)
# {
# 	char			*line;
# 	// t_token_lexer	lexer;
# 	// t_token			*l;

# 	rl_outstream = stderr;
# 	while (1)
# 	{
# 		line = readline(PROMPT);
# 		if (!line)
# 			break ;
# 		if (*line)
# 			add_history(line);
# 		free(line);
# 	}
# 	exit(0);
# }