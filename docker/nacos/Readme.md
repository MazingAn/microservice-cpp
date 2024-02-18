1.首次初始化： 
chmod +x init_nacos.sh
./init_nacos.sh

2.创建数据库
数据库名称 nacos_config
导入nacos_init.sql

3.创建docker镜像
docker-compose up -d

