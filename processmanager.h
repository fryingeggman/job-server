#ifndef _MPROCESSMANAGER_H
#define _MPROCESSMANAGER_H

#include "worker.h"
#include <list>
#include <sys/wait.h>

class ProcessManager
{
public:
    ProcessManager();
    ~ProcessManager();


  void init_num_process(int count);
	void start();
    void adjust_proc_num();
    int  (*adjust_proc_strategy)(long jobs_count,ProcessManager &pm);

	void set_maxprocnum(int newmaxprocnum) {
		m_maxprocnum=newmaxprocnum;
	}
	int  get_maxprocnum() const {
		return m_maxprocnum;
	}
	void set_minprocnum(int newminprocnum) {
		m_minprocnum=newminprocnum;
	}
	int  get_minprocnum() const {
		return m_minprocnum;
	}
	void set_jobs_count(long count) {
		m_jobs_count=count;
	}
	long get_jobs_count() const {
		return m_jobs_count;
	}

	static Worker * get_one_proc_by_status(bool status);
	Worker * get_one_proc_by_type(const string &type);
	int  cur_procnum();
	static	list<Worker> m_workers;
private:
	int		m_maxprocnum;
	int		m_minprocnum;
	long	m_jobs_count;

	static void sig_child(int sig);
	static void sig_term(int sig);
};


#endif
