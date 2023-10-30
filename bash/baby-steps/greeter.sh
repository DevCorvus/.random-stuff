#! /bin/bash

function greet()
{
  echo "Hi $1, you're welcome!"
}

greet $1 # This is the first argument in the command line
