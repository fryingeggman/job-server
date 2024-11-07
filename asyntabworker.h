#ifndef _MASYNTABWORKER_H
#define _MASYNTABWORKER_H

#include "xpipe.h"
#include "worker.h"
#include <string>
#include <iostream>
using namespace std;

class AsyntabWorker : public Worker
{
public:
  AsyntabWorker();
	~AsyntabWorker();
 	
	void	run();
	xpipe	*get_send_pipe();
	xpipe	*get_recv_pipe();
	void	set_send_pipe(xpipe &xpipe);
	void	set_recv_pipe(xpipe &xpipe);
	string	get_billtype();
	void	set_billtype(const string &type);
private:
	xpipe	*m_send;
	xpipe	*m_recv;
	string	m_billtype;
};
#endif
