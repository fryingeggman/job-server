#ifndef _MPROCME_JOBSERVER_H
#define _MPROCME_JOBSERVER_H

#include "xpipe.h"
#include "worker.h"
#include "processmanager.h"
#include <list>

class Jobserver:public Worker
{
public:
  Jobserver();
	~Jobserver();
	virtual void run();
	
	xpipe *get_send_pipe();
	xpipe *get_recv_pipe();
	void set_send_pipe(xpipe &send);
	void set_recv_pipe(xpipe &recv);

	void load_job();
private:
	xpipe *m_send;
	xpipe *m_recv;

	struct REC
	{
		char billtype[32];
		long recid;
	}rec;
};

#endif
