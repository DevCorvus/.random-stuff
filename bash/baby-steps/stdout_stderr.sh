#! /bin/bash

ls 1> ls.txt 2> errors.txt
ls -123 1> ls.txt 2> errors.txt
ls -123 > ls_and_errors 2>&1
ls -123 >& ls_any
