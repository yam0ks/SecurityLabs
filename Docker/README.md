## Выполним запуск контейнеров

```
docker-compose up -d --build
```

## Просканируем контейнеры при помощи утилиты docker_bench_security

```
docker run -it --net host --pid host --cap-add audit_control \
-e DOCKER_CONTENT_TRUST=$DOCKER_CONTENT_TRUST \
-v /var/lib:/var/lib \
-v /var/run/docker.sock:/var/run/docker.sock \
-v /etc:/etc --label docker_bench_security \
docker/docker-bench-security
```

## Отчет, полученный в результате сканирования

```
[INFO] 5 - Container Runtime
[WARN] 5.1  - Ensure AppArmor Profile is Enabled
[WARN]      * No AppArmorProfile Found: nginx_c
[WARN]      * No AppArmorProfile Found: db
[WARN] 5.2  - Ensure SELinux security options are set, if applicable
[WARN]      * No SecurityOptions Found: nginx_c
[WARN]      * No SecurityOptions Found: db
[PASS] 5.3  - Ensure Linux Kernel Capabilities are restricted within containers
[PASS] 5.4  - Ensure privileged containers are not used
[PASS] 5.5  - Ensure sensitive host system directories are not mounted on containers
[PASS] 5.6  - Ensure ssh is not run within containers
[WARN] 5.7  - Ensure privileged ports are not mapped within containers
[WARN]      * Privileged Port in use: 80 in nginx_c
[NOTE] 5.8  - Ensure only needed ports are open on the container
[PASS] 5.9  - Ensure the host's network namespace is not shared
[WARN] 5.10  - Ensure memory usage for container is limited
[WARN]      * Container running without memory restrictions: nginx_c
[WARN]      * Container running without memory restrictions: db
[WARN] 5.11  - Ensure CPU priority is set appropriately on the container
[WARN]      * Container running without CPU restrictions: nginx_c
[WARN]      * Container running without CPU restrictions: db
[WARN] 5.12  - Ensure the container's root filesystem is mounted as read only
[WARN]      * Container running with root FS mounted R/W: nginx_c
[WARN]      * Container running with root FS mounted R/W: db
[WARN] 5.13  - Ensure incoming container traffic is binded to a specific host interface
[WARN]      * Port being bound to wildcard IP: 0.0.0.0 in nginx_c
[WARN]      * Port being bound to wildcard IP: 0.0.0.0 in db
[WARN] 5.14  - Ensure 'on-failure' container restart policy is set to '5'
[WARN]      * MaximumRetryCount is not set to 5: nginx_c
[WARN]      * MaximumRetryCount is not set to 5: db
[PASS] 5.15  - Ensure the host's process namespace is not shared
[PASS] 5.16  - Ensure the host's IPC namespace is not shared
[PASS] 5.17  - Ensure host devices are not directly exposed to containers
[INFO] 5.18  - Ensure the default ulimit is overwritten at runtime, only if needed
[INFO]      * Container no default ulimit override: nginx_c
[INFO]      * Container no default ulimit override: db
[PASS] 5.19  - Ensure mount propagation mode is not set to shared
[PASS] 5.20  - Ensure the host's UTS namespace is not shared
[PASS] 5.21  - Ensure the default seccomp profile is not Disabled
[NOTE] 5.22  - Ensure docker exec commands are not used with privileged option
[NOTE] 5.23  - Ensure docker exec commands are not used with user option
[PASS] 5.24  - Ensure cgroup usage is confirmed
[WARN] 5.25  - Ensure the container is restricted from acquiring additional privileges
[WARN]      * Privileges not restricted: nginx_c
[WARN]      * Privileges not restricted: db
[WARN] 5.26  - Ensure container health is checked at runtime
[WARN]      * Health check not set: nginx_c
[WARN]      * Health check not set: db
[INFO] 5.27  - Ensure docker commands always get the latest version of the image
[WARN] 5.28  - Ensure PIDs cgroup limit is used
[WARN]      * PIDs limit not set: nginx_c
[WARN]      * PIDs limit not set: db
[PASS] 5.29  - Ensure Docker's default bridge docker0 is not used
[PASS] 5.30  - Ensure the host's user namespaces is not shared
[PASS] 5.31  - Ensure the Docker socket is not mounted inside any containers
```
## Выполним запуск контейнеров при помощи исправленной версии docker-compose

```
docker-compose -f docker-compose-fix.yml up -d
```

## Повторно просканируем контейнеры

```
[INFO] 5 - Container Runtime
[WARN] 5.1  - Ensure AppArmor Profile is Enabled
[WARN]      * No AppArmorProfile Found: web
[WARN]      * No AppArmorProfile Found: db
[PASS] 5.2  - Ensure SELinux security options are set, if applicable
[PASS] 5.3  - Ensure Linux Kernel Capabilities are restricted within containers
[PASS] 5.4  - Ensure privileged containers are not used
[PASS] 5.5  - Ensure sensitive host system directories are not mounted on containers
[WARN] 5.6  - Ensure ssh is not run within containers
[WARN]      * Container running sshd: web
[PASS] 5.7  - Ensure privileged ports are not mapped within containers
[NOTE] 5.8  - Ensure only needed ports are open on the container
[PASS] 5.9  - Ensure the host's network namespace is not shared
[PASS] 5.10  - Ensure memory usage for container is limited
[PASS] 5.11  - Ensure CPU priority is set appropriately on the container
[WARN] 5.12  - Ensure the container's root filesystem is mounted as read only
[WARN]      * Container running with root FS mounted R/W: web
[WARN]      * Container running with root FS mounted R/W: db
[PASS] 5.13  - Ensure incoming container traffic is binded to a specific host interface
[PASS] 5.14  - Ensure 'on-failure' container restart policy is set to '5'
[WARN] 5.15  - Ensure the host's process namespace is not shared
[WARN]      * Host PID namespace being shared with: web
[WARN]      * Host PID namespace being shared with: db
[PASS] 5.16  - Ensure the host's IPC namespace is not shared
[PASS] 5.17  - Ensure host devices are not directly exposed to containers
[INFO] 5.18  - Ensure the default ulimit is overwritten at runtime, only if needed
[INFO]      * Container no default ulimit override: web
[INFO]      * Container no default ulimit override: db
[PASS] 5.19  - Ensure mount propagation mode is not set to shared
[PASS] 5.20  - Ensure the host's UTS namespace is not shared
[PASS] 5.21  - Ensure the default seccomp profile is not Disabled
[NOTE] 5.22  - Ensure docker exec commands are not used with privileged option
[NOTE] 5.23  - Ensure docker exec commands are not used with user option
[PASS] 5.24  - Ensure cgroup usage is confirmed
[WARN] 5.25  - Ensure the container is restricted from acquiring additional privileges
[WARN]      * Privileges not restricted: db
[PASS] 5.26  - Ensure container health is checked at runtime
[INFO] 5.27  - Ensure docker commands always get the latest version of the image
[WARN] 5.28  - Ensure PIDs cgroup limit is used
[WARN]      * PIDs limit not set: web
[WARN]      * PIDs limit not set: db
[PASS] 5.29  - Ensure Docker's default bridge docker0 is not used
[PASS] 5.30  - Ensure the host's user namespaces is not shared
[PASS] 5.31  - Ensure the Docker socket is not mounted inside any containers
```
