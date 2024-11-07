#ifndef _MASYNTABWORKER_CPP
#define _MASYNTABWORKER_CPP

#include "asyntabworker.h" 

AsyntabWorker::AsyntabWorker()
:m_send(NULL),m_billtype("")
{
}

AsyntabWorker::~AsyntabWorker()
{
}
xpipe * AsyntabWorker::get_send_pipe()
{
  return m_send;
}
void AsyntabWorker::set_send_pipe(xpipe &xpipe)
{
	m_send=&xpipe;
}

xpipe * AsyntabWorker::get_recv_pipe()
{
	return m_recv;
}
void AsyntabWorker::set_recv_pipe(xpipe &xpipe)
{
	m_recv=&xpipe;
}
string AsyntabWorker::get_billtype()
{
	return m_billtype;
}
void AsyntabWorker::set_billtype(const string &type)
{
	m_billtype=type;
}
void AsyntabWorker::run()
{
	struct REC
	{
		char billtype[32];
		long recid;
	}rec;
	while (true){
		m_send->send("OK");
		m_recv->recv(&rec,sizeof(struct REC));
		if (strcmp(rec.billtype,"END")==0){
			exit(0);
		}
		m_billtype=rec.billtype;
				
		if (m_billtype == "PAYBY"){
			cout<<"PAYBY:doing job-"<<rec.recid<<endl;
		}
		else {
			cout<<m_billtype<<":doing job-"<<rec.recid<<endl;
		}
	}
}

#endif
