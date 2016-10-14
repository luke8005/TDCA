#include <limits.h>
#include <unistd.h>
#include <string>

std::string getExecPath()
{
	std::string fullFileName = "";
	// Code taken from: http://www.gamedev.net/community/forums/topic.asp?topic_id=459511
	std::string path = "";
	pid_t pid = getpid();
	char buf[20] = {0};
	sprintf(buf,"%d",pid);
	std::string _link = "/proc/";
	_link.append( buf );
	_link.append( "/exe");
	char proc[512];
	int ch = readlink(_link.c_str(),proc,512);
	if (ch != -1) {
		proc[ch] = 0;
		path = proc;
		std::string::size_type t = path.find_last_of("/");
		path = path.substr(0,t);
	}
	return fullFileName = path + std::string("/");
}
