docker rm test
docker rmi ubuntu
docker build -t ubuntu .
docker run -p 80:80 --name test -ti ubuntu