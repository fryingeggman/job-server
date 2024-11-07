#ifndef _MPROCESSMANAGER_WORKER_CPP
#define _MPROCESSMANAGER_WORKER_CPP

#include "worker.h"
#include <unistd.h>
#include <sys/wait.h>

Worker::Worker() : m_pid(0), m_status(false), m_type("") {}
Worker::~Worker()
{
  int ret;
	if (m_status ==true){
		wait(&ret);
		m_status=false;
	}
}
void Worker::start()
{
	m_pid=fork();
	if (m_pid == 0){
		run();
		exit(0);
	}
	else if (m_pid >=0){
		m_status=true;
	}
	else {
		throw puts("fork error!");
	}
}
void Worker::run()
{
	throw puts("You must overwrite this function:run()");
}
void Worker::stop()
{
	m_status=false;
//	exit(0);
}
void Worker::restart()
{
	if (m_status == false){
		start();
	}
}
string Worker::type(const string& newtype /* ="" */)
{
	if (newtype !=""){
		m_type = newtype;
	}

	return m_type;
}

#endif
