build-openuxas:
	@docker-compose -f ./openuxas/docker-compose.yml -p openuxas build openuxas

stop-openuxas:
	@docker-compose -f ./openuxas/docker-compose.yml -p openuxas stop

dangling-images-remove:
	@docker rmi --force `docker images -q -f dangling=true`

images-remove-all:
	@docker rmi --force `docker images -q -a`

containers-remove-all:
	@docker rm --force `docker ps -a -q`

volumes-remove-all:
	@docker volume rm `docker volume ls -q`

images-remove-match:
	@docker rmi --force `docker images -a | grep $(MATCH) | tr -s " " | cut -f3 -d " "`
