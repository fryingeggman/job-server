#ifndef _MPROCME_JOBSERVER_CPP
#define _MPROCME_JOBSERVER_CPP

#include <stdlib.h>
#include <string.h>
#include "processmanager.h"
#include "jobserver.h"
Jobserver::Jobserver()
{
}
Jobserver::~Jobserver()
{
}
xpipe * Jobserver::get_send_pipe()
{
  return m_send;
}
void Jobserver::set_send_pipe(xpipe &xpipe)
{
	m_send=&xpipe;
}

xpipe * Jobserver::get_recv_pipe()
{
	return m_recv;
}
void Jobserver::set_recv_pipe(xpipe &xpipe)
{
	m_recv=&xpipe;
}
void Jobserver::load_job()
{
	char type[4][32]={"PAYBY","XZ","HFGP","XSD"};
	static long i=0;
	srand(time(NULL));
	int r=(rand()/RAND_MAX)*4;
	strcpy(rec.billtype,type[r]);
	rec.recid=++i;
}
void Jobserver::run()
{
	ProcessManager pm;
	pm.init_num_process(2);
	pm.start();
		
	long jobscount=30;
	string is_worker_ready;
	int i=1;
	while (true){
		//collect Jobs
		jobscount=30*(i++);
		if (i>100){
			cout<<"Jobserver stop"<<endl;
			exit(0);
		}
		pm.set_jobs_count(jobscount);
		pm.adjust_proc_num();
	
		m_recv->recv(is_worker_ready);
		if (is_worker_ready=="OK"){
			//publish job
			load_job();	
			m_send->send(&rec,sizeof(struct REC));
			cout<<"Jobserver:publish job-"<<rec.billtype
				<<"-"<<rec.recid<<endl;		
		}
	}
}

#endif
