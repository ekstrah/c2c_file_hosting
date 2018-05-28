void kill(const char *msg){
	perror(msg);
	exit(1);
}