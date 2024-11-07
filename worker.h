#ifndef _MPROCESSMANAGER_WORKER_H
#define _MPROCESSMANAGER_WORKER_H
#include <iostream>
#include <string>
using namespace std;

class Worker
{
public:
  Worker();
	virtual ~Worker();

	void	start();
	virtual void run();
	virtual void stop();
	void	restart();

	pid_t	pid(){return m_pid;}
	bool	status(){return m_status;}
	void 	set_status(bool f){m_status=f;}
	string	type(const string & newtype="");
private:
	pid_t 	m_pid;
	bool 	m_status;
	string 	m_type;
};

#endif 
