#!/bin/bash
mkdir -p $PWD/nacos/{conf,log,env} #创建本地文件夹

#新建配置文件
tee $PWD/nacos/conf/application.properties <<-'EOF'
	# spring
	server.servlet.contextPath=${SERVER_SERVLET_CONTEXTPATH:/nacos}
	server.contextPath=/nacos
	server.port=${NACOS_APPLICATION_PORT:8848}
	server.tomcat.accesslog.max-days=30
	server.tomcat.accesslog.pattern=%h %l %u %t "%r" %s %b %D %{User-Agent}i %{Request-Source}i
	spring.datasource.platform=${SPRING_DATASOURCE_PLATFORM:""}
	spring.datasource.driver-class-name=org.mariadb.jdbc.Driver
	nacos.cmdb.dumpTaskInterval=3600
	nacos.cmdb.eventTaskInterval=10
	nacos.cmdb.labelTaskInterval=300
	nacos.cmdb.loadDataAtStart=false
	db.num=${MYSQL_DATABASE_NUM:1}
	db.url.0=jdbc:mariadb://${MYSQL_SERVICE_HOST}:${MYSQL_SERVICE_PORT:3306}/${MYSQL_SERVICE_DB_NAME:nacos_config}?${MYSQL_SERVICE_DB_PARAM:characterEncoding=utf8&connectTimeout=1000&socketTimeout=3000&autoReconnect=true&useSSL=false&serverTimezone=UTC}
	# db.url.1=jdbc:mysql://${MYSQL_SERVICE_HOST}:${MYSQL_SERVICE_PORT:3306}/${MYSQL_SERVICE_DB_NAME}?${MYSQL_SERVICE_DB_PARAM:characterEncoding=utf8&connectTimeout=1000&socketTimeout=3000&autoReconnect=true&useSSL=false}
	db.user=${MYSQL_SERVICE_USER}
	db.password=${MYSQL_SERVICE_PASSWORD}
	### The auth system to use, currently only 'nacos' and 'ldap' is supported:
	nacos.core.auth.system.type=${NACOS_AUTH_SYSTEM_TYPE:nacos}
	### worked when nacos.core.auth.system.type=nacos
	### The token expiration in seconds:
	nacos.core.auth.plugin.nacos.token.expire.seconds=${NACOS_AUTH_TOKEN_EXPIRE_SECONDS:18000}
	### The default token:
	nacos.core.auth.plugin.nacos.token.secret.key=${NACOS_AUTH_TOKEN:SecretKey012345678901234567890123456789012345678901234567890123456789}
	### Turn on/off caching of auth information. By turning on this switch, the update of auth information would have a 15 seconds delay.
	nacos.core.auth.caching.enabled=${NACOS_AUTH_CACHE_ENABLE:false}
	nacos.core.auth.enable.userAgentAuthWhite=${NACOS_AUTH_USER_AGENT_AUTH_WHITE_ENABLE:false}
	nacos.core.auth.server.identity.key=${NACOS_AUTH_IDENTITY_KEY:serverIdentity}
	nacos.core.auth.server.identity.value=${NACOS_AUTH_IDENTITY_VALUE:security}
	server.tomcat.accesslog.enabled=${TOMCAT_ACCESSLOG_ENABLED:false}
	# default current work dir
	server.tomcat.basedir=file:.
	## spring security config
	### turn off security
	nacos.security.ignore.urls=${NACOS_SECURITY_IGNORE_URLS:/,/error,/**/*.css,/**/*.js,/**/*.html,/**/*.map,/**/*.svg,/**/*.png,/**/*.ico,/console-fe/public/**,/v1/auth/**,/v1/console/health/**,/actuator/**,/v1/console/server/**}
	# metrics for elastic search
	management.metrics.export.elastic.enabled=false
	management.metrics.export.influx.enabled=false
	nacos.naming.distro.taskDispatchThreadCount=10
	nacos.naming.distro.taskDispatchPeriod=200
	nacos.naming.distro.batchSyncKeyCount=1000
	nacos.naming.distro.initDataRatio=0.9
	nacos.naming.distro.syncRetryDelay=5000
	nacos.naming.data.warmup=true
EOF

#新建环境配置
tee $PWD/nacos/env/nacos.env <<-'EOF'
	PREFER_HOST_MODE=hostname
	MODE=standalone  ##注意这里使用的是单机模式
	SPRING_DATASOURCE_PLATFORM=mariadb
	MYSQL_SERVICE_HOST=127.0.0.1
	MYSQL_SERVICE_DB_NAME=nacos_config
	MYSQL_SERVICE_PORT=3306
	MYSQL_SERVICE_USER=root
	MYSQL_SERVICE_PASSWORD=123456
	MYSQL_SERVICE_DB_PARAM=characterEncoding=utf8&connectTimeout=1000&socketTimeout=3000&autoReconnect=true&useSSL=false&serverTimezone=UTC
EOF
