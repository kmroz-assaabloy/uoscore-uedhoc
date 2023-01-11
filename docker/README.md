Docker test environment
===
How to run tests in docker:
```
cd uoscore-uedhoc 
# we need to do it only once
docker build -f docker/Dockerfile_environment -t environment .
# build and run tests inside the environment 
docker build -f docker/Dockerfile_posix_tests -t posix_test .
docker run posix_test
```