INPUTS=("ls && echo 2"
"echo 1 && echo 2 && echo 3; echo 4"
"echo1&&echo2"
"echo 1"
"echo 1 || ls; ls; ls && echo ls"
"echo ls"
" echo git; ls git status"
"git status && ls"
"echo git status"
"ls -a"
"ls -a; echo hello; mkdir bashCreatedDirectory"
"rm -rf bashCreatedDirectory"
"ls -a; echo hello && mkdir bashCreatedDirectory || echo world; git status" "rm -rf bashCreatedDirectory"
"echo there is a comment in this line #here is my comment"
"ls -lR"
"ls -a; (pwd) && git status || echo nope"
"(pwd; ls -a && (mkdir tests || (echo mkdir failed)) && echo Looks good to me;)"
"test -e src/"
"test -f src/"
"test -d src/"
"(echo 1 && cd fakeDir; echo complete) || echo failed"
"(echo 1 && echo 2) || (echo 3 && echo 4)"
"(test -e src/ && test -f src/)"
"(((echo bottom) && echo middle) && echo top)",
"cat startFile | tee newFile1 && rm newFile1"
"((echo 1 && echo 2) | tee newFile2); cat newFile2 | tee newFile3; rm newFile2 newFile3"
"(test -e startFile && cat startFile) | tr a-z A-Z | tee bigFile ")


true="(True)\n"
false="(False)\n"
replacement=""

for ((i = 0; i < ${#INPUTS[@]}; i++))
do
    echo -e  "\nInput: ${INPUTS[$i]}"
    outputRShell=$(./rshell ${INPUTS[$i]})

    eval $(rm -rf bashCreatedDirectory)
    outputBash=$(eval ${INPUTS[$i]})
 
    #echo -e "RShell Output: \"${outputRShell}\""
    #echo -e "Bash Output: \"${outputBash}\""

    if [ "$(sed '/(True)\|(False)\|(FALSE)\|(TRUE)\|(true)\|(false)/d' <<< "$outputRShell")" = "$outputBash" ]; then
        echo equal
    else
        echo different
    fi

    if [ "$(sed '/(True)\|(False)\|(FALSE)\|(TRUE)\|(true)\|(false)/d' <<< "$outputRShell")" = "$outputBash" ]; then
	tput setaf 6;
	echo -e "Test passed"
    else
	tput setaf 1;
	echo -e "Test failed"
    fi
    tput sgr0;
done
