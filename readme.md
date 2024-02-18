## Initialize project

The project use maria_db and rabbit_mq, we start them in docker.

### Initialize maria_db
delete the `mariadb` folder and re_init the mariadb, then start it, the init.sql will be executed;
`cd docker/mariadb`
`sudo rm -rf mariadb`
`./mysql_init.sh`
`docker-compose up -d`


### Initialize rabbit_mq
`cd docker/rabbitmq`
`docker-compose up -d`


## Download and build third parts

### restclient-cpp 

1. clone the project :
`git clone https://github.com/mrtazz/restclient-cpp ~/Public/restclient-cpp/`

2. build the restclient lib 
`cd ~/Public/restclient-cpp`
`mkdir build`
`cd build`
`cmake ..`
`make`

3. copy the lib file to project lib dir
`cp librestclient-cpp.so* {project_dir}/lib`


### mariadb-cpp-client
the same as restclient-cpp

`git clone https://github.com/mariadb-corporation/mariadb-connector-cpp ~/Public/mariadb-connector-cpp`
`cd ~/Public/mariadb-connector-cpp`
`mkdir build`
`cd build`
`cmake ..`
`make`
`cp libmariadbcpp.so libmariadbcpp-static.a {project_dir}/microservice-cpp/lib/`


### rabbitmq-c
`git clone https://github.com/alanxz/rabbitmq-c ~/Public/rabbitmq-c`
`cd ~/Public/rabbitmq-c`
`mkdir build`
`cd build`
`cmake ..`
`make`
`cp librabbitmq/librabbitmq.so* librabbitmq/librabbitmq.a {project_dir}/lib/`
