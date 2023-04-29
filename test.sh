#!/bin/sh

curl http://localhost:8000/api/receiveMessage -d From=1 -d Body=hello
echo
curl http://localhost:8000/api/receiveMessage -d From=1 -d Body=player
echo
curl http://localhost:8000/api/receiveMessage -d From=2 -d Body=hello
echo
curl http://localhost:8000/api/receiveMessage -d From=2 -d Body=judge
echo
curl http://localhost:8000/api/receiveMessage -d From=2 -d "Body=Player A, what is your favorite color?"
echo


