#!/bin/sh

p=$((1 + $RANDOM % 1000))
j=$((1 + $RANDOM % 1000))

curl http://localhost:8000/api/receiveMessage -d From=$p -d "Body=hello"
echo
curl http://localhost:8000/api/receiveMessage -d From=$p -d "Body=player"
echo
curl http://localhost:8000/api/receiveMessage -d From=$j -d "Body=hello"
echo
curl http://localhost:8000/api/receiveMessage -d From=$j -d "Body=judge"
echo
curl http://localhost:8000/api/receiveMessage -d From=$j -d "Body=Player A, what is your favorite color?"
echo
curl http://localhost:8000/api/receiveMessage -d From=$j -d "Body=Player B, what is your favorite color?"
echo
curl http://localhost:8000/api/receiveMessage -d From=$p -d "Body=blue"
echo

